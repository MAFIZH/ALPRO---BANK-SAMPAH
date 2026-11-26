#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

enum JenisSampah { PLASTIK = 1, KERTAS, LOGAM, KACA };

// satu setoran catet satu satuan (milih KG/Gram)
union Berat {
    double kg;
    int gram;
};

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
    cout << endl << "============== LAPORAN SETORAN ==============" << endl;
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

double bacaAngka(const string &pesan) {
    double x;
    while (true) {
        cout << pesan;
        if (cin >> x) return x;
        cout << "Input harus berupa angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

int main() {
    Transaksi data[MAKS];
    int jumlah = 0;
    string ulangi;

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

        cout << endl << "====== Satuan Berat ======" << endl;
        cout << "1. Kilogram" << endl;
        cout << "2. Gram" << endl;

        do {
            satuan = (int)bacaAngka("Pilih satuan berat (Input angka 1-2): ");
            if (satuan < 1 || satuan > 2)
                cout << "Input tidak valid! Masukkan angka 1 sampai 2." << endl;
        } while (satuan < 1 || satuan > 2);

        // Konversi sesuai satuan yang dipilih
        if (satuan == 1) {
            b.kg = bacaAngka("Berat (kg): ");
            t.beratKg = b.kg;
        } else {
            b.gram = (int)bacaAngka("Berat (gram): ");
            t.beratKg = b.gram / 1000.0;
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

        cout << endl << "Jalankan program lagi? (ya/tidak): ";
        cin >> ulangi;

    } while (ulangi == "ya" || ulangi == "Ya");

    tampilLaporan(data, jumlah);
    cout << endl << "Terima kasih telah menabung di bank sampah!" << endl;
    return 0;
}