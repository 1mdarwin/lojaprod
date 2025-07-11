<?php 
/**
* Function TEST to evaluate the process when get a valid URL for payment
*/
function test_p2p(){
	#require_once(__DIR__ . "/../bootstrap.php");
	#module_load_include('php','place2pay','vendor/dnetix/redirection/examples/bootstrap');
	module_load_include('php','place2pay','vendor/autoload');
	//$login = '85e46bb5b79eb163ce19b1aff9c02fcc';
	//$trankey = '9EPoJ98NIr72BJ9x';  // TEST
	$secretKey = TRANKEY_P2P;	// PROD
	$url_ep = 'https://test.placetopay.ec/redirection/'; // TEST
	$seed = date('c');	

	if (function_exists('random_bytes')) {
		$nonce = bin2hex(random_bytes(16));
	} elseif (function_exists('openssl_random_pseudo_bytes')) {
		$nonce = bin2hex(openssl_random_pseudo_bytes(16));
	} else {
    	$nonce = mt_rand();
	}
	$nonceBase64 = base64_encode($nonce);

	$tranKey = base64_encode(sha1($nonce . $seed . $secretKey, true));
	
	//SOLICITAMOS LA CREACION DE SESSION PARA EL PAGO PLACETOPAY
   $curl = curl_init();

   curl_setopt_array($curl, array(
      //CURLOPT_URL => $url_ep."api/session/", // TEST
      CURLOPT_URL => URL_EP."api/session/",	// PROD
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "POST",
      CURLOPT_HTTPHEADER => array(
         "Cache-Control: no-cache",
         "Content-Type: application/json",
         "Postman-Token: 96983e26-ba1b-4dfa-bbe9-54f877428d08"
      ),
   ));

	$reference = 'REFERENCE-1234';
	$request = [
		"auth" => [
         //"login" => $login, // TEST
         "login" => LOGIN_P2P, // PROD
         "seed" => $seed,
         "nonce" => $nonceBase64,
         "tranKey" => $tranKey
      ],
      "locale" => 'es_EC',
	   'payment' => [
	      'reference' => $reference, // (M)
	      'description' => 'Prueba de Pagos menores a 10 usd',
	      'amount' => [
	         'currency' => 'USD', // (M)
	         'total' => 8, // (M)
	      ],
	    ],
	   'buyer' => [
			"document" => "1103470892", //Mandatory (M)
			"documentType" => "CC",
			"name" => "Darwin", // (M)
			"surname" => "Betancourt",
			"email" => "drwbc@hotmail.com", // (M)
			"mobile" => "099148458",
			"address" => [
				"street" => "742 Evergreen Terrace",
				"city" => "Loja",
				"country" => "EC"
			]
		],
	    #'expiration' => date('c', strtotime('+1 days')), // (M)
	    'expiration' => date('c', strtotime('10 minute')), // (M)
	    'returnUrl' => 'https://www.loja.gob.ec/cuentaunica/response?reference=' . $reference, // (M)
	    'ipAddress' => '127.0.0.1', // (M)
	    'userAgent' => 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36', // (M)
	];
	$data = json_encode($request);
   curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
   $json_response = curl_exec($curl);
   $err = curl_error($curl);
   curl_close($curl);

   $response = json_decode($json_response, false);	

   dsm($response);

	/*$response = $placetopay->request($request);
	dsm($response);
	if ($response->isSuccessful()) {
	    // STORE THE $response->requestId() and $response->processUrl() on your DB associated with the payment order
	    // Redirect the client to the processUrl or display it on the JS extension
	    header('Location: ' . $response->processUrl());
	} else {
	    // There was some error so check the message and log it
	    $response->status()->message();
	}*/
        $params['id_order'] = '25538';
        $params['aut'] = '654321';
        $params['cct'] = 'DN';
        $params['total'] = 4567;
        $params['requestId'] = '123654';

        drupal_mail('place2pay','concilliation','dbetancourt@loja.gob.ec', language_default(), $params);
        // just run one time
	// tweaks_monto_int_dec();
	return "Resultados de las pruebas";
}
/**
* Function for update the payment process and order
* @param ipn Array
*/
function postprocess($ipn){
   $order = commerce_order_load($ipn['id_order']); // Get data from order	
   // Another block code
   // -------------------------------------------
   // If this is a prior authorization capture IPN for which we've already
   $transactions = commerce_payment_transaction_load_multiple(array(), array('order_id' => $ipn['id_order']));
   // $transactions = commerce_payment_transaction_load_multiple(array(), array('order_id' => $order->order_id));
   if (count($transactions) > 0) {
    $transaction = end($transactions);
    $ipn['txn_id'] = $transaction->transaction_id; 

    // The next line could be for Autorization Code from VPOS
    $transaction->remote_id = $ipn['aut'];
    //$transaction->amount = commerce_currency_decimal_to_amount($ipn['TransacctionValue'],'USD');
    watchdog('place2pay','Monto guardado: @txn_monto',array('@txn_monto'=> $transaction->amount),WATCHDOG_INFO);
    $transaction->amount = $ipn['total'];
    //$transaction->amount = $ipn['total']*100;
    watchdog('place2pay','Monto de transaccion tomado de vpos_total: @txn_monto',array('@txn_monto'=> $transaction->amount),WATCHDOG_INFO);
    //$transaction->amount = number_format($ipn['TransacctionValue'],2,'.','');
    $transaction->currency_code = 'USD'; //$ipn['CurrencyID'];
    $transaction->payload[REQUEST_TIME . '-ipn'] = $ipn;

    // Set the transaction's statuses based on the IPN's payment_status.
    $transaction->remote_status = $ipn['estado'];

    // If we didn't get an approval response code...
    switch ($ipn['estado']) {
      case 'REJECTED':
        $transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
        $transaction->message = t("El Pago ha sido RECHAZADO. a: @errorcode , @errordetails", array('@errorcode' => $ipn['ERRORCODE'], '@errordetails' => $ipn['ERRORDETAILS']));
        drupal_set_message(t($ipn['ERRORDETAILS']),'warning');
        watchdog('place2pay','ESTADO REJECTED para cancelar en postprocess',array(),WATCHDOG_INFO);
        commerce_payment_redirect_pane_previous_page($order);
        break;    

      case 'PARTIAL_EXPIRED':
        $transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
        $transaction->message = t("El Pago ha sido PARTIAL_EXPIRED. a: @errorcode , @errordetails", array('@errorcode' => $ipn['ERRORCODE'], '@errordetails' => $ipn['ERRORDETAILS']));
        drupal_set_message(t($ipn['ERRORDETAILS']),'warning');
        watchdog('place2pay','ESTADO PARTIAL_EXPIRED para cancelar en postprocess',array(),WATCHDOG_INFO);
        commerce_payment_redirect_pane_previous_page($order);
        break;

      case 'APPROVED_PARTIAL':
        $transaction->status = COMMERCE_PAYMENT_STATUS_FAILURE;
        $transaction->message = t("El Pago ha sido APPROVED_PARTIAL. a: @errorcode , @errordetails", array('@errorcode' => $ipn['ERRORCODE'], '@errordetails' => $ipn['ERRORDETAILS']));
        drupal_set_message(t($ipn['ERRORDETAILS']),'warning');
        watchdog('place2pay','ESTADO APPROVED_PARTIAL para cancelar en postprocess',array(),WATCHDOG_INFO);
        commerce_payment_redirect_pane_previous_page($order);
        break;

      case 'APPROVED':
        $transaction->status = COMMERCE_PAYMENT_STATUS_SUCCESS;
        $transaction->message = t('El pago ha sido APROBADO con autorización: @ac y Transaccion @txn', array('@ac' => $ipn['aut'],'@txn'=> $transaction->transaction_id));//        
        watchdog('place2pay','ESTADO APPROVED para completar pago',array(),WATCHDOG_INFO);
        update_place2pay($ipn,'concilia');
  	    confirmar_gimp2p($transaction->transaction_id); // Update GIM
        break;

      case 'PENDING':
        $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;
        $transaction->message = t('Pendiente espere su verificación, el estado PENDIENTE sera actualizado en unos minutos, transaccion @txn_id', array('@txn_id' => $ipn['txn_id']));
        watchdog('place2pay','ESTADO PENDING en postprocess ',array(),WATCHDOG_INFO);
        update_place2pay($ipn,'concilia');
        break;
    }

    // Save the transaction information.
    commerce_payment_transaction_save($transaction);
    $ipn['transacction_id'] = $transaction->transaction_id;

    // FUNCTION FOR CONTINUE WITH THE NEXT PAGE
    commerce_payment_redirect_pane_next_page($order);
    watchdog('place2pay', 'Payment processed for Order @order_number with Transaction ID @txn_id.', array('@txn_id' => $ipn['txn_id'], '@order_number' => $order->order_number), WATCHDOG_INFO);
  }
}
/**
* This function check if transaction is pending after 5 minutos ago from the current time
* @param cedula
* @return boolean
*/
function isPendingPayment($cedula){
  $fechahoy = Date('Y-m-d H:i:s');
  $horaActual = strtotime($fechahoy);
  $hora5min = strtotime($fechahoy) - 480; // 5*60 = 300
  $query = db_query("SELECT fecha, cedula 
		     FROM place2pay 
                     WHERE (cedula = :ced AND estado = '') OR 
                    (cedula = :ced AND estado = 'PENDING')
                     ORDER BY fecha 
                     DESC LIMIT 1", array(":ced" => $cedula))->fetchAll();
  $dt = strtotime($query[0]->fecha);
  if ($dt < $horaActual and $dt > $hora5min){
     return true;
  }
  return false;
}
/**
* Process for transaction
*/
function place2pay_process(){
    $orderid = arg(1); //get first parameter from URL
    $query = db_query('SELECT * from place2pay WHERE order_id = :orderid ORDER BY fecha DESC',array(':orderid' => $orderid))->fetchAll();
//    dsm($query);
    if($query[0]->estado == 'REJECTED' || $query[0]->estado == 'PARTIAL_EXPIRED' || $query[0]->estado == 'APPROVED_PARTIAL'){
      $msg = 'El proceso de pago ha sido RECHAZADO';
      $msg .= '<ul><li>Referencia: '.$orderid;
      $msg .= '</li><li>Número de petición: '.$query[0]->requestId .'</li></ul>';
    }else{
      $reqInf = _getRequestInformation($query[0]->requestId);
      if($reqInf->payment[0]->paymentMethod != ' '){
        $msg = 'El proceso de pago ha sido RECHAZADO';
	      $msg .= '<ul><li> Referencia: '.$orderid;
        $msg .= '</li><li>Número de petición: '.$query[0]->requestId;
        $msg .= '</li><li>Tarjeta: '.$reqInf->payment[0]->paymentMethod .'</li></ul>';
      }
    }
    $mensaje = "El proceso de pago ha sido cancelado por el usuario";
    $msg .= "<div>Gracias por usar los servicios de pagos Municipales</div>";
    return $msg;
}
/**
* Process for transaction
*/
function place2pay_pending(){
    $orderid = arg(1);
    $msg = '';
    $query = db_query('SELECT * from place2pay WHERE order_id = :orderid ORDER BY fecha DESC',array(':orderid' => $orderid))->fetchAll();
    if($query[0]->estado == 'PENDING'){
      $msg = 'Su pago esta siendo procesado, va a tomar algunos minutos...<br> Por favor espere un correo de confirmacion';
      $msg .= '<h3>Resumen de la transacción</h3>';
      $msg .= '<ul><li>Referencia: '. $query[0]->order_id;
      $msg .= '</li><li>Tarjeta: '. get_nameccp2p($query[0]->cct);
      $msg .= '</li><li>Estado: PENDIENTE';
      $msg .= '</li></ul>';
      $msg .= '<div>Municipio de Loja</div>';
    }
    return $msg;
}

/**
* function for postprocess when the payment was success before to notification's user
* Proccess the json POST from place2pay platform after the client use the credit card
*/
function place2pay_notificacionp2p(){
  $data = json_decode(file_get_contents('php://input'), true); // capture json POST that sent place2pay platform
  watchdog('place2pay', '****************** NOTIFICACION PLACE2PAY **************', array(), WATCHDOG_INFO);
	// Verify the data received with sha1
 	// requestId + status + date + tranKey Ej: sha1(58APPROVED2016-09-15T13:49:01-05:00ABCD1234)
	$signature = $data['signature'];
	$stringSig = $data['requestId'] . $data['status']['status'] . $data['status']['date'] . TRANKEY_P2P;
	watchdog('place2pay', '- Estado de pago notification :status', array(':status' => $data['status']['status']), WATCHDOG_INFO);
	watchdog('place2pay', '- Mensaje del estado de pago: :msg', array(':msg' => $data['status']['message']), WATCHDOG_INFO);
  watchdog('place2pay', 'Cadena de Encriptacion :enc', array(':enc' => $stringSig), WATCHDOG_INFO);
	$sigSHA = sha1($stringSig); // Cadena de comprobacion
	$requestId = $data['requestId'];
	$ipn['estado'] = $data['status']['status'];
	$ipn['mensaje'] = $data['status']['message'];
 	$ipn['requestId'] = $requestId;	
  	update_place2pay($ipn,'notifica'); // Allow to update table place2pay
	
  	watchdog('place2pay', 'Recibiendo sesion de pedido desde la notificacion (requestId) :enc', array(':enc' => $requestId), WATCHDOG_INFO);
//	$dataReturn = $data['requestId'] . "-" . $data['paymentMethod'] . "-" . $data['issuerName']."-". $data['authorization'];
	$reqInf = _getRequestInformation($requestId);
  watchdog('place2pay', 'requestId :requestId', array(':requestId' => $requestId), WATCHDOG_INFO);
  watchdog('place2pay', '_getRequestInformation status :status', array(':status' => $reqInf->status->status), WATCHDOG_INFO);
	$orderid = (isset($reqInf->request->payment->reference) ? $reqInf->request->payment->reference : $data['reference']);
	$order = commerce_order_load($orderid);  // load order with details using order id
	$user = user_load($order->uid);
	$params = (isset($user->name) ? $user->name : 'admin'); 
	
	if($data['status']['status'] == 'APPROVED' && $reqInf->status->status == 'APPROVED') {
		$aut = $reqInf->payment[0]->authorization;
		if($sigSHA == $signature){
		   watchdog('place2pay', 'Pago Aprobado :id with autorizacion :aut', array(':id' => $requestId, ':aut'=> $aut), WATCHDOG_INFO);
		   watchdog('place2pay', 'Estado del Pago notificado :not ', array(':not' => $data['status']['status']), WATCHDOG_INFO);
		   watchdog('place2pay', 'Estado del Pago :status', array(':status' => $reqInf->status->status), WATCHDOG_INFO);
		   watchdog('place2pay', 'Razon del Pago :status', array(':status' => $reqInf->status->reason), WATCHDOG_INFO);
		   watchdog('place2pay', 'Mensaje del Pago :status', array(':status' => $reqInf->status->message), WATCHDOG_INFO);
		   //watchdog('place2pay', 'Revisar devolucion :id', array(':id' => $dataReturn), WATCHDOG_INFO);
		   $ipn = array();
		   $ipn['id_order'] = $order->order_id;
		   $ipn['cct'] = getAbr($reqInf->payment[0]->paymentMethod); //get name abrev of credit card
		   //$ipn['total'] = $reqInf->payment[0]->processorFields[1]->value;
		   // TOTAL ---------------------------
		   $ipn['total'] = (isset($reqInf->request->payment->amount->total) ? $reqInf->request->payment->amount->total : $reqInf->payment[0]->amount->from->total);
		   //$ipn['total'] = $reqInf->payment[0]->amount->from->total;
		   watchdog('place2pay', 'Total de la transaccion :total', array(':total' => $ipn['total']), WATCHDOG_INFO);
		   $ipn['interes'] = 0;
		   $ipn['aut'] = $reqInf->payment[0]->authorization;   		   
		   $lenArr = sizeof($reqInf->payment[0]->processorFields);
		   $puntero = 0;
		   for($i=0; $i < $lenArr;$i++){
		      if(isset($reqInf->payment[0]->processorFields[$i]->value->installments)){
		        $puntero = $i;	
		        break;
		      }
   		  }
        	   $ipn['total'] = (isset($ipn['total']) ? $ipn['total'] : 0);         
        
		   $ipn['tc'] = $reqInf->payment[0]->processorFields[$puntero]->value->type;
		   watchdog('place2pay', 'El puntero :p  de tc es: :tc', array(':p'=> $puntero, ':tc' => $ipn['tc']), WATCHDOG_INFO);
		   //$ipn['tc'] = '00';
		   $ipn['tc'] = (isset($ipn['tc']) ? $ipn['tc'] : '00');
		   $ipn['mes'] = $reqInf->payment[0]->processorFields[$puntero]->value->installments;
		   $ipn['mes'] = (isset($ipn['mes']) ? $ipn['mes'] : 1);
		   watchdog('place2pay', 'El valor de mes es: :mes', array(':mes' => $ipn['mes']), WATCHDOG_INFO);
		   # $ipn['tipo'] = 'P';
		   $ipn['estado'] = $reqInf->status->status; // Return APPROVED OR REJECTED
		   $ipn['mensaje'] = $reqInf->status->message; // Return APPROVED OR REJECTED
		   $ipn['flag']= 1; // Cambia de 0 a 1 porque se hizo el getRequestInformation
 		   $ipn['requestId'] = $requestId;	
		   watchdog('place2pay', 'Order :id and month :mes', array(':id' => $ipn['id_order'], ':mes'=> $ipn['mes']), WATCHDOG_INFO);
       // Load Customer profile for update with datagram from RequestInfomation method
       watchdog('place2pay', 'Update Customer Profile Order :id', array(':id' => $ipn['id_order']), WATCHDOG_INFO);
       $profileBill = commerce_customer_profile_load($order->commerce_customer_billing['und'][0]['profile_id']); // Update profile.      
       $nombresPayer = $reqInf->request->payer->name . " "  . $reqInf->request->payer->surname; // concat names
       $profileBill->commerce_customer_address[LANGUAGE_NONE][0]['name_line'] = $nombresPayer;     
       // los payer no contiene informacion de address  
       //$profileBill->commerce_customer_address[LANGUAGE_NONE][0]['thoroughfare'] = $reqInf->request->buyer->address->city;
       //$profileBill->commerce_customer_address[LANGUAGE_NONE][0]['locality'] = $reqInf->request->buyer->address->city;
       commerce_customer_profile_save($profileBill); // Saving profile. 
       $order->commerce_customer_billing[LANGUAGE_NONE][0]['profile_id'] = $profileBill->profile_id; // Change profile id for billing
       commerce_order_save($order); // Saving Order
		  if(postprocess($ipn) !== FALSE){
		    // Do payment only in Commerce
		    drupal_mail('place2pay','success',$user->mail, language_default(),$params);
		    //echo 'ESTADO=OK';
		    watchdog('place2pay','Se imprime OK al VPOS, paso el postproceso', array(), WATCHDOG_DEBUG);
                  }
		}
		//actualiza el registro en aprobado
  }else{
    if($data['status']['status'] = 'PARTIAL_EXPIRED' || $data['status']['status'] = 'APPROVED_PARTIAL' || $data['status']['status'] = 'REJECTED' || $data['status']['status'] = 'PENDING') {
      //$wrapper = entity_metadata_wrapper('commerce_order', $order);
		  //$amount = $wrapper->commerce_order_total->amount->value();
		  $ipn['id_order'] = $order->order_id;
		  $ipn['aut'] = '00';
		  $ipn['interes'] = 0;
		  $ipn['total'] = (isset($reqInf->request->payment->amount->total) ? $reqInf->request->payment->amount->total : 0);
	 	  $ipn['estado'] = $data['status']['status'];
		  $ipn['ERRORDETAILS'] = $reqInf->status->message;
		  $ipn['ERRORCODE'] = $reqInf->status->status;
		  $ipn['requestId'] = $requestId;
		  postprocess($ipn);
		  watchdog('place2pay', 'El pago con petición :id ha sido rechazado con valor :val', array(':id' => $requestId,':val'=>$ipn['total']), WATCHDOG_INFO);
	 
	    }    
  }
	watchdog('place2pay', 'Actualizando URL con Id :id', array(':id' => $requestId), WATCHDOG_INFO);
	return "hola mundo en las notificaciones place2pay";
}
/*
* CHANGE BLOB FIELD for allow to store field_monto_li as decimal(10,2)
*/
function tweaks_monto_int_dec() {
  // Fetch the blob from the DB.
  $blob = db_select('field_config', 'f')
    ->fields('f')
    ->condition('field_name', 'field_monto_li')
    ->execute()
    ->fetchAssoc();

  // Unserialize the blob data and then add the extra bits.
  $data = unserialize($blob['data']);
  $data['settings']['precision'] = 10;
  $data['settings']['scale'] = 2;
  $data['settings']['decimal_separator'] = '.';

  // Do some printing out to make sure everythign works
  drupal_set_message('<pre>'. print_r($blob, true) .'</pre>');
  drupal_set_message('<pre>'. print_r($data, true) .'</pre>');

  // Reserialize the new data and then copy and paste into the table.
  // I could do a db_update here but I didn't fell like it.
  return serialize($data);
}
/**
 * Concilliation values between GIM and Placetopay platform
 * This function allow to update the GIM values with placetopay when the values are received in placetopay but not in GIM
 */
function concilliation_gim_p2p(){  
  $fechahoy = date('Y-m-d');
  // $fechahoy = "2022-07-06";
  $fStart = $fechahoy . " 05:00:00";
  $fEnd   = $fechahoy . " 23:59:59";
  $empty_status = db_query("SELECT requestId FROM place2pay
                          WHERE requestId != ''
		          AND estado != 'REJECTED'
                          AND gim = 0
                          AND fecha > :fStart AND fecha < :fEnd 
                          ORDER BY order_id desc",
                          array(':fStart'=> $fStart, ':fEnd' => $fEnd))->fetchall();
  
  for($i=0; $i<sizeof($empty_status); $i++){
    $requestId = $empty_status[$i]->requestId;
    $reqInf = _getRequestInformation($empty_status[$i]->requestId);
    if($reqInf->status->status == 'APPROVED') {
      watchdog('Concilliation', 'requestId :requestId', array(':requestId' => $requestId), WATCHDOG_INFO);
      watchdog('Concilliation', '_getRequestInformation status :status', array(':status' => $reqInf->status->status), WATCHDOG_INFO);
      $orderid = (isset($reqInf->request->payment->reference) ? $reqInf->request->payment->reference : '');
      $order = commerce_order_load($orderid);  // load order with details using order id
      $user = user_load($order->uid);
      $params['id_order'] = $orderid;
    
      $aut = $reqInf->payment[0]->authorization;
      
      watchdog('Concilliation', 'Pago Aprobado :id with autorizacion :aut', array(':id' => $requestId, ':aut'=> $aut), WATCHDOG_INFO);        
      watchdog('Concilliation', 'Mensaje del Pago :status', array(':status' => $reqInf->status->message), WATCHDOG_INFO);        
      $ipn = array();
      $ipn['id_order'] = $orderid;
      $ipn['cct'] = getAbr($reqInf->payment[0]->paymentMethod); //get name abrev of credit card        
      $ipn['total'] = (isset($reqInf->request->payment->amount->total) ? $reqInf->request->payment->amount->total : $reqInf->payment[0]->amount->from->total);
      
      watchdog('Concilliation', 'Total de la transaccion :total', array(':total' => $ipn['total']), WATCHDOG_INFO);
      $ipn['interes'] = 0;
      $ipn['aut'] = $reqInf->payment[0]->authorization;   		   
      $lenArr = sizeof($reqInf->payment[0]->processorFields);
      $puntero = 0;
      for($i=0; $i < $lenArr;$i++){
          if(isset($reqInf->payment[0]->processorFields[$i]->value->installments)){
            $puntero = $i;	
            break;
          }
        }
      $ipn['total'] = (isset($ipn['total']) ? $ipn['total'] : 0);          
      $ipn['tc'] = $reqInf->payment[0]->processorFields[$puntero]->value->type;
      watchdog('place2pay', 'El puntero :p  de tc es: :tc', array(':p'=> $puntero, ':tc' => $ipn['tc']), WATCHDOG_INFO);        
      $ipn['tc'] = (isset($ipn['tc']) ? $ipn['tc'] : '00');
      $ipn['mes'] = $reqInf->payment[0]->processorFields[$puntero]->value->installments;
      $ipn['mes'] = (isset($ipn['mes']) ? $ipn['mes'] : 1);        
      $ipn['estado'] = $reqInf->status->status; // Return APPROVED OR REJECTED
      $ipn['mensaje'] = $reqInf->status->message; // Return APPROVED OR REJECTED
      $ipn['flag']= 1; // Cambia de 0 a 1 porque se hizo el getRequestInformation
      $ipn['requestId'] = $requestId;	
      $params = $ipn;
      // drupal_mail('place2pay','concilliation',$user->mail, language_default(), $params);
      watchdog('Concilliation', 'Order :id and month :mes', array(':id' => $ipn['id_order'], ':mes'=> $ipn['mes']), WATCHDOG_INFO);
      // Load Customer profile for update with datagram from RequestInfomation method              
      commerce_order_save($order); // Saving Order
      if(postprocess($ipn) !== FALSE){
        // Do payment only in Commerce
        // drupal_mail('place2pay','concilliation',$user->mail, language_default(), $params);
        //echo 'ESTADO=OK';
        watchdog('Concilliation','Se imprime OK al VPOS, paso el postproceso', array(), WATCHDOG_DEBUG);
      }
            
    }    
  }
  return "hola";
  
}
function hola(){
  return "hola mundo";
}
/**
* Fill IPN Array for postprocess and update OrderStatus and later GIM inside the postprocess
*/
function fillIPN($reqInf){
   $ipn = array();
   $ipn['id_order'] = $reqInf->payment->reference;
   $ipn['cct'] = getAbr($reqInf->payment[0]->paymentMethod); //get name abrev of credit card
   $ipn['total'] = (isset($reqInf->request->payment->amount->total) ? $reqInf->request->payment->amount->total : $reqInf->payment[0]->amount->from->total);   

   $ipn['interes'] = 0;
   $ipn['aut'] = $reqInf->payment[0]->authorization;

   $lenArr = sizeof($reqInf->payment[0]->processorFields);
   $puntero = 0;
   for($i=0; $i < $lenArr;$i++){
      if(isset($reqInf->payment[0]->processorFields[$i]->value->installments)){
        $puntero = $i;  
        break;
      }
    }
        
   $ipn['tc'] = $reqInf->payment[0]->processorFields[$puntero]->value->type;   
   $ipn['tc'] = (isset($ipn['tc']) ? $ipn['tc'] : '00');
   $ipn['mes'] = $reqInf->payment[0]->processorFields[$puntero]->value->installments;
   $ipn['mes'] = (isset($ipn['mes']) ? $ipn['mes'] : 1);   
   $ipn['estado'] = $reqInf->status->status; // Return APPROVED OR REJECTED
   $ipn['mensaje'] = $reqInf->status->message; // Return APPROVED OR REJECTED
   $ipn['flag']= 1; // Cambia de 0 a 1 porque se hizo el getRequestInformation
   $ipn['requestId'] = $requestId;
   return $ipn;
}
/**
* Check if payment is pending using the getRequestInfomation method with requestId parameter
*/
function pendiente($requestId){
  watchdog('place2pay','Verifying PENDING with requestId :reqId', array('reqId' => $requestId), WATCHDOG_DEBUG);
  return _getRequestInformation($requestId);
}
/**
* Check the payment, this function allow to verify if the data is correct
* Can access from URL <path_site>/place2pay/requestinformation
* This function show a multilevel Array, is better if you have enable the dev module
*/
function place2pay_getRequestInformation(){
  // $reqId = '21141967';
  $reqId = arg(2);
  if(isset($reqId)){
  dsm('requestId: '.$reqId);
  $reqInf = _getRequestInformation($reqId);
  dsm($reqInf);
  dsm(sizeof($reqInf->payment[0]->processorFields));

  $lenArr = sizeof($reqInf->payment[0]->processorFields);
  $puntero = 0;
  for($i=0; $i < $lenArr;$i++){
      if(isset($reqInf->payment[0]->processorFields[$i]->value->installments)){
        $puntero = $i;
 	      break;
      }
  }
   
  dsm('El indice que tiene valor es: '.$puntero);
  $ipn['total'] = (isset($reqInf->request->payment->amount->total)?$reqInf->request->payment->amount->total:$reqInf->payment[0]->amount->from->total);
  dsm('El total valido o no es valido: '.$reqInf->request->payment->amount->total);

   //dsm('Numero de orden: '.$reqInf->request->payment->reference);
  $order = commerce_order_load($reqInf->request->payment->reference);
   //dsm($order);
  $usuario = user_load($order->uid);
   //dsm($usuario);
   //dsm($reqInf);
  dsm('Estado del pago: '.$reqInf->status->status);
  dsm('Nombre de la tarjeta: '.$reqInf->payment[0]->paymentMethod); // name of credit card
  dsm('Numero de orden: '.$reqInf->payment[0]->reference); // Num Order 
  dsm('Autorizacion: '.$reqInf->payment[0]->authorization); // authorizaton code
  dsm('Monto total: '.$reqInf->payment[0]->processorFields[1]->value); // monto total
  dsm('Referencia Intera: '.$reqInf->payment[0]->internalReference); // Referencia Interna
  dsm('Monto total: '.$reqInf->payment[0]->amount->from->total); // monto total
  dsm('Monto total: '.$reqInf->request->payment->amount->total); // monto total
   /*if(isset($reqInf->payment[0]->processorFields[0]->value->installments)){
     dsm($reqInf->payment[0]->processorFields[0]->value->installments);
   }else{
     dsm('seteado a arreglo 1');
     dsm($reqInf->payment[0]->processorFields[1]->value->installments);
   }*/
  dsm('Meses: '.$reqInf->payment[0]->processorFields[$puntero]->value->installments); // periodo plazo
  dsm('Tipo de credito: '.$reqInf->payment[0]->processorFields[$puntero]->value->type); // type of credit tc
  $transactions = commerce_payment_transaction_load_multiple(array(), array('order_id' => $order->order_id));
  dsm($transactions);
  isPendingPayment('1103756845');
  }else{
    drupal_set_message('You should send a GET parameter (requestId) ');
  }
  return "Retrieve information from getRequestInformation method from Place2Pay using requestId";
}
/**
* Get Abrev from credit card's name
*/
function getAbr($nameCard){
   $abrev = '';
   switch ($nameCard){
  	case 'visa': $abrev = "VI"; break;
  	case 'mastercard': $abrev = "NN"; break;
  	case 'diners': $abrev = "DN"; break;
  	case 'discover': $abrev = "DI"; break;
  	default: $abrev = "NN"; break;
   }
   return $abrev;
}
/*
* Return Stdclass with values from the payment
* @param $requestId
*	This value is build for each transacction from place2pay
* @return StdClass
*/
function _getRequestInformation($requestId){
  watchdog('place2pay', 'Metodo getRequestInformation con Id :id', array(':id' => $requestId), WATCHDOG_INFO);
  module_load_include('php','place2pay','vendor/autoload');
  $login = LOGIN_P2P;
  $trankey = '9EPoJ98NIr72BJ9x';
  $secretKey = TRANKEY_P2P;
  $url_ep = URL_EP;
  $seed = date('c');

  if (function_exists('random_bytes')) {
    $nonce = bin2hex(random_bytes(16));
  } elseif (function_exists('openssl_random_pseudo_bytes')) {
    $nonce = bin2hex(openssl_random_pseudo_bytes(16));
  } else {
    $nonce = mt_rand();
  }
  $nonceBase64 = base64_encode($nonce);

  $tranKey = base64_encode(sha1($nonce . $seed . $secretKey, true));

  $curl = curl_init();

   curl_setopt_array($curl, array(
      CURLOPT_URL => URL_EP . "api/session/".$requestId,  //Append the requestId builded from place2pay
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "POST",
      CURLOPT_HTTPHEADER => array(
         "Cache-Control: no-cache",
         "Content-Type: application/json",
         "Postman-Token: 96983e26-ba1b-4dfa-bbe9-54f877428d08"
      ),
  ));

  $request = [
    "auth" => [
       "login" => LOGIN_P2P,
       "seed" => $seed,
       "nonce" => $nonceBase64,
       "tranKey" => $tranKey
    ],
  ];	
  $data = json_encode($request);
  curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
  $json_response = curl_exec($curl);
  $err = curl_error($curl);
  if( $err != '' ){
    watchdog('place2pay', 'Place2pay - curl_error is :error', array(':error' => $err), WATCHDOG_DEBUG);
  }  
  curl_close($curl);

  $response = json_decode($json_response, false);	
  return $response;
}
/**
* Check the payment, this function allow to verify if the data is correct
* Can access from URL <path_site>/place2pay/requestinformation
* This function show a multilevel Array, is better if you have enable the dev module
*/
function place2pay_reversePayment(){
  // $reqId = '21141967';
  $internalReference = arg(2);
  if(isset($internalReference)){
    dsm('requestId: '.$internalReference);
    $reverseInf = _reversePayment($internalReference);
    dsm($reverseInf);  
  }else{
    drupal_set_message('You should send a GET parameter (internalReference) ');
  }
  return "Retrieve information from reversePayment method from Place2Pay using internalReference";
}
/*
* Reverse a Payment
* @param $internalReference
* Internal reference value, get from getRequestInformation
* @return StdClass
*/
function _reversePayment($internalReference){
  watchdog('place2pay', 'Metodo reversePayment con referencia interna :id', array(':id' => $internalReference), WATCHDOG_INFO);
  module_load_include('php','place2pay','vendor/autoload');
  $login = LOGIN_P2P;
  $trankey = '9EPoJ98NIr72BJ9x';
  $secretKey = TRANKEY_P2P;
  $url_ep = URL_EP;
  $seed = date('c');

  if (function_exists('random_bytes')) {
    $nonce = bin2hex(random_bytes(16));
  } elseif (function_exists('openssl_random_pseudo_bytes')) {
    $nonce = bin2hex(openssl_random_pseudo_bytes(16));
  } else {
    $nonce = mt_rand();
  }
  $nonceBase64 = base64_encode($nonce);
  $tranKey = base64_encode(sha1($nonce . $seed . $secretKey, true));
  $curl = curl_init();

   curl_setopt_array($curl, array(
      CURLOPT_URL => URL_EP . "api/reverse",  //Append the requestId builded from place2pay
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "POST",
      CURLOPT_HTTPHEADER => array(
         "Cache-Control: no-cache",
         "Content-Type: application/json",
         "Postman-Token: 96983e26-ba1b-4dfa-bbe9-54f877428d08"
      ),
  ));

  $request = [
    "auth" => [
       "login" => LOGIN_P2P,
       "seed" => $seed,
       "nonce" => $nonceBase64,
       "tranKey" => $tranKey
    ],
    "internalReference" => $internalReference
  ];	
  $data = json_encode($request);
  // dsm($data);
  curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
  $json_response = curl_exec($curl);
  $err = curl_error($curl);
  if( $err != '' ){
    watchdog('place2pay', 'Place2pay - curl_error is :error', array(':error' => $err), WATCHDOG_DEBUG);
  }  
  curl_close($curl);

  $response = json_decode($json_response, false);	
  return $response;
}
/**
* This function get requestId, processURL and status from REST service P2P
* Get a valid URL for the payment
*/
function get_validP2P($payerP2P, $amount, $order){
  global $base_url;
  $returnPath = $base_url . "/checkout/" . $order->order_id . "/review";
  module_load_include('php', 'place2pay', 'vendor/autoload');
  $secretKey = TRANKEY_P2P;	
  $seed = date('c');	

	if (function_exists('random_bytes')) {
		$nonce = bin2hex(random_bytes(16));
	} elseif (function_exists('openssl_random_pseudo_bytes')) {
		$nonce = bin2hex(openssl_random_pseudo_bytes(16));
	} else {
        $nonce = mt_rand();
	}
	$nonceBase64 = base64_encode($nonce);

	$trankey = base64_encode(sha1($nonce . $seed . $secretKey, true));
	
	//SOLICITAMOS LA CREACION DE SESSION PARA EL PAGO PLACETOPAY
  $curl = curl_init();

  curl_setopt_array($curl, array(
    CURLOPT_URL => URL_EP . "api/session/",
    CURLOPT_RETURNTRANSFER => true,
    CURLOPT_ENCODING => "",
    CURLOPT_MAXREDIRS => 10,
    CURLOPT_TIMEOUT => 30,
    CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
    CURLOPT_CUSTOMREQUEST => "POST",
    CURLOPT_HTTPHEADER => array(
      "Cache-Control: no-cache",
      "Content-Type: application/json",
      "Postman-Token: 96983e26-ba1b-4dfa-bbe9-54f877428d08"
    ),
  ));
  // Set data for placetopay datagram
	$reference = $order->order_id;
  	$nombre = $payerP2P['first_name'];
	$apellido = $payerP2P['last_name'];
	$direccion = $payerP2P['thoroughfare'];
  # watchdog('place2pay', 'Cadena apellido - notificacion :apellido', array(':apellido' => $apellido), WATCHDOG_INFO);
  // Multimensional Array forma with order data
	$request = [
		"auth" => [
         "login" => LOGIN_P2P,
         "seed" => $seed,
         "nonce" => $nonceBase64,
         "tranKey" => $trankey, 
      ],
      "locale" => 'es_EC',
	   'payment' => [
	      'reference' => $order->order_id, // (M)
	      'description' => 'Pago con Orden Nro ' . $order->order_id . " en Municipio de Loja" ,
	      'amount' => [
	         'currency' => 'USD', // (M)
	         'total' => $amount, // (M)
	      ],
	    ],
	   'buyer' => [
  			"document" => $_SESSION['ced'], //Mandatory (M)
  			"documentType" => "CC",
  			"name" => $nombre, // (M)
  			"surname" => $apellido,
  			"email" => $order->mail, // (M)
  			"mobile" => "099148458",
  			"address" => [
    			"street" => $direccion,
    			"city" => $payerP2P['locality'],
    			"country" => $payerP2P['country']
			  ]
		  ],
	    #'expiration' => date('c', strtotime('+1 days')), // (M)
	    'expiration' => date('c', strtotime('10 minute')), // (M)
	    'returnUrl' => $returnPath, // (M) Modify this line
	    'ipAddress' => $order->hostname, // (M)
	    'noBuyerFill' => TRUE, // (O) TRUE avoid autocomplete by default is FALSE
	    'userAgent' => 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36', // (M)
	];
	$data = json_encode($request); // generate json for $request and store at data
  curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
	$json_response = curl_exec($curl);
	$err = curl_error($curl);
  if( $err != '' ){
    watchdog('place2pay', 'Place2pay - curl_error is :error', array(':error' => $err), WATCHDOG_DEBUG);
  }  
	curl_close($curl);
	$response = json_decode($json_response, false);
        //watchdog('place2pay', 'Place2pay - Respuesta :response', array(':response' => $response), WATCHDOG_DEBUG);
  return $response;
}
/**
* FUNCTION for update place2pay table for control
* @param $ipn array
* @param $tipo string
*/
function update_place2pay($ipn, $tipo){
  switch ($tipo) {
    case 'notifica':
      $db_up = db_query('UPDATE place2pay
        SET mensaje = :msg,
            estado =  :estado
        WHERE requestId = :requestId',
          array(':msg' => $ipn['mensaje'],
            ':estado' => $ipn['estado'],
	          ':requestId' => $ipn['requestId']
          )
      );
      watchdog('place2pay', 'Update place2pay - notificacion :mensaje', array(':mensaje' => $ipn['mensaje']), WATCHDOG_INFO);
      break;

    case 'gim':
      $db_up = db_query('UPDATE place2pay
        SET gim = :gim,            
        WHERE requestId = requestId',
          array(':gim' => 1            
      ));
      watchdog('place2pay', 'Update GIM SYSTEM - Concilia :mensaje', array(':mensaje' => $ipn['estado']), WATCHDOG_INFO);
      break;

    case 'concilia':
      # code...
      $ipn['total']= (isset($ipn['total']) ? $ipn['total'] : 0);  //check if the total is empty      
      $db_up = db_query('UPDATE place2pay
        SET cct = :cct,
            interes = :interes,
            total = :total,
            aut = :aut,
            tc = :tc,
            mes = :mes,
            estado = :estado,
            mensaje = :msg
        WHERE requestId = :requestId
            ', array(
            ':cct' => $ipn['cct'],
            ':interes' => $ipn['interes'],
            ':total' => $ipn['total'],
            ':aut' => $ipn['aut'],
            ':tc' => $ipn['tc'],
            ':mes' => $ipn['mes'],
            ':estado' => $ipn['estado'],
            ':msg' => $ipn['mensaje'],
            ':requestId' => $ipn['requestId'] 
        ));
      watchdog('place2pay', 'Update place2pay - Concilia :mensaje', array(':mensaje' => $ipn['estado']), WATCHDOG_INFO);
      break;
    
    default:
      # code...
      break;
	}
}
/**
* Get Credit Card's name from abrev
* @param $abrev
*   Abrev for each Credit Card
*/
function get_nameccp2p($abrev){
   switch($abrev){
  	case 'DN': return "Diners Club"; break;
  	case 'DI': return "Discovery"; break;
  	case 'MC': return "Master Card"; break;
  	case 'VI': return "Visa"; break;
   }
}
//-------------------- FORM FOR UPDATE GIM MANUALLY ------------------------------
/**
* Form by conciliation and verification values between Municipality and VPOS (interdin)
*/
function updGim_form($form, &$form_state){  
  $form['updategim'] = array(
    '#title' => t('Actualización manual de GIM - P2P'),
    '#description' => t('Actualización manual de GIM con número de transacción - P2P'),
    '#type' => 'fieldset',    
  );
  $form['updategim']['txn'] = array(
    '#title' => t('Código de transacción'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 5,
      '#size' => 5,
      '#description' => t('Código de transacción'),      
  );
  $form['updategim']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Actualizar GIM'),    
  );  
  return $form;

}
function updGim_form_validate($form, &$form_state){

}
function updGim_form_submit($form, &$form_state){
  $txn_id = $form_state['values']['txn'];
  $db_up = db_query('UPDATE place2pay
                      SET flag = 0
                        WHERE txn_id = :txn_id
                        ', array(                          
                          ':txn_id' => $txn_id
                         ));
  confirmar_gimp2p($txn_id);
  drupal_set_message("Sistema GIM Actualizado - P2P con transaccion: " . $txn_id);
}
/**
* Function for confirm payment and update GIM with consulta XML
* @param $id_txn
*   Local Transaction ID
*/
function confirmar_gimp2p($id_txn){
  watchdog('UPDATE GIM', 'Verificando... :txn_id', array(':txn_id' => $id_txn), WATCHDOG_INFO);
  if(check_txnidp2p($id_txn)){ 
    watchdog('UPDATE GIM','Dentro de la funcion confirmar_gim .. update GIM',array(),WATCHDOG_INFO);
    module_load_include('inc','impuestos'); // Call for get functions available from impuestos module
    // Update paid taxes from GIM System    
    $pagado = registrarPagoatGIM($id_txn); // Enabled when the pay is done for update GIM
    #drupal_mail('payclub','success','dbetancourt@loja.gob.ec', language_default(),$params);
    $updb = db_query('UPDATE place2pay
                      SET flag = 1
                      WHERE txn_id = :id_txn',
                      array(':id_txn' => $id_txn));
    // TODO
    // Need to get requestId from place2pay table with $id_txn condition
    // $query = db_query('SELECT requestId from place2pay WHERE txn_id = :txn_id', array(':txn_id' => $id_txn));
    // After you need to call _getRequestInformation with $requestId like parameter
    // $reqInf = _getRequestInformation($query[0]->requestId);
    // Fill ipn with fillIPN function with reqInf like parameter
    // $ipn = fillIPN($reqInf);
    // Finally call to postprocess function with $ipn for update the order and change status
    // postprocess($ipn);
  }
}
/**
 * Concilliation values website and GIM 
 * This function allow to update the GIM values that can't be saved 
 */
