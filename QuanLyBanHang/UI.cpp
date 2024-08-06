#include "UI.h"
#include "DonHang.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <typeinfo>
#include "HangHoa.h"

using namespace std;

UI::UI()
{}

UI::~UI()
{}

//Ham hien thi man hinh trang chu
void UI::renderWelcomeScreen()
{
	getDefaultAttribute(); //Lay thong tin bo nho dem cua cua so console de dung cac ham cua tools
	ifstream iFileOpen;
	iFileOpen.open("GiaoDien.txt", ios::in);
	if (iFileOpen.is_open())
	{
		textColor(14); //doi mau chu
		string strFileLine;
		while (getline(iFileOpen, strFileLine))  //Hien thi dong chu Ban Hang Online HCMUE tu file GiaoDien.txt
		{
			cout << strFileLine << endl;
		}
	}
	cout << endl;

	string strWelcome = "Welcome back. We're very glad to see you again !!!";
	alignTextPositionWidth(strWelcome, 2); // Can giua dong chu strWelcom
	for (size_t i = 0; i < strWelcome.length(); i++)
	{
		if (strWelcome[i] == ' ')
		{
			textColor(getRandNum()); //Lay mau random cho dong chu
		}
		cout << strWelcome[i];
	}
	cout << endl;
	textColor(11);
		UI::renderMenuScreen();
	return;
}

//Ham hien thi man hinh dang nhap
void UI::renderLoginScreen()
{
	system("cls");
	getDefaultAttribute();
	ifstream iFileOpen;
	iFileOpen.open("Login.txt", ios::in);
	alignTextPositionHeight(20);
	textColor(14);
	if (iFileOpen.is_open())
	{
		textColor(14);
		string strFileLine;
		while (getline(iFileOpen, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
	}
	cout << endl;
	Admin admin;
	if (admin.login())
		admin.renderMenuAdmin();
}

//Ham hien thi man hinh ket thuc
void UI::renderGoodByeScreen()
{
	system("cls");
	getDefaultAttribute();
	ifstream ifAsciiTextArt;
	ifAsciiTextArt.open("GoodBye.txt", ios::in);
	alignTextPositionHeight(2.8);
	if (ifAsciiTextArt.is_open())
	{
		string strFileLine;
		textColor(14);
		while (getline(ifAsciiTextArt, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
		ifAsciiTextArt.close();
	}
	cout << flush;
	this_thread::sleep_for(chrono::milliseconds(1500));
	system("cls");
	ifAsciiTextArt.open("ThanksFor.txt", ios::in);
	alignTextPositionHeight(2.8);
	if (ifAsciiTextArt.is_open())
	{
		string strFileLine;
		textColor(14);
		while (getline(ifAsciiTextArt, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
		ifAsciiTextArt.close();
	}
	cout << flush;
	this_thread::sleep_for(chrono::milliseconds(1500));
	system("cls");
	ifAsciiTextArt.open("UsingOurServices.txt", ios::in);
	alignTextPositionHeight(2.8);
	if (ifAsciiTextArt.is_open())
	{
		string strFileLine;
		textColor(14);
		while (getline(ifAsciiTextArt, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
		ifAsciiTextArt.close();
	}
	resetColor();
	this_thread::sleep_for(chrono::milliseconds(1500));
}

//Ham hien thi Menu trang chu
void UI::renderMenuScreen() {
	getDefaultAttribute();
	ifstream iFileOpen;
	iFileOpen.open("Menu.txt", ios::in);
	alignTextPositionHeight(20);
	textColor(14);
	if (iFileOpen.is_open())
	{
		textColor(14);
		string strFileLine;
		while (getline(iFileOpen, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
	}
	cout << endl;
	int iChoice;
	cout << "Enter your choice: ";
	cin >> iChoice;
	cin.ignore();
	if (iChoice == 5)
		UI::renderGoodByeScreen();
	else if (iChoice == 4)
		UI::renderLoginScreen();
	else if (iChoice == 3)
		UI::renderDatHang();
	else if (iChoice == 2)
		UI::renderTimKiem();
	else if (iChoice == 1)
		UI::renderDSHangHoa();
}

//Ham hien thi man hinh chuc nang dat hang
void UI::renderDatHang() 
{
	system("cls");
	getDefaultAttribute();
	ifstream iFileOpen;
	iFileOpen.open("DatHang.txt", ios::in);
	alignTextPositionHeight(20);
	textColor(14);
	if (iFileOpen.is_open())
	{
		textColor(14);
		string strFileLine;
		while (getline(iFileOpen, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
	}
	cout << endl;
	DonHang a;
	a.NhapThongTinDonHang();
	string choice;
	while(true){
		cout << "Ban muon dat hang tiep hong ne: \n" ;
		cout << "Neu muon thi go yes khong la no: ";
		cin >> choice ;
		if ( choice == "yes" ) {
			Order::orderNumber--;
			a.NhapThongTinDonHang();
		}
		else break;
	}
	a.LuuDonHang();
	int iChoice;
	cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << endl;
	cout << "Choise: ";
	cin >> iChoice;
	if (iChoice == 1)
	{
		system("cls");
		UI::renderWelcomeScreen();
	}
	else if (iChoice == 0)
		UI::renderGoodByeScreen();
}

//Ham hien thi man hinh chuc nang tim kiem
void UI::renderTimKiem() 
{
	system("cls");
	getDefaultAttribute();
	ifstream iFileOpen;
	iFileOpen.open("TimKiemHangHoa.txt", ios::in);
	alignTextPositionHeight(20);
	textColor(14);
	if (iFileOpen.is_open())
	{
		textColor(14);
		string strFileLine;
		while (getline(iFileOpen, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
	}
	cout << endl;
	string strTenHangHoa;
	cout << "Nhap Ten Hang Hoa Can Tim Kiem: ";
	getline(cin, strTenHangHoa);
	cout << endl;
	HangHoa hanghoa;
	hanghoa.timkiemhanghoa(strTenHangHoa);
	cout << endl;
	int iChoice;
	cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << endl;
	cout << "Choise: ";
	cin >> iChoice;
	if (iChoice == 1)
	{
		system("cls");
		UI::renderWelcomeScreen();
	}
	else if (iChoice == 0)
		UI::renderGoodByeScreen();
}

//Ham hien thi man hinh chuc nang xem danh sach hang hoa
void UI::renderDSHangHoa() 
{
	system("cls");
	getDefaultAttribute();
	ifstream iFileOpen;
	iFileOpen.open("DSHangHoa.txt", ios::in);
	alignTextPositionHeight(20);
	textColor(14);
	if (iFileOpen.is_open())
	{
		textColor(14);
		string strFileLine;
		while (getline(iFileOpen, strFileLine))
		{
			alignTextPositionWidth(strFileLine, 2);
			cout << strFileLine << endl;
		}
	}
	cout << endl;
	HangHoa hanghoa;
	hanghoa.inhanghoasaukhisapxep();
	int iChoice;
	cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << endl;
	cout << "Choise: ";
	cin >> iChoice;
	if (iChoice == 1)
	{
		system("cls");
		UI::renderWelcomeScreen();
	}
	else if (iChoice == 0)
		UI::renderGoodByeScreen();
}