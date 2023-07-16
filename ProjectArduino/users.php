<?php
    include 'config.php';

    if (isset($_SESSION['auth_id'])) {
        
        if (isset($_POST['delete'])) {
            $id = $_POST['id'];
            $query = "DELETE FROM users WHERE ID = '$id'";
            $result = $conn->query($query);
        }    

        $query = "SELECT * FROM users";
        $result = $conn->query($query);        

    }
    else {
        header("Location: index.php");
    }

    if (isset($_POST['logout'])) {
        session_unset();
        header('Location: index.php');
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Users</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-9ndCyUaIbzAi2FUVXJi0CjmCapSmO7SnpJef0486qhLnuZ2cdeRhO02iuK6FUUVM" crossorigin="anonymous">

    <style>
        .md-distance-top {
            margin-top: 8rem;
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <nav class="navbar bg-danger fixed-top">
                <button class="navbar-toggler" type="button" data-bs-toggle="offcanvas" data-bs-target="#offcanvasNavbar" aria-controls="offcanvasNavbar" aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="offcanvas offcanvas-start" tabindex="-1" id="offcanvasNavbar" aria-labelledby="offcanvasNavbarLabel">
                    <div class="offcanvas-header">
                        <button type="button" class="btn-close" data-bs-dismiss="offcanvas" aria-label="Close"></button>
                    </div>
                    <div class="offcanvas-body">
                        <ul class="navbar-nav justify-content-end flex-grow-1 pe-3">
                            <li class="nav-item">
                                <a class="nav-link active" aria-current="page" href="history.php">Catatan</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="users.php">Users</a>
                            </li>
                            <li class="nav-item">
                                <form action="" method="POST">
                                    <button class="nav-link" type="submit" name="logout">Logout</button>
                                </form>
                            </li>
                        </ul>
                    </div>
                </div>
            </nav>
        </header>
        <section>
            <div class="md-distance-top">
                <h1 class="border-bottom mb-5">Users</h1>
                <a class="btn btn-primary mb-3" href="adduser.php">+Tambah</a>
                <table class="table table-bordered">
                    <thead>
                        <tr>
                            <th scope="col">ID</th>
                            <th scope="col">Nama</th>
                            <th scope="col">Tanggal Lahir</th>
                            <th scope="col">Asal</th>
                            <th scope="col"></th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php

                            while ($rows = $result->fetch_assoc()) {
                                echo "
                                    <tr>
                                        <th scope='row'>".$rows['ID']."</th>
                                        <td>".$rows['Nama']."</td>
                                        <td>".$rows['TanggalLahir']."</td>
                                        <td>".$rows['Asal']."</td>
                                        <td>
                                            <form action='' method='POST'>
                                                <input type='hidden' name='id' value='".$rows['ID']."'>
                                                <button type='submit' name='delete' class='btn btn-primary'>Delete</button>
                                            </form>            
                                        </td>
                                    </tr>
                                ";
                            }
                        ?>
                    </tbody>
                </table>        
            </div>
        </section>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js" integrity="sha384-geWF76RCwLtnZ8qwWowPQNguL3RmwHVBC9FhGdlKrxdiJJigb/j/68SIy3Te4Bkz" crossorigin="anonymous"></script>
</body>
</html>