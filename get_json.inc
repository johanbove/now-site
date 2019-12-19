<?php

/**
 * Rendering Tasks Active
 */
function tasks_active() {
  // Read JSON file
  $json = file_get_contents('./data/task-active.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  return $json_data;
}

/**
 * Rendering Tasks Completed
 */
function tasks_completed() {
  // Read JSON file
  $json = file_get_contents('./data/task-completed.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  return $json_data;
}

/**
 * Rendering Tasks Planned
 */
function tasks_ready() {
  // Read JSON file
  $json = file_get_contents('./data/task-ready.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  return $json_data;
}

/**
 * Returns the last updated time stamp
 */
function get_meta() {
  // Read JSON file
  $json = file_get_contents('./data/task-meta.json');

  // Decode JSON
  $json_data = json_decode($json, true);

  return $json_data;
}
