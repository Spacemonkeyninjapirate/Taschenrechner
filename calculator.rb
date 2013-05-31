#!/usr/bin/env ruby

# more readable
class NilClass
    def type
        nil
    end

    def data
        nil
    end
end

class Hash
    def type
        keys[0]
    end

    def data
        values[0]
    end
end

class String
    def replace_with_next
        replace_with_substring 1..-1
    end

    def replace_with_substring range
        self.replace self[range]
    end
end

$tokens = []
$level = -1

def tokens
    $tokens[$level]
end

def last_token
    tokens.last
end

def first_token
    tokens.first
end

def each_token
    each_token_with_index do |token, index|
        yield token
    end
end

def each_token_with_index
    begin
        size = tokens.size

        (0...tokens.size).each do |i|
            yield tokens[i], i

            raise unless tokens.size.eql? size
        end
    rescue
        retry
    end
end

def calculate input, level = 0
    $level += 1
    $tokens[$level] = []

    until input.empty?
        # use input.replace instead of
        # input = to also modify parents inputs
        case input
        # match numbers
        when /^\d/
            raise if last_token.type.eql? :number

            tokens << { number: input.to_f }

            length = (input[/^\d+\./] ? input.to_f : input.to_i).to_s.size

            input.replace_with_substring length..-1
        # match basic operators
        when /^(\+|-|\/|\*|\^)/
            raise if last_token.type.eql? :operator

            tokens << { operator: input[0] }

            input.replace_with_next
        # match subterm, call recursively
        when /^\(/
            raise if last_token.type.eql? :number

            input.replace_with_next

            tokens << { number: calculate(input, level + 1) }
        # match end of subterm, return
        when /^\)/
            raise if level.eql? 0

            input.replace_with_next

            level -= 1 if level.eql? 1 and input.empty?

            break
        when /^sqrt/
            raise if last_token.type.eql? :number or last_token.data.eql? "v"

            tokens << { operator: "v" }

            input.replace_with_substring "sqrt".size..-1
        else
            input.replace_with_next
        end
    end

    # test for invalid input
    raise if input.empty? and level > 0
    raise if last_token.type.eql? :operator or first_token.type.eql? :operator and not first_token.data.eql? "v"

    # do powers and roots first
    each_token_with_index do |token, index|
        if token.type.eql? :operator 
            if token.data.eql? "v"
                tokens[index] = { number: Math.sqrt(tokens[index + 1].data) }

                tokens.delete_at index + 1
            elsif token.data.eql? "^"
                tokens[index] = { number: tokens[index - 1].data ** tokens[index + 1].data }

                tokens.delete_at index + 1
                tokens.delete_at index - 1
            end
        end
    end

    # then do multiplication and division
    each_token_with_index do |token, index|
        if token.type.eql? :operator and token.data[/\*|\//]
            if token.data.eql? "*"
                tokens[index] = { number: tokens[index - 1].data * tokens[index + 1].data }
            else
                tokens[index] = { number: tokens[index - 1].data / tokens[index + 1].data }
            end

            tokens.delete_at index + 1
            tokens.delete_at index - 1
        end
    end

    result = 0.0
    operation = "="
    
    # do addition and subtraction last
    # also does assignment which only happens once per term
    each_token do |token|
        if token.type.eql? :number
            case operation
            when "="
                result = token.data
            when "-"
                result -= token.data
            when "+"
                result += token.data
            end
        else
            operation = token.data
        end
    end

    $level -= 1

    result
end

# read from standard input or use default term
if ARGV.empty?
    input = "23.4 * 49 / (2.1 ^ 3.5) - 0.23 + sqrt(9)"    
else
    input = ARGV.join
end

puts calculate input
