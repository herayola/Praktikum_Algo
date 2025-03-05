#include <iostream>
using namespace std;

struct mahasiswa {
    string nama;
    int nim;
    float ipk;
};

// menu pilihan
void menu(int &pilih) {
    cout << "1. Tampilkan mahasiswa" << endl;
    cout << "2. Cari berdasarkan NIM" << endl;
    cout << "3. Cari berdasarkan nama" << endl;
    cout << "4. Sort IPK mahasiswa (asc)" << endl;
    cout << "5. Sort IPK mahasiswa (desc)" << endl;
    cout << "6. Exit" << endl;
    cout << "Pilih menu : "; cin >> pilih;
    system("cls");
}

// menampilkan semua data mahasiswa
void tampil(mahasiswa *mhs) {
    for (int i = 0; i < 10; i++) {
        cout << "Nama : " << mhs[i].nama;
        cout << ", NIM : " << mhs[i].nim;
        cout << ", IPK : " << mhs[i].ipk << endl;
    }   
}

// cari nim dengan sequential search
void cariNIM(mahasiswa *mhs, int searchNIM) {
    bool ketemu;
    for (int i = 0; i < 10; i++) {
        if (searchNIM == mhs[i].nim) {
            cout << "Data ditemukan\n";
            cout << "Name : " << mhs[i].nama << endl;
            cout << "NIM  : " << mhs[i].nim << endl;
            cout << "IPK  : " << mhs[i].ipk << endl;
        ketemu = true;
        }
    }    
    if (!ketemu) {
        cout << "Mahasiswa dengan NIM " << searchNIM << " tidak ditemukan" << endl;
        cout << endl;
    }
}

// cari nama dengan binary search
void cariNAMA(mahasiswa *mhs, string searchNAMA) {
    bool ketemu;
    int awal = 0, akhir = 10, tengah;
    while ((!ketemu) && awal <= akhir) {
        tengah = (awal + akhir) / 2;
        if (searchNAMA == mhs[tengah].nama) {
            ketemu = true;
        } else if (searchNAMA < mhs[tengah].nama) {
            akhir = tengah - 1;
        } else {
            awal = tengah + 1;
        }
    }
    if (ketemu == 0) {
        cout << "Mahasiswa dengan nama " << searchNAMA << " tidak ditemukan" << endl;
    } else {
        cout << "Data ditemukan\n";
        for (int i = 0; i < 10; i++) {
            if (searchNAMA == mhs[i].nama) {
                cout << "Name : " << mhs[i].nama << endl;
                cout << "NIM  : " << mhs[i].nim << endl;
                cout << "IPK  : " << mhs[i].ipk << endl;
            }
        }
    }
}

// sort ipk (asc) dengan quicksort
void quick_sort(mahasiswa *mhs, int awal, int akhir) {
    int low = awal, high = akhir;
    float pivot = mhs[(awal + akhir) / 2].ipk;
    do {
        while (mhs[low].ipk < pivot) low++;
        while (mhs[high].ipk > pivot) high--;
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

int main() {
    mahasiswa mhs[10];
    int pilih, searchNIM;
    string searchNAMA;
    bool ketemu = false;

    mhs[0] = {"Budi", 124240001, 3.5};
    mhs[1] = {"Andi", 124240002, 3.6};
    mhs[2] = {"Caca", 124240003, 3.7};
    mhs[3] = {"Dedi", 124240004, 3.8};
    mhs[4] = {"Euis", 124240005, 3.9};
    mhs[5] = {"Feri", 124240006, 3.4};
    mhs[6] = {"Gina", 124240007, 3.3};
    mhs[7] = {"Hadi", 124240008, 3.2};
    mhs[8] = {"Ika" , 124240009, 3.1};
    mhs[9] = {"Joko", 124240010, 3};
    
    do {
        menu(pilih);
        switch (pilih) {
        case 1:
            tampil(mhs);
            cout << endl;
            break;
        case 2:
            cout << "Masukkan NiM yang dicari: "; cin >> searchNIM;
            cariNIM(mhs, searchNIM);
            cout << endl;
            break;
        case 3: 
            cout << "Masukkan nama yang dicari: "; cin >> searchNAMA;
            cariNAMA(mhs, searchNAMA);
            cout << endl;
            break;
        case 4: 
            cout << "Daftar mahasiswa" << endl;
            quick_sort(mhs, 0, 9);
            tampil(mhs);
            cout << "Daftar mahasiswa telah diurutkan berdasarkan IPK (ascending)" << endl;
            cout << endl;
            break;
        case 5:
        cout << "Daftar mahasiswa" << endl;
            for (int i = 0; i < 10; i++){
                for (int j = 0; j < 10 - 1 - i; j++){
                    if (mhs[j].ipk < mhs[j+1].ipk){
                        swap(mhs[j], mhs[j+1]);
                    }
                }
            }
            tampil(mhs);
            cout << "Daftar mahasiswa telah diurutkan berdasarkan IPK (descending)" << endl;
            cout << endl;
            break;
        default:
            break;
        }
    } while (pilih < 6);
    
    return 0;
}