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
