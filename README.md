<div align="center">

# 📅 ABSENCEPAT
# Sistem Absensi Mahasiswa Berbasis CLI dengan Fitur Riwayat Undo

<br>

> **ABSENCEPAT** adalah program berbasis CLI yang mendigitalisasi proses pencatatan kehadiran mahasiswa menggunakan bahasa pemrograman C. Program ini dirancang untuk menyelesaikan masalah pencatatan absensi manual yang kaku, lambat direkapitulasi, dan rentan terhadap *human error* (seperti salah input status kehadiran). Pendekatan sistem ini cukup menarik secara teknis karena memadukan `Singly Linked List` untuk penyimpanan riwayat secara dinamis, `Stack` untuk mengeksekusi fitur *Undo* secara instan, serta meminjam struktur `Array` temporer untuk melakukan *sorting* tanpa merusak urutan asli pointer pada memori.
<br>

</div>

---

## ✨ Fitur Utama

| # | Fitur | Deskripsi |
|:---:|---|---|
| 1 | ➕ **Tambah Data Dinamis** | Mencatat kehadiran mahasiswa tanpa batasan kapasitas kaku berbasis Linked List |
| 2 | ⏪ **Undo Pembatalan Instan** | Mencegah kesalahan input (*human error*) dengan membatalkan aksi terakhir |
| 3 | 📅 **Smart Sorting Tanggal** | Urutkan riwayat absensi dari tanggal terlama ke terbaru |
| 4 | 🔤 **Smart Sorting Nama** | Urutkan rekapitulasi daftar mahasiswa secara alfabetis (A-Z) |
| 5 | 💾 **Persistensi Data** | Simpan dan baca riwayat secara otomatis ke *file* `absensi.txt` |

---

## 🛠 Arsitektur Sistem

### 🌳 Struktur Data

| Struktur Data | Digunakan Untuk |
|---|---|
| **Singly Linked List** | Menyimpan riwayat absensi mahasiswa secara dinamis tanpa batasan kapasitas memori kaku. |
| **Stack** | Mengelola riwayat *input* terakhir untuk fitur *Undo* (LIFO) pembatalan data. |
| **Array** | Wadah sementara (*buffer*) untuk menyalin dan mengeksekusi algoritma *sorting*. |

### ⚙️ Algoritma

| Algoritma | Kompleksitas | Digunakan Untuk |
|---|---|---|
| **Insertion Sort** | O(n^2) | Mengurutkan data absensi secara *real-time* berdasarkan tanggal/waktu masuk. |
| **Bubble Sort** | O(n^2) | Mengurutkan laporan akhir absensi secara alfabetis (A-Z) berdasarkan nama. |
| **Traversal** | O(n) | Menelusuri *linked list* untuk menampilkan tabel data dan proses simpan/baca *file* teks. |

---

## 💻 Cara Menjalankan

### Prasyarat

Pastikan *compiler* GCC telah terinstal: Windows (MinGW-w64), Linux (`build-essential`), atau macOS (`xcode-select --install`).

### Langkah Instalasi & Kompilasi

```bash
# 1. Clone repositori (opsional jika menggunakan git)
git clone [https://github.com/username/absencepat.git](https://github.com/username/absencepat.git)
cd absencepat

# 2. Kompilasi program
gcc main.c -o absensi

# 3. Jalankan program
./absensi      # Untuk Linux / macOS
.\absensi.exe  # Untuk Windows
```

---

## 🖥️ Tampilan Program

### Menu Utama

```text
===== SISTEM ABSENSI =====
1. Tambah Absensi
2. Tampilkan Semua Data
3. Undo
4. Urutkan berdasarkan Tanggal
5. Urutkan berdasarkan Nama
6. Tampilkan Urutan Asli
0. Keluar & Simpan
Pilih menu: _
```

---

## 👥 Tim Pengembang

ABSENCEPAT dikembangkan secara kolaboratif oleh Kelompok 8, mahasiswa Informatika, Fakultas Matematika dan Ilmu Pengetahuan Alam, Universitas Syiah Kuala.

<div align="center">

| Nama | Kontribusi Utama |
|---|---|
| M. Isyraq Akramin | Implementasi `struct`, inisialisasi `Stack` untuk *undo*, pembuatan *node*, penambahan data (*tambahBelakang*), dan penghapusan data (Line 1 - 83) |
| Farras Arthada Siregar | Implementasi traversal untuk tabel tampilan, pembersihan memori (*freeLinkedList*), konversi *Linked List* ke *Array* dan sebaliknya, serta *Insertion Sort* (Line 85 - 152) |
| M. Farras Munawwir | Implementasi *Bubble Sort*, *File I/O* (*simpanKeFile* dan *bacaDariFile*), dan persiapan fungsi `main` (Line 154 - 232) |
| Nabil Al Fijar | Implementasi logika *switch-case* pada menu utama, pengelolaan fitur *undo* di `main`, proses *sorting* interaktif, fitur kembalikan urutan asli, *exit* program (Line 234 - Akhir), dan penyusunan dokumentasi README |


---

## 📄 Lisensi

Proyek ini dibuat untuk keperluan akademik dalam rangka Praktikum Struktur Data dan Algoritma, Universitas Syiah Kuala. Bebas digunakan sebagai referensi pembelajaran dengan menyebutkan sumber.
