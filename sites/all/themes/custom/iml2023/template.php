<?php

/**
 * @file
 * template.php
 */
function iml2023_preprocess_page(&$variables){
  $searchbox_form = drupal_get_form('search_form');
  $search_box = drupal_render($searchbox_form);
  $variables['search_box'] = $search_box;
}
/**
* Override main menu add span tag before link
*/
function iml2023_menu_link(array $variables){
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    //Here we need to change from ==1 to >=1 to allow for multilevel submenus
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] >= 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      //$element['#title'] .= ' <span class="caret"></span>'; Smartmenus plugin add's caret
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      //comment element bellow if you want your parent menu links to be "clickable"
      //$element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
* ADD GOOGLE Fonts
*/
function iml2023_preprocess_html(&$variables){
    drupal_add_css('https://fonts.googleapis.com/css?family=PT+Sans:400,700,400italic,700italic', array('type' => 'external'));
    drupal_add_css('https://fonts.googleapis.com/css?family=Lato:400,700,400italic,700italic', array('type' => 'external'));
}
