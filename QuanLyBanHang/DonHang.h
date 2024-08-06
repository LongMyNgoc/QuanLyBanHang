#pragma once
#include <iostream>
#include <cstring> // Để sử dụng memset

// Định nghĩa struct Order bên ngoài lớp DonHang
struct Order {
    static int orderNumber;
    std::string productCodes;
    int quantity;
    std::string Color;
    std::string Country;
    std::string customerName;
    std::string customerAddress;
    std::string phoneNumber;
    std::string orderDate;
    char orderNumberStr[10];
    Order* next;
};

class DonHang {
public:
    DonHang();
    ~DonHang();
    void datHang(std::string productCodes, int quantity, std::string Color , std::string Country, const std::string& customerName, const std::string& customerAddress, const std::string& phoneNumber, const std::string& orderDate);
    void luuDonHang();
    void nhapThongTinDonHang();
    bool kiemTraHangHoa(std::string productCodes);
    void capNhatSoLuongHangHoa(std::string productCodes, int quantityChange);
    void xuLyDonHang();
private:
    Order* head;
    int orderCount;
};