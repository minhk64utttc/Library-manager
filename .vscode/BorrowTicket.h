#ifndef BORROWTICKET_H
#define BORROWTICKET_H

#include <vector>
#include <string>
#include <iostream>
#include "Reader.h"
#include "Book.h"

using namespace std;

class BorrowTicket {
private:
    string maPhieu;
    vector<Reader*> docGia;
    vector<Book*> sachMuon;
    string ngayMuon;
    string ngayTra;
    bool trangThai;

public:
    BorrowTicket(string ma, vector<Reader*> dg, vector<Book*> sm, string nm, string nt, bool tt);
    void traSach();
    void hienThi() const;
    string getMaPhieu() const;
    bool getTrangThai() const;
    vector<Reader*> getDocGia() const;
    vector<Book*> getSachMuon() const;
    string getNgayTra() const;
};

#endif