<?php
require_once __DIR__ . "/vendor/autoload.php";

$loader = new \Twig\Loader\FilesystemLoader('./views/');
$twig = new \Twig\Environment($loader, [
  'debug' => true,
  'cache' => './compilation_cache',
  'strict_variables' => true
]);

echo $twig->render('home.html', ['text' => 'Hello Twig!']);
