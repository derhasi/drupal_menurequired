<?php
// $Id$

/**
 * Special identifier handling functions.
 */


/**
 * Crumb item builder for identifier <none>.
 */
function _custom_breadcrumbs_identifier_none($title, $path, $attributes, $identifier) {
  $crumb_item = array(
    'crumb' => check_plain($title),
    'title' => $title,
  );
  return array($crumb_item);
}

/**
 * Crumb item builder for identifier <pathauto>.
 */
function _custom_breadcrumbs_identifier_pathauto($title, $path, $attributes, $identifier) {
  $options = parse_url($path);
  $options = array_merge($options, $attributes);
  if (module_exists('pathauto')) {
    module_load_include('inc', 'pathauto', 'pathauto');
    $crumb = l($title, pathauto_cleanstring($options['path'], FALSE), $options);
  }
  else {
    $crumb = l($title, $options['path'], $options);
  }
  $crumb_item = array (
      'crumb' => $crumb,
      'title' => $title,
      'href' => $path,
  );
  return array($crumb_item);
}