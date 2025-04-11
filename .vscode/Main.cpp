#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

class Reader {
private:
    string maDocGia;
    string ten;
    string soDT;

public:
    Reader(string ma, string ten, string sdt)
        : maDocGia(ma), ten(ten), soDT(sdt) {}

    void hienThi() const {
        cout << "Doc gia: " << ten << " (" << maDocGia << ")\n";
        cout << "Lien he: "<<soDT << "\n\n";
    }

    string getMaDocGia() const { return maDocGia; }
    string getTen() const { return ten; }
};

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
    Book(string isbn, string ten, string tg, int nam, string nxb, string tl, int sl)
        : ISBN(isbn), tenSach(ten), tacGia(tg), namXB(nam), nhaXB(nxb), 
          theLoai(tl), soLuong(sl), soLanMuon(0) {}

    void hienThi() const {
        cout << "Sach: " << tenSach << " (" << ISBN << ")\n";
        cout << "Tac gia: " << tacGia << " | So luong: " << soLuong 
             << " | So lan muon: " << soLanMuon << "\n\n";
    }

    string getISBN() const { return ISBN; }
    string getTenSach() const { return tenSach; }
    int getSoLuong() const { return soLuong; }
    int getSoLanMuon() const { return soLanMuon; }
    void giamSoLuong() { if(soLuong > 0) soLuong--; }
    void tangSoLuong() { soLuong++; }
    void tangSoLanMuon() { soLanMuon++; }
};

class BorrowTicket {
private:
    string maPhieu;
    vector<Reader*> docGia;
    vector<Book*> sachMuon;
    string ngayMuon;
    string ngayTra;
    bool trangThai;

public:
    BorrowTicket(string ma, vector<Reader*> dg, vector<Book*> sm, string nm, string nt, bool tt)
        : maPhieu(ma), docGia(dg), sachMuon(sm), ngayMuon(nm), ngayTra(nt), trangThai(tt) 
    {
        if (!trangThai) {
            for(auto& s : sachMuon) {
                s->giamSoLuong();
                s->tangSoLanMuon();
            }
        }
    }

    void traSach() {
        if(!trangThai) {
            for(auto& s : sachMuon) s->tangSoLuong();
            trangThai = true;
        }
    }

    void hienThi() const {
        cout << "PHIEU MUON " << maPhieu << " - " << (trangThai ? "Da tra" : "Dang muon") << endl;
        cout << "Doc gia: ";
        for (auto& dg : docGia) cout << dg->getTen() << ", ";
        
        cout << "\nSach da muon: ";
        for (auto& s : sachMuon) cout << s->getTenSach() << ", ";
        
        cout << "\nThoi gian: " << ngayMuon << " -> " << ngayTra << "\n\n";
    }

    string getMaPhieu() const { return maPhieu; }
    bool getTrangThai() const { return trangThai; }
    vector<Reader*> getDocGia() const { return docGia; }
    vector<Book*> getSachMuon() const { return sachMuon; }
};

class QuanLyThuVien {
private:
    vector<Reader*> docGia;
    vector<Book*> allSach;
    vector<Book*> sachChuaMuon;
    vector<Book*> sachDaMuon;
    vector<BorrowTicket*> tatCaPhieu;

    Reader* timDocGia(string ma) {
        for (auto& r : docGia) {
            if (r->getMaDocGia() == ma) return r;
        }
        return nullptr;
    }

    Book* timSach(string isbn) {
        for (auto& b : allSach) {
            if (b->getISBN() == isbn) return b;
        }
        return nullptr;
    }

    void capNhatDanhSach() {
        sachChuaMuon.clear();
        sachDaMuon.clear();
        
        for (auto& s : allSach) {
            bool dangMuon = false;
            for (auto& phieu : tatCaPhieu) {
                if (!phieu->getTrangThai()) {
                    auto sachMuon = phieu->getSachMuon();
                    if (find(sachMuon.begin(), sachMuon.end(), s) != sachMuon.end()) {
                        dangMuon = true;
                        break;
                    }
                }
            }
            if (dangMuon) {
                sachDaMuon.push_back(s);
            } else {
                sachChuaMuon.push_back(s);
            }
        }
    }

public:
    void sapXepTheoTenGiamDan() {
        sort(allSach.begin(), allSach.end(), [](Book* a, Book* b) {
            return a->getTenSach() > b->getTenSach();
        });
    }

    void sapXepTheoMuonNhieuNhat() {
        sort(allSach.begin(), allSach.end(), [](Book* a, Book* b) {
            return a->getSoLanMuon() > b->getSoLanMuon();
        });
    }

    void timDocGia() {
        cout << "Nhap ma doc gia: ";
        string ma;
        cin.ignore();
        getline(cin, ma);
        Reader* docGiaTimThay = timDocGia(ma);
        if (docGiaTimThay) {
            docGiaTimThay->hienThi();
        } else {
            cout << "Khong tim thay doc gia co ma " << ma << endl;
        }
    }

