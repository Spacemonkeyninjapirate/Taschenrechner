#pragma once
#include <stdexcept>
_declspec(dllimport) float _cdecl taschenrechner(char *&rest, int level);

namespace gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::TextBox^  ausgabe;
    private: System::Windows::Forms::TextBox^  eingabe;
    private: System::Windows::Forms::Button^  button;
    protected: 

    protected: 


    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
            this->ausgabe = (gcnew System::Windows::Forms::TextBox());
            this->eingabe = (gcnew System::Windows::Forms::TextBox());
            this->button = (gcnew System::Windows::Forms::Button());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // ausgabe
            // 
            this->ausgabe->Location = System::Drawing::Point(13, 67);
            this->ausgabe->Name = L"ausgabe";
            this->ausgabe->Size = System::Drawing::Size(259, 20);
            this->ausgabe->TabIndex = 0;
            // 
            // eingabe
            // 
            this->eingabe->Location = System::Drawing::Point(13, 156);
            this->eingabe->Name = L"eingabe";
            this->eingabe->Size = System::Drawing::Size(260, 20);
            this->eingabe->TabIndex = 1;
            // 
            // button
            // 
            this->button->Location = System::Drawing::Point(82, 227);
            this->button->Name = L"button";
            this->button->Size = System::Drawing::Size(75, 23);
            this->button->TabIndex = 2;
            this->button->Text = L"berechnen";
            this->button->UseVisualStyleBackColor = true;
            this->button->Click += gcnew System::EventHandler(this, &Form1::button_Click);
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(13, 48);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(49, 13);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Ausgabe";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(16, 137);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(46, 13);
            this->label2->TabIndex = 4;
            this->label2->Text = L"Eingabe";
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(284, 262);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->button);
            this->Controls->Add(this->eingabe);
            this->Controls->Add(this->ausgabe);
            this->Name = L"Form1";
            this->Text = L"Form1";
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void button_Click(System::Object^  sender, System::EventArgs^  e) {
                 String ^v_eingabe = eingabe->Text; 
                 IntPtr ptr_eingabe = Marshal::StringToHGlobalAnsi(v_eingabe);
                 const char* c_eingabe = static_cast<const char*>(ptr_eingabe.ToPointer());
                 char *rest = const_cast<char*>(c_eingabe);
                 try
                 {
                 float ergebnis = taschenrechner(rest, 0);
                 ausgabe->Text = Convert::ToString(ergebnis);
                 }
                 catch (std::runtime_error &e)
                 {
                     ausgabe->Text = gcnew String(e.what());
                 }
                 
                 Marshal::FreeHGlobal(ptr_eingabe);
             }
};
}

