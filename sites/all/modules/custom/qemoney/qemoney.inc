<?php
/**
* TEST PAGE
*/
global $rubros;

/**
* Test Page
*/
function test_page(){    
  $idr = $_POST['rubro'];
  dsm($_POST);
  $rubros = $_SESSION['rubros'];
  $nr = $rubros[$idr];
  dsm($_SESSION);
  dsm($nr);  
  return '<h1>Pagina de Prueba</h1>';
}

/**
* Formulario de consulta 
*/
function consultando_form($form, $form_state){
  $_SESSION['dataws'] = NULL; // Reset de sesssion variable
  $rubros = array(
    0 => 'PREDIO URBANO',
    1 => 'PREDIO RUSTICO',
    2 => 'SERVICIO DE AGUA POTABLE',
    3 => 'MULTAS COMISARIA DE ORNATO',
    4 => 'ARR. PUESTOS EN LOS MERCADOS',
  ); 
  $_SESSION['rubros'] = $rubros;

  $form['consulta'] = array(
      '#title' => t('Datos del abonado'),
      '#type' => 'fieldset',
      '#description' => t('Consulta a traves de su cédula y pague con dinero electrónico')
  );
  $form['consulta']['cedula'] = array(
      '#title' => t('Número de cédula'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 15,
      '#description' => t('Your ID have to 10 characters'),
        );
  $form['consulta']['rubro'] = array(
    '#type' => 'select',
    '#title' => t('Rubro a consultar'),
    '#required' => true,
    '#description' => t('Elija el rubro que desea pagar'),
    '#options' => $rubros,
    '#default_value' => 2,
  );
  $form['consulta']['captcha'] = array(
    '#type' =>  'captcha',
    //'#captcha_type' =>  'recaptcha/reCAPTCHA',
    '#captcha_type' =>  'captcha/Math',
    //'#captcha_type' =>  'image_captcha/Image',
  );

  $form['#action'] = 'http://loja71.local.drw/emoney/res';
  //$form['#action'] = 'https://www.loja.gob.ec/consulta/resultado';
  //$form['#attached']['js'] = array(drupal_get_path('module','impuestos').'/js/impuestos.js',);
  
  $form['consulta']['save'] = array(
      '#prefix' => '<div class="consulta">',      
      '#type' => 'submit',
      '#value' => t('Consultar'),
      '#suffix' => '</div>',
  );
  return $form;
}
/**
*
*/
/*
 * Function for validate consulta_form
 */
function consultando_form_validate($form, &$form_state){
  $cedula = $form_state['values']['cedula'];
  if(strlen($cedula) < 10 ||(strlen($cedula) > 13) || !is_numeric($cedula)){
    form_set_error('cedula', t('Debe digitar un número de cedula valido'));
  }
}
/*
 * Function for submit consulta_form
 */
function consultando_form_submit($form, &$form_state){  
  if(module_exists('impuestos')){
    //$form_state['redirect'] = 'consulta/res';
  }
  dsm("Hola desde el submit");
  $_SESSION['nrubro']  = $form_state['values']['rubro'];
  //$form_state['redirect'] = 'emoney/test';
}
/**
* Result Page
*/
function qemoney_resultado(){
  dsm($_SESSION);
  dsm($_POST);
  return "Pagina de resultado qemoney";
}
/**
* Function for generate a table with checkboxes to get data from webservices
* @param $form
*   Properties from form
* @param $form_state
*   Values from form
*/
function taxese_form($form, $form_state){
  if(empty($_POST)){
    return drupal_goto('http://loja71.local.drw/emoney/consulta');
  }
  
  $ced = $_POST['cedula'];
  $rubro = $_POST['rubro'];
  /*if(!is_numeric($ced)){
    return drupal_goto('http://www.loja.gob.ec/consulta');
  }*/
  $header = array(
    'codSer'  => t('Código de Servicio'),
    'rubro'   => t('Rubro'),
    'fInicio' => t('Fecha Emisión'),
    'fFin'    => t('Fecha de Expiración'),
    'monto'   => t('Valor'),
    );

  $default_value  = array();
  $options        = array();
  $sum            = 0;

  if(empty($_SESSION['dataws'])){     
    $dataws = _getDataWebs($ced, $rubro); // Fill array with data get from web services
    $_SESSION['dataws'] = NULL;
  }else{
    $dataws = $_SESSION['dataws'];
    $ced = $_SESSION['ced'];
  }
  $cliente = $_SESSION['firstName'];
  dsm($dataws);
  foreach ($dataws as $tax) {
    $options[$tax['sku']] = array(
        'codSer'  => $tax['codSer'],
        'rubro'   => $tax['rubro'],
        'fInicio' => $tax['fInicio'],
        'fFin'    => $tax['fFin'],
        'monto'   => $tax['monto'],
      );
    $sum += (float) $tax['monto'];
  }
  //asort($options);  // Sort by codServ and Date but the key is changed
  //$data = keyfrom1($options, FALSE); // Change keys from number 1   

  $default_value[0]  = true;
  $form['taxes'] = array(
    '#type'     => 'tableselect',
    '#title'    =>  t('Tabla con datos'),
    '#header'   =>  $header,
    '#options'  =>  $options,
    '#prefix'   => '</br><strong>Nombre:</strong> '.$cliente.'</br><strong>Cedula:</strong> '.$ced,        
    '#js_select'=>  TRUE,
    '#empty'    =>  t('No dispone de impuestos por pagar con el RUBRO seleccionado'),
    '#default_value'=> $default_value,
    );
  $form['submit'] = array(
    '#type'   => 'submit',
    '#prefix' => '<div class="totalq">'.$sum.'</div>',    
    '#suffix' => '<div><a href="consulta">Nueva Consulta</a></div><p><strong>RECUERDE:</strong>Que para hacer uso del dinero electr&oacute;nico Ud debe activar su cuenta de dinero electr&oacute;nico y recargar su tel&eacute;fono celular</div><div><!--<a href="https://goo.gl/vqw9x3">Descargar manual de pagos</a>--></div>',    
    '#value'  =>  t('Pagar Impuestos'),
    );  
  // Store data in session vars and validate open checkout

  /*if(validateCaja()){
      $form['submit']['#disabled'] = FALSE;
  }else{
      $form['submit']['#disabled'] = TRUE;
      drupal_set_message("Pagos no disponibles :: Caja Cerrada");
      //impuestos_mesg();
  }*/
  $_SESSION['dataws'] = $dataws;
  $_SESSION['ced'] = $ced;

  return $form;
}
/**
* Function for validate the data before submit the results
*
*/
function taxese_form_validate($form, &$form_state){
//  $ced = $form_state['values']['cedula'];
  #global $ced;
  $ced = $_SESSION['ced'];
//  global $dataws;  // Have data with all taxes get from GIM system
  $dataws = $_SESSION['dataws'];

  $fechahora = date('H:i:s');

  $lenA = sizeof($dataws);
  $sel = array_filter($form_state['values']['taxes']); // Get the values selected from tableselect
  $pagar = FALSE;
  
  $lenB = sizeof($sel);  
  if($lenB != 0){ 
  /*  foreach ($sel as $key) {      
        if($key == 1){
          $pagar = TRUE;
        }else{
          $ant = $dataws[$key-1]['codSer'] . $dataws[$key-1]['rubro'];
          $act = $dataws[$key]['codSer'] . $dataws[$key]['rubro'];
          
          if($ant == $act){
            if(in_array($key, $sel) && in_array($key-1, $sel)){
              $pagar = TRUE;
            }else{
              $pagar = FALSE;
              break;
            }            
          }else{
            if(in_array($key-1, $sel)){
              if($ant == $act){
                $pagar = TRUE;
              }
            }else{              
              if($ant == $act){
                $pagar = FALSE;
                break;
              }else{
                $pagar = TRUE;
              }
            }
          }
        }
    }// End foreach
*/ 
    // The payment only can do it between 08 and 17 hours
     if (!($fechahora > "08:00:00" && $fechahora < "17:30:00")){
      form_set_error("taxes","El horario de pago es de 08H00 a 17H00");
    }
    if(user_is_anonymous()){
      form_set_error("taxes","Debe <a class='registro' href='https://www.loja.gob.ec/user/register'>registrarse</a> e ingresar al sitio para poder efectuar Pagos");
    }
    if($lenA == $lenB){$pagar = TRUE;}
    else $pagar = FALSE;
    if($pagar){
      //drupal_set_message("Puede pagar");
      $dataws = array_intersect_key($dataws, $sel); // Get intersection between keys
      $_SESSION['dataws'] = $dataws;
            
    }else{      
      //form_set_error("taxes","No puede pagar debiendo meses anteriores");
      form_set_error("taxes","Debe pagar todos los impuestos listados impuestos");
    }
  }else{
    form_set_error("taxes","Debe elegir todos los rubros para realizar el pago");    
  }// End if lenB !=0  
  
}
/**
* Function for submit the results and data
*
*/
function taxese_form_submit($form, &$form_state){ 
  
  global $dataws;  
  $dataws = $_SESSION['dataws'];
  // params id_product and data array
  create_order_with_impuestos(2,$dataws);  
}

/**
 * Function for make query to web service with identificationNumber
 * @param $product_id
 *    Identification number for product
 * @param $line_item_values
 *    (Array) taxes for include into one order
 */
// Example from http://anthonypower.com/notebook/creating-orders-custom-line-items-using-drupal-commerce-api
function create_order_with_impuestos($product_id, $line_item_values = array(), $uid = NULL, $use_cart = TRUE) {
  global $user;
  global $ced;
  $ced = $_SESSION['ced'];

  // Make sure the user id is set.
  if (is_null($uid)) {
    $uid = $user->uid;
  }  
 
  // First, see if there is already a cart for this user.
  // Here we will not assume that commerce_cart is enabled.
  if (module_exists('commerce_cart') && $use_cart) {
    $order = commerce_cart_order_load($uid);

  }
 
  ////if (empty($order)) {
    // Create the new order in checkout status with a custom order type of "donate_now_order_type".    
    // $order = commerce_order_new($uid, 'commerce_checkout');
    // The next line is alter with checkout_checkout for allows payment :: DRW
    $order = commerce_order_new($uid, 'checkout_checkout');
 
    // Save the order so its ID is assigned.
    commerce_order_save($order);
  ////}
  
 
  // Load whatever product represents the item the customer will be
  // paying for and create a line item for it.
  $product = commerce_product_load($product_id);
  $keybond = 0;  
 foreach ($line_item_values as $field_name => $value) {
  // Create a line item with quantity 1 and this product.
  $line_item = commerce_product_line_item_new($product, 1, $order->order_id, array(), 'impuestoline');  
  
  // Add the custom values to the line_item fields
  
    //$line_item->{$field_name}[LANGUAGE_NONE][0]['value'] = $value['$field_name'];
    //$line_item->commerce_price[LANGUAGE_NONE][0]['amount'] = 40;
    $line_item->field_rubro_li[LANGUAGE_NONE][0]['value'] = $value['rubro'];
    $line_item->field_fecha_pa_li[LANGUAGE_NONE][0]['value'] = $value['fInicio'];
    $line_item->field_monto_li[LANGUAGE_NONE][0]['value'] = (float) $value['monto'];
    $line_item->field_servicio_li[LANGUAGE_NONE][0]['value'] = $value['codSer'];

    $bondIds[$keybond++] = $value['id'];  // BondId
    $bondNum[$keybond++] = $value['number']; // BondNumber
 
  // Save the line item to get its ID.
  commerce_line_item_save($line_item);
 
  // Add the line item to the order using the wrapper.
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $order_wrapper->commerce_line_items[] = $line_item;  
 }

 $_SESSION['bondsid'] = $bondIds;  // Set variable on session browser for recover later
 $_SESSION['bondsNum'] = $bondNum;  // Set variable on session browser for recover later
 $_SESSION['ced'] = $ced;

  // Save the order again to update its line item reference field.    
  commerce_order_save($order);
  
  //return $order->order_id;
  drupal_goto('checkout/' . $order->order_id);
}


/**
 * Function for make query to web service with identificationNumber from GIM System
 * this function call a webservice called impuesto
 * @param $ced 
 *    (string) Identification Number from customer (client)
 * @return 
 *    (array) Taxes data and personal information from customer
 */
function _ws_impuesto($cedula){
  if(empty($cedula)|| !is_numeric($cedula)){
    return drupal_goto('https://www.loja.gob.ec/emoney/consulta');
  }

  $result = array();
  // Call selected web service with name at next function
  ini_set('soap.wsdl_cache_enabled',0);
  $serv = wsclient_service_load('impuesto');  

  try{    
    $serviceRequest = array(
        //'identificationNumber' => '1103756845',
        'identificationNumber' => (String)$cedula,
        'username' => 'dabetancourtc',
        'password' => 'Loja.2015.IML', // PROD 199 
//        'username' => 'munpayclub',
//        'password' => '75e10d8c-937d-47f6-a21d-bc930cd8b9c9', // PROD 199 
        'tramitId' => ''
    );
    $findStatement = array(
        'arg0' => $serviceRequest
    );
    // Call operation findStatement with parameters    
    $result = $serv->findStatement($findStatement);
    return $result;
//    watchdog('impuestos','Se ejecuto la consulta con datos de acceso',array(),WATCHDOG_DEBUG);
    
  }catch(WSClientException $f){
    //If the connection is failed the return will be FALSE
    //echo $f;    
  }
  
  return $result;
}

/**
* Get taxes from webservices GIM and AGP systems
* @param $ced
*   (integer) ID from from citizens
* @return $alltaxes
*   (array) Return only one array with all values got from webservices
*/
function _getDataWebs($ced, $rubro){
  
  $rubros = array(
    0 => 'PREDIO URBANO',
    1 => 'PREDIO RUSTICO',
    2 => 'SERVICIO DE AGUA POTABLE',
    3 => 'MULTAS COMISARIA DE ORNATO',
    4 => 'ARR. PUESTOS EN LOS MERCADOS',
  );

  if(empty($ced)|| !is_numeric($ced)){
    return drupal_goto('https://www.loja.gob.ec/emoney/consulta');
  }
  dsm($rubros);

  $result = array();

  $result = _ws_impuesto($ced); // call function from webservice
  
  $ipadd = $_SERVER['REMOTE_ADDR'];
  
  $suma = 0;  // save sum values
  $par = 1;   // Control class table "even" and "odd" for TR element  
  $alltaxes = array(); // Store all values taxes in only one array 

  if(isset($result)){ 
    $ced = $result->return->taxpayer->identificationNumber;
    $_SESSION['firstName'] = $result->return->taxpayer->firstName;
    watchdog('impuestos','Consulta realizada para: ced desde ipadd',array('ced'=> $ced, 'ipadd' => $ipadd),WATCHDOG_DEBUG);

    
    if(isset($result->return->bonds)){          
      // Get size from array
      $lengthB = sizeof($result->return->bonds);
      // if array have just one element      
      if($lengthB == 1){
        //$suma = $suma + (float)$result->return->bonds->total;
        dsm($rubros[$rubro]);
        if($rubros[$rubro] == $result->return->bonds->account){   // Comprobate account     
          $alltaxes[$par] = array(          
            'codSer'  => $result->return->bonds->serviceCode,
            'rubro'   => $result->return->bonds->account,
            'fInicio' => substr($result->return->bonds->serviceDate, 0, 10),
            'fFin'    => substr($result->return->bonds->expirationDate, 0, 10),
            'monto'   => $result->return->bonds->total,
            'id'      => $result->return->bonds->id, // Bond's Id for register payment
            'number'      => $result->return->bonds->number, // Bond's Id for register payment
            'sku'     => $par,
            );
        }
        $par+=1;
      }
      // More than one element
      else{        
        for($i=0; $i<$lengthB; $i++){          
          if($rubros[$rubro] == $result->return->bonds[$i]->account){   // Comprobate account     
            $alltaxes[$par] = array(          
            'codSer'  => substr($result->return->bonds[$i]->serviceCode,0,15),
            'rubro'   => $result->return->bonds[$i]->account,
            'fInicio' => substr($result->return->bonds[$i]->serviceDate, 0, 10),
            'fFin'    => substr($result->return->bonds[$i]->expirationDate, 0, 10),
            'monto'   => $result->return->bonds[$i]->total,
            'id'  => $result->return->bonds[$i]->id,
            'number'  => $result->return->bonds[$i]->number,
            'sku'     => $par,
            );
          }
          $par+=1;          
        }        
      }// End else      
    }    
  }
  return $alltaxes;
}


