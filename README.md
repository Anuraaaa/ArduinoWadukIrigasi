#IOT Waduk Arduino


##Komponen:

- Arduino ESP32
- BreadBoard
- Motor Servo 3
- Sensor Ultrasonik 4
- Liquid Crystal 16x2 1
- Kabel Jumper


##Algoritma:
	Arduino:
	- Terdapat 1 waduk yang ada 3 pintu
	- Terdapat 3 pintu untuk mengalirkan air dari waduk
	- Pintu akan terbuka jika ketinggian air di waduk diatas 8 cm
	- Pintu akan terbuka jika semua pintu memiliki volume minimal 3cm
	- Salah satu pintu akan terbuka jika ketinggian airnya lebih rendah daripada di pintu lain
	- Ketiga pintu akan terbuka jika semua pintu tidak dapat air
	- Ketiga pintu akan terbuka jika semua pintu terdapat volume air yang sama

	Website:
	- Ketika pintu terbuka akan mengirimkan data ke database sebagai catatan
	- Data ditampilkan pada data table frontend
	- Kolom pada data tabel ialah ID, Waktu, Ketinggian Air
	- Terdapat login admin only 
	- Terdapat CRUD user admin 

