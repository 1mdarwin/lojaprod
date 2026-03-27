<?php
	// 1100048451 varios medidores
	//

	$ced = '';
	$dataws = array();
	$cliente = '';
	$sum = 0;
	$bondIds = array();

	function consulta_form($form, &$form_state){
	  global $base_url;  
          
	  $enabledtaxes =  variable_get('taxesquery', 0);
	  if($enabledtaxes == 1){
		return drupal_goto($base_url .'/consultam');
	  }
          
	  $impuestospopulares = array(
	    "TODOS" => "TODOS",
	    "SERVICIO DE AGUA POTABLE" => "SERVICIO DE AGUA POTABLE",
	    "PREDIO URBANO" => "PREDIO URBANO",
	    "PATENTE MUNICIPAL" => "PATENTE MUNICIPAL",
	    "ALCABALAS" => "ALCABALAS",
	    "UTILIDAD EN LA VENTA DE PREDIOS" => "UTILIDAD EN LA VENTA DE PREDIOS",
	    "PREDIO RUSTICO" => "PREDIO RUSTICO",
	    "IMPUESTO A LOS ACTIVOS TOTALES" => "IMPUESTO A LOS ACTIVOS TOTALES",
	    "ARR. BODEGAS,EDIF,LOCALES,TIERRAS" => "ARR. BODEGAS,EDIF,LOCALES,TIERRAS",
	    "CEM (OTRAS CONTRIBUCIONES) GLOBALES" => "CEM (OTRAS CONTRIBUCIONES) GLOBALES",
	    "PAVIMENTACION CIUDAD ALEGRIA" => "PAVIMENTACION CIUDAD ALEGRIA",
	    "PAVIMENTACION PITAS I" => "PAVIMENTACION PITAS I",
	    "SOLARES NO EDIFICADOS" => "SOLARES NO EDIFICADOS",
	    "USO Y ESTACIONAMIENTO TERMINAL TERR" => "USO Y ESTACIONAMIENTO TERMINAL TERR",
	    "SERVICIOS TECNICOS Y ADMINISTRATIVO" => "SERVICIOS TECNICOS Y ADMINISTRATIVO",
	    "MULTAS PATENTE MUNICIPAL" => "MULTAS PATENTE MUNICIPAL"
	  );  

	  if(isset($_SESSION['dataws'])){
	    unset($_SESSION['dataws']);
	  }
	  $form['consulta'] = array(
	      '#title' => t('Datos del abonado'),
	      '#type' => 'fieldset',
	      '#description' => t('Consulta a través de su cédula y por RUBRO'),
              '#suffix' => t('Para consulta de infracciones de tránsito, haga <a href="/infracciones">clic aquí</a></br>')
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
	      '#title' => t('Rubro del impuesto a consultar'),
	      '#type' => 'select',
	      '#required' => true,
	      '#options' => $impuestospopulares,
	      '#default_value' => 'TODOS'
	  );
 	  //if(!user_is_logged_in()){
	  $form['consulta']['captcha'] = array(
	    '#type' =>  'captcha',
	    '#captcha_type' =>  'recaptcha/reCAPTCHA',  // prod
	    //'#captcha_type' =>  'captcha/Math', // test
	    //'#captcha_type' =>  'image_captcha/Image',    
	  );
	  //} 
	  //$form['#action'] = $base_url . '/consulta/res';  
	  //$form['#action'] = 'https://www.loja.gob.ec/consulta/resultado';
	  $form['#attached']['js'] = array(drupal_get_path('module','impuestos').'/js/impuestos.js',);
	  $form['consulta']['save'] = array(
	      '#prefix' => '<div class="consulta">',
	      '#type' => 'submit',
	      '#value' => t('Consultar'),
	      '#suffix' => '</div>',      
	  );  
	  return $form;
	}
	/*
	 * Function for validate consulta_form 
	 */
	function consulta_form_validate(&$form, &$form_state){
	  /*$cedula = $form_state['values']['cedula'];
	  if(strlen($cedula) < 9 ||(strlen($cedula) > 13) || !is_numeric($cedula)){
	    form_set_error('cedula', t('Debe digitar un número de cédula válido'));
	  }
	  if(empty($cedula)|| !is_numeric($cedula)){// || strlen($_POST['g-recaptcha-response'])==0){
	    form_set_error('cedula', t('Debe digitar un número de cédula válido'));
	  }*/
	}
	/*
	 * Function for submit consulta_form
	 */  
	function consulta_form_submit(&$form, &$form_state){
	  $_SESSION['ced'] = $form_state['values']['cedula'];
	  unset($_SESSION['firstName']);
	  unset($_SESSION['dataws']);
	  $_SESSION['post'] = $_POST;  
	  $_SESSION['dataws'] = _getDataWebs($form_state['values']['cedula']); // Get data from webservice
	  $form_state['redirect'] = 'consulta/res';
	  //if(module_exists('impuestos')){
	    //$form_state['redirect'] = 'consulta/res';
	  //}  
	}
	/**
	* Admin pages with form
	*/
        function impuestos_admin_form($form, &$form_state){
		$form['payments'] = array(
			'#title' => t('Payments with credit card'),
			'#type' => 'fieldset',
			'#description' => t('Pagos con tarjeta de crédito para <strong>el rol administrador</strong>')
		);
		$form['payments']['payments_all'] = array(
			'#type' => 'checkbox',
			'#title' => t('Allow Payments only to administrator rol'),			
			//'#required' => TRUE,
			'#default_value' => variable_get('payments_all', 0),
		);
		$form['endyear'] = array(
			'#title' => t('End of year'),
			'#type' => 'fieldset',
			'#description' => t('Deshabilitar consulta por fin de año')
		);
		$form['endyear']['taxesquery'] = array(
			'#type' => 'checkbox',
			'#title' => t('Disabled Taxes Query'),			
			//'#required' => TRUE,
			'#default_value' => variable_get('taxesquery', 0),
		);
		$form['endyear']['message'] = array(
			'#type' => 'textarea',
			'#title' => t('Message for Disabled Taxes Query'),			
			//'#required' => TRUE,
			'#default_value' => variable_get('message', "welcome"),
		);
	        $form['notifypayment'] = array(
			'#title' => t('Emails for notification'),
			'#type' => 'fieldset',
			'#description' => t('Email address for notification')
		);		
		$form['notifypayment']['n_email'] = array(
			'#type' => 'textarea',
			'#title' => t('Add email address separated by semicolons'),			
			//'#required' => TRUE,
			'#default_value' => variable_get('n_email', "dabetancourt@loja.gob.ec"),
		);
		// system_settings_form allow to save data into table variables from drupal core
		return system_settings_form($form);
		
	}

	/**
	* Get taxes from webservices GIM and AGP systems
	* @param $ced
	*   (integer) ID from from citizens
	* @return $alltaxes
	*   (array) Return only one array with all values got from webservices
	*/
	function _getDataWebs($ced){
	  global $user, $base_url;
	  if( empty($_POST['g-recaptcha-response'])){
		 //dsm('captcha vacio');
	  } 
 	  // if(!user_is_logged_in()){
	  if(empty($ced) || strlen($_POST['g-recaptcha-response'])==0){
	    unset($_SESSION['rubro']);
	    return drupal_goto($base_url.'/consulta');
	  }
	  // }
	  $_SESSION['rubro'] = $_POST['rubro'];
	  $rubro = (isset($_SESSION['rubro']) ? $_SESSION['rubro'] : 'TODOS');

	//  $ced = variable_get('ced1');
	  $result = array();
	  $rango_impuestos = array();
	  $patente_list = array(
	    "PATENTE MUNICIPAL",
	    "IMPUESTO A LOS ACTIVOS TOTALES",
	    "MULTAS PATENTE MUNICIPAL"  
	  );
	  $agua_list = array(
	    "SERVICIO DE AGUA POTABLE",
	    "CEM (OTRAS CONTRIBUCIONES) GLOBALES"
	  );  
	  $alcabala_list = array(
	    "ALCABALAS",
	    "UTILIDAD EN LA VENTA DE PREDIOS"
	  );

	  // Asign selected array to another array
	  switch ($rubro) {
	    case 'SERVICIO DE AGUA POTABLE':
	      $rango_impuestos = $agua_list;
	      break;
	    case 'PATENTE MUNICIPAL':
	      $rango_impuestos = $patente_list;
	      break;
	    case 'ALCABALAS':
	      $rango_impuestos = $alcabala_list;
	      break;
		  
	    default:
	      $rango_impuestos = array($rubro => $rubro);
	      break;
	  }

	  $result = _ws_impuesto($ced); // call function from webservice
	  //dsm($result);
	  // $query = ws_emaalep($ced);
	  $ipadd = $_SERVER['REMOTE_ADDR'];
	  
	  $suma = 0;  // save sum values
	  $par = 1;   // Control class table "even" and "odd" for TR element  
	  $alltaxes = array(); // Store all values taxes in only one array 

	  if(isset($result)){ 
	    $ced = (isset($result->return->taxpayer->identificationNumber) ? $result->return->taxpayer->identificationNumber : $ced);
	    //$ced = $result->return->taxpayer->identificationNumber;
	    //$_SESSION['firstName'] = $result->return->taxpayer->firstName;
	    $_SESSION['firstName'] = (isset($result->return->taxpayer->firstName) ? $result->return->taxpayer->firstName : 'Contribuyente');
	    //watchdog('impuestos','Consulta para: ced desde ipadd',array('ced'=> $ced, 'ipadd' => $ipadd),WATCHDOG_DEBUG);
	    watchdog('impuestos','Consulta: ced desde ipadd con :rubro',array('ced'=> $ced, 'ipadd' => $ipadd, ':rubro' => $rubro),WATCHDOG_DEBUG);
	    // dsm($result->return->bonds); 
	    if(isset($result->return->bonds)){                
	    // if(isset($result->return->bonds) && is_array($result->return->bonds)){                
	      // Get size from array
	      // $lengthB = count($result->return->bonds);
	      $lengthB = is_array($result->return->bonds) ? count($result->return->bonds) : count(array($result->return->bonds));
	      if ($rubro == 'TODOS'){        
		$alltaxes = fill_taxes($result->return->bonds);
	      }else{
		// if array have just one element      
		if($lengthB == 1){
		  //$remision = json_decode($result->return->bonds->metadata, false); // transform the json data
		  //$suma = $suma + (float)$result->return->bonds->total;
		  $srvcode = (isset($result->return->bonds->serviceCode) ? $result->return->bonds->serviceCode : '');
		  if(in_array($result->return->bonds->account, $rango_impuestos)){
		    $alltaxes[$par] = array(          
		    'codSer'  => $srvcode,
		    'rubro'   => $result->return->bonds->account,
		    'fInicio' => substr($result->return->bonds->serviceDate, 0, 10),
		    'fFin'    => substr($result->return->bonds->expirationDate, 0, 10),
		    'monto'   => $result->return->bonds->total,
		    'id'      => $result->return->bonds->id, // Bond's Id for register payment
		    'number'      => $result->return->bonds->number, // Bond's Id for register payment
		    'interes' => 0,
		    'recargo' => 0,
			#'interes' => $remision->interest,
		    #'recargo' => $remision->surcharge,
		    'sku'     => $par,
		    );
		    $par+=1;          
		  }
		}
		// More than one element
		else{        
		  for($i=0; $i<$lengthB; $i++){          
			  #$remision = json_decode($result->return->bonds[$i]->metadata, false);
			  if(isset($result->return->bonds[$i]->serviceCode)){
				  $srvcode = substr($result->return->bonds[$i]->serviceCode,0,15);
			  }else{
				  $srvcode = '';
			  }        
		    if(in_array($result->return->bonds[$i]->account, $rango_impuestos)){
		      $alltaxes[$par] = array(            
		      'codSer'  => $srvcode,
		      'rubro'   => $result->return->bonds[$i]->account,
		      'fInicio' => substr($result->return->bonds[$i]->serviceDate, 0, 10),
		      'fFin'    => substr($result->return->bonds[$i]->expirationDate, 0, 10),
		      'monto'   => $result->return->bonds[$i]->total,
		      'id'  => $result->return->bonds[$i]->id,
		      'number'  => $result->return->bonds[$i]->number,    	        
			'interes' => 0,
		      'recargo' => 0,
		      'sku'     => $par,
		      );            
		      $par+=1;
		    }
		    
		  }// end for        
		}// End else
	      }// End else - Todos (rubro)      
	    }    
	  }
	  return $alltaxes;
	}
	/**
	* this function is for total query without filters
	* @param $query
	*         Values from webservice GIM - multidimensional array
	* @return $alltaxes
	*         Return all taxes into array
	*/
	function fill_taxes($query){
	  $par = 1;  
	  // $lenQuery = count($query);
          $lenQuery = is_array($query) ? count($query) : count(array($query));
	  if($lenQuery == 1){        
		if(isset($query->serviceCode)){
		  $srvcode = $query->serviceCode;
		}else{
		  $srvcode = '';
		}        
		$alltaxes[$par] = array(          
		  'codSer'  => $srvcode,
		  'rubro'   => chgPredioName($query->account),
		  'fInicio' => substr($query->serviceDate, 0, 10),
		  'fFin'    => substr($query->expirationDate, 0, 10),
		  'monto'   => $query->total,
		  'id'      => $query->id, // Bond's Id for register payment
		  'number'  => $query->number, // Bond's Id for register payment
		  'interes' => 0,
		  'recargo' => 0,
		  #'interes' => $remision->interest,
		  #'recargo' => $remision->surcharge,
		  'sku'     => $par,
		);
		$par+=1;
	  }
	  // More than one element
	  else{
	    for($i=0; $i<$lenQuery; $i++){            
	      if(isset($query[$i]->serviceCode)){
		$srvcode = substr($query[$i]->serviceCode,0,15);
	      }else{
		$srvcode = '';
	      }
	      $alltaxes[$par] = array(            
		'codSer'  => $srvcode,
		'rubro'   => chgPredioName($query[$i]->account),
		'fInicio' => substr($query[$i]->serviceDate, 0, 10),
		'fFin'    => substr($query[$i]->expirationDate, 0, 10),
		'monto'   => $query[$i]->total,
		'id'  => $query[$i]->id,
		'number'  => $query[$i]->number,          
		'interes' => 0,
		'recargo' => 0,
		'sku'     => $par,
	      );            
	      $par+=1;                
	    }// end for    
	  }
	  return $alltaxes;
	}

	/**
	* Function for generate a table with checkboxes and get data from webservices
	* Take values from form and captcha
	* @param $form
	*   Properties from form
	* @param $form_state
	*   Values from form
	*/
	function taxes_form($form, $form_state){
	  global $base_url, $user;  
	  $_POST = (isset($_SESSION['post']) ? $_SESSION['post'] : null);
	  //$_POST = $_SESSION['post'];  
	  if(empty($_POST)){
	    return drupal_goto($base_url .'/consulta');
	  }
	  $ced = $_POST['cedula'];
	  $_SESSION['rubro'] = $_POST['rubro'];
	  

	  /*if(!is_numeric($ced)){
	    return drupal_goto('http://www.loja.gob.ec/consulta');
	  }*/
	  $header = array(
	    'codSer'  => t('Código de Servicio'),
	    'rubro'   => t('Rubro'),
	    'fInicio' => t('Fecha de Servicio'),
	    'fFin'    => t('Fecha de Expiración'),
	    'monto'   => t('Valor'),
	    );

	  $default_value  = array();
	  $options        = array();
	  $sumInteres = 0;  // Sum Interest
	  $sumRecargo = 0; // Sum subcharge
	  $sum            = 0;
	  $dataws = array();

	//  global $ced;  
	  //global $dataws;
	  if(empty($_SESSION['dataws'])){ 
	    //$dataws = _getDataWebs($ced); // Fill array with data get from web services
	    
	    $_SESSION['dataws'] = NULL;
	  }else{
	    //unset($_SESSION['dataws']);
	    $dataws = $_SESSION['dataws'];
	    $ced = $_SESSION['ced'];
	  }
	  $cliente = $_SESSION['firstName'];
	  // $cliente = (isset($_SESSION['firstName']) ? $_SESSION['firstName'] : 'Contribuyente');
	  // dsm($dataws);
	  if(sizeof($dataws) > 0){ 
	  foreach ($dataws as $tax) {
	    $options[$tax['sku']] = array(
		'codSer'  => $tax['codSer'],
		'rubro'   => $tax['rubro'],
		'fInicio' => $tax['fInicio'],
		'fFin'    => $tax['fFin'],
		'monto'   => $tax['monto'],
	      );
	    //$sumInteres += (float) $tax['interes'];
	    $sumInteres += 0;
	    $sumRecargo += 0;
	    $sum += (float) $tax['monto'];
	    
	    $sumInteres = number_format((float)$sumInteres, 2, '.', ''); // Format with 2 decimals
	    $sumRecargo = number_format((float)$sumRecargo, 2, '.', '');
	    $sum = number_format((float)$sum, 2, '.', '');
	  }
	  asort($options);  // Sort by codServ and Date but the key is changed
	  }//end if sizeof
	  $data = keyfrom1($options, FALSE); // Change keys from number 1   
	  $emision = emisionFuturaView($ced);
 	  # $emision = ''; # comment this line for enabled the future emision

	  $default_value[0]  = true;
	  $form['taxes'] = array(
	    '#type'     => 'tableselect',
	    '#title'    =>  t('Tabla con datos'),
	    '#header'   =>  $header,
	    '#options'  =>  $data,
	    '#prefix'   => '<div class="contribuyente">
			      <div class="nombrecon"><strong>Nombre:</strong> '.$cliente.'</div><div class="apecon"><strong>Cédula:</strong> '.$ced.'</div><div><strong>Rubro Seleccionado:</strong> '.$_POST['rubro'].'</div>
			    </div>',        
	    '#js_select'=>  TRUE,
	    '#empty'    =>  t('No dispone de impuestos por pagar'),
	    '#default_value'=> $default_value,
	    );
	  $notadescuento = '<div><strong>Nota:</strong> En el valor mostrado ya esta incluido el 10% de descuento</div>';
	  $form['submit'] = array(
	    '#type'   => 'submit',
	    '#prefix' => '
			  <div class="totalq">' .$sum.'</div>' 
			 . '<div>' .$emision. '</div>',    
	    '#suffix' => '<div class="nuevacon"><a class="nueva" href="'.$base_url.'/consulta">Nueva Consulta</a></div>
			  <div class="notas">
			    <p><strong>RECUERDE:</strong> Se pueden efectuar pagos con tarjeta de crédito en DIFERIDO desde 10 USD en adelante</p>
			    <p><strong></strong>Pagos con tarjeta de débito y crédito, en CORRIENTE HASTA 300 USD con cualquier tarjeta de
débito, tarjeta de crédito Diners club, Discover, Visa y Mastercard de cualquier banco Nacional</p>
			    <div><strong>Tarjetas Aceptadas en diferido:</strong> 
				<ul>
				  <li><strong>Diners Club:</strong> emitidas en el Ecuador siglas ZD</li>
				  <li><strong>Discover Card:</strong> emitida por Diners Club del Ecuador</li>
				  <li><strong>Visa TITANIUM, Mastercard TITANIUM</strong> </li>
				  <li><strong>Banco del Pichincha:</strong> Visa o Mastercard, Tarjeta de débito.</li>
				  <li><strong>Banco de Loja:</strong> Visa,  Tarjeta de débito.</li>
				  <li><strong>Banco General Rumiñahui:</strong> Visa, Tarjeta de débito.</li>
				  <li><strong>Banco Comercial de Manabí:</strong> Visa, Tarjeta de débito.</li>
				</ul>
			     </div>
			    <div class="manualpagos"><a href="https://goo.gl/vqw9x3">Descargar manual de pagos</a></div>
			  </div>',    
	    '#value'  =>  t('Pagar Impuestos'),
	    );  
	  //drupal_add_js(drupal_get_path('module', 'impuestos') . '/js/payment.js'); // Check all checkboxes are marked
	  // Store data in session vars
	  if(validateCaja()){
	      $form['submit']['#disabled'] = FALSE;
	  }else{
	      $form['submit']['#disabled'] = TRUE;
	      drupal_set_message("Pagos no disponibles :: Caja Cerrada");
	      //impuestos_mesg();
	  }
 	  $admin_payments = variable_get('payments_all',0);
	  if($admin_payments == 1){
		if (!in_array('administrador', $user->roles)) {
			$form['submit']['#disabled'] = TRUE; // Delete this line - DRW
		 }else{
			$form['submit']['#disabled'] = FALSE;
		 }
	  }
          /*if (!in_array('administrador', $user->roles)) {
	     $form['submit']['#disabled'] = TRUE; // Delete this line - DRW
          }*/
	  $_SESSION['dataws'] = $dataws;
	  $_SESSION['ced'] = $ced;
	  return $form;
	}
	/***
	 * Valid name of predio
	 * @param $namePredio
	 * 	  Name of the predio
	 *  @return TRUE or FALSE
	 * Check if the name of predio is valid
	 * @return TRUE if the name is valid
	 * @return FALSE if the name is not valid
	 * 
	 */
	function getValidPredio($namePredio){
		if ((strpos($namePredio, 'PREDI') !== false) ){
			return TRUE;
		}else{
			return FALSE;
		}
	}
	/***
         * Change name of predio
         * @param $namePredio
         *        Name of the predio
         *  @return String
         * 
         */
        function chgPredioName($namePredio){
                if ((strpos($namePredio, 'PREDI') !== false) ){
		    if ((strpos($namePredio, 'URB') !== false) ){
                        return "PREDIO URBANO";
                    }else{
			return "PREDIO RURAL";
					}
                }else{
                        return $namePredio;
                }
        }
	/**
	* Function for validate the data before submit the results
	*
	*/
	function taxes_form_validate($form, &$form_state){
	//  $ced = $form_state['values']['cedula'];
	  #global $ced;
	  global $user;
	  $ced = $_SESSION['ced'];
	//  global $dataws;  // Have data with all taxes get from GIM system
	  $dataws = $_SESSION['dataws'];

	  $fechahora = date('H:i:s');
	  
	  asort($dataws);  // Sort taxes by codServ and Date like as tableselect above 
	  $dataws = keyfrom1($dataws, TRUE);  // re Sort keys for array from key 1
	  
	  $lenA = sizeof($dataws); //Get the array length
	  $sel = array_filter($form_state['values']['taxes']); // Get the values selected from tableselect
	  $pagar = FALSE;
	  
	  $lenB = sizeof($sel);  
	  if($lenB != 0){ 
	    foreach ($sel as $key) {      
		if($key == 1){
		  $pagar = TRUE;
		}else{
		  //concat string with codSer and rubro items
		  $ant = $dataws[$key-1]['codSer'] . ($predioAnt = (getValidPredio($dataws[$key-1]['rubro']) ? 'PREDIO': $dataws[$key-1]['rubro'])); 
		  $act = $dataws[$key]['codSer'] . ($predioAct = (getValidPredio($dataws[$key]['rubro']) ? 'PREDIO': $dataws[$key]['rubro']));
		  
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
	 
	    // The payment only can do it between 08 and 17 hours with thirty minutes
	     //if (!($fechahora > "08:00:00" && $fechahora < "17:30:00")){
	     if (!($fechahora > "07:00:00" && $fechahora < "17:00:00")){
	      form_set_error("taxes","El horario de pago es de 07H00 a 17H00");
    }
    if(user_is_anonymous()){ //Check if the user is anonymous and ask register
      form_set_error("taxes","Debe <a class='registro' href='https://www.loja.gob.ec/user/register'>registrarse</a> e ingresar al sitio para poder efectuar pagos. Si ya dispone de una cuenta <a class='registro' href='https://www.loja.gob.ec/user'>ingrese al sitio</a>");
	drupal_goto('https://www.loja.gob.ec/user');
    }
    
    /*if($lenA == $lenB){$pagar = TRUE;}
    else $pagar = FALSE;*/
    if($pagar){
      //drupal_set_message("Puede pagar");
      $dataws = array_intersect_key($dataws, $sel); // Get intersection between keys to determine the selected items from complete array
      $_SESSION['dataws'] = $dataws;
            
    }else{      
      form_set_error("taxes","NO puede pagar los impuestos seleccionados debiendo meses anteriores");
      //form_set_error("taxes","Debe pagar todos los impuestos listados");
    }
  }else{
    form_set_error("taxes","Debe elegir rubros para realizar el pago");    
  }// End if lenB !=0  
  
}
/**
* Function for submit the results and data
*
*/
function taxes_form_submit($form, &$form_state){  
  global $dataws, $user;  
  $dataws = $_SESSION['dataws'];
  // Check if the user has the 'editor' role. 'authenticated user'
  //if (in_array('administrador', $user->roles)) { // Just access to Administrator
  if (in_array('administrador', $user->roles)|| in_array('authenticated user', $user->roles)) {
    //drupal_set_message("El servicio solo esta disponible para el Administrador");
    // if (isset($dataws)){
    if (payment_in_process($_SESSION['ced'])){
       drupal_set_message(t('Pago en proceso, vuela intentarlo luego de 8 minutos'), 'warning');
    }else{
       create_order_with_impuestos(1,$dataws); // PROD
    }

    //create_order_with_impuestos(9,$dataws); // TEST
    // }else{ drupal_goto('https://www.loja.gob.ec/consulta/res')}
    
  }else{
    drupal_set_message("Servicio de pago suspendido temporalmente, por favor espere unos minutos y vuelva e intentar");
  }
  //dsm($user->roles); // roles array take it from user global variable

    
}
/**
* Check payment in process when it was send request to external server Placetopay
* @param cedula
*        Citizen's Id
*/
function payment_in_process($cedula){
  $fechahoy = date('Y-m-d H:i:s');
  $fecha5min = strtotime('+4 minute', strtotime($fechahoy));  // Date 4 min after current date
  $fecha5minb = strtotime('-4 minute', strtotime($fechahoy));  // Date 4 min before current date
  $fecha5min = date('Y-m-d H:i:s', $fecha5min);
  $fecha5minb = date('Y-m-d H:i:s', $fecha5minb);
  // dsm('Date after, current date: '.$fecha5min);
  // dsm('Date before, current date: '.$fecha5minb);
  $pendient = db_query("SELECT * FROM place2pay
                            WHERE requestId != '' 
                            AND cedula = :ced 
                            AND flag = 0 
                            AND estado != 'REJECTED'
                            AND fecha > :fecha_5b AND :fecha_hoy < :fecha_5a 
                            ORDER BY order_id desc limit 2",
                            array(':ced' => $cedula, ':fecha_hoy'=> $fechahoy, ':fecha_5a'=> $fecha5min, ':fecha_5b' => $fecha5minb))->fetchall();
  if(empty($pendient)){
    // drupal_set_message("Esta vacio, puede pagar");
    // dsm($pendient);
    return FALSE;
  }else{
    // drupal_set_message("No esta vacio, pago en proceso");
    // dsm($pendient);
    return TRUE;
  }
}

/**
* Consumo de emisiones futuras
* @param cedula  - Numeric
*/

function _ws_emisionFutura($cedula){
  $serv = wsclient_service_load('impuesto'); 
  $result = '';
  try{    
    $serviceRequest = array(        
        'identificationNumber' => (String)$cedula,
        // 'username' => 'dabetancourtc',
        // 'password' => 'Loja.2016.IML', // PROD 199 
	'username' => 'munpayclub', //199
        'password' => 'bfc2b6f7-9eea-4368-9cb0-cde8e2da37f7',   //199
        'tramitId' => ''
    );
    $findStatement = array(
        'arg0' => $serviceRequest
    );
    // Call operation findStatement with parameters    
    $result = $serv->findFutureEmission($findStatement);    
    # dsm($result);
    return $result;

  }catch(WSClientException $f){    
    //echo $f;    
  }
  return $result;
}
/**
* Render information about future till
* @param ced - Identification
*/
function emisionFuturaView($ced){  
  $ef = _ws_emisionFutura($ced); // Call function for get data from webservices 
  $sc='';
       
  if(isset($ef->return->bonds)){ 
    $sc = "<h2>Emisiones Futuras</h2>";
    $sc .= "<table border=1><tbody>";
    $sc .="<tr><th>Cantidad</th><th>Rubro</th><th class='total'>Total</th><tr>";
    $sc .= "</thead><tbody>";
    $par=0;      
    // Get size of array
    // $lengthB = sizeof($ef->return->bonds);      
    $lengthB = is_array($ef->return->bonds) ? count($ef->return->bonds) : count(array($ef->return->bonds));
    // if array have just one element      
    if($lengthB == 1){        
      $sc .= '<tr class="odd"><td>'.$ef->return->bonds->quantity.'</td>'
      . "<td>". $ef->return->bonds->account ."</td>"        
      . "<td class='valor total'>$". $ef->return->bonds->total ."</td></tr>";
    }
    // More than one element
    else{
      for($i=0; $i<$lengthB; $i++){
        $par +=1;
        // Set a clase for tr element with even or odd for CSS
        $tr = ($par % 2 ? '<tr class="even">' : '<tr class="odd">');          
        $sc .= $tr."<td>".$ef->return->bonds[$i]->quantity."</td>"
        . "<td>". $ef->return->bonds[$i]->account ."</td>"
        . "<td class='valor total'>$". $ef->return->bonds[$i]->total ."</td></tr>";
      }        
    }// End else   
    $sc .= "</table>";     
  }
  return $sc;
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
  global $user;
  if(empty($cedula)){
    return drupal_goto('https://www.loja.gob.ec/consulta');
  }

  $result = array();
  // Call selected web service with name at next function
  ini_set('soap.wsdl_cache_enabled',0);
  ini_set("default_socket_timeout", 150); // Extend the timeout for clients with large queue taxes
  $serv = wsclient_service_load('impuesto');  
  // $params = $user->name;  
  $params = (isset($user->name)? $user->name : 'Contribuyente');  
  if( $serv == null ){ // If GIM server service is DOWN
	  $msg = '<h1>Municipio de Loja</h1>';
	  $msg .= '<p><i>No se ha podido establecer conexión con recaudaciones</i></p>';
	  $msg .= '<p>Por favor reintente en unos minutos, estamos solucionando el inconveniente</p>';
	  $msg .= '<br/><p><strong>Gracias por su comprensión</strong></p>';
	  drupal_mail('impuestos','serverdown','dbetancourt@loja.gob.ec', language_default(),$params);
	  exit($msg);
  }

  try{    
    $serviceRequest = array(
        //'identificationNumber' => '1103756845',
        'identificationNumber' => (String)$cedula,
        //'username' => 'dabetancourtc',
        //'password' => 'Loja.2016.IML', // PROD 199 
	'username' => 'munpayclub', //199
        'password' => 'bfc2b6f7-9eea-4368-9cb0-cde8e2da37f7',   //199
        'tramitId' => ''
    );
    $findStatement = array(
        'arg0' => $serviceRequest
    );
    // Call operation findStatement with parameters    
    $result = $serv->findStatement($findStatement);
#    if(!$result) $result = array('Vacio');
    return $result;
//    watchdog('impuestos','Se ejecuto la consulta con datos de acceso',array(),WATCHDOG_DEBUG);
    
  }catch(WSClientException $f){
    //If the connection is failed the return will be FALSE
    //echo $f;    
  }
  
  return $result;
}
/**
* Validate Open Cash
* @return $result
* Boolean
*/
function validateCaja(){
   $result = FALSE; 
   ini_set('soap.wsdl_cache_enabled',0);
   $serv = wsclient_service_load('impuesto');
   try{
      $serviceRequest = array(
	'username' => 'munpayclub', //199
        'password' => 'bfc2b6f7-9eea-4368-9cb0-cde8e2da37f7',   //199
      );
      $validateOpenTill = array (
        'arg0'	=> $serviceRequest
      );
      $result = $serv->validateOpenTill($validateOpenTill);
   }catch(WSClientException $f){
   }
   return $result->return;
}
/**
 * Function for register payment in GIM system and update status taxes
 * @param $txn_id
 *    Order with data from buy
 * @return 
 *    Multidimentional Array with many values
 */
function registrarPagoatGIM($id_txn){
  global $user;
  ini_set('soap.wsdl_cache_enabled',0);
  $result = array();
  $transaction = db_query('SELECT * FROM place2pay
                            WHERE txn_id = :id_txn',
                            array(':id_txn' => $id_txn))->fetchall();
  $bondsid = array(); // Initialize array
  $bondsid = explode(',',$transaction[0]->bondsid); //$_SESSION['bondsid'];  // Recover variable from session browser
  $ced = $transaction[0]->cedula;
  $params = array();
  $params['orden']=$transaction[0]->order_id;
  $params['cedula']=$ced;
  $params['subtotal']=$transaction[0]->subtotal;
  $params['transaccion']=$transaction[0]->txn_id;
  
  
  // Amount recover from order created and convert to decimal
  $amount = $transaction[0]->subtotal;
//  $amount = "67.32";
//  $bondsid = array("1993199","2063036","2131850");
  //dsm($bondsid);
//  $ced = "1104246291";
 /* if ($amount == '13448.9'){
	$amount = '13448.93';
  }*/
    
  $fechahoy = strtotime(date('Y-m-d H:i:s'));  

  // Call selected web service with name at next function
  $serv = wsclient_service_load('impuesto');        
  # dsm("Antes de registrar en el GIM: ".$id_txn);
  $n_emails = variable_get('n_email',0); // Get email address from settings form
  
  try{    
    $serviceRequest = array(        
        'identificationNumber' => $ced,
//        'username' => 'municipioonline', // 203
//        'password' => 'c4185d49-1e52-46fe-a4ba-3e38d58ca615', //203
        'username' => 'munpayclub', //199
        'password' => 'bfc2b6f7-9eea-4368-9cb0-cde8e2da37f7',   //199
        'tramitId' => ''
    );
    $payout = array(
        'amount'      => (float) $amount, // Decimal - Total Sum
        'bondIds'     => $bondsid,        // Array with bonds Ids
        'paymentDate' => $fechahoy,       // Current Date (timestamp format)
    );
    $registerDeposit = array(
        'arg0' => $serviceRequest,
        'arg1' => $payout,
    );
    //dsm($registerDeposit);
    // Call operation registerDeposit with parameters
    $result = $serv->registerDeposit($registerDeposit);
    if($result){
      watchdog('impuestosTRUE','Bandera de registro en GIM', array(),WATCHDOG_DEBUG);
      $updb = db_query('UPDATE place2pay
                      SET gim = 1
                      WHERE txn_id = :id_txn',
                      array(':id_txn' => $id_txn));
    } 
    drupal_mail('impuestos','success','dbetancourt@loja.gob.ec', language_default(),$params);    
    watchdog('GIM','Pago registrado en GIM con txn_id :txnid', array(':txnid' => $id_txn),WATCHDOG_INFO);
    // check if GIM was updated, or could be updated with cron
    /* $updb = db_query('UPDATE place2pay
                      SET gim = 1
                      WHERE txn_id = :id_txn',
                      array(':id_txn' => $id_txn));*/
  }catch(WSClientException $f){
    //echo $f;    
    drupal_mail('impuestos','failed',$n_emails, language_default(),$params);
    # dsm($f);
  }
  
  return $result;
}
/**
 * Function for register payment at GIM system and update status taxes
 * @param $requestId
 *    Order with data from buy
 * @return 
 *    Multidimentional Array with many values
 */
function registerPaymentAtGIM($requestId){
  ini_set('soap.wsdl_cache_enabled',0);
  $result = array();
  $transaction = db_query('SELECT * FROM place2pay
                            WHERE requestId = :requestId',
                            array(':requestId' => $requestId))->fetchall();
  $bondsid = array(); // Initialize array
  $bondsid = explode(',',$transaction[0]->bondsid);
  $ced = $transaction[0]->cedula;
  
  // Amount recover from order created and convert to decimal
  $amount = $transaction[0]->subtotal;    
  $fechahoy = strtotime(date('Y-m-d H:i:s'));  

  // Call selected web service with name at next function
  $serv = wsclient_service_load('impuesto');        
  # dsm("Antes de registrar en el GIM: ".$requestId);
  
  try{    
    $serviceRequest = array(        
        'identificationNumber' => $ced,
        'username' => 'munpayclub', //199
        'password' => 'bfc2b6f7-9eea-4368-9cb0-cde8e2da37f7',   //199
        'tramitId' => ''
    );
    $payout = array(
        'amount'      => (float) $amount, // Decimal - Total Sum
        'bondIds'     => $bondsid,        // Array with bonds Ids
        'paymentDate' => $fechahoy,       // Current Date (timestamp format)
    );
    $registerDeposit = array(
        'arg0' => $serviceRequest,
        'arg1' => $payout,
    );
    //dsm($registerDeposit);
    // Call operation registerDeposit with parameters
    $result = $serv->registerDeposit($registerDeposit);
    //watchdog('impuesto','Se registro en GIM el pago para :ced',array(':ced'=> $ced),WATCHDOG_DEBUG);
    drupal_mail('impuestos','success','dbetancourt@loja.gob.ec', language_default(),$params);    
    watchdog('GIM','Pago registrado en GIM con requestId :requestId',array(':requestId' => $requestId),WATCHDOG_INFO);
    // check if GIM was updated, or could be updated with cron
    $updb = db_query('UPDATE place2pay 
                      SET gim = 1
                      WHERE requestId = :requestId',
                      array(':requestId' => $requestId));
  }catch(WSClientException $f){
    //echo $f;    
    drupal_mail('impuestos','failed','dbetancourt@loja.gob.ec', language_default(),$params);
    # dsm($f);
  }
  
  return $result;
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
 
  //if (empty($order)) {
    // Create the new order in checkout status with a custom order type of "donate_now_order_type".    
    // $order = commerce_order_new($uid, 'commerce_checkout');
    // The next line is alter with checkout_checkout for allows payment :: DRW
    $order = commerce_order_new($uid, 'checkout_checkout');
 
    // Save the order so its ID is assigned.
    commerce_order_save($order);
  //}
  
 
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
 * Function for reorder array start with key from 1
 * @param $data
 *    (Array) An array order with asort function
 * @param $all
 *    (Boolean) To know if there is all elements include Id field Bonds
 * @return $of1
 *    Multidimentional Array with many values
 */
function keyfrom1($data, $all){
  $of1 = array();
  $i =0;
  foreach ($data as $tax) {
    $i +=1;
    if($all){
      $of1[$i] = array(          
          'codSer'  => $tax['codSer'],
          'rubro'   => $tax['rubro'],
          'fInicio' => $tax['fInicio'],
          'fFin'    => $tax['fFin'],
          'monto'   => $tax['monto'],
          'id'  => $tax['id'],
          'number'  => $tax['number'],
          'sku'  => $tax['sku'],
      );
    }else{
      $of1[$i] = array(
          'codSer'  => $tax['codSer'],
          'rubro'   => $tax['rubro'],
          'fInicio' => $tax['fInicio'],
          'fFin'    => $tax['fFin'],
          'monto'   => $tax['monto'],
      );
    }
  }  
  return $of1;
}
/**
* Makes a query with ID from webservice with out wsclient module
*/

function consultaflat($ced){
  $servicio="http://190.57.168.200:8080/gim/paymentPlatform?wsdl";
  $client = new SoapClient($servicio);
  $serviceRequest = array(
        'identificationNumber' => '1103756845',
        //'identificationNumber' => (String)$cedula,
        'username' => 'dabetancourtc',
        'password' => 'Loja.2015.IML', // PROD 199 
        'tramitId' => ''
    );
    $findStatement = array(
        'arg0' => $serviceRequest
    );

  try{
    $result = $client->findStatement($findStatement);
    return $result;
  }catch(Exception $e){
    print $e;
  }

}
function test_page(){
  $ced = '1103756845';
  $params['orden']= '90345';
  $params['cedula']= '1103470892';
  $params['subtotal']= 23.55;
  $params['transaccion']= 12355;
  $n_emails = variable_get('n_email',0);
  drupal_set_message("Emails obtenidos: ". $n_emails);
  drupal_mail('impuestos','failed', $n_emails, language_default(), $params);
  //drupal_mail('impuestos','failed','dbetancourt@loja.gob.ec', language_default(),$params);
  $result = array();
//  $result =  consultaflat($ced);
//  $result = _ws_impuesto($ced);
  //dsm($result);
  return 'Test with out module and tried to send mail';
}
