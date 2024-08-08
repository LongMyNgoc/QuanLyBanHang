#include "DonHang.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <string>
// Khởi tạo biến tĩnh orderNumber
int Order::iOrderNumber = 1;

// Constructor
DonHang::DonHang()
{
    pHead = nullptr;
    iOrderCount = 0;
}

// Destructor
DonHang::~DonHang()
{
    Order *pCurrent = pHead;
    while (pCurrent != nullptr)
    {
        Order *pTemp = pCurrent->pNext;
        delete pCurrent;
        pCurrent = pTemp;
    }
}
bool DonHang::kiemTraHangHoa(std::string strProductCodes)
{
    std::ifstream inFile("DanhSachHangHoa.txt");
    if (!inFile)
    {
        std::cerr << "Không thể mở file DanhSachHangHoa.txt để đọc!" << std::endl;
        return false;
    }

    std::string strLine;
    while (std::getline(inFile, strLine))
    {
        std::istringstream iss(strLine);
        std::string strCode, strOrdernumber;
        if (iss >> strOrdernumber >> strCode)
        {
            if (strCode == strProductCodes)
            {
                return true; // Sản phẩm có sẵn
            }
        }
    }
    return false; // Sản phẩm không có sẵn
}
// Hàm đặt hàng
void DonHang::datHang(std::string strProductCodes, int iQuantity, std::string strColor, std::string strCountry, const std::string &strCustomerName, const std::string &strCustomerAddress, const std::string &strPhoneNumber, const std::string &strOrderDate)
{
    // Tạo đơn hàng mới
    if (!kiemTraHangHoa(strProductCodes))
    {
        std::cerr << "Hết hàng!" << std::endl;
        return;
    }
    Order *newOrder = new Order;
    newOrder->strProductCodes = strProductCodes;
    newOrder->iQuantity = iQuantity;
    newOrder->strColor = strColor;
    newOrder->strCountry = strCountry;
    newOrder->strCustomerName = strCustomerName;
    newOrder->strCustomerAddress = strCustomerAddress;
    newOrder->strPhoneNumber = strPhoneNumber;
    newOrder->strOrderDate = strOrderDate;
    newOrder->pNext = nullptr;

    // Định dạng orderNumber và lưu vào orderNumberStr
    snprintf(newOrder->cOrderNumberStr, sizeof(newOrder->cOrderNumberStr), "%04d", Order::iOrderNumber++);
    newOrder->iOrderNumber = Order::iOrderNumber;

    // Thêm đơn hàng mới vào danh sách liên kết
    if (pHead == nullptr)
    {
        pHead = newOrder;
    }
    else
    {
        Order *pTemp = pHead;
        while (pTemp->pNext != nullptr)
        {
            pTemp = pTemp->pNext;
        }
        pTemp->pNext = newOrder;
    }
    iOrderCount++;
    std::cout << "Don Hang Dang Cho Xu Ly.\n";
}

// Hàm lưu đơn hàng vào file
void DonHang::luuDonHang()
{
    std::ofstream outFile("DonHang.txt", std::ios::app);
    if (!outFile)
    {
        std::cerr << "Không thể mở file để ghi!" << std::endl;
        return;
    }

    Order *pCurrent = pHead;
    while (pCurrent != nullptr)
    {
        outFile << pCurrent->cOrderNumberStr;
        outFile << " " << pCurrent->strProductCodes;
        outFile << " " << pCurrent->iQuantity;
        outFile << " " << pCurrent->strColor;
        outFile << " " << pCurrent->strCountry;
        outFile << " " << pCurrent->strCustomerName;
        outFile << " " << pCurrent->strCustomerAddress;
        outFile << " " << pCurrent->strPhoneNumber;
        outFile << " " << pCurrent->strOrderDate << "\n";
        pCurrent = pCurrent->pNext;
    }

    outFile.close();
}

