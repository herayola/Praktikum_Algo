#include <iostream>
using namespace std;

// informasi video
struct video 
{
    string judul;
    int durasi;
    string status;
};

// struktur pohon
struct Node 
{
    video data;
    Node *left;
    Node *right;

    // konstruktor
    Node(video data) {
        this->data = data; // node data diisi dengan parameter data
        left = nullptr;
        right = nullptr;
    }
};

// struct undo
struct Undo
{
    string aksi;
    video data;
    Undo *next;
};
struct Undo *topUndo = nullptr;

// penyimpanan aksi
void simpanUndo(string aksi, video data) {
    struct Undo *baru = new struct Undo;
    baru->aksi = aksi;
    baru->data = data;
    baru->next = topUndo;
    topUndo = baru;
}

void menu() {
    cout << "~ ~ | IDLIX TUBE | ~ ~\n\n";
    cout << "1. Tambah Video\n";
    cout << "2. Tampilkan Daftar Video\n";
    cout << "3. Tambahkan ke Playlist\n";
    cout << "4. Tonton Video\n";
    cout << "5. Riwayat Tontonan\n";
    cout << "6. Hapus Video\n";
    cout << "7. Undo Tindakan Terakhir\n";
    cout << "0. Keluar\n";
}

// menyimpan dalam struktur pohon
void tambahVideo(Node *&root, video data) 
{
    // jika akar masih kosong
    if (root == nullptr) 
    {
        root = new Node(data);
        return;
    }

    // jika akar sudah ada data
    Node *current = root;
    while (true) 
    {
        if (data.judul < current->data.judul) 
        {
            if (current->left == nullptr) {
                current->left = new Node(data);
                return;
            }
            current = current->left;
        } 
        else 
        {
            if (current->right == nullptr) {
                current->right = new Node(data);
                return;
            }
            current = current->right;
        }
    }
} 

// Pengecekan duplikat judul 
video *cekDuplikat(Node *root, string judul) 
{
    Node *current = root;
    while (current != nullptr) 
    {
        if (judul == current->data.judul) 
        { 
            return &current->data;
        } 
        else if(judul < current->data.judul) 
        {
            current = current->left;
        } 
        else 
        {
            current = current->right;
        }
    }
    return nullptr;
}

// cari video
void search (Node *root, string target) 
{   
    cout << endl;
    Node *curr = root;
    while (curr) 
    {
        if (curr->data.judul == target) 
        {
            // tampilan
            cout << curr->data.judul << endl;
            cout << "------------------------------------------\n";
            cout << curr->data.durasi << " menit\n";
            cout << curr->data.status << endl;
            cout << endl;
            system("pause");
            return;
        }
        curr = (target < curr->data.judul) ? curr->left : curr->right;
    }
    cout << target << " tidak ditemukan\n\n";
    system("pasue");
}

void loopTampil(Node *root) {
    if (root == nullptr) return;

    // urut ascending dengan inorder
    loopTampil(root->left);

    // tampilan data
    cout << root->data.judul << endl;
    cout << "------------------------------------------\n";
    cout <<"Durasi  : " << root->data.durasi << " menit\n";
    cout << "Status : " << root->data.status << endl << endl;

    loopTampil(root->right);
}

void tampil(Node *root) {
    if (root == nullptr) 
    {   
        cout << "Video dalam daftar kosong.\n";
        return;
    }

    loopTampil(root);

    // mencari berdasarkan judul
    char choice;
    string target;
    cout << "Apakah anda ingin mencari video? (y/t) : ";
    cin >> choice;
    system("cls");

    if (choice == 'y' || choice == 'Y')
    {   
        cin.ignore();
        cout << "Masukkan Judul video yang ingin dicari : ";
        getline(cin, target); 
        search(root, target);
    } 

    return;
}

// masuk ke riwayat dengan seperti stack
Node *top = nullptr;
void pushRiwayat (video data) 
{   
    Node *newNode = new Node(data);

    if (top == nullptr) {
        top = newNode;
    } else {
        top->right = newNode;
        top = newNode;
    }
}

