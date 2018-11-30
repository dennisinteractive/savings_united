<?php
/**
 * @file
 * Theme the 'savings-united' block.
 * See savings_united_preprocess_block().
 */
?>
<div class="coupons">
  <h3><?php print render($block_title); ?></h3>
  <ul class="coupons__list">
    <?php foreach($template_links as $template_link): ?>
      <li class="coupon">
        <?php print render($template_link); ?>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
