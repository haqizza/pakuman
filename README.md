# pakuman
Simple Pacman Multiplayer Game


### Copy repository dari remote(cloud) ke local
~ Arahkan terminal ke tempat akan menyimpan directory, lalu
```
git clone https://github.com/haqizza/pakuman.git
```

### Saat Hendak Mengubah
~ Untuk mengambil perubahan yang ada di remote, jika ada
```
git pull
```
~ Untuk cek branch yang ada dan sedang aktif, yang sedang dipakai akan dibintangi
```
git branch
```
~ Untuk pindah branch, agar tidak ada perubahan yang tabrakan
```
git checkout -b [Nama Branch]
```

[Nama Branch] : Isi boleh hanya dengan _update1_, _update2_. Tapi cek dulu apakah belum ada, di command sebelumnya, jika ada tambah angaknya

### Jika Selesai Mengubah
~ Untuk menambahkan semua perubahan
```
git add .
```
~ Untuk menetapkan perubahan
```
git commit -m "[Tulis Perubahan/penambahan yang dilakukan]"
```
~ Menyimpan dari local ke remote
```
git push origin [Nama Branch]
```


\*Perintah-perintah ini dilakukan di terminal

\*Untuk menggabungkan semua perubahan, biar oleh haqizza