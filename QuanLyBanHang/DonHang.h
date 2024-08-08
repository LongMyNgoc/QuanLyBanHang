#pragma once
#include <iostream>
#include <cstring> // Để sử dụng memset

// Định nghĩa struct Order bên ngoài lớp DonHang
struct Order {
    static int iOrderNumber;
    std::string strProductCodes;
    int iQuantity;
    std::string strColor;
    std::string strCountry;
    std::string strCustomerName;
    std::string strCustomerAddress;
    std::string strPhoneNumber;
    std::string strOrderDate;
    char cOrderNumberStr[10];
    Order* pNext;
};

class DonHang {
public:
    DonHang();
    ~DonHang();
    void datHang(std::string strProductCodes, int iQuantity, std::string strColor , std::string strCountry, const std::string& strCustomerName, const std::string& strCustomerAddress, const std::string& strPhoneNumber, const std::string& strOrderDate);
    void luuDonHang();
    void nhapThongTinDonHang();
    bool kiemTraHangHoa(std::string strProductCodes);
    void capNhatSoLuongHangHoa(std::string strProductCodes, int iQuantityChange, std::string strCountry, std::string strColor);
    void xuLyDonHang();
private:
    Order* pHead;
    int iOrderCount;
};