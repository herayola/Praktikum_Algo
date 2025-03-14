#include <iostream>
#include <iomanip>
using namespace std;

struct mahasiswa {
    string nama, jurusan;
    int nim, tahun;
    float ipk;
};

void input(mahasiswa *mhs, int banyak) {
    FILE *data = fopen("MahasiswaData.dat", "ab");
    if (data == NULL){
        cout << "Proses gagal. Coba lagi!" << endl;
        exit(1);
    }
    for (int i = 0; i < banyak; i++) {
        cout << endl;
        cout << "Data ke-" << i + 1 << endl;
        cout << setfill('=') << setw(30) << "=" << setfill(' ') << endl; 
        cout << "NIM         : "; cin >> mhs[i].nim; cin.ignore();
        cout << "Nama        : "; getline(cin, mhs[i].nama);
        cout << "Jurusan     : "; getline(cin, mhs[i].jurusan); 
        cout << "Tahun Masuk : "; cin >> mhs[i].tahun; cin.ignore();
        mhs[i].ipk = 0.0;
        fwrite(&mhs[i], sizeof(mahasiswa), 1, data);
    }
    fclose(data);
}

int hitungData() {
    FILE *data = fopen("MahasiswaData.dat", "rb");
    if (data == NULL) return 0;
    fseek(data, 0, SEEK_END);
    int jumlah = ftell(data);
    fclose(data);
    return jumlah / sizeof(mahasiswa);
}

void quick_sort(mahasiswa *mhs, int awal, int akhir) {
    int low = awal, high = akhir;
    float pivot = mhs[(awal + akhir) / 2].nim;
    int temp;
    do {
        while (mhs[low].nim < pivot) {
            low++;
        }
        while (mhs[high].nim > pivot) {
            high--;
        }
        if (low <= high) {
            swap(mhs[low], mhs[high]);
            low++;
            high--;
        }
    } while (low <= high);
    if (awal < high) {
        quick_sort(mhs, awal, high);
    }
    if (low < akhir) {
        quick_sort(mhs, low, akhir);
    }
}

void tampil(mahasiswa *mhs, int banyak){
    FILE *data = fopen("MahasiswaData.dat","rb");
    if(data == NULL) {
        cout << "Data kosong." << endl;
        exit(1);
    }
    fread(mhs, sizeof(mahasiswa), banyak, data);
    fclose(data);
    quick_sort(mhs, 0, banyak-1);
    cout << setfill('=') << setw(95) << "=" << setfill(' ') << endl; 
    cout << "|No.|";
    cout << setiosflags(ios::right) << setw(9) << "NIM" << setw(7) << "|";
    cout << setiosflags(ios::right) << setw(17) << "Nama" << setw(15) << "|";
    cout << setiosflags(ios::right) << setw(15) << "Jurusan" << setw(9) << "|";
    cout << setiosflags(ios::right) << setw(10) << "Tahun Masuk" << setw(2) << "|";
    cout << setiosflags(ios::right) << setw(4) << "IPK" << setw(2) << "|\n";
    cout << setfill('=') << setw(95) << "=" << setfill(' ') << endl; 
    for (int i = 0; i < banyak; i++) {
        cout << "|" << setw(3) << i + 1 << "|";
        cout << setiosflags(ios::left) << setw(9) << mhs[i].nim << setw(7) << "|";
        cout << setiosflags(ios::left) << setw(17) << mhs[i].nama << setw(15) << "|";
        cout << setiosflags(ios::left) << setw(15) << mhs[i].jurusan << setw(9) << "|";
        cout << setiosflags(ios::left) << setw(10) << mhs[i].tahun << setw(2) << "|";
        cout << setiosflags(ios::left) << setw(4) << mhs[i].ipk << setw(2) << "|\n";
    }
}

void searchNIM(mahasiswa *mhs, int banyak, int cariNIM) {
    quick_sort(mhs, 0, banyak-1);
    bool ketemu = false;
    int awal = 0, akhir = banyak-1, tengah;
    while ((!ketemu) && awal <= akhir) {
        tengah = (awal + akhir) / 2;
        if (cariNIM == mhs[tengah].nim) {
            ketemu = true;
        } else if (cariNIM < mhs[tengah].nim) {
            akhir = tengah - 1;
        } else {
            awal = tengah + 1;
        }
    }
    if (ketemu == 0) {
        cout << "Mahasiswa dengan NIM " << cariNIM << " tidak ditemukan!" << endl;
    } else {
        cout << "Data ditemukan\n";
        for (int i = 0; i < banyak; i++) {
            if (cariNIM == mhs[i].nim) {
                cout << endl; 
                cout << "NIM         : " << mhs[i].nim << endl;
                cout << "Nama        : " << mhs[i].nama << endl;
                cout << "Jurusan     : " << mhs[i].jurusan << endl;
                cout << "Tahun Masuk : " << mhs[i].tahun << endl;
                cout << "IPK         : " << mhs[i].ipk << endl;
            }
        }
    }
}

