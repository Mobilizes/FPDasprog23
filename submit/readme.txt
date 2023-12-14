Final Project Dasar Pemrograman 2023
oleh : Fernando 5025231091

Information :
- Perubahan yang dilakukan dalam aplikasi belum masuk ke dalam file gudang.txt hingga dilakukan perintah commit, jadi pastikan untuk mengcommit perubahan sebelum menutup aplikasi.
- ID bersifat UNIK, maka tidak bisa add data ke ID yang sudah ada datanya, dan juga tidak bisa modifikasi ID data ke ID yang sudah ada datanya.

Don't do section :
- Data hanya dapat dibuat saat data grup ada. Contoh, Beras Rajawali tidak bisa dibuat jika data grup Beras tidak ada.
- Stok memiliki konstrain 0 - 2^63-1. Menginput nilai yang lebih atau kurang akan mengeluarkan hasil yang tidak sesuai.
- ID memiliki konstrain 0 - 1000. Menginput nilai yang di luar konstrain akan menyebabkan error. Mengubah data gudang.txt secara langsung sebelum aplikasi diluncurkan akan menyebabkan error.

Q/A section :
Q : Apa guna aplikasi ini?
A : Aplikasi ini menyimpan dan memproses data di file gudang.txt secara interaktif dan user friendly. Aplikasi ini terinspirasi dari format tabel mySQL.

Q : Bagaimana cara setup aplikasi ini?
A : Hanya perlu menjalankan file FP.exe saat gudang.txt dan backup.txt berada di folder yang sama.

Q : Apa itu toggle to group?
A : Toggle to group adalah perintah untuk mengganti dari mode modifikasi data singular menjadi mode modifikasi data grup. Setelah perintah dijalankan, maka perintah berubah menjadi Toggle to singular.

Q : Apa itu reset changes?
A : Reset changes berfungsi untuk mereset semua perubahan yang belum dicommit ke file.

Q : Apa itu commit changes to file?
A : Commit changes to file adalah perintah untuk menyimpan semua perubahan ke dalam file. Perubahan yang dilakukan pada program BELUM diubah di dalam file, jadi sebelum menutup aplikasi diharapkan untuk commit file terlebih dahulu.

Q : File gudang.txt salah format.
A : Gunakan backup.txt untuk memulihkan data. backup.txt berisi data gudang.txt dari commit sebelumnya. backup.txt tidak memuat data sebelumnya, silahkan menggunakan template.txt.


Github repository dari final project ini.
https://github.com/Mobilizes/FPDasprog23
