<?php

function taxpayer_form($form, &$form_state){

    global $base_url;

    $enabledtaxpayer =  variable_get('taxpayerupdate', 0);
    if($enabledtaxpayer == 1){
        return drupal_goto($base_url .'/consultam');
    }

    if(isset($_SESSION['dataws'])){
        unset($_SESSION['dataws']);
    }
    $form['consulta'] = array(
        '#title' => t('Datos del abonado'),
        '#type' => 'fieldset',
        '#description' => t('Consulta a través de su cédula')
    );
    $form['consulta']['cedula'] = array(
        '#title' => t('Número de cédula'),
        '#type' => 'textfield',
        '#required' => true,
        '#maxlenght' => 10,
        '#size' => 15,
        '#description' => t('Your ID have to 10 characters'),
    );
    //if(!user_is_logged_in()){
    if(variable_get('taxpayer_captcha') == 1){
        $form['consulta']['captcha'] = array(
            '#type' =>  'captcha',
            // '#captcha_type' =>  'recaptcha/reCAPTCHA',  // prod
             '#captcha_type' =>  'captcha/Math', // test
            // '#captcha_type' =>  'image_captcha/Image',
        );
    }
    // $form['#attached']['js'] = array(drupal_get_path('module','taxpayerupdate').'/js/impuestos.js',);
    $form['consulta']['save'] = array(
        '#prefix' => '<div class="consulta">',
        '#type' => 'submit',
        '#value' => t('Consultar'),
        '#suffix' => '</div>',
    );
    return $form;
}
    /**
    * Admin pages with form
    */
    function taxpayerupdate_admin_form($form, &$form_state){
        $form['taxpayer'] = array(
            '#title' => t('Administrator'),
            '#type' => 'fieldset',
            '#description' => t('Actualizacion de contribuyente <strong>el rol administrador</strong>')
        );
        $form['taxpayer']['taxpayer_admin'] = array(
            '#type' => 'checkbox',
            '#title' => t('Allow access only to administrator rol'),
            '#default_value' => variable_get('taxpayer_admin', 0),
        );
        $form['taxpayer']['taxpayer_disable'] = array(
            '#type' => 'checkbox',
            '#title' => t('Disable taxpayer update form'),
            '#default_value' => variable_get('taxpayer_disable', 0),
        );
        $form['taxpayer']['taxpayer_captcha'] = array(
            '#type' => 'checkbox',
            '#title' => t('Enable captcha for taxpayer update form'),
            '#default_value' => variable_get('taxpayer_captcha', 0),
        );
        $form['taxpayer_config'] = array(
            '#title' => t('Config taxpayer update'),
            '#type' => 'fieldset',
            '#description' => t('Configurar correos de notificación')
        );
        $form['taxpayer_config']['emails'] = array(
            '#type' => 'textfield',
            '#title' => t('Email address to send notification'),
            '#description' => t('Separate each email address with semicolon. Ej: info@mail.com; admin@hotmail.com'),
            //'#required' => TRUE,
            '#default_value' => variable_get('emails', 'info@loja.gob.ec'),
        );
        $form['taxpayer_config']['message_confirm'] = array(
            '#type' => 'textarea',
            '#title' => t('Message for Disabled Taxes Query'),
            //'#required' => TRUE,
            '#description' => t('Message after send update information'),
            '#default_value' => variable_get('message_confirm'),
        );
        // system_settings_form allow to save data into table variables from drupal core
        return system_settings_form($form);

    }
    /*
	 * Function for validate consulta_form
	 */
	function taxpayer_form_validate(&$form, &$form_state){
        $cedula = $form_state['values']['cedula'];
        if(strlen($cedula) < 9 ||(strlen($cedula) > 13) || !is_numeric($cedula)){
          form_set_error('cedula', t('Debe digitar un número de cédula válido'));
        }
        if(empty($cedula)|| !is_numeric($cedula)){// || strlen($_POST['g-recaptcha-response'])==0){
          form_set_error('cedula', t('Debe digitar un número de cédula válido'));
        }
      }
    /*
    * Function for submit consulta_form
    */
    function taxpayer_form_submit(&$form, &$form_state){
        $_SESSION['ced'] = $form_state['values']['cedula'];
        unset($_SESSION['firstName']);
        unset($_SESSION['dataws']);
        $_SESSION['post'] = $_POST;
        $_SESSION['data_taxpayer'] = _getDataWebs($form_state['values']['cedula']); // Get data from webservice
        $form_state['redirect'] = 'taxpayer/update';
        //if(module_exists('impuestos')){
            //$form_state['redirect'] = 'consulta/res';
        //}
    }
    /**
	* Get taxes from webservices GIM and AGP systems
	* @param $ced
	*   (integer) ID from from citizens
	* @return $result
	*   (array) Return only one array with all values got from webservices
	*/
	function _getDataWebs($ced){
        global $user, $base_url;

        $result = _ws_taxpayer($ced); // call function from webservice
        dsm($result);

        $ipadd = $_SERVER['REMOTE_ADDR'];

        if(isset($result)){
          $ced = (isset($result->return->taxpayer->identificationNumber) ? $result->return->taxpayer->identificationNumber : $ced);
          $_SESSION['firstName'] = (isset($result->return->taxpayer->fullName) ? $result->return->taxpayer->fullName : 'Contribuyente');
          watchdog('TaxpayerUpdate','Consulta: ced desde ipadd ',array('ced'=> $ced, 'ipadd' => $ipadd),WATCHDOG_DEBUG);
          // dsm($result->return->bonds);
        }
        return $result;
      }
/**
 * Update form taxpayer
 */

