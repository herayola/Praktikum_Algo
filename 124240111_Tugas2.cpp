#include <iostream>
using namespace std;

struct node {
    char nama[75];
    int total, jenis;
    node *prev, *next;
};

node *depan, *belakang;
node *awal, *akhir;

void tampilMenu() {
    cout << "Selamat Datang\n";
    cout << "Di Toko Roti Manis Lezat\n";
    cout << "1. Ambil Antrean\n";
    cout << "2. Layani Pembeli\n";
    cout << "3. Tampilkan Pesanan\n";
    cout << "4. Batalkan Pesanan\n";
    cout << "5. Tampilkan History Pesanan\n";
    cout << "6. Keluar\n";
}

bool antreanKosong() {
    return depan == NULL;
}

void ambilAntrean() {
    node *data = new node;

    cout << "Toko Roti Manis Lezat\n\n";
    cout << "Masukkan detail pemesanan\n";

    // input pesanan
    cin.ignore();
    cout << "Nama : "; cin.getline(data->nama, 75);
    cout << "Jenis Roti:\n";
    cout << "1. Roti Kering\n";
    cout << "2. Roti Basah\n";
    cout << "3. Roti Lapis\n";
    cout << "Jenis roti yang dipilih : "; cin >> data->jenis;
    switch (data->jenis) {
    case 1:
        data->total = 10000;
        cout << "Total harga : " << data->total << endl;
        break;
    case 2:
        data->total = 15000;
        cout << "Total harga : " << data->total << endl;
        break;
    case 3:
        data->total = 20000;
        cout << "Total harga : " << data->total << endl;
        break;
    default:
        break;
    }
    cout << endl;
    data->prev = NULL;
    data->next = NULL;

    // membuat antrean
    if(antreanKosong()) {
        depan = belakang = data;
        return;
    } else {
        belakang->next = data;
        data->prev = belakang;
        belakang = data;
    }
}

void history(node *selesai) {
    // memasukkan antrean yang telah dilayani
    if(awal == NULL) {
        awal = akhir = selesai;
    } else {
        akhir->next = selesai;
        selesai->prev = akhir;
        akhir = selesai;
    }
}

void layaniPembeli() {
    cout << "Toko Roti Manis Lezat\n\n";

    // hapus antrean awal
    if (antreanKosong()) {
        cout << "Tidak ada antrean\n";
        return;
    }

    node *hapus = depan;

    // hanya satu dalam antrean
    if (depan == belakang) { 
        depan = belakang = NULL;
    } else {
        depan = depan->next;
        depan->prev = NULL;
    }    

    // memutuskan hapus dengan antrean
    hapus->next = NULL;
    hapus->prev = NULL;

    // proses pesanan terdepan dari antrean dan disimpan ke riwayat
    history(hapus);
    cout << "1 pelanggan berhasil dilayani\n";
    cout << endl;
}

void tampilPesanan(int count) {
    cout << "Toko Roti Manis Lezat\n\n";

    // lihat daftar pesanan dalam antrean
    if (antreanKosong()) {
        cout << "Tidak ada pesanan\n";
        return;
    }

    // perulangan tampil
    node *bantu = depan;
    int i = 1;
    while (bantu != NULL) {
        cout << "Pesanan " << i << endl;
        cout << "Nama : " << bantu->nama << endl;
        switch (bantu->jenis) {
        case 1:
            cout << "Jenis roti : Roti Kering" << endl;
            break;
        case 2:
            cout << "Jenis roti : Roti Basah" << endl;
            break;
        case 3:
            cout << "Jenis roti : Roti Lapis" << endl;
            break;
        default:
            break;
        }
        cout << "Total harga : " << bantu->total << endl;
        bantu = bantu->next;
        cout << endl;
        i++;
    }
}

void batalPesan(int count) {
    cout << "Toko Roti Manis Lezat\n\n";

    // pengecekan antrean kosong
    if (antreanKosong()) {
        cout << "Tidak ada pesanan\n";
        return;
    }

    // hapus antrean akhir
    node *hapus = belakang;
    belakang = belakang->prev;
    belakang->next = NULL;
    delete hapus;
    cout << "1 pesanan telah dibatalkan\n";
}

void tampilHistory(int jumlah) {
    cout << "Toko Roti Manis Lezat\n\n";

    // liat daftar pesanan dalam history
    if(awal == NULL) {
        cout << "Belum melayani pesanan\n";
        return;
    }

    node *bantu = awal;
    int i = 1;
    while (bantu != NULL) {
        cout << "Dilayani ke-" << i << endl;
        cout << "Nama : " << bantu->nama << endl;
        switch (bantu->jenis) {
        case 1:
            cout << "Jenis roti : Roti Kering" << endl;
            break;
        case 2:
            cout << "Jenis roti : Roti Basah" << endl;
            break;
        case 3:
            cout << "Jenis roti : Roti Lapis" << endl;
            break;
        default:
            break;
        }
        cout << "Total harga : " << bantu->total << endl;
        bantu = bantu->next;
        cout << endl;
        i++;
    }
}

int main() {
    int pilih, count = 0, jumlah = 0;
    FILE *pesanan;
    do {
        tampilMenu();
        cout << "Masukkan pilihan : ";
        cin >> pilih;
        system("pause");
        system("cls");
        switch (pilih){
        case 1:
            ambilAntrean();
            cout << "Terima kasih telah memesan!\n";
            count = count + 1;
            system("pause");
            system("cls");
            break;
        case 2:
            layaniPembeli();
            count--;
            jumlah = jumlah + 1;
            system("pause");
            system("cls");
            break;
        case 3:
            tampilPesanan(count);
            system("pause");
            system("cls");
            break;
        case 4:
            batalPesan(count);
            count--;
            system("pause");
            system("cls");
            break;
        case 5:
            tampilHistory(jumlah);
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    } while (pilih != 6);
    
    return 0;
}