// Hàm nhập thông tin đơn hàng từ người dùng
void DonHang::nhapThongTinDonHang()
{
    std::string strProductCodes;
    int iQuantity;
    std::string strColor;
    std::string strCountry;
    std::string strCustomerName;
    std::string strCustomerAddress;
    std::string strPhoneNumber;
    std::string strOrderDate;

    std::cout << "Nhap ma san pham: ";
    std::cin >> strProductCodes;
    std::cout << "Nhap so luong: ";
    std::cin >> iQuantity;
    std::cout << "Nhap mau sac: ";
    std::cin >> strColor;
    std::cout << "Nhap quoc gia: ";
    std::cin >> strCountry;
    std::cin.ignore(); // Bỏ qua ký tự newline còn lại trong bộ đệm
    std::cout << "Nhap ten khach hang: "; 
    std::getline(std::cin, strCustomerName);
    std::cout << "Nhap dia chi khach hang: ";
    std::getline(std::cin, strCustomerAddress);
    std::cout << "Nhap so dien thoai khach hang: ";
    std::getline(std::cin, strPhoneNumber);
    std::cout << "Nhap ngay dat hang: ";
    std::getline(std::cin, strOrderDate);

    datHang(strProductCodes, iQuantity, strColor, strCountry, strCustomerName, strCustomerAddress, strPhoneNumber, strOrderDate);
}
void DonHang::capNhatSoLuongHangHoa(std::string strProductCodes, int iQuantityChange, std::string strCountry, std::string strColor)
{
    std::ifstream inFile("DanhSachHangHoa.txt");
    if (!inFile)
    {
        std::cerr << "Khong the mo file DanhSachHangHoa.txt de doc!" << std::endl;
        return;
    }

    std::ofstream tempFile("TempDanhSachHangHoa.txt");
    if (!tempFile)
    {
        std::cerr << "Khong the mo file TempDanhSachHangHoa.txt de ghi!" << std::endl;
        return;
    }

    std::string strOrderNumber, strCode, strTempCountry, strTempColor, strDate;
    int iQuantity;
    double dTotalAmount;

    while (inFile >> strOrderNumber >> strCode >> strTempCountry >> strTempColor >> dTotalAmount >> strDate >> iQuantity)
    {
        if (strCode == strProductCodes && strTempCountry == strCountry && strTempColor == strColor)
        {
            iQuantity -= iQuantityChange;
        }
        if (iQuantity)
            tempFile << strOrderNumber << " " << strCode << " " << strTempCountry << " " << strTempColor << " " << dTotalAmount << " " << strDate << " " << iQuantity << "\n";
    }

    inFile.close();
    tempFile.close();

    // Xoa thong tin trong file "DanhSachHangHoa.txt"
    std::ofstream danhSachHangHoaFile("DanhSachHangHoa.txt", std::ios::trunc);

    // Copy du lieu tu "TempDanhSachHangHoa.txt" vao "DanhSachHangHoa.txt"
    std::ifstream tempFileRead("TempDanhSachHangHoa.txt");
    std::string strLine;
    while (std::getline(tempFileRead, strLine))
    {
        danhSachHangHoaFile << strLine << "\n";
    }

    tempFileRead.close();
    danhSachHangHoaFile.close();

    // Xoa du lieu trong "TempDanhSachHangHoa.txt"
    std::ofstream tempFileClear("TempDanhSachHangHoa.txt", std::ios::trunc);
}

