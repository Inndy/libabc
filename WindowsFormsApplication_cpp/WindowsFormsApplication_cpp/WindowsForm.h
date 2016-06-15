#pragma once
#include"DataManager.h"
#include"DotNetUtilities.h"
#include "util.hpp"
#include "matrix.hpp"
#include"vector.hpp"
#include"loadfile.hpp"

myVecD ** vector_list;
myMatD ** matrix_list;
int current_vector_count = 0;
int current_matrix_count = 0;
int load_flag;

namespace WindowsFormsApplication_cpp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// WindowsForm 的摘要
	/// </summary>
	public ref class WindowsForm : public System::Windows::Forms::Form
	{
	public:
		WindowsForm(void)
		{
			InitializeComponent();
			dataManager = new DataManager();
			lastInputLength = -1;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~WindowsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip2;
	private: System::Windows::Forms::ToolStripMenuItem^  FileToolStripMenuItem;

	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::ToolStripMenuItem^  LoadVectorToolStripMenuItem;



	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
	private: System::Windows::Forms::Label^  OutputLabel;
	private: System::Windows::Forms::TextBox^  Output;

	private: System::Windows::Forms::Label^  InputLabel;
	private: System::Windows::Forms::TextBox^  Input;
	private: System::Windows::Forms::Label^  VectorLabel;
	private: System::Windows::Forms::ListBox^  VectorList;



	protected:















	protected:

	private:
		/// <summary>
			DataManager* dataManager;
			String^ userInput;
			int lastInputLength;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  loadMatrixToolStripMenuItem;
			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LoadVectorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->InputLabel = (gcnew System::Windows::Forms::Label());
			this->Input = (gcnew System::Windows::Forms::TextBox());
			this->VectorLabel = (gcnew System::Windows::Forms::Label());
			this->VectorList = (gcnew System::Windows::Forms::ListBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->OutputLabel = (gcnew System::Windows::Forms::Label());
			this->Output = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->loadMatrixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip2->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip2
			// 
			this->menuStrip2->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->FileToolStripMenuItem });
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Padding = System::Windows::Forms::Padding(9, 3, 0, 3);
			this->menuStrip2->Size = System::Drawing::Size(576, 34);
			this->menuStrip2->TabIndex = 1;
			this->menuStrip2->Text = L"menuStrip2";
			// 
			// FileToolStripMenuItem
			// 
			this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->LoadVectorToolStripMenuItem,
					this->loadMatrixToolStripMenuItem
			});
			this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			this->FileToolStripMenuItem->Size = System::Drawing::Size(51, 28);
			this->FileToolStripMenuItem->Text = L"File";
			// 
			// LoadVectorToolStripMenuItem
			// 
			this->LoadVectorToolStripMenuItem->Name = L"LoadVectorToolStripMenuItem";
			this->LoadVectorToolStripMenuItem->Size = System::Drawing::Size(211, 30);
			this->LoadVectorToolStripMenuItem->Text = L"Load Vector";
			this->LoadVectorToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::LoadVectorToolStripMenuItem_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 34);
			this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 30)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(576, 509);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->InputLabel);
			this->flowLayoutPanel1->Controls->Add(this->Input);
			this->flowLayoutPanel1->Controls->Add(this->VectorLabel);
			this->flowLayoutPanel1->Controls->Add(this->VectorList);
			this->flowLayoutPanel1->Location = System::Drawing::Point(292, 4);
			this->flowLayoutPanel1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(279, 498);
			this->flowLayoutPanel1->TabIndex = 0;
			// 
			// InputLabel
			// 
			this->InputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->InputLabel->AutoSize = true;
			this->InputLabel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->InputLabel->Location = System::Drawing::Point(4, 0);
			this->InputLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->InputLabel->Name = L"InputLabel";
			this->InputLabel->Size = System::Drawing::Size(57, 23);
			this->InputLabel->TabIndex = 0;
			this->InputLabel->Text = L"Input";
			// 
			// Input
			// 
			this->Input->Location = System::Drawing::Point(4, 27);
			this->Input->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Input->Multiline = true;
			this->Input->Name = L"Input";
			this->Input->Size = System::Drawing::Size(268, 235);
			this->Input->TabIndex = 1;
			this->Input->TextChanged += gcnew System::EventHandler(this, &WindowsForm::Input_TextChanged);
			// 
			// VectorLabel
			// 
			this->VectorLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->VectorLabel->AutoSize = true;
			this->VectorLabel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->VectorLabel->Location = System::Drawing::Point(4, 266);
			this->VectorLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->VectorLabel->Name = L"VectorLabel";
			this->VectorLabel->Size = System::Drawing::Size(67, 23);
			this->VectorLabel->TabIndex = 2;
			this->VectorLabel->Text = L"Vector";
			// 
			// VectorList
			// 
			this->VectorList->FormattingEnabled = true;
			this->VectorList->ItemHeight = 18;
			this->VectorList->Location = System::Drawing::Point(4, 293);
			this->VectorList->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->VectorList->Name = L"VectorList";
			this->VectorList->Size = System::Drawing::Size(268, 184);
			this->VectorList->TabIndex = 3;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->OutputLabel);
			this->flowLayoutPanel2->Controls->Add(this->Output);
			this->flowLayoutPanel2->Location = System::Drawing::Point(4, 4);
			this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(279, 498);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// OutputLabel
			// 
			this->OutputLabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->OutputLabel->AutoSize = true;
			this->OutputLabel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(136)));
			this->OutputLabel->Location = System::Drawing::Point(4, 0);
			this->OutputLabel->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->OutputLabel->Name = L"OutputLabel";
			this->OutputLabel->Size = System::Drawing::Size(73, 23);
			this->OutputLabel->TabIndex = 0;
			this->OutputLabel->Text = L"Output";
			// 
			// Output
			// 
			this->Output->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Output->Location = System::Drawing::Point(4, 27);
			this->Output->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Output->Multiline = true;
			this->Output->Name = L"Output";
			this->Output->ReadOnly = true;
			this->Output->Size = System::Drawing::Size(272, 468);
			this->Output->TabIndex = 1;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &WindowsForm::openFileDialog1_FileOk);
			// 
			// loadMatrixToolStripMenuItem
			// 
			this->loadMatrixToolStripMenuItem->Name = L"loadMatrixToolStripMenuItem";
			this->loadMatrixToolStripMenuItem->Size = System::Drawing::Size(211, 30);
			this->loadMatrixToolStripMenuItem->Text = L"Load Matrix";
			this->loadMatrixToolStripMenuItem->Click += gcnew System::EventHandler(this, &WindowsForm::loadMatrixToolStripMenuItem_Click);
			// 
			// WindowsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(576, 543);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->menuStrip2);
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"WindowsForm";
			this->Text = L"VectorExample";
			this->Load += gcnew System::EventHandler(this, &WindowsForm::WindowsForm_Load);
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void WindowsForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void LoadVectorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	//set load_flag to zero, which will be used to judge whether we want to load vector or matrix 
	load_flag = 0;
	//開啟Dialog
	openFileDialog1->ShowDialog();
}
private: System::Void Input_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	//當Input textbox中的輸入改變時，便會進入此函式
	//取得向量資料
	std::vector<Vector> vectors = dataManager->GetVectors();
	//判斷輸入自元為'\n'，並防止取到字串-1位置
	if (Input->Text->Length-1 >= 0 &&Input->Text[Input->Text->Length - 1] == '\n')
	{
		//將使用者輸入字串(在userInput中)，依空白作切割
		array<String^> ^userCommand = userInput->Split(' ');
		//字串比較，若指令為"print"的情況
		if (userCommand[0] == "print")
		{
			//定意輸出暫存
			String^ outputTemp = "";
			//透過for迴圈，從向量資料中找出對應變數
			if (userCommand[1] == "vector") {
				int temp = Convert::ToInt32(userCommand[2]);
				if (temp < current_vector_count&&temp>=0) {
					Output->Text += gcnew String(vector_list[temp]->str().c_str());
					Output->Text += Environment::NewLine;
				}
				else Output->Text += gcnew String("command handle: print: vector: invalid index of vector") + Environment::NewLine;
			}
			else if (userCommand[1] == "matrix") {
				int temp = Convert::ToInt32(userCommand[2]);
				if (temp < current_matrix_count&&temp >= 0) {
					Output->Text += gcnew String(matrix_list[temp]->str().c_str());
					Output->Text += Environment::NewLine;
				}
				else Output->Text += gcnew String("command handle: print: vector: invalid index of matrix") + Environment::NewLine;
			}
		}
		else if (userCommand[0] == "add") {
			//if it's a matrix addition
			if (userCommand[1] == "matrix" && userCommand[3] == "matrix") {
				int indexa = Convert::ToInt32(userCommand[2]); int indexb = Convert::ToInt32(userCommand[4]);
				if (indexa >= 0 && indexa < current_matrix_count && indexb >= 0 && indexb < current_matrix_count) {
					myMatD * temp = new myMatD(matrix_list[indexa]->h, matrix_list[indexa]->w);
					temp->copy_from(matrix_list[indexa]);
					temp->add(*matrix_list[indexb]);
					Output->Text += gcnew String(temp->str().c_str());
					Output->Text += Environment::NewLine;
					delete temp;
				}
				else Output->Text += gcnew String("command handle: add: matrix addition: invalid index input") + Environment::NewLine;
			}
			//if it's a vector addition
			else if (userCommand[1] == "vector" && userCommand[3] == "vector") {
				int indexa = Convert::ToInt32(userCommand[2]); int indexb = Convert::ToInt32(userCommand[4]);
				if (indexa >= 0 && indexa < current_vector_count&& indexb >= 0 && indexb < current_vector_count) {
					myVecD * temp = vector_list[indexa]->copy();
					temp->add(vector_list[indexb]);
					Output->Text += gcnew String(temp->str().c_str());
					Output->Text += Environment::NewLine;
					delete temp;
				}
				else Output->Text += gcnew String("command handle: add: vector addition: invalid index input") + Environment::NewLine;
			}
		}
		else if (userCommand[0] == "sub") {
			if (userCommand[1] == "matrix" && userCommand[3] == "matrix") {
				int indexa = Convert::ToInt32(userCommand[2]); int indexb = Convert::ToInt32(userCommand[4]);
				if (indexa >= 0 && indexa < current_matrix_count && indexb >= 0 && indexb < current_matrix_count) {
					myMatD * temp = new myMatD(matrix_list[indexa]->h, matrix_list[indexa]->w);
					temp->copy_from(matrix_list[indexa]);
					temp->sub(*matrix_list[indexb]);
					Output->Text += gcnew String(temp->str().c_str());
					Output->Text += Environment::NewLine;
					delete temp;
				}
				else Output->Text += gcnew String("command handle: add: matrix substraction: invalid index input") + Environment::NewLine;
			}
			//if it's a vector addition
			else if (userCommand[1] == "vector" && userCommand[3] == "vector") {
				int indexa = Convert::ToInt32(userCommand[2]); int indexb = Convert::ToInt32(userCommand[4]);
				if (indexa >= 0 && indexa < current_vector_count&& indexb >= 0 && indexb < current_vector_count) {
					myVecD * temp = vector_list[indexa]->copy();
					temp->sub(vector_list[indexb]);
					Output->Text += gcnew String(temp->str().c_str());
					Output->Text += Environment::NewLine;
					delete temp;
				}
				else Output->Text += gcnew String("command handle: add: vector substraction: invalid index input") + Environment::NewLine;
			}
		}
		else if (userCommand[0] == "idx") {
			Output->Text += gcnew String("Avaliable vector index") + current_vector_count +Environment::NewLine;
			Output->Text += gcnew String("Avaliable matrix index") + current_matrix_count + Environment::NewLine;
		}
		else if (userCommand[0] == "clr") {
			Input->Text = "";
			Output->Text = "";
		}
		else if (userCommand[0] == "dot") {
			int indexa = Convert::ToInt32(userCommand[1]); int indexb = Convert::ToInt32(userCommand[2]);
			if (indexa >= 0 && indexa < current_vector_count&&indexb >= 0 && indexb < current_vector_count) {
				Output->Text += myVecD::dot(vector_list[indexa], vector_list[indexb]) + Environment::NewLine;
			}else Output->Text += gcnew String("command handle: dot: invalid index input") + Environment::NewLine;
		}
		else if (userCommand[0] == "mul") {
			if (userCommand[1] == "matrix" && userCommand[3] == "scalar") {
				int indexa = Convert::ToInt32(userCommand[2]);
				double scalar = Convert::ToDouble(userCommand[4]);
				if (indexa < current_matrix_count&& indexa >= 0) {
					myMatD * mat = new myMatD(matrix_list[indexa]->h, matrix_list[indexa]->w);
					mat->copy_from(matrix_list[indexa]);
					mat->mul(scalar);
					Output->Text += gcnew String(mat->str().c_str()) + Environment::NewLine;
					delete mat;
				}
				else Output->Text += gcnew String("command handle: mul: matrix scalar multiplication: invalid index input") + Environment::NewLine;
			}
		}
		else if (userCommand[0] == "cmd") {
			Output->Text += gcnew String("print vector/matrix int(vectoridx/matrixidx)\r\n    print vector/matrix with index");
			Output->Text += Environment::NewLine;
			Output->Text += gcnew String("clr\r\n    clean Input and Output box");
			Output->Text += Environment::NewLine;
			Output->Text += gcnew String("add matrix/vector int(indexa) matrix/vector int(indexb)");
			Output->Text += Environment::NewLine;
			//sub
			//idx
		}
		//反之則判斷找不到指令
		else
		{
			Output->Text += "-Command not found-" + Environment::NewLine;
		}
		userInput = "";
	}
	else
	{
		//將使用者輸入字串(在Text box中)，依'\n'作切割
		array<String^> ^userCommand = Input->Text->Split('\n');
		//並將最後一行，作為目前使用者輸入指令
		userInput = userCommand[userCommand->Length-1];
	}

}
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) 
{
	//click load vector will set load_flag to zero
	//the following code block after if statement is used to laod vectors

	//在Dialog按下OK便會進入此函式
	//字串轉制string^ to string
	std::string tempFileName;
	MarshalString(openFileDialog1->FileName, tempFileName);

	if (!load_flag) {

		//=====================================================
			//use my own load file class to load vector
			/*--------initialization-----------------*/
			//if current vector list is not empty, we should clean it before use
		if (!current_vector_count) {
			for (int index = 0; index < current_vector_count; index++)
				delete vector_list[index];
			delete[] vector_list;
		}
		current_vector_count = 0;
		LoadFile * lf = new LoadFile(tempFileName.c_str());
		//load information to vector list
		vector_list = lf->load_vector(current_vector_count);
		//print out for test;
		if(0)
			for (int index = 0; index < current_vector_count; index++) {
				std::string mytemp = vector_list[index]->str();
				cout << "mytemp" << mytemp << endl;
			}
		//delete object
		delete lf;
		//=====================================================


			//將檔案路徑名稱傳入dataManager
		dataManager->SetFileName(tempFileName);
		//從讀取讀取向量資料
		if (dataManager->LoadVectorData())
		{
			//將VectorList中項目先做清除
			VectorList->Items->Clear();
			//取得所有向量資料
			std::vector<Vector> vectors = dataManager->GetVectors();

			for (unsigned int i = 0; i < vectors.size(); i++)
			{
				//將檔案名稱存入暫存
				std::string tempString = vectors[i].Name;
				//將輸出格式存入暫存
				tempString += " [";
				//將輸出資料存入暫存
				for (unsigned int j = 0; j < vectors[i].Data.size(); j++)
				{
					std::string scalarString = std::to_string(vectors[i].Data[j]);
					tempString += scalarString.substr(0, scalarString.size() - 5);
					if (j != vectors[i].Data.size() - 1)
						tempString += ",";
				}
				//將輸出格式存入暫存
				tempString += "]";
				//將項目加入VectorList中
				VectorList->Items->Add(gcnew String(tempString.c_str()));
			}
			Output->Text += "-Vector datas have been loaded-" + Environment::NewLine;
		}
	}
	if (load_flag == 1) {
		cout << "load matrix" << endl;
		if (!current_matrix_count) {
			for (int index = 0; index < current_matrix_count; index++) 
				delete matrix_list[index];
			delete[] matrix_list;
		}
		current_matrix_count = 0;
		LoadFile * lf = new LoadFile(tempFileName.c_str());
		matrix_list = lf->load_matrix(current_matrix_count);
		delete lf;
		if (1) {
			for (int index = 0; index < current_matrix_count; index++)
				cout << matrix_list[index]->str() << index++;
		}
	}
}
private: System::Void loadMatrixToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	//set load_flag to zero, which will be used to judge whether we want to load vector or matrix 
	load_flag = 1;
	//開啟Dialog
	openFileDialog1->ShowDialog();
}
};
}
