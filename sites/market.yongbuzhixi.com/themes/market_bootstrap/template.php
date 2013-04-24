<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */
function market_bootstrap_preprocess_page(&$variables) {
  // exclude backend pages to avoid core js not working anymore
  // you could also just use a backend theme to avoid this
  if (arg(0) != 'admin' || !(arg(1) == 'add' && arg(2) == 'edit') || arg(0) != 'panels' || arg(0) != 'ctools') {
    $scripts = drupal_add_js();
    $new_jquery = array(drupal_get_path('theme', 'market_bootstrap') . '/js/jquery-1.7.2.min.js' => $scripts['core']['misc/jquery.js']);
    $scripts['core'] = array_merge($new_jquery, $scripts['core']);
    unset($scripts['core']['misc/jquery.js']);
    $variables['scripts'] = drupal_get_js('header', $scripts);
  }
}