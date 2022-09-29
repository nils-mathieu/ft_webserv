<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>FizzBuzz</title>
</head>
<body>
    <h1>FizzBuzz</h1>

    <ul>
<?php
for ($i = 1; $i <= 100000; $i++) {
    if ($i % 15 == 0)
        echo "        <li>fizzbuzz</li>\n";
    else if ($i % 3 == 0)
        echo "        <li>fizz</li>\n";
    else if ($i % 5 == 0)
        echo "        <li>buzz</li>\n";
    else
        echo "        <li>$i</li>\n";
}
?>
    </ul>
</body>
</html>