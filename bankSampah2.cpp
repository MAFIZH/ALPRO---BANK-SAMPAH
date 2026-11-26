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

void tampilHarga() {
    cout << endl << "=== DAFTAR HARGA PER KG ===" << endl;
    for (int i = 1; i <= 4; i++) {
        cout << i << ". " << left << setw(8) << namaJenis((JenisSampah)i)
            << ": Rp " << fixed << setprecision(0) << HARGA[i] << endl;
    }
}

// MENU 1: catat setoran (bisa diulang)
void setorSampah(Transaksi data[], int &jumlah) {
    string ulangi;

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
            data[jumlah] = t;
            jumlah++;

            cout << endl << "Setoran berhasil dicatat!" << endl;
            cout << "Berat : " << fixed << setprecision(2) << t.beratKg << " kg" << endl;
            cout << "Uang  : Rp " << setprecision(0) << t.total << endl;
        }

        cout << endl << "Catat setoran lagi? (ya/tidak): ";
        cin >> ulangi;

    } while (ulangi == "ya" || ulangi == "Ya");
}

// MENU 2: laporan semua setoran
void tampilLaporan(Transaksi data[], int n) {
    if (n == 0) {
        cout << endl << "Belum ada setoran." << endl;
        return;
    }

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

// MENU 3: saldo satu nasabah (dijumlah otomatis dari semua setorannya)
void cariSaldo(Transaksi data[], int n) {
    string cari;
    double saldo = 0, totalKg = 0;
    int banyak = 0;

    cout << endl << "Nama nasabah : ";
    cin >> ws;
    getline(cin, cari);

    for (int i = 0; i < n; i++) {
        if (data[i].namaNasabah == cari) {
            saldo += data[i].total;
            totalKg += data[i].beratKg;
            banyak++;
        }
    }

    if (banyak == 0) {
        cout << "Nasabah tidak ditemukan." << endl;
    } else {
        cout << endl << "=== SALDO NASABAH ===" << endl;
        cout << "Nama          : " << cari << endl;
        cout << "Jumlah setoran: " << banyak << "x" << endl;
        cout << "Total sampah  : " << fixed << setprecision(2) << totalKg << " kg" << endl;
        cout << "Saldo         : Rp " << setprecision(0) << saldo << endl;
    }
}

// MENU 4: rekap berat dan uang per jenis sampah
void rekapJenis(Transaksi data[], int n) {
    double kg[5] = {0, 0, 0, 0, 0};
    double uang[5] = {0, 0, 0, 0, 0};

    for (int i = 0; i < n; i++) {
        kg[data[i].jenis] += data[i].beratKg;
        uang[data[i].jenis] += data[i].total;
    }

    cout << endl << "======== REKAP PER JENIS SAMPAH ========" << endl;
    cout << left << setw(10) << "Jenis" << setw(12) << "Berat(kg)" << "Total (Rp)" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 1; i <= 4; i++) {
        cout << left << setw(10) << namaJenis((JenisSampah)i)
            << setw(12) << fixed << setprecision(2) << kg[i]
            << "Rp " << setprecision(0) << uang[i] << endl;
    }
}

int main() {
    Transaksi data[MAKS];
    int jumlah = 0;
    int menu;

    do {
        cout << endl << "========== PROGRAM BANK SAMPAH ==========" << endl;
        cout << "1. Setor sampah" << endl;
        cout << "2. Laporan setoran" << endl;
        cout << "3. Saldo nasabah" << endl;
        cout << "4. Rekap per jenis sampah" << endl;
        cout << "5. Keluar" << endl;
        menu = (int)bacaAngka("Pilih menu (1-5): ");

        switch (menu) {
            case 1: setorSampah(data, jumlah); break;
            case 2: tampilLaporan(data, jumlah); break;
            case 3: cariSaldo(data, jumlah); break;
            case 4: rekapJenis(data, jumlah); break;
            case 5: cout << endl << "Terima kasih telah menabung di bank sampah!" << endl; break;
            default: cout << "Menu tidak valid!" << endl;
        }
    } while (menu != 5);

    return 0;
}