#include "Book.h"
Book::Book(string isbn, string ten, string tg, int nam, string nxb, string tl, int sl)
    : ISBN(isbn), tenSach(ten), tacGia(tg), namXB(nam), nhaXB(nxb),
      theLoai(tl), soLuong(sl), soLanMuon(0) {}
void Book::hienThi() const {
    cout << "Sach: " << tenSach << " (" << ISBN << ")\n";
    cout << "Tac gia: " << tacGia << " | So luong: " << soLuong 
         << " | So lan muon: " << soLanMuon << "\n\n";
}

string Book::gettheLoai() { return theLoai; }
string Book::getISBN() const { return ISBN; }
string Book::getTenSach() const { return tenSach; }
int Book::getSoLuong() const { return soLuong; }
int Book::getSoLanMuon() const { return soLanMuon; }
void Book::giamSoLuong() { if(soLuong > 0) soLuong--; }
void Book::tangSoLuong() { soLuong++; }
void Book::tangSoLanMuon() { soLanMuon++; }
void Book::suaThongTin(string tenMoi, string tacGiaMoi, int namMoi, string nhaXBMoi, string theLoaiMoi, int soLuongMoi) {
    tenSach = tenMoi;
    tacGia = tacGiaMoi;
    namXB = namMoi;
    nhaXB = nhaXBMoi;
    theLoai = theLoaiMoi;
    soLuong = soLuongMoi;
    cout << "Da cap nhat thong tin sach " << ISBN << endl;
}