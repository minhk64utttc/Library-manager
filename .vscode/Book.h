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
};

#endif