    void timSach() {
        cout << "Nhap ma sach (ISBN): ";
        string isbn;
        cin.ignore();
        getline(cin, isbn);
        Book* sachTimThay = timSach(isbn);
        if (sachTimThay) {
            sachTimThay->hienThi();
        } else {
            cout << "Khong tim thay sach co ma " << isbn << endl;
        }
    }

    void traSach(string maPhieu) {
        for (auto& phieu : tatCaPhieu) {
            if (phieu->getMaPhieu() == maPhieu && !phieu->getTrangThai()) {
                phieu->traSach();
                capNhatDanhSach();
                cout << "Tra sach thanh cong!" << endl;
                return;
            }
        }
        cout << "Khong tim thay phieu muon hoac da tra roi!" << endl;
    }

    void docFileSach(const string& tenFile) {
        ifstream file(tenFile);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, ',');
            if (parts.size() == 7) {
                Book* newBook = new Book(
                    parts[0], parts[1], parts[2], stoi(parts[3]), 
                    parts[4], parts[5], stoi(parts[6])
                );
                allSach.push_back(newBook);
            }
        }
        file.close();
        capNhatDanhSach();
    }

    void docFilePhieuMuon(const string& tenFile) {
        ifstream file(tenFile);
        if (!file.is_open()) {
            cerr << "Khong the mo file phieu muon!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            vector<string> parts = split(line, ',');
            if (parts.size() != 6) {
                cerr << "Dinh dang dong khong hop le: " << line << endl;
                continue;
            }

            string maPhieu = parts[0];
 vector<Reader*> docGiaList;
        vector<string> readerInfos = split(parts[1], '-');
        for (auto& info : readerInfos) {
            vector<string> fields = split(info, ':');
            if (fields.size() != 3) {
                cerr << "Thong tin doc gia khong hop le: " << info << endl;
                continue;
            }
            string ma = fields[0];
            string ten = fields[1];
            string sdt = fields[2];

            Reader* r = timDocGia(ma);
            if (!r) {
                r = new Reader(ma, ten, sdt);
                docGia.push_back(r);
            }
            docGiaList.push_back(r);
        }           

            vector<Book*> sachList;
            vector<string> isbns = split(parts[2], '-');
            for (auto& isbn : isbns) {
                Book* b = timSach(isbn);
                if (!b) {
                    cerr << "Khong tim thay sach: " << isbn << endl;
                    continue;
                }
                sachList.push_back(b);
            }

            string ngayMuon = parts[3];
            string ngayTra = parts[4];
            bool trangThai = (parts[5] == "1");

            BorrowTicket* phieu = new BorrowTicket(
                maPhieu, 
                docGiaList, 
                sachList, 
                ngayMuon, 
                ngayTra, 
                trangThai
            );
            
            tatCaPhieu.push_back(phieu);
        }
        file.close();
        capNhatDanhSach();
    }

    void hienThiSach() const {
        cout << "===== DANH SACH SACH CHUA MUON =====" << endl;
        for (auto& s : sachChuaMuon) s->hienThi();
        cout << "\n===== DANH SACH SACH DA MUON =====" << endl;
        for (auto& s : sachDaMuon) s->hienThi();
    }

    void hienThiDocGia() const {
        cout << "===== DANH SACH DOC GIA =====" << endl;
        for (auto& dg : docGia) dg->hienThi();
    }

    void hienThiPhieuMuon() const {
        cout << "===== DANH SACH PHIEU MUON =====" << endl;
        for (auto& phieu : tatCaPhieu) phieu->hienThi();
    }
};

int main() {
    QuanLyThuVien ql;
    
    ql.docFileSach("books.txt");
    ql.docFilePhieuMuon("phieu_muon.txt");
    
    int choice;
    do {
        cout << "\n========= MENU =========" << endl;
        cout << "1. Hien thi danh sach sach" << endl;
        cout << "2. Hien thi danh sach doc gia" << endl;
        cout << "3. Hien thi danh sach phieu muon" << endl;
        cout << "4. Tim doc gia" << endl;
        cout << "5. Tim sach" << endl;
        cout << "6. Sap xep sach theo ten giam dan" << endl;
        cout << "7. Sap xep sach theo so lan muon nhieu nhat" << endl;
        cout << "8. Tra sach" << endl;
        cout << "0. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1: ql.hienThiSach(); break;
            case 2: ql.hienThiDocGia(); break;
            case 3: ql.hienThiPhieuMuon(); break;
            case 4: ql.timDocGia(); break;
            case 5: ql.timSach(); break;
            case 6: 
                ql.sapXepTheoTenGiamDan();
                ql.hienThiSach();
                break;
            case 7:
                ql.sapXepTheoMuonNhieuNhat();
                ql.hienThiSach();
                break;
            case 8: {
                string maPhieu;
                cout << "Nhap ma phieu muon: ";
                cin >> maPhieu;
                ql.traSach(maPhieu);
                break;
            }
            case 0: cout << "Thoat chuong trinh!" << endl; break;
            default: cout << "Lua chon khong hop le. Vui long thu lai!" << endl;
        }
    } while (choice != 0);

    return 0;
}