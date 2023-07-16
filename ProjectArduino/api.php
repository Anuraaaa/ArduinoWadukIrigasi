<?php
    include "config.php";

    if (!empty($_POST)) {
        $waktu = $_POST['waktu'];
        $ketinggianair = $_POST['ketinggianair'];

        $query = "INSERT INTO history (Waktu, KetinggianAir) VALUES ('$waktu', '$ketinggianair')"; 

        $conn->query($query);
    }
?>