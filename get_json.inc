<?php

/**
 * @param {String} $file
 */
function get_json(string $file) {
  // Read JSON file
  $json = file_get_contents($file);

  // Decode JSON
  $json_data = json_decode($json, true);

  return $json_data;
}

/**
 * Rendering Tasks Active
 */
function tasks_active() {
  return get_json('./data/task-active.json');
}

/**
 * Rendering Tasks Completed
 */
function tasks_completed() {
  return get_json('./data/task-completed.json');
}

/**
 * Rendering Tasks Planned
 */
function tasks_ready() {
  return get_json('./data/task-ready.json');
}

/**
 * Returns the last updated time stamp
 */
function get_meta() {
  return get_json('./data/task-meta.json');
}
