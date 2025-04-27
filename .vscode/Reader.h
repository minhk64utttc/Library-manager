#ifndef READER_H
#define READER_H

#include <string>
#include <iostream>

using namespace std;

class Reader {
private:
    string maDocGia;
    string ten;
    string soDT;

public:
    Reader(string ma, string ten, string sdt);
    void hienThi() const;
    string getMaDocGia() const;
    string getTen() const;
};

#endif