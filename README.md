# IOT Waduk Arduino


## Komponen:

- Arduino ESP32
- BreadBoard
- Motor Servo 3
- Sensor Ultrasonik 4
- Liquid Crystal 16x2 1
- Kabel Jumper


## Algoritma:

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


## Usable Pin:
- LCD
	- SDA LCD to G21;
	- SCL LCD to G22;


- Ultrasonic Respon To LCD
	- const int trigPin0 = 16;
	- const int echoPin0 = 17;

- Ultrasonic 1 Respon To Servo 1
	- const int pinServo1 = 5;
	- const int trigPin1 = 19;
	- const int echoPin1 = 18;

- Ultrasonic 2 Respon To Servo 2
	- const int pinServo2 = 32;
	- const int trigPin2 = 33;
	- const int echoPin2 = 25;

- Ultrasonic 3 Respon To Servo 3
	- const int pinServo3 = 4;
	- const int trigPin3 = 26;
	- const int echoPin3 = 27;