void searchJurusan(mahasiswa *mhs, int banyak, string cariJurusan) {
    bool ketemu = false;
    for (int i = 0; i < banyak; i++) {
        if (cariJurusan == mhs[i].jurusan) {
            cout << "Data ditemukan\n";
            cout << setfill('=') << setw(30) << "=" << setfill(' ') << endl; 
            cout << "NIM         : " << mhs[i].nim << endl;
            cout << "Nama        : " << mhs[i].nama << endl;
            cout << "Jurusan     : " << mhs[i].jurusan << endl;
            cout << "Tahun Masuk : " << mhs[i].tahun << endl;
            cout << "IPK         : " << mhs[i].ipk << endl;
        ketemu = true;
        }
    }    
    if (!ketemu) {
        cout << "Mahasiswa dengan Jurusan " << cariJurusan << " tidak ditemukan!" << endl;
        cout << endl;
    }
}

void update(mahasiswa *mhs, int banyak, int cariNIM) {
    FILE *data = fopen("MahasiswaData.dat", "wb");
    if (data == NULL){
        cout << "Proses gagal. Coba lagi!" << endl;
        exit(1);
    }
    searchNIM(mhs, banyak, cariNIM);
    for (int i = 0; i < banyak; i++) {
        if (cariNIM == mhs[i].nim) {
            cout << setfill('=') << setw(30) << "=" << setfill(' ') << endl; 
            cout << "Masukkan IPK (baru) : "; cin >> mhs[i].ipk;
            if (mhs[i].ipk > 4.0){
                cout << "Kesalahan input. IPK hanya dalam rentang 0.0 - 4.0";
            }
            cout << endl;
        }
    }
    fwrite(mhs, sizeof(mahasiswa), banyak, data);
    fclose(data);
    cout << "IPK mahasiswa dengan NIM " << cariNIM << " berhasil diperbarui!" << endl;
}

void hapus(mahasiswa *mhs, int banyak, int cariNIM) {
    FILE *data = fopen("MahasiswaData.dat", "rb");
    FILE *temp = fopen("Temp.dat", "wb");
    for (int i = 0; i < banyak; i++) {
        fread(&mhs[i], sizeof(mahasiswa), 1, data);
        if (cariNIM != mhs[i].nim) {
            fwrite(&mhs[i], sizeof(mahasiswa), 1, temp);
        }
    }
    fclose(data);
    fclose(temp);
    remove("MahasiswaData.dat");
    rename("Temp.dat", "MahasiswaData.dat");
}

int main() {
    int pilih, banyak, cariNIM;
    string cariJurusan;
    mahasiswa *mhs = nullptr;

    do {
        cout << setfill('=') << setw(30) << "=" << setfill(' ') << endl;
        cout << "|" << setw(21) << "SmartCampus++" << setiosflags(ios::right) << setw(9) << "|\n";
        cout << setfill('=') << setw(30) << "=" << setfill(' ') << endl;
        cout << "1. Input data\n";
        cout << "2. Tampil data\n";
        cout << "3. Cari mahasiswa (NIM)\n";
        cout << "4. Cari mahasiswa (Jurusan)\n";
        cout << "5. Update IPK\n";
        cout << "6. Hapus data\n";
        cout << "7. Keluar\n";

        cout << setfill('=') << setw(30) << "=" << setfill(' ') << endl;
        cout << "Pilih menu : "; cin >> pilih;
        system("cls");

        switch (pilih) {
        case 1:
            cout << "Banyak data yang ingin ditambahkan : "; cin >> banyak;
            mhs = new mahasiswa[banyak];
            input(mhs, banyak);
            system("pause");
            system("cls");
            break;
        case 2:
            cout << endl;
            banyak = hitungData();
            tampil(mhs, banyak);
            system("pause");
            system("cls");
            break;
        case 3:
            cout << "Masukkan NIM yang dicari : "; cin >> cariNIM;
            searchNIM(mhs, banyak, cariNIM);
            system("pause");
            system("cls");
            break;
        case 4:
            cin.ignore();
            cout << "Masukkan jurusan yang dicari : "; getline(cin, cariJurusan);
            searchJurusan(mhs, banyak, cariJurusan);
            system("pause");
            system("cls");
            break;
        case 5:
            cout << "Masukkan NIM yang ingin diperbarui : "; cin >> cariNIM;
            update(mhs, banyak, cariNIM);
            system("pause");
            system("cls");
            break;
        case 6:
            cout << "Masukkan data NIM yang ingin dihapus : "; cin >> cariNIM;
            hapus(mhs, banyak, cariNIM);
            system("pause");
            system("cls");
            break;
        default:
            cout << "Terima kasih telah menggunakan SmartCampus++!\n";
            cout << "Semoga sukses dalam studi Anda!\n";
            delete[] mhs;
            system("pause");
            system("cls");
            break;
        }
    } while (pilih < 7);
    
    return 0;
}