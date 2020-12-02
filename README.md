# pakuman
Simple Pacman Multiplayer Game


# Copy repository dari remote(cloud) ke local
~ Arahkan terminal ke tempat akan menyimpan directory, lalu

git clone https://github.com/haqizza/pakuman.git


# Saat Hendak Mengubah
~ Untuk mengambil perubahan yang ada di remote, jika ada

git pull

~ Untuk cek branch yang ada dan sedang aktif, yang sedang dipakai akan dibintangi

git branch

~ Untuk pindah branch, agar tidak ada perubahan yang tabrakan

git checkout -b _[Nama Branch]_


_[Nama Branch]_ : Isi boleh hanya dengan _update1_, _update2_.

tapi cek dulu apakah belum ada, di command sebelumnya, jika ada tambah angaknya

# Jika Selesai Mengubah
~ Untuk menambahkan semua perubahan

git add .

~ Untuk menetapkan perubahan

git commit -m "_[Tulis Perubahan/penambahan yang dilakukan]_"

~ Menyimpan dari local ke remote

git push origin _[Nama Branch]_


* Perintah-perinah ini dilakukan di terminal
* Untuk menggabungkan semua perubahan, biar oleh haqizza