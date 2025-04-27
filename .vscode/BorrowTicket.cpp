#include "BorrowTicket.h"
#include <algorithm>

BorrowTicket::BorrowTicket(string ma, vector<Reader*> dg, vector<Book*> sm, string nm, string nt, bool tt)
    : maPhieu(ma), docGia(dg), sachMuon(sm), ngayMuon(nm), ngayTra(nt), trangThai(tt) {
    if (!trangThai) {
        for(auto& s : sachMuon) {
            s->giamSoLuong();
            s->tangSoLanMuon();
        }
    }
}

void BorrowTicket::traSach() {
    if(!trangThai) {
        for(auto& s : sachMuon) s->tangSoLuong();
        trangThai = true;
    }
}

void BorrowTicket::hienThi() const {
    cout << "PHIEU MUON " << maPhieu << " - " << (trangThai ? "Da tra" : "Dang muon") << endl;
    cout << "Doc gia: ";
    for (auto& dg : docGia) cout << dg->getTen() << ", ";
    
    cout << "\nSach da muon: ";
    for (auto& s : sachMuon) cout << s->getTenSach() << ", ";
    
    cout << "\nThoi gian: " << ngayMuon << " -> " << ngayTra << "\n\n";
}

string BorrowTicket::getMaPhieu() const { return maPhieu; }
bool BorrowTicket::getTrangThai() const { return trangThai; }
vector<Reader*> BorrowTicket::getDocGia() const { return docGia; }
vector<Book*> BorrowTicket::getSachMuon() const { return sachMuon; }
string BorrowTicket::getNgayTra() const { return ngayTra; }