function concilliation_gim(){  
  $fechahoy = date('Y-m-d');
  // $fechahoy = '2022-10-10';    
  $fStart = $fechahoy . " 05:00:00";
  $fEnd   = $fechahoy . " 23:59:59";
  drupal_set_message($fechahoy);
  $empty_status = db_query("SELECT txn_id FROM place2pay
                          WHERE aut != ''
                          AND estado = 'APPROVED'
                          AND gim = 0
                          AND fecha > :fStart AND fecha < :fEnd 
                          ORDER BY txn_id desc",
                          array(':fStart'=> $fStart, ':fEnd' => $fEnd))->fetchall();
  
  for($i=0; $i<sizeof($empty_status); $i++){
    dsm($empty_status[$i]->txn_id);
    watchdog('ConcilliationGIM', 'txn_id :txn_id', array(':txn_id' => $empty_status[$i]->txn_id), WATCHDOG_INFO);
    module_load_include('inc','impuestos'); // Call for get functions available from impuestos module
    // Update paid taxes from GIM System    
    $pagado = registrarPagoatGIM($id_txn); // Enabled when the pay is done for update GIM
    // confirmar_gimp2p($empty_status[$i]->txn_id);            
  }
  return "Conciliado GIM";
  
}
/**
* Make a verification for txn_id if it was update with flag equal 0
* @param $txn_id
*   Transaction ID for check status at DB
* @return 
*   Boolean
*/
function check_txnidp2p($txn_id){
  $check = array();
  $check = db_query('SELECT txn_id, flag
         FROM place2pay
         WHERE txn_id = :txn_id
         AND flag = 0',
               array(':txn_id' => $txn_id))->fetchall();
  if(empty($check))
     return false;
  else return true;
}
//----------------- CIERRE DE CAJA ----------------------------------------
/**
* Form by conciliation and verification values between Municipality and VPOS (interdin)
*/
function cajap2p_form($form, &$form_state){
  global $base_url;
  
  $form['caja'] = array(
    '#title' => t('Generando archivo de Caja por fecha'),
    '#description' => t('Recuerde que las conciliaciónes se deben realizar hasta las 10am'),
    '#type' => 'fieldset',    
  );
  $form['caja']['fecha'] = array(
    '#title' => t('Fecha de caja'),    
    '#type' => 'date_popup',
    '#default_value' => date('Y-m-d'),
    '#date_format' => 'Y-m-d',
    '#date_label_position' => 'within',
    '#date_increment' => 15,
    '#date_year_range' => '-4:+2',      
  );
  $form['caja']['old'] = array(
    '#title' => t('Payclub (plataforma anterior 2015-2019)'),
    '#type' => 'checkbox'
  );
  $form['caja']['conciliar'] = array(
    '#type' => 'submit',
    '#value' => t('Generar cierre'),    
  );
  $form['#method']  = 'post';
  $form['#action']  = $base_url . '/place2pay/cierrecaja';  
  return $form;

}
/**
* Validate the form sent
*/
function cajap2p_form_validate($form, &$form_state){

}
function cajap2p_form_submit($form, &$form_state){  
  $fec = $form_state['values']['fecha']." 00:01:00";
  $fecm = $form_state['values']['fecha']." 23:59:00";
  $txns = db_query("SELECT txn_id, fecha, cedula, subtotal, cct, aut, estado 
                  FROM place2pay pc                  
                  WHERE pc.fecha > :fec 
                  AND pc.fecha < :fecm 
                  AND pc.estado = 'APPROVED' ",
                  array(':fec' => $fec, ':fecm' => $fecm))->fetchall();
                  
  $txns = json_decode(json_encode($txns), true);  
  
  // $txns = prepareDataCSV($txns);
  // write_pdf($txns);
  // $form_state['redirect'] = 'payclub/cierrecaja';
   
}
/* Cierre de Caja Payclub */
function place2pay_cierrecaja(){  
  if(!isset($_POST['fecha']['date'])){

  }
  $fec = $_POST['fecha']['date']." 00:01:00";
  $fecm = $_POST['fecha']['date']." 23:59:00";
  $txns = db_query("SELECT txn_id, fecha, cedula, subtotal, cct, aut, estado, order_id    
                  FROM place2pay pc                  
                  WHERE pc.fecha >  :fec 
      AND pc.fecha < :fecm
      AND pc.estado = 'APPROVED' ",
                  array('fec' => $fec, 'fecm' => $fecm))->fetchall();
  // Query for old values from payclub table (2015-2019)
  if(isset($_POST['old'])){
    $txns = db_query("SELECT vpos_txn_id as txn_id, 
                             vpos_fec as fecha, 
                             vpos_ced as cedula, 
                             vpos_subtotal as subtotal, 
                             vpos_cct as cct, 
                             vpos_aut as aut                             
                  FROM payclub_vpos pc
                  WHERE pc.vpos_fec >  :fec
      AND pc.vpos_fec < :fecm
      AND pc.vpos_aut != '' ",
                  array('fec' => $fec, 'fecm' => $fecm))->fetchall();
  }
  $t = sizeof($txns);  
  $tvisa = 0;
  $tdiners =0;
  $tmcard = 0;
  $tdiscover = 0;
  $s = '<table border=1><thead>'.
       '<tr><th>Num</th>'.       
       '<th>ID Transaccion</th>'.
       '<th>Fecha de Pago</th>'.
       '<th>Cédula Contribuyente</th>'.
       '<th>Valor</th>'.
       '<th>Tarjeta</th>'.
       '<th>Autorizacion</th>'.
       '<th>Referencia</th>'.
       '<th>Estado</th>'.       
       '</tr></thead><tbody>';
  
  for($i=0; $i<$t; $i++){    
    switch ($txns[$i]->cct) {
      case 'VI':
        $tvisa = $tvisa + $txns[$i]->subtotal;
        break;
      case 'DN':
        $tdiners = $tdiners + $txns[$i]->subtotal;
        break;
      case 'DI':
        $tdiscover = $tdiscover + $txns[$i]->subtotal;
        break;
      case 'NN':
        $tmcard = $tmcard + $txns[$i]->subtotal;
        break;
      
      default:
        # code...
        break;
    }
    $s .= '<tr>';
    $s .= '<td>'. ($i + 1) .'</td>';
    $s .= '<td>'. $txns[$i]->txn_id .'</td>';
    $s .= '<td>'. $txns[$i]->fecha .'</td>';
    $s .= '<td>'. $txns[$i]->cedula .'</td>';
    $s .= '<td text-align"right">'. $txns[$i]->subtotal .'</td>';
    $s .= '<td>'. $txns[$i]->cct .'</td>';
    $s .= '<td>'. $txns[$i]->aut .'</td>';
    if(!isset($_POST['old'])){
      $s .= '<td>'. $txns[$i]->order_id .'</td>';
      $s .= '<td>'. $txns[$i]->estado .'</td>';
    }else{
      $s .= '<td>'. 'Order Id' .'</td>';
      $s .= '<td>'. 'APPROVED' .'</td>';
    }

  }
  $s .= '</tbody></table>'; 

  $s .= '<strong>(VI) VISA:</strong> ' . $tvisa .' :: ';
  $s .= '<strong>(DN) DINERS: </strong>' . $tdiners .' :: ';
  $s .= '<strong>(DI) DISCOVER: </strong>' . $tdiscover .' :: ';
  $s .= '<strong>(MC) MASTERCARD:</strong> ' . $tmcard .' :: ';
  $s .= '<h3>Recaudación TOTAL: ' . ($tvisa + $tdiners + $tdiscover + $tmcard) .'</h3>';
  write_pdfp2p($s); // disable this line if you want html


  return $s;
}
/* WRITE PDF
* @param html - render get from another function
*/
function write_pdfp2p($html){
  //module_load_include('php','place2pay','mpdf/mpdf');
  module_load_include('php','place2pay','vendor/autoload');
  //module_load_include('php','payclub','lib/fpdf');  
  $mode=''; // (Blanco para establecer el valor por defecto)<br>
  /* Se especifica un tamaño de página predefinido o como un arreglo<br>
  * de ancho y altura en milímetros */   
  $format=array(180,150);
  // Establecemos el tamaño de la fuente por defecto para el documento (pt)<br>
  $font_s=''; // (Blanco para establecer el valor por defecto)<br>
  // Establecemos el tipo de letra familia a aplicar en el documento<br>
  $font_f=''; // (Blanco para establecer el valor por defecto)<br>
  // Establecemos los márgenes de las páginas en milímetros para el documento<br>
  $marg_l=5;  // Margen izquierdo<br>
  $marg_r=5;  // Margen derecho<br>
  $marg_t=25; // Margen superior<br>
  $marg_b=10; // Margen inferior<br>
  $marg_h=5;  // Margen de la cabecera de la página<br>
  $marg_f=5;  // Margen del pie de página<br>
  //$mpdf = new mPDF();
//  $mpdf=new mPDF($mode,'',$font_s,$font_f,$marg_l,$marg_r,$marg_t,$marg_b,$marg_h,$marg_f);
  $mpdf = new \Mpdf\Mpdf(['tempDir' => '/tmp',
			  'margin_top'=> 28, 
			  'margin_left'=> 5, 
			  'margin_header'=> 5, 
			  'margin_footer'=> 5, 
			  'margin_right' => 5
  ]);
  $mpdf->showImageErrors = true;
  $headerLogo = '<img src="sites/all/modules/custom/place2pay/images/logo.png" width="80" height="80">';  
  $mpdf->setHTMLHeader($headerLogo);
  $mpdf->defaultfooterline=1;
  $mpdf->SetHTMLFooter('
    <table width="100%" style="vertical-align: bottom; font-family: serif; 
        font-size: 8pt; color: #000000; font-weight: bold; font-style: italic;">
        <tr>
            <td width="33%">{DATE j-m-Y}</td>
            <td width="33%" align="center">{PAGENO}/{nbpg}</td>
            <td width="33%" style="text-align: right;">Cierre de Caja - Tarjetas de Crédito</td>
        </tr>
    </table>');
  $mpdf->WriteHTML($html);
  $filename = "CierreCaja-".Date("Y-m-d").".pdf";
  $mpdf->Output($filename,'D');  

}
