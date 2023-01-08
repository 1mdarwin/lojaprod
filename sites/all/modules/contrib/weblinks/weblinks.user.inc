<?php
/**
 * @file
 * Displays a Drupal page containing weblinks submitted by a given user.
 * Drupal 7 Version
 */
function weblinks_user_page($account) {
  $save_hp = @$account->homepage;
  unset($account->homepage);
  $trail = array(l(t('Home'), ''), theme('username', array('account' => $account, 'levels' => FALSE)));
  if ($save_hp) {
    $account->homepage = $save_hp;
  }
  drupal_set_breadcrumb($trail);

  $form = drupal_get_form('weblinks_user_form', $account);
  $output = theme('weblinks_user_form', array('form' => $form)); 
  return $output;
}

function _weblinks_user_access_check($user, $account) {
  if (user_access('edit own weblinks', $user) && ($account->uid == $user->uid)) {
    return TRUE;
  }
  return user_access('administer weblinks', $user);
}

function weblinks_user_form($form, &$form_state, $account) {
  global $user;
  $vocid = _weblinks_get_vocid();
  // If $vocid is not empty, we know that the taxonomy module is available.
  $taxo = !empty($vocid);
  $unclassed = _weblinks_unclassed();
  $destination = drupal_get_destination();
  $options = array();
  $now = $_SERVER['REQUEST_TIME'];
  $limit = 20;
  $node_ops = module_invoke_all('node_operations');

  // $query = db_rewrite_sql("SELECT n.* FROM {node} n WHERE n.uid=%d AND n.type='weblinks' ORDER BY n.changed DESC");
  // $result = pager_query($query, $limit, 0, NULL, $account->uid);
  $query = db_select('node', 'n');
  $query->extend('PagerDefault')
    ->limit($limit);
  $query->condition('n.uid', $account->uid, '=')
    ->condition('n.type', 'weblinks', '=')
    ->fields('n')
    ->orderBy('n.changed', 'DESC');
  $query_result = $query->execute();

  foreach ($query_result as $node) {
    $status = array();
    $status[] = $node->status ? t('published') : t('not published');
    if (isset($node->promoted)) {
      $status[] = t('promoted');
    }
    if ($node->sticky > 0) {  // >0 allows for sticky-encoded weighting.
      $status[] = t('sticky');
    }
    if (isset($node->moderated)) {
      $status[] = t('moderated');
    }

    // We don't want to "mark" our own content.
    if ($account->uid == $user->uid) {
      $mark = NULL;
    }
    else {
      $mark = ' '. theme('mark', array('type' => node_mark($node->nid, $node->changed)));
    }
    $form['title'][$node->nid] = array('#markup' => l($node->title, 'node/'. $node->nid) . $mark);
    $form['status'][$node->nid] =  array('#markup' => implode(', ', $status));
    $form['update'][$node->nid] =  array('#markup' => format_interval($now - $node->changed));

    $tid_list = array();
    if ($taxo) {
      $terms = db_query("SELECT tn.tid, td.name FROM {taxonomy_index} tn 
                        LEFT JOIN {taxonomy_term_data} td USING (tid) WHERE tn.nid=:nid",
                        array(':nid' => $node->nid));
      if ($terms->rowCount() > 0) {
        foreach ($terms as $row) {
          $tid_list[] = check_plain($row->name);
        }
      }
      else {
        $tid_list[] = $unclassed->name;
      }
    }
    $form['group'][$node->nid] =  array('#markup' => implode(', ', $tid_list));

    if (_weblinks_user_access_check($user, $account)) {
      $form['operationse'][$node->nid] = array('#markup' => l(t('edit'), 'node/'. $node->nid .'/edit', array('query' => $destination)));
      $form['operationsd'][$node->nid] = array('#markup' => l(t('delete'), 'node/'. $node->nid .'/delete', array('query' => $destination)));
    }
  }
  $form['pager'] = array('#markup' => theme('pager'));

  return $form;
}

/**
 * Theme node administration overview.
 */
function theme_weblinks_user_form($variables) {
  $form = $variables['form'];
  // Overview table:
  $header = array(t('Title'), t('Status'), t('Group'), t('Last updated'), array('data' => t('Operations'), 'colspan' => '2'));
  $rows =array();

  if (isset($form['title']) && is_array($form['title'])) {
    foreach (element_children($form['title']) as $key) {
      $rows[] = array(
        drupal_render($form['title'][$key]),
        drupal_render($form['status'][$key]),
        drupal_render($form['group'][$key]),
        drupal_render($form['update'][$key]),
        drupal_render($form['operationse'][$key]),
        drupal_render($form['operationsd'][$key]),
        );
    }
  }
  else  {
    $rows[] = array(array('data' => t('No posts available.'), 'colspan' => '6'));
  }
  $output = theme('table', array(
                    'header'     => $header,
                    'rows'       => $rows,
                    'attributes' => array('class' => array('pagerer'))));
  if ($form['pager']['#markup']) {
    $output .= drupal_render($form['pager']);
  }
  // $output .= drupal_render($form);  // Not needed in D7!
  return $output;
}

