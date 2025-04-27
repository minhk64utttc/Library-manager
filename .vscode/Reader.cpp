#include "Reader.h"

Reader::Reader(string ma, string ten, string sdt)
    : maDocGia(ma), ten(ten), soDT(sdt) {}

void Reader::hienThi() const {
    cout << "Doc gia: " << ten << " (" << maDocGia << ")\n";
    cout << "Lien he: " << soDT << "\n\n";
}

string Reader::getMaDocGia() const { return maDocGia; }
string Reader::getTen() const { return ten; }