#include "HangHoa.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>
#include <iomanip>
Stack<string> HangHoa::_deletedIDs;

int HangHoa::soHangHoa() {
    ifstream file("DanhSachHangHoa.txt");
    string line;
    int cnt = 0;
    while (getline(file, line)) {
        ++cnt;
    }
    file.close();
    return cnt;
}


void HangHoa::taoHangHoa(string name, string origin, string color, int price, string entryDate, int amount) {
    ofstream file("DanhSachHangHoa.txt", ios::app); 
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string id;
    int soHangHoa = HangHoa::soHangHoa();

    if(!_deletedIDs.isEmpty()){
        id = _deletedIDs.pop();
    } else{
        id = to_string(soHangHoa + 1);
        while(id.length() < 4){ 
            id = '0' + id;
        }
    }
    file << id << " " << name << " " << origin << " " << color << " "
         << price << " " << entryDate << " " << amount << endl;
    file.close();
}


void HangHoa::xoaHangHoa(string ma) {
    ifstream inputFile("DanhSachHangHoa.txt");
    ofstream tempFile("TempDanhSachHangHoa.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        if (id != ma) {
            tempFile << line << endl;
        } else {
            found = true;
            _deletedIDs.push(id);
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        remove("DanhSachHangHoa.txt");
        rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
        cout << "Xoa Hang Hoa Thanh Cong" << endl;
    } else {
        remove("TempDanhSachHangHoa.txt");
        cout << "Khong Tim Thay Hang Hoa" << endl;
    }
}


void HangHoa::capNhatSoLuong(string ma, int soluong) {
    if (soluong <= 0) {
        cout << "So luong phai lon hon 0" << endl;
        return;
    }

    ifstream inputFile("DanhSachHangHoa.txt");
    ofstream tempFile("TempDanhSachHangHoa.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string id;
        iss >> id;
        if (id == ma) {
            string name, origin, color, entryDate;
            int price, amount;
            iss >> name >> origin >> color >> price >> entryDate >> amount;
            // Update so luong
            amount = soluong;
            tempFile << id << " " << name << " " << origin << " " << color << " " << price << " " << entryDate << " " << amount << endl;
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        remove("DanhSachHangHoa.txt");
        rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
        cout << "Cap nhat so luong thanh cong" << endl;
    } else {
        remove("TempDanhSachHangHoa.txt");
        cout << "Ma hang hoa khong co trong danh sach hang hoa" << endl;
    }
}

void HangHoa::timkiemhanghoa() {
        ifstream inputdata("DanhSachHangHoa.txt");
        ifstream input("TimKiemHangHoa.txt");
        ofstream output("TimKiemHangHoa.txt");
        string ten;
        input >> ten;
    bool khongtontai = true;
    for (int i = 0; i < soHangHoa(); i++) {
        string id, name, origin, color, entryDate;
        int price , amount;
        inputdata >> id >> name >> origin >> color >> price >> entryDate >> amount;
        if (name == ten) {
            int dorongcuama = 10;
            int dorongcuaten = 20;
            int dorongcuaorigin = 20;
            int dorongcuacolor = 10;
            int dorongcuaentrydate = 15;
            int dorongcuagia = 15;
            int dorongcuaamount = 25;
            output << std::left << std::setw(dorongcuama) << "Ma"
                << std::left << std::setw(dorongcuaten) << "Name"
                << std::left << std::setw(dorongcuaorigin) << "Origin"
                << std::left << std::setw(dorongcuacolor) << "Color"
                << std::left << std::setw(dorongcuagia) << "Price"
                << std::left << std::setw(dorongcuaentrydate) << "EntryDate"
                << std::left << std::setw(dorongcuaamount) << "Amount"
                << std::endl;

            output << std::setfill('-') << std::setw(dorongcuama) << ""
                << std::setw(dorongcuaten) << ""
                << std::setw(dorongcuaorigin) << ""
                << std::setw(dorongcuacolor) << ""
                << std::setw(dorongcuagia) << ""
                << std::setw(dorongcuaentrydate) << ""
                << std::setw(dorongcuaamount) << ""
                << std::setfill(' ') << std::endl;

            output << std::left << std::setw(dorongcuama) << id
                << std::left << std::setw(dorongcuaten) << name
                << std::left << std::setw(dorongcuaorigin) << origin
                << std::left << std::setw(dorongcuacolor) << color
                << std::left << std::setw(dorongcuagia) << price
                << std::left << std::setw(dorongcuaentrydate) << entryDate
                << std::left << std::setw(dorongcuaamount) << amount
                << std::endl;
            bool khongtontai = false;
            break;
        }
    }
    if (khongtontai) output << "khong tim thay hang hoa";
    inputdata.close();
    input.close();
    output.close();
}

void HangHoa::inhanghoasaukhisapxep() {
    ifstream input("DanhSachHangHoa.txt");
    ofstream output("DSHangHoa.txt");

    if (!input.is_open() || !output.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    int soLuong = soHangHoa();
    if (soLuong == 0) {
        output << "Khong co hang hoa nao de sap xep" << endl;
        input.close();
        output.close();
        return;
    }

    struct product{
        string id, name, origin, color, entryDate;
        int price , amount;
    };
    product* products = new product[soHangHoa()];
    int soLuong = soHangHoa();

    for (int i = 0; i < soLuong ; ++i) {
        input >> products[i].id >> products[i].name >> products[i].origin >> products[i].color >> products[i].entryDate >> products[i].amount;
    }
    for (int i = 0; i < soLuong - 1; ++i) {
        for (int j = 0; j < soLuong - i - 1; ++j) {
            if (products[j].name > products[j + 1].name) {
                product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < soLuong; ++i) {
        output << products[i].id << products[i].name  << products[i].origin
            << products[i].color << products[i].price << products[i].entryDate
            << products[i].amount << endl;
    }
    input.close();
    output.close();
    delete[] products;
}


