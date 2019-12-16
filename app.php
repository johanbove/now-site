<!DOCTYPE html>
<html lang="en" class="h-feed">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title class="p-name">Open Productivity - Now</title>
    <link rel="self" href="https://johanbove.info/now.php" class="u-url">
    <style>
    body { font-family: 'Share Tech Mono', consolas, monospace; color: #47B9B7; background-color: #0D1F18; }
    /* Layout: grid */
    h1, h2, h3 { margin-top: 0; font-weight: 400; }
    main, header { margin: 1em; }
    nav { margin: 1em 0; }
    dt { font-style: italic; opacity: 0.6; }
    footer, header, section { padding: 1em; }
    footer { margin: 1em; text-align: center; }
    section > article > h3 { font-size: 1.4em; padding-top: 1em; margin-top: 1em; }
    header > section,
    header > nav {
      border: none;
      border-radius: 0;
      padding: 0.5em 0;
      margin: 0;
    }
    header > nav {
      padding-top: 1em;
    }

    .annotations { list-style-type: none; margin: 1em; padding: 0 0.25em; }
    .annotations li { margin-top: 0.25em; }
    .annotations li:first-child { margin-top: inherit; }
    .annotations time { font-weight: 600; display: block; }

    section { margin: 3em 0; display: flex; flex-wrap: wrap; justify-content: space-between; }

    section > h2 { flex: 0 0 100%; }
    section > p { flex: 0 0 100%; }
    section > article { flex: 0 0 100%; }

    @media (min-width: 1024px) {
      section > article { flex: 0 0 30%; }
    }
    </style>

    <!-- Theme -->
    <link href="https://fonts.googleapis.com/css?family=Share+Tech+Mono&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="now_theme_bladerunner.css">
</head>
<body>
<?php
// Prepare the output
$data_active = tasks_active();
$data_ready = tasks_ready();
$data_completed = tasks_completed();

// Print data
?>
<header>
<h1>Open Productivity Now</h1>
<p>Sharing my <em>plans</em> managed in <a href="https://taskwarrior.org/">TaskWarrior</a> after getting inspired by <a href="https://noeldemartin.com/now">Noel De Martin</a>.</p>
<p>All times are in timezone Europe/Berlin.</p>
<?php render_meta() ?>
<nav>Tags: <a href="#active">Active</a> | <a href="#planned">Planned</a> | <a href="#closed">Closed</a></nav>
</header>
<main>
<?php if(!empty($data_active)) { ?>
<section id="active">
<h2>Active - currently focused on...</h2>
<?php
echo $data_active;
?>
</section>
<?php } ?>
<?php if(!empty($data_ready)) { ?>
<section id="planned">
<h2>Planned - planning to work on this soon...</h2>
<?php
echo $data_ready;
?>
</section>
<?php
}
?>
<?php if(!empty($data_completed)) { ?>
<section id="closed">
<h2>Closed - Finished tasks...</h2>
<p>This list shows all task closed in the last month (<a href="https://taskwarrior.org/docs/durations.html">30 days</a>).</p>
<?php
echo $data_completed;
?>
</section>
<?php
}
?>
</main>
<?php render_footer() ?>
</body>
</html>
