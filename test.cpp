#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// ENUM: jenis sampah
enum JenisSampah { PLASTIK = 1, KERTAS, LOGAM, KACA };

// UNION: satu setoran hanya mencatat satu satuan (kg ATAU gram)
union Berat {
    double kg;
    int gram;
};

// STRUCT: data satu transaksi
struct Transaksi {
    string namaNasabah;
    JenisSampah jenis;
    double beratKg;
    double harga;
    double total;
};

// ARRAY: harga per kg (indeks 0 tidak dipakai)
const double HARGA[5] = {0, 2000, 1500, 4000, 500};
const int MAKS = 100;

string namaJenis(JenisSampah j) {
    switch (j) {
        case PLASTIK: return "Plastik";
        case KERTAS:  return "Kertas";
        case LOGAM:   return "Logam";
        case KACA:    return "Kaca";
        default:      return "-";
    }
}

double hitungUang(double kg, double hargaPerKg) {
    return kg * hargaPerKg;
}

void tampilHarga() {
    cout << "\n=== DAFTAR HARGA PER KG ===\n";
    for (int i = 1; i <= 4; i++) {
        cout << i << ". " << left << setw(8) << namaJenis((JenisSampah)i)
             << ": Rp " << fixed << setprecision(0) << HARGA[i] << endl;
    }
}

void tampilLaporan(Transaksi data[], int n) {
    double totalKg = 0, totalUang = 0;
    cout << "\n=========== LAPORAN SETORAN ===========\n";
    cout << left << setw(4) << "No" << setw(15) << "Nasabah"
         << setw(10) << "Jenis" << setw(11) << "Berat(kg)"
         << "Total (Rp)" << endl;
    cout << "---------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(4) << i + 1
             << setw(15) << data[i].namaNasabah
             << setw(10) << namaJenis(data[i].jenis)
             << setw(11) << fixed << setprecision(2) << data[i].beratKg
             << "Rp " << setprecision(0) << data[i].total << endl;
        totalKg += data[i].beratKg;
        totalUang += data[i].total;
    }
    cout << "---------------------------------------------\n";
    cout << "Total sampah : " << fixed << setprecision(2) << totalKg << " kg\n";
    cout << "Total uang   : Rp " << setprecision(0) << totalUang << endl;
}

// Baca angka dengan validasi (supaya tidak error kalau user ketik huruf)
double bacaAngka(const string &pesan) {
    double x;
    while (true) {
        cout << pesan;
        if (cin >> x) return x;
        cout << "Input harus angka!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Transaksi data[MAKS];
    int jumlah = 0;
    char ulang;

    cout << "=== PROGRAM BANK SAMPAH ===\n";

    do {
        if (jumlah >= MAKS) {
            cout << "Data penuh!\n";
            break;
        }

        Transaksi t;
        int pilih, satuan;
        Berat b;

        cout << "\nNama nasabah : ";
        cin >> ws;
        getline(cin, t.namaNasabah);

        tampilHarga();

        do {
            pilih = (int)bacaAngka("Pilih jenis sampah (1-4): ");
            if (pilih < 1 || pilih > 4)
                cout << "Pilihan tidak valid!\n";
        } while (pilih < 1 || pilih > 4);

        t.jenis = (JenisSampah)pilih;
        t.harga = HARGA[pilih];

        satuan = (int)bacaAngka("Input berat dalam (1. Kilogram, 2. Gram): ");

        if (satuan == 2) {
            b.gram = (int)bacaAngka("Berat (gram): ");
            t.beratKg = b.gram / 1000.0;
        } else {
            b.kg = bacaAngka("Berat (kg): ");
            t.beratKg = b.kg;
        }

        if (t.beratKg <= 0) {
            cout << "Berat harus lebih dari 0. Data tidak disimpan.\n";
        } else {
            t.total = hitungUang(t.beratKg, t.harga);
            data[jumlah++] = t;

            cout << "\nSetoran berhasil dicatat!\n";
            cout << "Berat : " << fixed << setprecision(2) << t.beratKg << " kg\n";
            cout << "Uang  : Rp " << setprecision(0) << t.total << endl;
        }

        cout << "\nJalankan program lagi? (y/t): ";
        cin >> ulang;

    } while (ulang == 'y' || ulang == 'Y');

    tampilLaporan(data, jumlah);
    cout << "\nTerima kasih telah menabung sampah!\n";
    return 0;
}