<?php
    include "config.php";

    if (isset($_SESSION['auth_id'])) {
        header('Location: history.php');
    }

    if (isset($_POST['login'])) {
        $nama = $_POST['nama'];
        $password = $_POST['password'];

        $query = "SELECT * FROM users WHERE Nama = '$nama' AND Password = '$password' LIMIT 1";
    
        $result = $conn->query($query);
    
        if ($result->num_rows > 0) {
            while ($rows = $result->fetch_assoc()) {
                $_SESSION['auth_id'] = $rows['ID'];
                break;
            }
            header("Location: history.php");
        }
    }

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link rel="stylesheet" href="style.css">
    <link href="https://cdn.jsdelivr.net/npm/remixicon@3.4.0/fonts/remixicon.css" rel="stylesheet">
</head>
<body>
    <div class="login">
        <form action="" method="POST">
            <h1>LOGIN</h1>            
            <div class="inputbox">
                <input type="text" placeholder="Username" name="nama">
                <i class="ri-user-3-line"></i>
            </div>
            <div class="inputbox">
                <input type="password" placeholder="Password" name="password">
                <i class="ri-git-repository-private-line"></i>
            </div>
            <div class="inputbox">
                <button type="submit" name="login">Login</button>
            </div>
        </form>
    </div>

</body>

</html>