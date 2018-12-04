<?php

class SavingsUnited {
  // API base url.
  protected $base_url;
  // Endpoint without the base url.
  protected $endpoint;
  // API token.
  protected $token;
  // Render block only in parent path.
  protected $only_parent_path;
  // Number of results to render.
  protected $number_results;
  // Path category mapping.
  protected $mapping;

  public function __construct() {
    $this->base_url = variable_get('savings_united_base_url', '');
    $this->endpoint = variable_get('savings_united_endpoint', '');
    $this->token = variable_get('savings_united_api_token', '');
    $this->only_parent_path = variable_get('savings_united_mapping_only_parent', 0);
    $this->number_results = variable_get('savings_united_number_results', 5);
    $this->mapping = variable_get('savings_united_mapping', '');
  }

  public function getOptions() {
    $headers = array(
      'Authorization' => 'Bearer ' . $this->token
    );
    $options = array(
      'headers' => $headers
    );
    return $options;
  }

  public function testConnection() {
    $result = drupal_http_request($this->base_url . $this->endpoint, $this->getOptions());
    return $result->status_message;
  }

  public function getMapping() {
    $new_array = array();
    if (!empty($this->mapping)) {
      $mapping_lines = explode(PHP_EOL, $this->mapping);
      foreach ($mapping_lines as $mapping_line) {
        $explode = explode('|', $mapping_line);
        $new_array[$explode[0]] = trim($explode[1]);
      }
    }
    return $new_array;
  }

  public function getCoupons() {
    $is_admin = path_is_admin(current_path());
    if (!$is_admin) {
      $alias = explode('/', drupal_get_path_alias());

      // Return empty array if it's a child path and we are only rendering in the parent path.
      if (count($alias) > 1 && $this->only_parent_path) {
        return array();
      }

      $alias = reset($alias);
      $url = $this->base_url . $this->endpoint . '?limit=' . $this->number_results;

      $mapping = $this->getMapping();
      if (isset($mapping[$alias])) {
        $url .= '&categories=' . $mapping[$alias];
      }
      else {
        // Calling all modules implementing hook_savings_united_alter():
        drupal_alter('savings_united', $url);
        $parse_url = drupal_parse_url($url);
        // Return empty array if the current category is not in the mapping and there's no implementations of the hook.
        if ((!isset($parse_url['query']['categories']))) {
          return array();
        }
      }
      if (variable_get('savings_united_enable_debug', 0) == 1) {
        drupal_set_message($url);
      }

      $result = drupal_http_request($url, $this->getOptions());
      return drupal_json_decode($result->data);
    }
  }
}
