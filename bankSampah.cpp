#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// ---------- Struktur Data ----------
struct JenisSampah {
    string nama;
    double hargaPerKg;   // Rp per kg
};

struct Nasabah {
    int id;
    string nama;
    double saldo;
};

struct Transaksi {
    int idTransaksi;
    int idNasabah;
    string tanggal;
    string jenisSampah;
    double beratKg;
    double hargaPerKg;
    double total;
};

