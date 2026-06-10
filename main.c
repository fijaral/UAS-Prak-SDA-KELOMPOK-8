#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Struktur kotak (baris dan kolom) untuk daftar isi sistem absensi:
typedef struct Node {
    char npm[15];
    char nama[50];
    char jurusan[50];
    int semester;
    char tanggal[11];
    char kunciSort[11];
    struct Node *next;
} Node;

// Struktur stack untuk undo pada daftar isi sistem absensi:
typedef struct {
    char npm[15];
    char nama[50];
    char jurusan[50];
    int semester;
    char tanggal[11];
} StackItem;

#define MAX_STACK 100
StackItem undoStack[MAX_STACK];
int topUndo = -1;

// Menaruh data absensi terbaru ke stack untuk undo:
void pushUndo(char *npm, char *nama, char *jurusan, int semester, char *tanggal) {
    if (topUndo < MAX_STACK - 1) {
        topUndo++;
        strcpy(undoStack[topUndo].npm, npm);
        strcpy(undoStack[topUndo].nama, nama);
        strcpy(undoStack[topUndo].jurusan, jurusan);
        undoStack[topUndo].semester = semester;
        strcpy(undoStack[topUndo].tanggal, tanggal);
    }
}

// Mengambil data absensi terbaru dari stack untuk dihapus:
StackItem popUndo() {
    StackItem item;
    strcpy(item.npm, "");
    strcpy(item.nama, "");
    strcpy(item.jurusan, "");
    item.semester = 0;
    strcpy(item.tanggal, "");
    if (topUndo >= 0) {
        item = undoStack[topUndo];
        topUndo--;
    }
    return item;
}

// Membuat kotak baru untuk menyimpan setiap pembuatan / penambahan data baru:
Node* createNode(char *npm, char *nama, char *jurusan, int semester, char *tanggal) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->npm, npm);
    strcpy(newNode->nama, nama);
    strcpy(newNode->jurusan, jurusan);
    newNode->semester = semester;
    strcpy(newNode->tanggal, tanggal);
    sprintf(newNode->kunciSort, "%.4s-%.2s-%.2s", tanggal+6, tanggal+3, tanggal);
    newNode->next = NULL;
    return newNode;
}

// Menambahkan data baru ke urutan paling terakhir:
void tambahBelakang(Node **head, char *npm, char *nama, char *jurusan, int semester, char *tanggal) {
    Node *newNode = createNode(npm, nama, jurusan, semester, tanggal);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}


