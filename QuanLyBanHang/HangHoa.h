#pragma once
#include <iostream>
#include <string>
#include "Stack.h"

using namespace std;

class HangHoa {
private:
    char _cMa[5]; // Size + 1 for null terminator
    string _StrName, _StrOrigin, _strColor, _strEntryDate;
    int _iPrice, _iAmount;
    static Stack<string> _deletedIDs;
public:
    HangHoa() {}
    ~HangHoa() {}
    void taoHangHoa(string name, string origin, string color, int price, string entryDate, int amount);
    static void xoaHangHoa(string ma);
    static void capNhatSoLuong(string ma, int soluong);
    static int soHangHoa(); 
    void timkiemhanghoa(string strTenHangHoa);
    void inhanghoasaukhisapxep();
};