// menampilkan riwayat
void tampilRiwayat() {
    if (top == nullptr) 
    {
        cout << "Riwayat tontonan kosong.\n";
        return;
    }

    Node *bantu = top;
    while (bantu != nullptr) {
        // nampilin video yang selesai diputar
        cout << bantu->data.judul << " - (" << bantu->data.durasi <<" menit)"<< endl;

        // terakhir ditonton di bagian atas
        bantu = bantu->left;
    }
}

Node *depan = nullptr;
Node *belakang = nullptr;
void enqueue(video data) {
    Node *newNode = new Node(data);

    if(depan == nullptr) 
    {
        depan = belakang = newNode;  
        newNode->data.status = "Sedang diputar"; // masuk pertama = sedang diputar
    } 
    else 
    {
        belakang->right = newNode; 
        belakang = newNode; 
        newNode->data.status = "Dalam antrean"; // video yg masuk playlist = dalam antrean
    }
}

// pencarian di playlist
bool cekPlaylist (string cek) {
    Node *bantu = depan;
    while (bantu != nullptr) {
        if (bantu->data.judul == cek) {
            return true;
        }
        bantu = bantu->right;
    }
    return false;
}

void tampilDaftar(Node *root) 
{
    if (root == nullptr) return;
    
    // tampil daftar judul sama menit
    tampilDaftar(root->left);
    cout << root->data.judul << " - (" << root->data.durasi <<" menit)"<< endl;
    tampilDaftar(root->right);
}

void tambahKePlaylist(Node *root) 
{   
    if (root == nullptr)
    {
        cout << "Daftar video kosong.\n";
        return;
    }

    tampilDaftar(root);
    cout << endl;

    // pilih tambah ke playlist
    string pilih; 
    cin.ignore();
    cout << "Masukkan judul video yang ingin ditambahkan : ";
    getline(cin, pilih);
    
    // cek judul ada di daftar atau tidak
    Node *bantu = root;
    while (bantu)
    {
        if (bantu->data.judul == pilih) break; 
        bantu = (pilih < bantu->data.judul) ? bantu->left : bantu->right;
    }


    if (bantu == nullptr)
    {
        cout << "Video tidak ditemukan.\n";
        return;
    }
    
    Node *cek = depan;
    while (cek)
    {   
        if (cekPlaylist(cek->data.judul) || cek->data.status == "Sedang diputar")
        {
            cout << pilih << " Sudah ada dalam playlist.\n";
            return;
        }
        else 
        {
            cek = cek->right;
        }
    }
    
    enqueue(bantu->data); 
    simpanUndo("playlist", bantu->data);
    cout << "video berhasil ditambahkan ke playlist.\n";
}

void tonton(Node *root) {
    if (depan == nullptr)
    {
        cout << "Tidak ada video dalam antrean.\n";
        return;
    }

    Node *diputar = depan;
    

    // geser antrean
    depan = depan->right;
    if (depan == nullptr) {
        belakang = nullptr;
    }

    diputar->data.status = "Tersedia"; // ubah status kembali
    cout << "Memutar video " << diputar->data.judul << endl;

    // masuk ke riwayat
    pushRiwayat(diputar->data);

    simpanUndo("tonton", diputar->data);
    diputar = nullptr;
    delete diputar;

    // ubah status
    if (depan != nullptr) {
        depan->data.status = "Sedang diputar";
    }    
}

void hapus (Node *&root, string target) {
    char choice;

    if (root == nullptr)
    {
        cout << "Daftar video kosong.\n";
        return;        
    }

    if (target < root->data.judul)
    {
        hapus(root->left, target);
    }
    else if (target > root->data.judul)
    {
        hapus(root->right, target);
    }
    else
    {
        // menemukan data yang ingin dihapus dan disimpan ke temp
        Node *temp = root;
        if (root->left == nullptr)
        {
            root = root->right;
        }
        else if (root->right == nullptr)
        {
            root = root->left;
        }
        else
        {   
            // jika punya 2 anak
            Node *successor = root->right;
            while (successor->left != nullptr)
                successor = successor->left;
            root->data = successor->data;
            hapus(root->right, successor->data.judul);
            return;
        }
        if (temp->data.status == "Sedang diputar" || cekPlaylist(temp->data.judul))
        {
            cout << "Apakah yakin untuk menghapus video ini? (y/t) : ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                simpanUndo("hapus", temp->data);
                delete temp;
                cout << "\n\nBerhasil dihapus!\n";
                return;
            }
        }
        simpanUndo("hapus", temp->data);
        delete temp;
        cout << "\n\nBerhasil dihapus!\n";
        return;
    }
}

