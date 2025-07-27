<html>
<head>
    <title>Редактор</title>
</head>
<body>
<?  

    $user = trim(stripcslashes($_REQUEST['user']));
    $password = trim(stripcslashes($_REQUEST['password']));

    function isUserDataCorrect($user, $password) {

        $conn = new mysqli("mysql", "server", "server", "forum");
        if (!$conn -> connect_errno) {
            $users = $conn -> query("SELECT * FROM users WHERE login='$user'");
            if (!is_null($users)) {

                while($row = $users -> fetch_row()){
                    if (password_verify($password, $row[2]) == 0) {
                        return true;
                    }
                }
            }
            $conn -> close();
        }
        return false;
    }

    function isUserAdmin($user, $password) {
        $conn = new mysqli("mysql", "server", "server", "forum");
        if (!$conn -> connect_errno) {
            $users = $conn -> query("SELECT * FROM users WHERE login='$user'");

            $row = $users -> fetch_row();

            if ($row[2] == 1) {
                return true;
            }
            $conn -> close();
        }
        return false;
    }

    if (!isUserDataCorrect($user, $password) && !isUserAdmin($user, $password)){
        echo "<script type='text/javascript'>alert('Неверный логин или пароль'); window.location.href = 'main-page.php'</script>";
    } else {
        
        $post_id = $_REQUEST['post_id'];
    
        if ($post_id == "new"){

            $post_title = "Post";
            $post_text = "";
            $author = $user;

        } else {

            $conn = new mysqli("mysql", "server", "server", "forum");
            if (!$conn -> connect_errno) {

                $post = $conn -> query("SELECT * FROM posts WHERE id=$post_id");
                $post = $post -> fetch_row();
                
                $author = $post[2];
                $post_title = $post[1];
                $post_text = str_replace("<br>", "\n", $post[3]);
            
                if (strcmp($user, $author) !== 0 && !isUserAdmin($user, $password)) {
                    echo "<script type='text/javascript'>alert('У вас нет прав для редактирования'); window.location.href = 'main-page.php'</script>";
                }
            
                $conn -> close();

            } else {
                echo "<script type='text/javascript'>alert('Не удалось загрузить сообщение, попробуйте ещё раз');";
                echo " history.back()</script>";
            }
        }

        print 
        <<<HERE
        <script>
            function setActionDelete() {
                document.getElementById('action').value = 'delete';
            }
        </script>
        <form action = "write-post.php" method = "post">
            <table border = 1>
                <tr>
                    <th>Post title</th>
                    <td>
                        <input type = "text" name = "title" value = "$post_title">
                    </td>
                </tr>
                <tr>
                    <td rowspan = 1 colspan = 2>
                        <textarea name = "text" rows = 20 cols = 60>$post_text</textarea>
                    </td>
                </tr>
                <tr>
                    <td colspan = 2>
                        <center>
                        <input type = "hidden" name = "author" value = "$author">
                        <input type = "hidden" name = "id" value = "$post_id">
                        <input type = "hidden" id="action" name="action" value = "update">
                        <input type = "button" value = "Создать / Изменить" onClick="document.getElementById('submit').click()">&nbsp;&nbsp;
                        <input type = "button" value = "Удалить" onClick="setActionDelete(); document.getElementById('submit').click()">
                        </center>
                    </td>
                </tr>
            </table>
            <input type = "submit" id="submit" hidden>
        </form>
        HERE;
    }
?>
</body>
</html>