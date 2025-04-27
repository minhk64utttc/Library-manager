#include "QuanLyThuVien.h"
#include <algorithm>

vector<string> QuanLyThuVien::split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Reader* QuanLyThuVien::timDocGia(string ma) {
    for (auto& r : docGia) {
        if (r->getMaDocGia() == ma) return r;
    }
    return nullptr;
}

Book* QuanLyThuVien::timSach(string isbn) {
    for (auto& b : allSach) {
        if (b->getISBN() == isbn) return b;
    }
    return nullptr;
}

void QuanLyThuVien::capNhatDanhSach() {
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

tm QuanLyThuVien::stringToTm(const string &dateStr) {
    tm tm = {};
    sscanf(dateStr.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    return tm;
}

int QuanLyThuVien::tinhSoNgayTreHan(const string &ngayPhaiTra, const string &ngayTraThucTe) {
    tm tm1 = stringToTm(ngayPhaiTra);
    tm tm2 = stringToTm(ngayTraThucTe);

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    if (time1 == -1 || time2 == -1) {
        cerr << "Loi chuyen doi ngay thang!" << endl;
        return 0;
    }

    const int SEC_PER_DAY = 86400;
    double diff = difftime(time2, time1) / SEC_PER_DAY;
    return (diff > 0) ? static_cast<int>(diff) : 0;
}

void QuanLyThuVien::lietKeTheoTheLoai() {
    map<string, vector<Book*>> nhomTheLoai;
    for (auto& sach : allSach) {
        nhomTheLoai[sach->gettheLoai()].push_back(sach);
    }
    cout << "===== DANH SACH SACH THEO THE LOAI =====" << endl;
    for (auto& pair : nhomTheLoai) {
        string theLoai = pair.first;
        vector<Book*> sachTrongLoai = pair.second;

        cout << "\n[The loai: " << theLoai << "]" << endl;
        if (sachTrongLoai.empty()) {
            cout << "(Khong co sach nao trong the loai nay)\n";
        } else {
            for (auto& sach : sachTrongLoai) {
                sach->hienThi();
            }
        }
    }
}

void QuanLyThuVien::sapXepTheoTenGiamDan() {
    sort(allSach.begin(), allSach.end(), [](Book* a, Book* b) {
        return a->getTenSach() > b->getTenSach();
    });
}

void QuanLyThuVien::sapXepTheoMuonNhieuNhat() {
    sort(allSach.begin(), allSach.end(), [](Book* a, Book* b) {
        return a->getSoLanMuon() > b->getSoLanMuon();
    });
}

void QuanLyThuVien::timDocGia() {
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

void QuanLyThuVien::tienPhat() {
    string ngayHienTai;
    cout << "Nhap ngay hien tai (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, ngayHienTai);

    cout << "\n===== DANH SACH TIEN PHAT =====" << endl;
    bool coPhieuTreHan = false;

    for (auto phieu : tatCaPhieu) {
        if (!phieu->getTrangThai()) {
            int soNgayTre = tinhSoNgayTreHan(phieu->getNgayTra(), ngayHienTai);
            if (soNgayTre > 0) {
                coPhieuTreHan = true;
                int tienPhat = soNgayTre * 500; 
                cout << "Phieu ma " << phieu->getMaPhieu() << ":" << endl;
                cout << "Doc gia : ";
                for (auto dg : phieu->getDocGia()) {
                    cout << dg->getTen() << ", ";
                }
                cout << "\n- So ngay tre hen: " << soNgayTre << endl;
                cout << "- Tien phat: " << tienPhat << " VNĐ\n" << endl;
            }
        }
    }

    if (!coPhieuTreHan) {
        cout << "Khong co phieu nao tre han!" << endl;
    }
}

void QuanLyThuVien::timSach() {
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

void QuanLyThuVien::traSach(string maPhieu) {
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

void QuanLyThuVien::docFileSach(const string& tenFile) {
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

void QuanLyThuVien::docFilePhieuMuon(const string& tenFile) {
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

void QuanLyThuVien::hienThiSach() const {
    cout << "===== DANH SACH SACH CHUA MUON =====" << endl;
    for (auto& s : sachChuaMuon) s->hienThi();
    cout << "\n===== DANH SACH SACH DA MUON =====" << endl;
    for (auto& s : sachDaMuon) s->hienThi();
}

void QuanLyThuVien::hienThiDocGia() const {
    cout << "===== DANH SACH DOC GIA =====" << endl;
    for (auto& dg : docGia) dg->hienThi();
}

void QuanLyThuVien::hienThiPhieuMuon() const {
    cout << "===== DANH SACH PHIEU MUON =====" << endl;
    for (auto& phieu : tatCaPhieu) phieu->hienThi();
}