// Menghapus data tertentu pada sistem absensi:
void hapusData(Node **head, char *npm, char *nama, char *jurusan, int semester, char *tanggal) {
    Node *temp = *head;
    Node *prev = NULL;
    while (temp != NULL && (strcmp(temp->npm, npm) != 0 || strcmp(temp->tanggal, tanggal) != 0)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

// Menampilkan semua data dalam bentuk tabel:
void tampilkan(Node *head) {
    if (head == NULL) {
        printf("\nBelum ada data.\n");
        return;
    }
    printf("\n+-----------------+---------------------------+--------------------------+----------+--------------------+\n");
    printf("| %-15s | %-25s | %-24s | %-8s | %-18s |\n", "NPM", "Nama", "Jurusan", "Semester", "Tanggal");
    printf("+-----------------+---------------------------+--------------------------+----------+--------------------+\n");
    Node *temp = head;
    while (temp != NULL) {
        printf("| %-15s | %-25s | %-24s | %-8d | %-18s |\n",
            temp->npm, temp->nama, temp->jurusan, temp->semester, temp->tanggal);
        temp = temp->next;
    }
    printf("+-----------------+---------------------------+--------------------------+----------+--------------------+\n");
}

// Membersihkan memori saat program selesai:
void freeLinkedList(Node **head) {
    Node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Menyalin data ke array biar aman:
void linkedListToArray(Node *head, Node arr[], int *size) {
    *size = 0;
    Node *temp = head;
    while (temp != NULL) {
        strcpy(arr[*size].npm, temp->npm);
        strcpy(arr[*size].nama, temp->nama);
        strcpy(arr[*size].jurusan, temp->jurusan);
        arr[*size].semester = temp->semester;
        strcpy(arr[*size].tanggal, temp->tanggal);
        strcpy(arr[*size].kunciSort, temp->kunciSort);
        (*size)++;
        temp = temp->next;
    }
}

// Memindahkan data dari array balik ke linked list:
void arrayToLinkedList(Node **head, Node arr[], int size) {
    freeLinkedList(head);
    for (int i = 0; i < size; i++) {
        tambahBelakang(head, arr[i].npm, arr[i].nama, arr[i].jurusan, arr[i].semester, arr[i].tanggal);
    }
}


// Fungsi insertion sort (untuk urutan tanggal):
void insertionSortTanggal(Node arr[], int size) {
    int i, j;
    Node key;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && strcmp(arr[j].kunciSort, key.kunciSort) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Fungsi bubble sort (untuk urutan nama):
void bubbleSortNama(Node arr[], int size) {
    int i, j;
    Node temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (strcasecmp(arr[j].nama, arr[j + 1].nama) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Menyimpan data ke dalam file absensi.txt:
void simpanKeFile(Node *head) {
    FILE *file = fopen("absensi.txt", "w");
    if (file == NULL) {
        printf("Gagal menyimpan file!\n");
        return;
    }
    Node *temp = head;
    while (temp != NULL) {
        fprintf(file, "%s;%s;%s;%d;%s\n", temp->npm, temp->nama, temp->jurusan, temp->semester, temp->tanggal);
        temp = temp->next;
    }
    fclose(file);
}

// Membaca data dari file absensi.txt:
void bacaDariFile(Node **head) {
    FILE *file = fopen("absensi.txt", "r");
    if (file == NULL) {
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        char npm[15], nama[50], jurusan[50], tanggal[11];
        int semester;
        char *token = strtok(line, ";");
        if (!token) continue;
        strcpy(npm, token);

        token = strtok(NULL, ";");
        if (!token) continue;
        strcpy(nama, token);

        token = strtok(NULL, ";");
        if (!token) continue;
        strcpy(jurusan, token);

        token = strtok(NULL, ";");
        if (!token) continue;
        semester = atoi(token);

        token = strtok(NULL, "\n");
        if (!token) continue;
        strcpy(tanggal, token);

        tambahBelakang(head, npm, nama, jurusan, semester, tanggal);
    }
    fclose(file);
}

// Program sistem absensi dengan fitur riwayat undo:
int main() {
    Node *head = NULL;
    int pilihan;
    char npm[15], nama[50], jurusan[50], tanggal[11];
    int semester;
    Node arr[100];
    int size;

    bacaDariFile(&head);

    do {
        printf("\n===== SISTEM ABSENSI =====\n");
        printf("1. Tambah Absensi\n");
        printf("2. Tampilkan Semua Data\n");
        printf("3. Undo\n");
        printf("4. Urutkan berdasarkan Tanggal\n");
        printf("5. Urutkan berdasarkan Nama\n");
        printf("6. Tampilkan Urutan Asli\n");
        printf("0. Keluar & Simpan\n");
        printf("Pilih menu: ");

        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                printf("Masukkan NPM: ");
                scanf(" %[^\n]s", npm);

                printf("Masukkan Nama Lengkap: ");
                scanf(" %[^\n]s", nama);

                printf("Masukkan Jurusan: ");
                scanf(" %[^\n]s", jurusan);

                printf("Masukkan Semester: ");
                scanf("%d", &semester);

                printf("Masukkan Tanggal (DD-MM-YYYY): ");
                scanf(" %[^\n]s", tanggal);

                tambahBelakang(&head, npm, nama, jurusan, semester, tanggal);
                pushUndo(npm, nama, jurusan, semester, tanggal); // Simpan history
                simpanKeFile(head); // Simpan urutan ASLI ke file
                printf("Data berhasil ditambahkan!\n");
                break;

            case 2:
                tampilkan(head);
                break;

            case 3: // undo
                {
                    StackItem item = popUndo();
                    if (strlen(item.npm) > 0) {
                        printf("Undo: Menghapus %s - %s\n", item.npm, item.nama);
                        hapusData(&head, item.npm, item.nama, item.jurusan, item.semester, item.tanggal);
                        simpanKeFile(head); // Update file setelah undo
                        printf("Undo berhasil!\n");
                    } else {
                        printf("Tidak ada aksi yang bisa di-undo.\n");
                    }
                }
                break;

            case 4:
                linkedListToArray(head, arr, &size);
                if (size > 0) {
                    insertionSortTanggal(arr, size);
                    arrayToLinkedList(&head, arr, size);
                    printf("Data diurutkan berdasarkan Tanggal!\n");
                    tampilkan(head);
                    // // hapus baris ini -> topUndo = -1;
                } else {
                    printf("Tidak ada data.\n");
                }
                break;

            case 5:
                linkedListToArray(head, arr, &size);
                if (size > 0) {
                    bubbleSortNama(arr, size);
                    arrayToLinkedList(&head, arr, size);
                    printf("Data diurutkan berdasarkan Nama!\n");
                    tampilkan(head);
                    // // hapus baris ini -> topUndo = -1;
                } else {
                    printf("Tidak ada data.\n");
                }
                break;

            case 6: // kembali ke urutan asli
                printf("Mengembalikan ke urutan input asli...\n");
                freeLinkedList(&head);
                bacaDariFile(&head); // baca ulang dari file asli
                tampilkan(head);
                break;

            case 0:
                simpanKeFile(head);
                printf("Terima kasih! Program selesai.\n");
                freeLinkedList(&head);
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }

    } while(pilihan != 0);

    return 0;
}
