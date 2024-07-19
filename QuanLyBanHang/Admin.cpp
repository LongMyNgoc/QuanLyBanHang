#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <iomanip>
#include <ctime>
#include <conio.h>
#include <thread>
#include <chrono>
#include "Admin.h"
#include "tools.h"
#include "UI.h"

Admin::Admin(std::string strID, std::string strPassword) 
{}

Admin::Admin(const Admin& admin)
{}

//H�m nhap mat khau m� h�a bang k� tu *
Admin::~Admin() {}
std::string Admin::getPassword() {
    std::string password;
    char ch;

    std::cout << "Enter password (Enter ESC to Exit): ";
    while ((ch = _getch()) != '\r') { // '\r' l� k� tu ket th�c (Enter)
        if (ch == 8) { // Xu l� k� tu Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; // X�a k� tu cuoi c�ng tr�n m�n h�nh
            }
        }
        else {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    std::cin.clear();
    return password;
}

//H�m dang nhap admin
bool Admin::login()
{
    UI ui;
    bool bCheck = false;
    std::ifstream ifAdminFile;
    ifAdminFile.open("admin.txt", std::ios::in); //Lay th�ng tin tu file Admin.txt
    int iCount = 0;
    while (iCount < 3)
    {
        std::string strID;
        std::cout << "Enter ID: ";
        getline(std::cin, strID);
        std::string strPassword = getPassword();
        if (strPassword == "ESC") //Neu nhap ESC se tro ve trang chu
        {
            system("cls");
            ui.renderWelcomeScreen();
        }
        if (ifAdminFile.is_open()) //Kiem tra th�ng tin nhap c� d�ng hay kh�ng tu file Admin.txt
        {
            std::string strFileLine;
            while (std::getline(ifAdminFile, strFileLine))
            {
                std::stringstream ss(strFileLine);
                std::string strfileID;
                std::string strfilePassword;
                ss >> strfileID;
                ss >> strfilePassword;
                if (strfileID == strID && strfilePassword == strPassword)
                {
                    bCheck = true;
                }
            }
        }
        if (bCheck) //dang nhap th�nh c�ng tra ve gia tri true
        {
            std::cout << "login successfully" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return true;
        }
        else
        {
            std::cout << "ID or password incorrect" << std::endl; //Neu nhap sai so lan se tang l�n 1. du 3 lan se quay ve lai trang chu
            iCount++;
        }
    }
    if(bCheck == false) //Neu nhap sai 3 lan se quay tro ve trang chu
    std::cout << "login falied" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); //Dung m�n h�nh 1 khoang thoi gian
    system("cls");
    ui.renderWelcomeScreen();
    return false;
}

//H�m hien thi m�n h�nh chuc nang xu l� don h�ng
void Admin::renderXuLyDonHang()
{
    UI ui;
    system("cls");                                      //
    getDefaultAttribute();                              //
    std::ifstream iFileOpen;                            //
    iFileOpen.open("XuLyDonHang.txt", std::ios::in);    //
    alignTextPositionHeight(20);                        //
    textColor(14);                                      //
    if (iFileOpen.is_open())                            // Hien thi m�n h�nh chuc nang xu l� don hang tu file XyLyDonHang.txt
    {                                                   //
        textColor(14);                                  //
        std::string strFileLine;                        //
        while (getline(iFileOpen, strFileLine))         //
        {                                               //
            alignTextPositionWidth(strFileLine, 2);     //
            std::cout << strFileLine << std::endl;      //
        }                                               //
    }
    std::cout << std::endl;
    int iChoice;
    std::cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << std::endl;
    std::cout << "Choise: ";
    std::cin >> iChoice;
    if (iChoice == 1)
    {
        system("cls");
        Admin::renderMenuAdmin();
    }
    else if (iChoice == 0)
        ui.renderGoodByeScreen();
}

//H�m hien thi chuc nang quan l� h�ng h�a
void Admin::renderQuanLyHangHoa()
{
    UI ui;                                                  //
    system("cls");                                          //
    getDefaultAttribute();                                  //
    std::ifstream iFileOpen;                                //
    iFileOpen.open("QuanLyHangHoa.txt", std::ios::in);      //
    alignTextPositionHeight(20);                            //
    textColor(14);                                          //
    if (iFileOpen.is_open())                                // Hien thi m�n h�nh chuc nang Quan l� h�ng h�a tu file QuanLyHangHoa.txt
    {                                                       //
        textColor(14);                                      //
        std::string strFileLine;                            //
        while (getline(iFileOpen, strFileLine))             //
        {                                                   //
            alignTextPositionWidth(strFileLine, 2);         //
            std::cout << strFileLine << std::endl;          //
        }                                                   //
    }                                                       //
    std::cout << std::endl;
    int iChoice;
    std::cout << "Do you want go back to main menu ? press 1 for yes, 0 for no" << std::endl;
    std::cout << "Choise: ";
    std::cin >> iChoice;
    if (iChoice == 1)
    {
        system("cls");
        Admin::renderMenuAdmin();
    }
    else if (iChoice == 0)
        ui.renderGoodByeScreen();
}

//H�m hien thi m�n h�nh menu admin
void Admin::renderMenuAdmin()
{
    UI ui;                                           //
    system("cls");                                   //
    getDefaultAttribute();                           //
    std::ifstream iFileOpen;                         //
    iFileOpen.open("Menu_Admin.txt", std::ios::in);  //
    alignTextPositionHeight(20);                     //
    textColor(14);                                   //
    if (iFileOpen.is_open())                         // Hien thi m�n h�nh menu admin tu file Menu_Admin.txt
    {                                                //
        textColor(14);                               //
        std::string strFileLine;                     //
        while (getline(iFileOpen, strFileLine))      //
        {                                            //
            alignTextPositionWidth(strFileLine, 2);  //
            std::cout << strFileLine << std::endl;   //
        }                                            //
    }                                                //
    std::cout << std::endl;
    int iChoice;
    std::cout << "Enter your choice: ";
    std::cin >> iChoice;
    std::cin.ignore();
    if (iChoice == 4)
    {
        system("cls");
        ui.renderWelcomeScreen();
    }
    else
        if (iChoice == 3)
            ui.renderGoodByeScreen();
        else
            if (iChoice == 2)
                Admin::renderQuanLyHangHoa();
            else
                if (iChoice == 1)
                    Admin::renderXuLyDonHang();
}