function taxpayer_up_form($form, &$form_state){
    global $base_url;
    $taxpayer_data = $_SESSION['data_taxpayer']->return;
    dsm($taxpayer_data);
    if(isset($taxpayer_data->identificationNumber)){

    $fullName =$taxpayer_data->firstName . " " . $taxpayer_data->lastName;

    $form['update_taxpayer'] = array(
        '#title' => t('Datos del abonado'),
        '#type' => 'fieldset',
        '#description' => t('Consulta a través de su cédula')
    );
    $form['update_taxpayer']['cedula'] = array(
        '#title' => t('Cedula'),
        '#type' => 'textfield',
        '#maxlenght' => 150,
        '#disabled' => true,
        '#default_value' => $taxpayer_data->identificationNumber,
        '#size' => 15,
        '#description' => t('Nombres del contribuyente'),
    );
    $form['update_taxpayer']['fullname'] = array(
        '#title' => t('Nombres'),
        '#type' => 'textfield',
        '#maxlenght' => 150,
        '#disabled' => true,
        '#default_value' => $fullName,
        '#size' => 15,
        '#description' => t('Nombres del contribuyente'),
    );
    $form['update_taxpayer']['email'] = array(
        '#title' => t('Correo electónico'),
        '#type' => 'textfield',
        '#maxlenght' => 150,
        '#default_value' => $taxpayer_data->email,
        '#size' => 15,
        '#description' => t('Correo del contribuyente'),
    );
    $form['update_taxpayer']['address'] = array(
        '#title' => t('Direccion'),
        '#type' => 'textfield',
        '#required' => true,
        '#maxlenght' => 150,
        '#default_value' => $taxpayer_data->street,
        '#size' => 15,
        '#description' => t('Direccion del contribuyente'),
    );
    $form['update_taxpayer']['phone'] = array(
        '#title' => t('Telefono'),
        '#type' => 'textfield',
        '#required' => true,
        '#maxlenght' => 150,
        '#size' => 15,
        '#description' => t('Telefono del contribuyente'),
    );
    //$form['#attached']['js'] = array(drupal_get_path('module','taxpayerupdate').'/js/impuestos.js',);
    $form['update_taxpayer']['save'] = array(
        '#prefix' => '<div class="consulta">',
        '#type' => 'submit',
        '#value' => t('Send'),
        '#suffix' => '<div class="nuevacon"><a class="nueva" href="'.$base_url.'/taxpayer">Nueva Consulta</a></div></div>',
    );
    }else{
        $form['update_taxpayer']['no-data']= array(
            '#markup' => '<div><h3>El número de cédula no devuelve datos</h3></div><div class="nuevacon"><a class="nueva" href="'.$base_url.'/consulta">Nueva Consulta</a></div>',
        );
    }
    return $form;
}
/**
* Function for validate consulta_form
*/
function taxpayer_up_form_validate(&$form, &$form_state){
//    $cedula = $form_state['values']['cedula'];
//    if(strlen($cedula) < 9 ||(strlen($cedula) > 13) || !is_numeric($cedula)){
//      form_set_error('cedula', t('Debe digitar un número de cédula válido'));
//    }
//    if(empty($cedula)|| !is_numeric($cedula)){// || strlen($_POST['g-recaptcha-response'])==0){
//      form_set_error('cedula', t('Debe digitar un número de cédula válido'));
//    }
 }
 /*
  * Function for submit consulta_form
  */
 function taxpayer_up_form_submit(&$form, &$form_state){
//    $_SESSION['ced'] = $form_state['values']['cedula'];
//    unset($_SESSION['firstName']);
//    unset($_SESSION['dataws']);
//    $_SESSION['post'] = $_POST;
//    $_SESSION['data_taxpayer'] = _getDataWebs($form_state['values']['cedula']); // Get data from webservice
//    $form_state['redirect'] = 'taxpayer/update';

      $data = $form_state['values'];
      $emails = variable_get('emails'); // get data from admin form (table variables from drupal core)
      drupal_mail('taxpayerupdate','taxpayer', $emails, language_default(), $data);
      save_taxpayertable($data);
      $_SESSION['data_taxpayer'] = $data;
      $form_state['redirect'] = 'taxpayer/confirm';
 }

 /**
  * INSERT data into table
  */
  function save_taxpayertable($data){
    $vpos = array();
    $vpos['date_tax'] = Date("Y-m-d H:i:s");
    $vpos['dni_tax'] = $data['cedula'];
    $vpos['lastname_tax'] = $data['fullname'];
    $vpos['address_tax'] = $data['address'];
    $vpos['mail_tax'] = $data['email'];
    $vpos['phone_tax'] = $data['phone'];
    drupal_write_record('taxpayerupdate',$vpos);
  }

/**
* Consumo de emisiones futuras
* @param cedula  - Numeric
*/

function _ws_taxpayer($cedula){
    $serv = wsclient_service_load('taxpayer');
    $result = '';
    try{
      $serviceRequest = array(
        'identificationNumber' => (String)$cedula,
        'username' => 'munpayclub', //199
        'password' => 'bfc2b6f7-9eea-4368-9cb0-cde8e2da37f7',   //199
        'tramitId' => ''
      );
      $findStatement = array(
          'arg0' => $serviceRequest
      );
      // Call operation findStatement with parameters
      $result = $serv->findTaxpayer($findStatement);
      //dsm($result);
      return $result;

    }catch(WSClientException $f){
      //echo $f;
    }
    return $result;
  }

  /**
   * Confirm page taxpayer update
   */
  function confirm_page(){
    $message = '<div>Gracias</div>' . $_SESSION['data_taxpayer']['fullname'];
    $message .= '<div>' . variable_get('message_confirm') . '</div>';
    $message .= '<div>La informacion ha sido recibida</div>';
    return $message;
  }
