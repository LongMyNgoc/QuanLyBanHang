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
    ifstream iFile("DanhSachHangHoa.txt");
    string strLine;
    int iCnt = 0;
    while (getline(iFile, strLine)) {
        ++iCnt;
    }
    iFile.close();
    return iCnt;
}

void HangHoa::taoHangHoa(string strName, string strOrigin, string strColor, int iPrice, string strEntryDate, int iAmount) {
    ofstream iFile("DanhSachHangHoa.txt", ios::app); 
    if (!iFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string strID;
    int soHangHoa = HangHoa::soHangHoa();

    if(!_deletedIDs.isEmpty()){
        strID = _deletedIDs.pop();
    } else{
        strID = to_string(soHangHoa + 1);
        while(strID.length() < 4){ 
            strID = '0' + strID;
        }
    }
    iFile << strID << " " << strName << " " << strOrigin << " " << strColor << " "
         << iPrice << " " << strEntryDate << " " << iAmount << endl;
    iFile.close();
}


void HangHoa::xoaHangHoa(string strMa) {
    ifstream inputFile("DanhSachHangHoa.txt");
    ofstream tempFile("TempDanhSachHangHoa.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string strLine;
    bool bFound = false;
    while (getline(inputFile, strLine)) {
        istringstream iss(strLine);
        string strID;
        iss >> strID;
        if (strID != strMa) {
            tempFile << strLine << endl;
        } else {
            bFound = true;
            _deletedIDs.push(strID);
        }
    }

    inputFile.close();
    tempFile.close();

    if (bFound) {
        remove("DanhSachHangHoa.txt");
        rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
        cout << "Xoa Hang Hoa Thanh Cong" << endl;
    } else {
        remove("TempDanhSachHangHoa.txt");
        cout << "Khong Tim Thay Hang Hoa" << endl;
    }
}


void HangHoa::capNhatSoLuong(string strMa, int iSoLuong) {
    if (iSoLuong <= 0) {
        cout << "So luong phai lon hon 0" << endl;
        return;
    }

    ifstream inputFile("DanhSachHangHoa.txt");
    ofstream tempFile("TempDanhSachHangHoa.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cerr << "Failed to open file" << endl;
        return;
    }

    string strLine;
    bool bFound = false;

    while (getline(inputFile, strLine)) {
        istringstream iss(strLine);
        string strID;
        iss >> strID;
        if (strID == strMa) {
            string name, origin, color, entryDate;
            int price, amount;
            iss >> name >> origin >> color >> price >> entryDate >> amount;
            // Update so luong
            amount = iSoLuong;
            tempFile << strID << " " << name << " " << origin << " " << color << " " << price << " " << entryDate << " " << amount << endl;
            bFound = true;
        } else {
            tempFile << strLine << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (bFound) {
        remove("DanhSachHangHoa.txt");
        rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
        cout << "Cap nhat so luong thanh cong" << endl;
    } else {
        remove("TempDanhSachHangHoa.txt");
        cout << "Ma hang hoa khong co trong danh sach hang hoa" << endl;
    }
}

void HangHoa::timKiemHangHoa(string strTenHangHoa) {
        ifstream inputFile("DanhSachHangHoa.txt");
    bool bFound = true;
    for (int i = 0; i < soHangHoa(); i++) {
        string strID, strName, strOrigin, strColor, strEntryDate;
        int iPrice , iAmount;
        inputFile >> strID >> strName >> strOrigin >> strColor >> iPrice >> strEntryDate >> iAmount;
        if (strName == strTenHangHoa) {
            int iWidthMa = 10;
            int iWidthName = 20;
            int iWidthOrigin = 20;
            int iWidthColor = 10;
            int iWidthEntrydate = 15;
            int iWidthPrice = 15;
            int iWidthAmount = 25;
            if (i==0) {
                cout << std::left << std::setw(iWidthMa) << "Ma"
                    << std::left << std::setw(iWidthName) << "Name"
                    << std::left << std::setw(iWidthOrigin) << "Origin"
                    << std::left << std::setw(iWidthColor) << "Color"
                    << std::left << std::setw(iWidthPrice) << "Price"
                    << std::left << std::setw(iWidthEntrydate) << "EntryDate"
                    << std::left << std::setw(iWidthAmount) << "Amount"
                    << std::endl;
            }
            cout << std::setfill('-') << std::setw(iWidthMa) << ""
                << std::setw(iWidthName) << ""
                << std::setw(iWidthOrigin) << ""
                << std::setw(iWidthColor) << ""
                << std::setw(iWidthPrice) << ""
                << std::setw(iWidthEntrydate) << ""
                << std::setw(iWidthAmount) << ""
                << std::setfill(' ') << std::endl;

            cout << std::left << std::setw(iWidthMa) << strID
                << std::left << std::setw(iWidthName) << strName
                << std::left << std::setw(iWidthOrigin) << strOrigin
                << std::left << std::setw(iWidthColor) << strColor
                << std::left << std::setw(iWidthPrice) << iPrice
                << std::left << std::setw(iWidthEntrydate) << strEntryDate
                << std::left << std::setw(iWidthAmount) << iAmount
                << std::endl;
             bFound = false;
        }
    }
    if (bFound) {
        cout << "khong tim thay hang hoa";
    }
    inputFile.close();
}

void HangHoa::printList() {
    ifstream inputFile("DanhSachHangHoa.txt");
    for (int i = 0; i < soHangHoa(); i++) {
        string strID, strName, strOrigin, strColor, strEntryDate;
        int iPrice, iAmount;
        inputFile >> strID >> strName >> strOrigin >> strColor >> iPrice >> strEntryDate >> iAmount;
            int iWidthMa = 10;
            int iWidthName = 20;
            int iWidthOrigin = 20;
            int iWidthColor = 10;
            int iWidthEntrydate = 15;
            int iWidthPrice = 15;
            int iWidthAmount = 25;
            if (i == 0) {
                cout << std::left << std::setw(iWidthMa) << "Ma"
                    << std::left << std::setw(iWidthName) << "Name"
                    << std::left << std::setw(iWidthOrigin) << "Origin"
                    << std::left << std::setw(iWidthColor) << "Color"
                    << std::left << std::setw(iWidthPrice) << "Price"
                    << std::left << std::setw(iWidthEntrydate) << "EntryDate"
                    << std::left << std::setw(iWidthAmount) << "Amount"
                    << std::endl;
            }
            cout << std::setfill('-') << std::setw(iWidthMa) << ""
                << std::setw(iWidthName) << ""
                << std::setw(iWidthOrigin) << ""
                << std::setw(iWidthColor) << ""
                << std::setw(iWidthPrice) << ""
                << std::setw(iWidthEntrydate) << ""
                << std::setw(iWidthAmount) << ""
                << std::setfill(' ') << std::endl;

            cout << std::left << std::setw(iWidthMa) << strID
                << std::left << std::setw(iWidthName) << strName
                << std::left << std::setw(iWidthOrigin) << strOrigin
                << std::left << std::setw(iWidthColor) << strColor
                << std::left << std::setw(iWidthPrice) << iPrice
                << std::left << std::setw(iWidthEntrydate) << strEntryDate
                << std::left << std::setw(iWidthAmount) << iAmount
                << std::endl;
    }
    inputFile.close();
}

void HangHoa::sort()
{
    class Node
    {
        friend class LinkList;
    private:
        string _strData;
        Node* _pNext;
    public:
        Node(string strData)
        {
            _strData = strData;
            _pNext = NULL;
        }
        ~Node(){}
    };
    class LinkList
    {
    private:
        Node* _pHead;
        Node* _pTail;
    public:
        LinkList()
        {
            _pHead = _pTail = NULL;
        }
        ~LinkList(){}
        void add(string strData)
        {
            Node* pNode = new Node(strData);
            if (_pHead == NULL)
            {
                _pHead = _pTail = pNode;
            }
            else
            {
                _pTail->_pNext = pNode;
                _pTail = pNode;
            }
        }
        void sapXep()
        {
            for (Node* pNode1 = _pHead; pNode1 != NULL; pNode1 = pNode1->_pNext)
            {
                int iAmount1 = 1000;
                stringstream ss1(pNode1->_strData);
                string str1;
                ss1 >> str1;
                int iData1 = 0;
                for (int i = 0; i < str1.length(); i++)
                {
                    iData1 += (((int)str1[i]-48)*iAmount1);
                    iAmount1 /= 10;
                }
                for (Node* pNode2 = pNode1->_pNext; pNode2 != NULL; pNode2 = pNode2->_pNext)
                {
                    int iAmount2 = 1000;
                    stringstream ss2(pNode2->_strData);
                    string str2;
                    ss2 >> str2;
                    int iData2 = 0;
                    for (int j = 0; j < str2.length(); j++)
                    {
                        iData2 += (((int)str2[j]-48)*iAmount2);
                        iAmount2 /= 10;
                    }
                    if (iData2 < iData1)
                    {
                        string strTemp = pNode1->_strData;
                        pNode1->_strData = pNode2->_strData;
                        pNode2->_strData = strTemp;
                    }
                }
            }
        }
        void printList()
        {
            ofstream oFile("DanhSachHangHoa.txt");
            if (oFile.is_open())
            {
                for (Node* pNode = _pHead; pNode != NULL; pNode = pNode->_pNext)
                {
                    oFile << pNode->_strData << endl;
                }
                oFile.close();
            }
        }
    };
    ifstream iFile("DanhSachHangHoa.txt");
    LinkList list;
    if (iFile.is_open())
    {
        string strLine;
        while (getline(iFile, strLine))
        {
            list.add(strLine);
        }
        iFile.close();
    }
    list.sapXep();
    list.printList();
}
