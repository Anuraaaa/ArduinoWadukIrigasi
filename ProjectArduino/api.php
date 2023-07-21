<?php
    include "config.php";

    if (!empty($_POST)) {
        $waktu = date("d/m/y h:m:s");
        $ketinggianair = $_POST['ketinggianair'];

        $query = "INSERT INTO history (Waktu, KetinggianAir) VALUES ('$waktu', '$ketinggianair')"; 

        $conn->query($query);
    }
?>