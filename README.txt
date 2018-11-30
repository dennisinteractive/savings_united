
-- SUMMARY --

Savings United offers integration with https://savings-united.com.
It provides a configurable block that loads contents from Savings United API.

Visit the project page:
  https://drupal.org/project/savings_united
To submit bug reports and feature suggestions, or to track changes:
  https://drupal.org/project/issues/savings_united


-- REQUIREMENTS --

* None.


-- INSTALLATION --

* Install as usual, see
  http://drupal.org/documentation/install/modules-themes/modules-7


-- CONFIGURATION --

* Go to Administration » Configuration » System » Savings United API. You'll see the following fields:

  - Base url - default value: https://api.savings-united.com/api. It's unlikely you need to change this.
  - API Token - add here your Savings United token.
  - Path/category mapping - the format is: [drupal url]|[savings united categories] (separated by comma). Example: mobile-phones|gadgets,mobile-tablets.
  - Only in parent path checkbox - when selected it will only load in the parent path. For example: it will display the block for mobile-phones, but not mobile-phones/iphone.
  - Number of results - number of contents from the API you want to load in the block.
  - Endpoint url - relative path to the Savings United endpoint. Example: /v1/snippet/shops.
  - Endpoint link text - variable from the API you want to use as link text. Examples: anchor_text, best_offer_text.

* Once you configure the fields above, you can place the block "Savings United Block" anywhere you want.

-- CREDITS --

This project has been sponsored by: Dennis Publishing.
