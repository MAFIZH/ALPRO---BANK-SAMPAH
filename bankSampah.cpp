#include <iostream>
#include <iomanip>
#include <string>
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
    cout << endl << "=== DAFTAR HARGA PER KG ===" << endl;
    for (int i = 1; i <= 4; i++) {
        cout << i << ". " << left << setw(8) << namaJenis((JenisSampah)i)
             << ": Rp " << fixed << setprecision(0) << HARGA[i] << endl;
    }
}

void tampilLaporan(Transaksi data[], int n) {
    double totalKg = 0, totalUang = 0;
    cout << endl << "=========== LAPORAN SETORAN ===========" << endl;
    cout << left << setw(4) << "No" << setw(15) << "Nasabah"
         << setw(10) << "Jenis" << setw(11) << "Berat(kg)"
         << "Total (Rp)" << endl;
    cout << "---------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        cout << left << setw(4) << i + 1
             << setw(15) << data[i].namaNasabah
             << setw(10) << namaJenis(data[i].jenis)
             << setw(11) << fixed << setprecision(2) << data[i].beratKg
             << "Rp " << setprecision(0) << data[i].total << endl;
        totalKg += data[i].beratKg;
        totalUang += data[i].total;
    }
    cout << "---------------------------------------------" << endl;
    cout << "Total sampah : " << fixed << setprecision(2) << totalKg << " kg" << endl;
    cout << "Total uang   : Rp " << setprecision(0) << totalUang << endl;
}

// Baca angka dengan validasi (supaya tidak error kalau user ketik huruf)
double bacaAngka(const string &pesan) {
    double x;
    string buang;
    while (true) {
        cout << pesan;
        if (cin >> x) return x;
        cout << "Input harus angka!" << endl;
        cin.clear();
        cin >> buang;
    }
}

int main() {
    Transaksi data[MAKS];
    int jumlah = 0;
    char ulang;

    cout << "=== PROGRAM BANK SAMPAH ===" << endl;

    do {
        if (jumlah >= MAKS) {
            cout << "Data penuh!" << endl;
            break;
        }

        Transaksi t;
        int pilih, satuan;
        Berat b;

        cout << endl << "Nama nasabah : ";
        cin >> ws;
        getline(cin, t.namaNasabah);

        tampilHarga();

        do {
            pilih = (int)bacaAngka("Pilih jenis sampah (1-4): ");
            if (pilih < 1 || pilih > 4)
                cout << "Pilihan tidak valid!" << endl;
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
            cout << "Berat harus lebih dari 0. Data tidak disimpan." << endl;
        } else {
            t.total = hitungUang(t.beratKg, t.harga);
            data[jumlah++] = t;

            cout << endl << "Setoran berhasil dicatat!" << endl;
            cout << "Berat : " << fixed << setprecision(2) << t.beratKg << " kg" << endl;
            cout << "Uang  : Rp " << setprecision(0) << t.total << endl;
        }

        cout << endl << "Jalankan program lagi? (y/t): ";
        cin >> ulang;

    } while (ulang == 'y' || ulang == 'Y');

    tampilLaporan(data, jumlah);
    cout << endl << "Terima kasih telah menabung sampah!" << endl;
    return 0;
}