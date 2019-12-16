<?php

/**
 * Parse a string links as an HTML clickable link
 * @see <https://daringfireball.net/2010/07/improved_regex_for_matching_urls>
 */
function parse_as_link($string) {
  $pattern = "/(?i)\b((?:https?:\/\/|www\d{0,3}[.]|[a-z0-9.\-]+[.][a-z]{2,4}\/)(?:[^\s()<>]+|\(([^\s()<>]+|(\([^\s()<>]+\)))*\))+(?:\(([^\s()<>]+|(\([^\s()<>]+\)))*\)|[^\s`!()\[\]{};:'\".,<>?«»“”‘’]))/";
  return preg_replace($pattern, "<a href=\"$1\">$1</a>", $string);
}

/**
 * Outputs give date in specific format
 * @see <https://blog.serverdensity.com/handling-timezone-conversion-with-php-datetime/>
 */
function render_date($date, $format = 'D, j\<\s\u\p\>S<\/\s\u\p\> M Y \a\t H:i:s') {
  $userTimezone = new DateTimeZone('Europe/Berlin');
  $gmtTimezone = new DateTimeZone('GMT');
  $myDateTime  = new DateTime($date, $gmtTimezone);
  $offset = $userTimezone->getOffset($myDateTime);
  $myInterval=DateInterval::createFromDateString((string)$offset . 'seconds');
  $myDateTime->add($myInterval);
  $formatedTime = $myDateTime->format($format);
  return $formatedTime;
}

/**
 * Rendering Task Annotations
 */
function render_annotations($annotations) {
  $output = '';
  if (empty($annotations)) {
    return $output;
  }
  $annotations_reversed = array_reverse($annotations);
  if (sizeof($annotations_reversed)) {
    $output .= "<h4>Activity</h4>";
    $output .= "<ol class='annotations'>";
    foreach ($annotations_reversed as $annotationKey => $annotation) {
      $annotation_text = parse_as_link($annotation["description"]);
      $output .= "<li>";
      $output .= '<time class="entry" datetime="' . render_date($annotation["entry"], 'Y-m-d H:i:s') . '">'
      . render_date($annotation["entry"], 'Y-m-d H:i:s')
      . "</time>"
      . " "
      . '<span class="text">'
      . $annotation_text
      . "</span>";
    }
    $output .= "</li>";
    $output .= "</ol>";
  }
  return $output;
}

/**
 * Rendering Tasks Active
 */
function tasks_active() {
  // Read JSON file
  $json = file_get_contents('./data/task-active.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  $output = '';

  // print_r($json_data);
  foreach ($json_data as $taskKey => $task) {
    $output .= '<article id="task-' . $task["uuid"] .'" class="h-entry h-event">';
    $output .= "<h3 title=\"ID " . $task["id"] . "\" class=\"p-name\">Working on: " . $task["project"] . "</h3>";
    $output .= "<p class=\"p-summary\">" . $task["description"]. "</p>";
    if (!empty($task["start"]) && !empty($task["modified"])) {
      $output .= "<dl class='meta'>";
      $output .= "<dt>Entry</dt><dd><time class=\"dt-published\" datetime=\"" . render_date($task["entry"], "Y-m-d H:i:s") . "\">" . render_date($task["entry"]) . "</time></dd>";
      $output .= "<dt>Start</dt><dd><time class=\"dt-start\" datetime=\"" . render_date($task["start"], "Y-m-d H:i:s") . "\">" . render_date($task["start"]) . "</time></dd>";
      $output .= "<dt>Modified</dt><dd><time class=\"dt-updated\" datetime=\"" . render_date($task["modified"], "Y-m-d H:i:s") . "\">" . render_date($task["modified"]) . "</time></dd>";
      $output .= "</dl>";
    }
    if (!empty($task["annotations"])) {
      $output .= render_annotations($task["annotations"]);
    }
    $output .= "</article>";
  }

  return $output;
}

/**
 * Rendering Tasks Completed
 */
function tasks_completed() {
  // Read JSON file
  $json = file_get_contents('./data/task-completed.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  $output = '';

  // print_r($json_data);
  foreach ($json_data as $taskKey => $task) {
    $output .= '<article id="task-' . $task["uuid"] .'" class="h-entry">';
    $output .= "<h3 title=\"UUID " . $task["uuid"] . "\" class=\"p-name\">Closed: " . $task["project"] . "</h3>";
    $output .= "<p class=\"p-summary\">" . $task["description"]. "</p>";
    if (!empty($task["end"])) {
      $output .= "<dl class='meta'>";
      $output .= "<dt>Entry</dt><dd><time class=\"dt-start\" datetime=\"" . render_date($task["entry"], "Y-m-d H:i:s") . "\">" . render_date($task["entry"]) . "</time></dd>";
      $output .= "<dt>End</dt><dd><time class=\"dt-end\" datetime=\"" . render_date($task["end"], "Y-m-d H:i:s") . "\">" . render_date($task["end"]) . "</time></dd>";
      $output .= "<dt>Modified</dt><dd><time class=\"dt-updated\" datetime=\"" . render_date($task["modified"], "Y-m-d H:i:s") . "\">" . render_date($task["modified"]) . "</time></dd>";
      $output .= "</dl>";
    }
    if (!empty($task["annotations"])) {
      $output .= render_annotations($task["annotations"]);
    }
    $output .= "</article>";
  }

  return $output;
}

/**
 * Rendering Tasks Planned
 */
function tasks_ready() {
  // Read JSON file
  $json = file_get_contents('./data/task-ready.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  $output = '';

  foreach ($json_data as $taskKey => $task) {
    if (empty($task["start"])) {
      $output .= '<article id="task-' . $task["uuid"] .'" class="h-entry">';
      $output .= "<h3 title=\"ID " . $task["id"] . "\" class=\"p-name\">Planned: " . $task["project"]. "</h3>";
      $output .= "<p class=\"p-summary\">" . $task["description"]. "</p>";
      if (!empty($task["modified"])) {
        $output .= "<dl class='meta'>";
        $output .= "<dt>Entry</dt><dd><time class=\"dt-start\" datetime=\"" . render_date($task["entry"], "Y-m-d H:i:s") . "\">" . render_date($task["entry"]) . "</time></dd>";
        $output .= "<dt>Modified</dt><dd><time class=\"dt-published\" datetime=\"" . render_date($task["modified"], "Y-m-d H:i:s") . "\">" . render_date($task["modified"]) . "</time></dd>";
        $output .= "</dl>";
      }
      if (!empty($task["annotations"])) {
        $output .= render_annotations($task["annotations"]);
      }
      $output .= "</article>";
    }
  }

  return $output;
}

/**
 *
 */
function render_meta() {
  // Read JSON file
  $json = file_get_contents('./data/task-meta.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  echo "<section id=\"meta\"><p>Last updated: " . render_date($json_data["updated"]) . "</p></section>";
}

/**
 *
 */
function render_footer() {
  $version = 'v1.4.4';
  echo '<footer>'
      . '<address>Made by <a href="https://johanbove.info" rel="me" class="p-author h-card">Johan Bové</a> in December 2019. (<em>Version ' . $version . '</em>)</address>'
      . '</footer>';
}
