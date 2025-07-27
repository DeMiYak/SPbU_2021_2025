<html>
    <head>
        <title>Форум</title>
    </head>
    <body>
        <center>
            <h2>Главная страница</h2>
        </center>
        <div>
        <?

            include("functions.php");

            showEdit();
            showUserRegistration();
            showPosts();
            
            
        ?>
        </div>
        
    </body>
</html>