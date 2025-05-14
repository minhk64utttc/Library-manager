#include "QuanLyThuVien.h"
#include<bits/stdc++.h>
using namespace std;
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
        cout << "9. Danh sach tien phat" << endl;
        cout << "10. Liet ke sach theo the loai" << endl;
         cout << "11. Them doc gia (nhap tay)" << endl;
        cout << "12. Them sach (nhap tay)" << endl;
        cout << "13. Xuat danh sach doc gia ra file" << endl;
        cout << "14. Xuat danh sach sach ra file" << endl;
        cout << "0. Thoat" << endl;
         cout << "15. Sua thong tin doc gia" << endl;
        cout << "16. Sua thong tin sach" << endl;
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
            case 9: 
            ql.tienPhat(); 
            break;
            case 10: 
                ql.lietKeTheoTheLoai(); 
                break;
            case 11: 
                ql.nhapDocGiaTuBanPhim();
                break;
            case 12:
                ql.nhapSachTuBanPhim();
                break;
            case 13:
                ql.xuatDocGiaRaFile("output_docgia.txt");
                break;
            case 14:
                ql.xuatSachRaFile("output_sach.txt");
                break;
             case 15: {
                string ma;
                cout << "Nhap ma doc gia can sua: ";
                cin >> ma;
                ql.suaThongTinDocGia(ma);
                break;
            }
            case 16: {
                string isbn;
                cout << "Nhap ISBN sach can sua: ";
                cin >> isbn;
                ql.suaThongTinSach(isbn);
                break;
            }
            case 0: cout << "Thoat chuong trinh!" << endl; break;
            default: cout << "Lua chon khong hop le. Vui long thu lai!" << endl;
        }
    } while (choice != 0);

    return 0;
}