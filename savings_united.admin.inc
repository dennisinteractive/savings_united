<?php
/**
 * @file
 * Savings United admin pages.
 */

/**
 * Savings United settings form.
 * @param $form
 * @param $form_state
 * @return mixed
 */
function savings_united_settings_form($form, &$form_state) {
  // Test connection fieldset.
  $form['test_connection'] = array(
    '#type' => 'fieldset',
    '#title' => t('Test connection'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['test_connection']['button'] = array(
    '#type' => 'button',
    '#value' => t('Test connection'),
    '#ajax' => array(
      'callback' => '_savings_united_test_connection',
      'wrapper' => 'edit-connection-markup',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['test_connection']['connection_markup'] = array(
    '#type' => 'item',
    '#markup' => '',
  );

  // Configuration fieldset.
  $form['configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['configuration']['savings_united_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base url'),
    '#default_value' => variable_get('savings_united_base_url', ''),
    '#size' => 60,
    '#description' => t('Savings United base url. Example: https://api.savings-united.com/api'),
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['configuration']['savings_united_api_token'] = array(
    '#type' => 'textfield',
    '#title' => t('API token'),
    '#default_value' => variable_get('savings_united_api_token', ''),
    '#size' => 60,
    '#description' => t('Savings United API token.'),
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['configuration']['savings_united_mapping'] = array(
    '#title' => t('Path/category mapping'),
    '#type' => 'textarea',
    '#description' => t('For each path, assign one or more categories (separated by comma). One path per row. Example:<br><b>mobile-phones|gadgets,mobile-tablets,online-shopping-centres</b><br>(use slug, not category name)'),
    '#default_value' => variable_get('savings_united_mapping', ''),
  );
  $form['configuration']['savings_united_mapping_only_parent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Render block only in parent path'),
    '#description' => t('Check this if you want to render the block only in the parent path.<br>Example: it will load in mobile-phones but not mobile-phones/iphone.'),
    '#default_value' => variable_get('savings_united_mapping_only_parent', 0),
  );
  $form['configuration']['savings_united_number_results'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of results'),
    '#default_value' => variable_get('savings_united_number_results', 5),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Number of results you want to display in the block.'),
    '#required' => TRUE,
  );

  // Endpoints.
  $form['endpoints'] = array(
    '#type' => 'fieldset',
    '#title' => t('Endpoints'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['endpoints']['savings_united_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Endpoint URL'),
    '#default_value' => variable_get('savings_united_endpoint', ''),
    '#size' => 60,
    '#description' => t('Savings United Endpoint. Example: /v1/snippet/coupons'),
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['endpoints']['savings_united_endpoint_link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Endpoint link text'),
    '#default_value' => variable_get('savings_united_endpoint_link_text', 'anchor_text'),
    '#size' => 60,
    '#description' => t('Variable to use as link text (name, anchor_text, best_offer_text...).'),
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Custom callback to test the connection to the api.
 * @return mixed
 */
function _savings_united_test_connection() {
  $connection = new SavingsUnited();
  return $connection->testConnection();
}
