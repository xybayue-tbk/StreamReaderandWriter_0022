#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;
    string namaFile = "DB_SumberjayaElektronik.txt";

public:
    TokoElektronik() {
        etalase[0] = "Laptop Gaming Solo";
        etalase[1] = "Monitor 24 Inch";
        etalase[2] = "Keyboard Mechanical";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        } catch (const out_of_range& e) {
            string pesanError =
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!";
            throw runtime_error(pesanError);
        }
    }

    void tampilkanGudang() {
        ifstream file(namaFile);

        cout << "\n=== Daftar Barang di Gudang (DB_SumberjayaElektronik.txt) ===\n";

        if (!file.is_open()) {
            cout << "[ Gudang masih kosong / file belum dibuat ]\n";
            return;
        }

        string baris;
        int nomor = 1;
        bool adaIsi = false;

        while (getline(file, baris)) {
            cout << nomor << ". " << baris << "\n";
            nomor++;
            adaIsi = true;
        }

        if (!adaIsi)
            cout << "[ Gudang kosong ]\n";

        file.close();
    }

    void tambahBarang(const string& namaBarang) {
        ofstream file(namaFile, ios::app);

        if (file.is_open()) {
            file << namaBarang << "\n";
            file.close();

            cout << ">> Sukses: Barang '"
                 << namaBarang
                 << "' ditambahkan ke gudang!\n";
        } else {
            cout << ">> Error: Gagal membuka file gudang.\n";
        }
    }

    vector<string> muatSemuaBarang() {
        vector<string> daftarBarang;
        ifstream file(namaFile);
        string baris;

        if (file.is_open()) {
            while (getline(file, baris)) {
                daftarBarang.push_back(baris);
            }
            file.close();
        }

        return daftarBarang;
    }

    void updateBarang(int indeksBaris, const string& namaBaru) {
        vector<string> daftar = muatSemuaBarang();

        if (indeksBaris < 1 || indeksBaris > daftar.size()) {
            cout << ">> Error: Nomor barang tidak valid!\n";
            return;
        }

        daftar[indeksBaris - 1] = namaBaru;

        ofstream file(namaFile, ios::trunc);

        if (file.is_open()) {
            for (const string& barang : daftar) {
                file << barang << "\n";
            }

            file.close();
            cout << ">> Sukses: Data barang berhasil diperbarui!\n";
        }
    }

    void hapusBarang(int indeksBaris) {
        vector<string> daftar = muatSemuaBarang();

        if (indeksBaris < 1 || indeksBaris > daftar.size()) {
            cout << ">> Error: Nomor barang tidak valid!\n";
            return;
        }

        daftar.erase(daftar.begin() + (indeksBaris - 1));

        ofstream file(namaFile, ios::trunc);

        if (file.is_open()) {
            for (const string& barang : daftar) {
                file << barang << "\n";
            }

            file.close();
            cout << ">> Sukses: Data barang berhasil dihapus!\n";
        }
    }
};

int main() {
    TokoElektronik toko;
    int pilihan;

    do {
        toko.tampilkanGudang();

        cout << "\n========================================\n";
        cout << "      TOKO SUMBERJAYA ELEKTRONIK\n";
        cout << "          Pemilik : Nanang\n";
        cout << "========================================\n";

        cout << "1. Tambah Barang ke Gudang\n";
        cout << "2. Update Barang di Gudang\n";
        cout << "3. Hapus Barang dari Gudang\n";
        cout << "4. Simulasi Etalase\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = -1;
        }

        cin.ignore();

        switch (pilihan) {

        case 1: {
            string nama;

            cout << "\nMasukkan nama barang baru: ";
            getline(cin, nama);

            toko.tambahBarang(nama);
            break;
        }

        case 2: {
            int id;
            string namaBaru;

            cout << "\nMasukkan nomor barang yang ingin diubah: ";
            cin >> id;
            cin.ignore();

            cout << "Masukkan nama barang yang baru: ";
            getline(cin, namaBaru);

            toko.updateBarang(id, namaBaru);
            break;
        }

        case 3: {
            int id;

            cout << "\nMasukkan nomor barang yang ingin dihapus: ";
            cin >> id;
            cin.ignore();

            toko.hapusBarang(id);
            break;
        }

        case 4: {
            cout << "\n=== Menjalankan Simulasi2Etalase ===\n";

            cout << "Mencoba mengambil barang di rak indeks ke-1...\n";

            try {
                string barangSukses = toko.ambilProduk(1);
                cout << ">> Berhasil! Barang yang didapat: "
                     << barangSukses << "\n";
            }
            catch (const exception& e) {
                cout << ">> Error: "
                     << e.what() << "\n";
            }

            cout << "\nMencoba mengambil barang di rak indeks ke-5...\n";

            try {
                string barangGagal = toko.ambilProduk(5);
                cout << ">> Berhasil! Barang yang didapat: "
                     << barangGagal << "\n";
            }
            catch (const exception& e) {
                cout << ">> Error Tertangkap: "
                     << e.what() << "\n";
            }

            cout << "========================================\n";
            break;
        }

        case 0:
            cout << "\nTerima kasih telah menggunakan sistem "
                 << "Sumberjaya Elektronik.\n";
            cout << "Sampai jumpa, Pak Nanang!\n";
            break;

        default:
            cout << "\n>> Error: Pilihan tidak valid.\n";
            break;
        }

    } while (pilihan != 0);

    return 0;
}