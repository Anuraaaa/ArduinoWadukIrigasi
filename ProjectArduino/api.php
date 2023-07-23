<?php
    include "config.php";

    if (!empty($_POST)) {
        date_default_timezone_set('Asia/Jakarta');
        $waktu = date("d/m/y H:m:s");
        $ketinggianair = $_POST['ketinggianair'];

        $query = "INSERT INTO history (Waktu, KetinggianAir) VALUES ('$waktu', '$ketinggianair')"; 

        $conn->query($query);
    }
?>