<?php
require_once __DIR__ . "/vendor/autoload.php";
// Application logic
require_once __DIR__ . "/now_code.inc";

require_once __DIR__ . "/TwigExtension/customFilters.php";

$loader = new \Twig\Loader\FilesystemLoader('./views/');

$twig = new \Twig\Environment($loader, [
  'debug' => true,
  // 'cache' => './compilation_cache',
  'strict_variables' => true,
  'autoescape' => false
]);

$twig->addExtension(new Custom_Filters());

$template = $twig->load('home.twig');

echo $template->render([
  'lang' => 'en',
  'classNames' => [
    'html' => 'h-feed',
    'title' => 'p-name',
  ],
  'version' => 'v1.5.0',
  'meta' => get_meta(),
  'data_active' => tasks_active(),
  'data_ready' => tasks_ready(),
  'data_completed' => tasks_completed(),
]);