void DonHang::xuLyDonHang()
{
    std::ifstream inFile("DonHang.txt");
    std::string strLine;
    Order *newOrder = new Order();
    while (std::getline(inFile, strLine))
    {
        std::istringstream iss(strLine);
        int iOrderNumber;
        std::string strProductCodes;
        int iQuantity;
        std::string strColor;
        std::string strCountry;
        std::string strCustomerName;
        std::string strCustomerAddress;
        std::string strPhoneNumber;
        std::string strOrderDate;
        if (iss >> iOrderNumber >> strProductCodes >> iQuantity >> strColor >> strCountry >> strCustomerName >> strCustomerAddress >> strPhoneNumber >> strOrderDate)
        {
            Order *newOrder = new Order();
            newOrder->iOrderNumber = iOrderNumber;
            newOrder->strProductCodes = strProductCodes;
            newOrder->iQuantity = iQuantity;
            newOrder->strColor = strColor;
            newOrder->strCountry = strCountry;
            newOrder->strCustomerName = strCustomerName;
            newOrder->strCustomerAddress = strCustomerAddress;
            newOrder->strPhoneNumber = strPhoneNumber;
            newOrder->strOrderDate = strOrderDate;
            snprintf(newOrder->cOrderNumberStr, sizeof(newOrder->cOrderNumberStr), "%04d", Order::iOrderNumber++);
            newOrder->iOrderNumber = Order::iOrderNumber;

            // Them don hang moi vao danh sach lien ket
            if (pHead == nullptr)
            {
                pHead = newOrder;
            }
            else
            {
                Order *pCurrent = pHead;
                while (pCurrent->pNext != nullptr)
                {
                    pCurrent = pCurrent->pNext;
                }
                pCurrent->pNext = newOrder;
            }
        }
    }
    inFile.close();

    Order *pCurrent = pHead;
    Order *pPrevious = nullptr;
    std::cout << "Xu ly don hang: 0001 " << std::endl;
    while (pCurrent != nullptr)
    {
        // Xu ly don hang o day
        // Vi du: Hien thi thong tin don hang
        // Cap nhat so luong hang hoa trong file DanhSachHangHoa.txt
        if (strcmp(pCurrent->cOrderNumberStr, "0001") == 0)
        {
            capNhatSoLuongHangHoa(pCurrent->strProductCodes, pCurrent->iQuantity, pCurrent->strCountry, pCurrent->strColor);
        }
        else
        {
            std::ofstream outFile("TempDonHang.txt", std::ios::app);
            int iOrderNumber = std::stoi(pCurrent->cOrderNumberStr);
            iOrderNumber--;
            snprintf(pCurrent->cOrderNumberStr, sizeof(pCurrent->cOrderNumberStr), "%04d", iOrderNumber);
            pCurrent->iOrderNumber = iOrderNumber;
            outFile << pCurrent->cOrderNumberStr;
            outFile << " " << pCurrent->strProductCodes;
            outFile << " " << pCurrent->iQuantity;    
            outFile << " " << pCurrent->strColor;
            outFile << " " << pCurrent->strCountry;
            outFile << " " << pCurrent->strCustomerName;
            outFile << " " << pCurrent->strCustomerAddress;
            outFile << " " << pCurrent->strPhoneNumber;
            outFile << " " << pCurrent->strOrderDate << "\n";

            outFile.close();
        }

        // Doc don hang tiep theo
        pPrevious = pCurrent;
        pCurrent = pCurrent->pNext;

        // Xoa don hang da xu ly khoi danh sach
        delete pPrevious;
    }

    // Doi ten file tam thanh ten file goc
    //std::rename("TempDanhSachHangHoa.txt", "DanhSachHangHoa.txt");
    // Xoa thong tin trong file "DanhSachHangHoa.txt"
    std::ofstream danhSachHangHoaFile("DonHang.txt", std::ios::trunc);

    // Copy du lieu tu "TempDanhSachHangHoa.txt" vao "DanhSachHangHoa.txt"
    std::ifstream tempFileRead("TempDonHang.txt");
    while (std::getline(tempFileRead, strLine))
    {
        danhSachHangHoaFile << strLine << "\n";
    }

    tempFileRead.close();
    danhSachHangHoaFile.close();

    // Xoa du lieu trong "TempDanhSachHangHoa.txt"
    std::ofstream tempFileClear("TempDonHang.txt", std::ios::trunc);
    // xóa thông tin trong DonHang.txt
}
