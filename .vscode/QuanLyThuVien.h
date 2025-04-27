#ifndef QUANLYTHUVIEN_H
#define QUANLYTHUVIEN_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <ctime>
#include "Reader.h"
#include "Book.h"
#include "BorrowTicket.h"

using namespace std;

class QuanLyThuVien {
private:
    vector<Reader*> docGia;
    vector<Book*> allSach;
    vector<Book*> sachChuaMuon;
    vector<Book*> sachDaMuon;
    vector<BorrowTicket*> tatCaPhieu;
    
    Reader* timDocGia(string ma);
    Book* timSach(string isbn);
    void capNhatDanhSach();
    vector<string> split(const string& s, char delimiter);
    tm stringToTm(const string &dateStr);

public:
    void lietKeTheoTheLoai();
    void sapXepTheoTenGiamDan();
    void sapXepTheoMuonNhieuNhat();
    void timDocGia();
    void timSach();
    void traSach(string maPhieu);
    void docFileSach(const string& tenFile);
    void docFilePhieuMuon(const string& tenFile);
    void hienThiSach() const;
    void hienThiDocGia() const;
    void hienThiPhieuMuon() const;
    void tienPhat();
    int tinhSoNgayTreHan(const string &ngayPhaiTra, const string &ngayTraThucTe);
};

#endif