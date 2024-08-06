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
    void taoHangHoa(string strName, string strOrigin, string strColor, int iPrice, string strEntryDate, int iAmount);
    static void xoaHangHoa(string strMa);
    static void capNhatSoLuong(string strMa, int iSoLuong);
    static int soHangHoa(); 
    void timKiemHangHoa(string strTenHangHoa);
    void printList();
    void sort();
};
