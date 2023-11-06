<?php

/**
 * @file
 * Functions for rules integration.
 */

/**
 * Implements of hook_rules_event_info().
 * @ingroup rules
 */
function webform_rules_rules_event_info() {
  return array(
    'webform_rules_submit_as_draft' => array(
      'label' => t('After a webform has been saved as draft'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_submit' => array(
      'label' => t('After a webform has been submitted'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_insert' => array(
      'label' => t('After a submission draft has been submitted'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_update' => array(
      'label' => t('After a webform submission has been updated'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_delete' => array(
      'label' => t('After a webform submission has been deleted'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
  );
}

/**
 * Implementation of hook_condition_info().
 */
function webform_rules_rules_condition_info() {
  return array(
    'webform_has_id' => array(
      'label' => t('Webform has name'),
      'parameter' => array(
        'form_id' => array(
          'type' => 'text',
          'label' => t('The form id of the submitted form'),
        ),
        'selected_webform' => array(
          'type' => 'list<text>',
          'label' => t('Webforms'),
          'options list' => 'webform_rules_get_webforms_as_options',
          'description' => t('The name of the webform to check for.'),
          'restriction' => 'input',
        ),
      ),
      'help' => t('This condition compares the id of the submitted form with the selected value(s).'),
      'group' => t('Webform'),
      'base' => 'webform_rules_condition_webform_has_id',
    ),
    'node_is_webform' => array(
      'label' => t('Content is webform-enabled'),
      'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Content'),
        'description' => t('The content to verify.'),
      ),
      ),
      'help' => t('This condition verifies a node contains a webform.'),
      'group' => t('Webform'),
      'base' => 'webform_rules_condition_node_is_webform',
    ),
    'data_nid' => array(
      'label' => t('Submission to a particular webform'),
      'parameter' => array(
        'webform' => array(
          'type' => 'webform',
          'label' => t('Current submission data'),
          'description' => t('Specifiy the submission to check. Value data.'),
          'restriction' => 'selector',
        ),
        'nid' => array(
          'type' => 'list<integer>',
          'label' => t('Webforms'),
          'description' => t('The webforms to check for.'),
          'options list' => 'webform_rules_get_webforms_as_options',
          'restriction' => 'input',
        ),
      ),
      'help' => t('Use this condition to expose webform components for a particular webform.'),
      'group' => t('Webform'),
      'base' => 'webform_rules_condition_data_nid',
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 *
 */
function webform_rules_rules_action_info() {
  $defaults = array(
    'group' => t('Webform'),
    'access callback' => 'rules_node_admin_access',
    'parameter' => array(
      'entity' => array(
        'type' => 'node',
        'label' => t('Webform'),
        'description' => t('A webform-enabled node.'),
        'save' => TRUE,
        'optional' => TRUE,
      ),
      'selected_webform' => array(
        'type' => 'list<text>',
        'label' => t('Webforms'),
        'options list' => 'webform_rules_get_webforms_as_options',
        'description' => t('List of webforms to open.'),
        'restriction' => 'input',
        'optional' => TRUE,
      ),
    ),
    'callbacks' => array(
      'validate' => 'webform_rules_webform_statuschange_validate',
    ),
  );
  $actions = array(
    'webform_open' => $defaults + array(
      'label' => t('Open webforms'),
      'base' => 'webform_rules_webform_open',
    ),
    'webform_close' => $defaults + array(
      'label' => t('Close webforms'),
      'base' => 'webform_rules_webform_close',
    ),
    'webform_submissions_load' => array(
      'label' => t('Fetch webform submissions'),
      'base' => 'webform_rules_submissions_load',
      'group' => t('Webform'),
      'access callback' => 'rules_node_admin_access',
      'parameter' => array(
        'nid' => array(
          'type' => 'integer',
          'label' => t('Node ID'),
          'description' => t('The ID of the webform node to load the submission for.'),
        ),
        'sid' => array(
          'type' => 'integer',
          'label' => t('Submission ID'),
          'description' => t('The ID of a webform submission. If omitted all submissions of the specified node ID will be fetched.'),
          'optional' => TRUE,
        ),
      ),
      'provides' => array(
        'submissions' => array(
          'label' => t('Fetched submissions'),
          'type' => 'list<webform_data>',
        ),
      ),
    ),
  );

  // Modify description of closing action.
  $actions['webform_close']['parameter']['selected_webform']['description'] = t('The name of the webforms to close.');

  return $actions;
}

/**
 * Implements hook_rules_data_info().
 */
function webform_rules_rules_data_info() {
  return array(
    'webform' => array(
      'label' => t('webform data'),
      'group' => t('Webform'),
      'token type' => 'webform',
      'wrapper class' => 'WebformRulesSubmissionWrapper',
      'wrap' => TRUE,
      'is wrapped' => FALSE,
      'property info' => array(
        'sid' => array(
          'type' => 'integer',
          'label' => 'Submission ID',
        ),
        'submitted' => array(
          'type' => 'date',
          'label' => 'Date Submitted',
          ),
        'remote_addr' => array(
          'type' => 'text',
          'label' => 'IP Address of the submitter',
          ),
        'uid' => array(
          'type' => 'integer',
          'label' => 'User ID of the submitter',
          ),
        'name' => array(
          'type' => 'text',
          'label' => 'Username of the submitter',
          ),
        'is_draft' => array(
          'type' => 'boolean',
          'label' => 'Whether the submission was finalized',
        ),
      ),
    ),
  );
}

/**
 * Compare the form id of the submitted webform with the selected form.
 */
function webform_rules_condition_data_nid($submission, $selection, $settings, $state, $condition, $op) {
  $first_key = key($submission);
  if (empty($submission) || !$submission[$first_key]->nid) {
    drupal_set_message('No submission found!','error');
    return FALSE;
  }
  if (is_array($selection)) {
    if(!empty($selection['webform-client-form-' . $submission[$first_key]->nid])){
      return TRUE;
    }else{
      drupal_set_message('Submission is not in webform!','error');
      return FALSE;
    }
  }
  elseif (is_string($selected_webform)) {
    if('webform-client-form-' . $submission[$first_key]->nid == $selection){
      return TRUE;
    }else{
      drupal_set_message('Submission is not in webform(string)!','error');
      return FALSE;
    }
  }
  return FALSE;
}

/**
 * Use an assertion to expose webform component submission data.
 * @see rules_condition_entity_has_field_assertions()
 */
function webform_rules_condition_data_nid_assertions($element) {
  // Expose webform components if we're given a particular webform condition.
  if ($wrapper = $element->applyDataSelector($element->settings['webform:select'])) {
    $assertion = array('property info' => array());
    $nids = str_replace('webform-client-form-', '', $element->settings['nid']);
    foreach ($nids as $nid) {
      // Get webform components and check whether we have one for this webform.
      $assertion['property info'] += _webform_rules_component_property_info($nid);
    }
    if (!empty($assertion['property info'])) {
      return array($element->settings['webform:select'] => $assertion);
    }
  }
}

/**
 * Utility callback to build property info based on a particular webform's
 * components.
 */
function _webform_rules_component_property_info($nid) {
  $info = array();
  $webform = node_load($nid);
  foreach ($webform->webform['components'] as $cid => $component) {
    // A unique selector, using $nid, is important so that our rule will
    // fail validation if the selected webform changes.
    $id = "{$component['form_key']}";
    // Provide property info, as in hook_rules_data_info().
    $info[$id] = array(
      'label' => $component['name'],
      'description' => t('@component_name from @title(@nid)', array('@component_name' => $component['name'], '@title' => $webform->title, '@nid' => $webform->nid)),
      // All submission data is stored in arrays, whether its multiple or
      // not. Hence, to simplify, we expose all data as list.
      'type' => 'list<text>',
      'getter callback' => 'webform_rules_submission_data_get',
      // @TODO: implement setter callback
    );
  }
  return $info;
}

/**
 * Getter callback for webform submission data.
 */
function webform_rules_submission_data_get($submission, $options, $name, $type, $context) {
  if (is_array($submission) && array_key_exists($name, $submission)) {
    // If we're looking for the submission component data value, and it's not a
    // list, return the first entry of the submission component data value.
    if ($name == 'data' && strpos($context['type'], 'list') === FALSE) {
      return current($submission[$name]);
    }
    // Otherwise, just return whatever value we're looking for.
    return $submission[$name];
  }
  elseif (is_object($submission) && property_exists($submission, $name)) {
    return $submission->$name;
  }
}

/**
 * Validation callback for actions 'webform_rules_webform_open' and
 * 'webform_rules_webform_close'.
 */
function webform_rules_webform_statuschange_validate($element) {
  if (empty($element->settings['entity:select']) && empty($element->settings['selected_webform'])) {
    throw new RulesIntegrityException(t('At least one parameter needs to be set.'), array($element, 'parameter', 'node'));
  }
}

/**
 * Function to compare the form id of the submitted webform with the selected
 * form.
 */
function webform_rules_condition_webform_has_id($form_id, $selected_webform) {
  if (is_array($selected_webform)) {
    return in_array($form_id, $selected_webform);
  }
  elseif (is_string($selected_webform)) {
    return $form_id == $selected_webform;
  }
  return FALSE;
}

/**
 * Condition callback to determine whether a node contains a webform.
 */
function webform_rules_condition_node_is_webform($node) {
  // Get a list of all nodes that are configured to use a webform.
  $query = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('n.nid', $node->nid);
  // Join to limit result list to node that really have a webform.
  $query->join('webform', 'w', 'n.nid = w.nid');
  // Join {webform_component} to prevent listing unconfigured webforms.
  $query->join('webform_component', 'c', 'n.nid = c.nid');
  // Get the result list.
  if ($query->execute()->rowCount() > 0) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Rules action callback to open webforms.
 */
function webform_rules_webform_open($entity = FALSE, $selected_webforms = array()) {
  _webform_rules_webform_set_status($entity, $selected_webforms);
}

/**
 * Rules action callback to close webforms.
 */
function webform_rules_webform_close($entity = FALSE, $selected_webforms = array()) {
  _webform_rules_webform_set_status($entity, $selected_webforms, FALSE);
}

/**
 * Helper method to update the status of a webform.
 */
function _webform_rules_webform_set_status($entity = FALSE, $selected_webforms = array(), $open = TRUE) {
  if (!empty($entity->nid) && webform_rules_condition_node_is_webform($entity)) {
    // Set new status.
    $entity->webform['status'] = ($open == TRUE) ? 1 : 0;
  }
  module_load_include('inc', 'rules', 'modules/entity.eval');
  // Try to close all selected webforms.
  foreach ($selected_webforms as $form_id) {
    // Try to get node id from form_id.
    $nid = str_replace('webform-client-form-', '', $form_id);
    // Load the node object.
    $result = rules_action_entity_fetch('node', $nid, NULL);
    $webform = $result['entity_fetched'];
    if (!empty($webform->nid) && webform_rules_condition_node_is_webform($webform)) {
      // Set new status.
      $webform->webform['status'] = ($open == TRUE) ? 1 : 0;
      // Save the webform node. Maybe we can find a better way how to save?
      node_save($webform);
    }
  }
}

/**
 * Rules action to load a list of webform submissions.
 *
 * @param int $nid
 *   ID of node to load the submissions for.
 * @param int $sid
 *   (optional) Submission ID.
 *
 * @return array
 *   List of loaded webform submissions.
 */
function webform_rules_submissions_load($nid, $sid = NULL) {
  // Make sure the needed functions are available.
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  $filters = array(
    'nid' => $nid,
  );
  if (!empty($sid)) {
    $filters['sid'] = $sid;
  }
  // Fetch submissions.
  $submissions = webform_get_submissions($filters);

  return array('submissions' => $submissions);
}

/**
 * Helper function for event variables.
 *
 * @return
 *   All available variables for the rules events provided by webform_rules.
 */
function _webform_rules_event_variables() {
  return array(
    'user' => array(
      'type' => 'user',
      'label' => t('User, who submitted the webform'),
    ),
    'node' => array(
      'type' => 'node',
      'label' => t('The webform node'),
    ),
    'data' => array(
      'type' => 'webform',
      'label' => t('The submitted webform data'),
    ),
    'form_id' => array(
      'type' => 'text',
      'label' => t('The form id of the submitted form'),
      'hidden' => TRUE,
    ),
    'selected_webform' => array(
      'type' => 'list<text>',
      'label' => t('Webforms'),
      'options list' => 'webform_rules_get_webforms_as_options',
      'description' => t('The name of the webform to check for.'),
      'restriction' => 'input',
      'hidden' => TRUE,
      'optional' => TRUE,
    ),
  );
}

/**
 * Provide entity-like access to webform submission data.
 * @see webform_rules_condition_data_nid_assertions()
 */
class WebformRulesSubmissionWrapper extends RulesIdentifiableDataWrapper {
// @TODO: implement RulesDataWrapperSavableInterface

  public function __construct($type, $data = NULL, $info = array()) {
    if (!is_null($data)) {
      // If we have a webform submission, add the form values as properties.
      // (If we do not have a submission, properties are added by assertion.
      // @see webform_rules_condition_data_nid_assertions()).
      $info['property info alter'] = array('WebformRulesSubmissionWrapper', 'webformSubmissionValues');
    }
    parent::__construct($type, $data, $info);
    $this->setData($data);
  }

  public static function webformSubmissionValues($wrapper, $property_info) {
    $submission = $wrapper->value();
    $properties = $property_info['properties'];
    if (!empty($submission->nid)) {
      $properties += _webform_rules_component_property_info($submission->nid);
    }
    return array('properties' => $properties);
  }

  protected function setData($data) {
    parent::setData($data);
    if (!is_array($data)) {
      return;
    }
    $submission = current($data);
    if (!isset($submission->sid)) {
      return;
    }
    $s = webform_get_submissions(array('sid' => $submission->sid));
    if (empty($s) || !is_array($s)) {
      return;
    }
    $s = current($s);
    $this->id = $s->sid;
    $this->data = $s;
    $webform = node_load($this->data->nid);
    $components = $webform->webform['components'];
    foreach ($s->data as $cid => $val) {
      $c_key = $components[$cid]['form_key'];
      $id = "{$c_key}";
      $this->data->$id = array_values($val);
    }
  }

  protected function extractIdentifier($data) {
    return $data->sid;
  }

  public function getIdentifier() {
    return $this->dataAvailable() && $this->value() ? $this->id : NULL;
  }

  protected function load($data) {
    if (is_array($data)) {
      $sid = $data['sid'];
    }
    else {
      $sid = $data;
    }
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    return webform_get_submissions(array('sid' => $sid));
  }
}