void Undo(Node *&root) 
{
    if (topUndo == nullptr)
    {
        cout << "Tidak ada tindakan sebelumnya.\n";
        return;
    }
    
    struct Undo *aksi = topUndo;
    topUndo = topUndo->next;

    video data = aksi->data;

    // hapus dari pohon
    if (aksi->aksi == "tambah") 
    {
        cout << "Undo : membatalkan penambahan video ``" << data.judul << "``\n";
        hapus(root, data.judul);
    }
    else if (aksi->aksi == "hapus")
    {
        cout << "Undo : membatalkan penghapusan video ``" << data.judul << "``\n";
        tambahVideo(root, data);
    }
    else if (aksi->aksi == "playlist")
    {
        cout << "Undo : membatalkan penambahan video ``" << data.judul << "`` ke dalam playlist\n";
        Node* prev = nullptr;
        Node* curr = depan;

        while (curr != nullptr) 
        {
            if (curr->data.judul == data.judul) 
            {
                if (prev == nullptr) {
                    depan = curr->right;
                } else {
                    prev->right = curr->right;
                }

                if (curr == belakang) {
                    belakang = prev;
                }

                delete curr;
                break;
            }
            prev = curr;
            curr = curr->right;
        }

        // ubah status kembali
        Node* cari = root;
        while (cari) {
            if (cari->data.judul == data.judul) {
                cari->data.status = "Tersedia";
                break;
            }
            cari = (data.judul < cari->data.judul) ? cari->left : cari->right;
        }
    }
    else if (aksi->aksi == "tonton") 
    {
        cout << "Undo : membatalkan menonton video ``" << data.judul << "``\n";

        // Keluarkan dari riwayat
        if (top != nullptr && top->data.judul == data.judul) {
            Node* hapusTop = top;
            top = top->left;
            delete hapusTop;
        }

        // Tambahkan ke depan antrian playlist
        Node* newNode = new Node(data);
        newNode->right = depan;
        depan = newNode;
        if (belakang == nullptr) belakang = newNode;

        newNode->data.status = "Sedang diputar";

        // Geser yang tadinya sedang diputar jadi antrean
        if (depan->right != nullptr)
            depan->right->data.status = "Dalam antrean";
    }

    delete aksi;
}


int main() 
{
    int pilih;
    Node *root = nullptr;
    video data;
    string target;

    do 
    {
        menu();
        cout << "Masukkan menu yang dipilih : "; cin >> pilih;
        system("cls");
        
        cout << "~ ~ | IDLIX TUBE | ~ ~\n\n";
        switch (pilih) {
        case 1:
            cin.ignore();
            cout << "Lengkapi detail video yang ingin ditambahkan\n";
            cout << "Judul          : "; getline(cin, data.judul);
            cout << "Durasi (menit) : "; cin >> data.durasi;
            data.status = "Tersedia";

            // judul gaboleh sama
            if (cekDuplikat(root, data.judul) != nullptr) 
            {
                cout << "video dengan judul " << data.judul << " sudah ada.\n";
                break;
            }
            
            tambahVideo(root, data);
            simpanUndo("tambah", data);
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 2:
            tampil(root);
            cout << endl;
            break;
        case 3:
            tambahKePlaylist(root);
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 4:
            tonton(root);
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 5:
            tampilRiwayat();
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 6:
            cin.ignore();
            cout << "Judul video yang ingin dihapus : ";
            getline(cin, target);
            cout << endl;
            hapus(root, target);
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 7:
            Undo(root);
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 0: 
            cout << "Terima kasih, sampai jumpa lagi.\n";
            break;
        default: 
            cout << "Pilihan tidak valid!\n";
            cout << endl;
            system("pause");
            system("cls");
        }
    } while (pilih != 0);

    return 0;
}