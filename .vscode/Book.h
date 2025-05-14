#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

using namespace std;

class Book {
private:
    string ISBN;
    string tenSach;
    string tacGia;
    int namXB;
    string nhaXB;
    string theLoai;
    int soLuong;
    int soLanMuon;

public:
    Book(string isbn, string ten, string tg, int nam, string nxb, string tl, int sl);
    void hienThi() const;
    string gettheLoai();
    string getISBN() const;
    string getTenSach() const;
    int getSoLuong() const;
    int getSoLanMuon() const;
    void giamSoLuong();
    void tangSoLuong();
    void tangSoLanMuon();
    void setTenSach(const string& ten) { tenSach = ten; }
    void setTacGia(const string& tg) { tacGia = tg; }
    void setNamXB(int nam) { namXB = nam; }
    void setNhaXB(const string& nxb) { nhaXB = nxb; }
    void setTheLoai(const string& tl) { theLoai = tl; }
    void setSoLuong(int sl) { soLuong = sl; }
      void suaThongTin(string tenMoi, string tacGiaMoi, int namMoi, string nhaXBMoi, string theLoaiMoi, int soLuongMoi);
};

#endif