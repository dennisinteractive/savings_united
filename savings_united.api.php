<?php

/**
 * @file
 * Documents hooks provided by this module.
 */

/**
 * Alter the api url.
 *
 * Useful if you need to override any api url parameter or add new ones.
 * @param $url
 */
function hook_savings_united_alter(&$url) {
  $category = 'test';
  $url .= '&categories=' . $category;
}
