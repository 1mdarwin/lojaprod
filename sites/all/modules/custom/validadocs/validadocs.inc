<?php
// 1100048451 varios medidores
//
function consultadoc_form($form, &$form_state){
  global $base_url;    
  $form['consulta'] = array(
      '#title' => t('Datos del documento Municipal'),
      '#type' => 'fieldset',
      '#description' => t('Consulta a través de su número de documento'),
  );
  $form['consulta']['numDoc'] = array(
      '#title' => t('Número de documento'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 15,
      '#description' => t('Ingrese su número de documento. Ej: fff666677777'),
	); 
  $form['consulta']['captcha'] = array(
    '#type' =>  'captcha',
    //'#captcha_type' =>  'recaptcha/reCAPTCHA',  // prod
    '#captcha_type' =>  'captcha/Math', // test
    //'#captcha_type' =>  'image_captcha/Image',    
  );
  //$form['#action'] = $base_url . '/consulta/res';  
  //$form['#action'] = 'https://www.loja.gob.ec/consulta/resultado';
  //$form['#attached']['js'] = array(drupal_get_path('module','impuestos').'/js/impuestos.js',); // desactiva javascript
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
function consultadoc_form_validate(&$form, &$form_state){
  // $cedula = $form_state['values']['cedula'];
  /*if(strlen($cedula) < 10 ||(strlen($cedula) > 13) || !is_numeric($cedula)){
    form_set_error('cedula', t('Debe digitar un número de cédula válido'));
  }
  if(empty($cedula)|| !is_numeric($cedula)){// || strlen($_POST['g-recaptcha-response'])==0){
    form_set_error('cedula', t('Debe digitar un número de cédula válido'));
  }*/
}
/*
 * Function for submit consulta_form
 */  
function consultadoc_form_submit(&$form, &$form_state){
  $_SESSION['numDoc'] = $form_state['values']['numDoc'];  
  unset($_SESSION['dataws']);
  $_SESSION['post'] = $_POST;  
  // $_SESSION['dataws'] = get_documento($form_state['values']['numDoc']); // Get document PDF from webservice
  $form_state['redirect'] = '/validadocs/'. $form_state['values']['numDoc'];
  //if(module_exists('impuestos')){
    //$form_state['redirect'] = 'consulta/res';
  //}  
}

/**
* Get taxes from GIM System for each citizen with parameter ID
* @param ced - DNI for each person
* @return response - Multidimmensional array
*/
function get_documento(){
  $docNumber = arg(1);
	$url = "http://" . IP_VDOCS . PORT_WS_VDOCS . QRY_GET_PDF_VDOCS . $docNumber;	

	// The token will be get when the user log in and after save into SESSION var
	// module_load_include('inc','infopersona'); // Call for get functions available from ctaunica module
    $token = get_tokenWS();
    if(!isset($_SESSION['tokeniml'])){
    	$token = get_tokenWS(); // Renew Token
    }else{
    	$token = $_SESSION['tokeniml'];
    }
  $authorization = "Authorization: Bearer ".$token; // Prepare the authorisation token    
	

	$curl = curl_init($url);
	// $headers = array( "Content-Type: application/json;");
  $headers = array( "Accept: application/octet-stream;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, array($headers, $authorization));
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	// curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM_VDOCS); // With authentication
	// curl_setopt($curl, CURLOPT_POST, true);
	$json_response = curl_exec($curl);
	
	if($json_response){
	  //drupal_set_message('Se ha emitido con éxito - get_facturas_file ', 'status');
	}	
	$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);	
	curl_close($curl);
	
	$path = '/tmp/'. $docNumber .'.pdf'; // Temporal files with number document like filename
	
	// save PDF buffer
	file_put_contents($path, $json_response);

	// ensure we don't have any previous output
	if(headers_sent()){
	    exit("PDF stream will be corrupted - there is already output from previous code.");
	}

	header('Cache-Control: public, must-revalidate, max-age=0'); // HTTP/1.1
	header('Pragma: public');
	header('Expires: Sat, 26 Jul 1997 05:00:00 GMT'); // Date in the past
	header('Last-Modified: '.gmdate('D, d M Y H:i:s').' GMT');

	// force download dialog
	 header('Content-Type: application/force-download'); // Forzar descarga  
	 header('Content-Type: application/octet-stream', false);
	 header('Content-Type: application/download', false);

	// use the Content-Disposition header to supply a recommended filename
	// header('Content-Disposition: attachment; filename="'.basename($path).'";'); // Download
  header('Content-Disposition: inline; filename="'.basename($path).'";'); // View  
	header('Content-Transfer-Encoding: binary');
	header('Content-Length: '.filesize($path));
	header('Content-Type: application/pdf', true);

	// send binary stream directly into buffer rather than into memory
	readfile($path);

	// make sure stream ended
	exit();
	return "Documento válido";
}

/**
  * Mandatory*
  * Function get token for many connections to other endpoints
  */
  function get_tokenWS(){    
    $url = "http://" . IP_VDOCS . PORT_WS_VDOCS . QRY_LOGIN_VDOCS;  
  
    // $content = "username=1103535991&password=Lojapp59911087"; // parameters body
    $content = [
      'username' => '1103535991',
      'password' => 'Lojapp59911087'
    ];
    $headers = array( "Content-Type: application/json;");
    
    $curl = curl_init($url);
    curl_setopt($curl, CURLOPT_HEADER, false);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    // curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM_VDOCS); // With authentication
    curl_setopt($curl, CURLOPT_POST, true);
    curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($content)); // Content with parameters body
    curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
  
    $json_response = curl_exec($curl); // JSON output
    dsm($json_response);
  
    /*if($json_response){
      drupal_set_message('JSON dentro de - get_tokenWS', 'status');
    }*/
    $status = curl_getinfo($curl, CURLINFO_HTTP_CODE);
  
    curl_close($curl);  
    $response = json_decode($json_response, true); // Convert JSON to ARRAY
    //dsm($response['token']);
    $_SESSION['tokeniml'] = $response['token']; // set session var
    return $response['token'];
  }

/**
* Get Details from process for each citizen with parameter ID process like 2020-ext-678
* @param ced - DNI for each person
* @return response - Multidimmensional array
*/
function get_vdocs_data($numdoc){
	$url = "http://" . IP_CERT . PORT_WS_DOC . QRY_DETAILPROCESS;		
        dsm($numdoc);
        dsm($url);
	$params = array('number' => $numdoc);
	$json_data = json_encode($params);	

	$curl = curl_init($url);
	$headers = array( "Content-Type: application/json;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM_CERT); // With authentication
	curl_setopt($curl, CURLOPT_POST, true);
	curl_setopt($curl, CURLOPT_POSTFIELDS, $json_data);
	$json_response = curl_exec($curl);
  dsm($json_response);
	
	/*if($json_response){
	  drupal_set_message('Se ha emitido con éxito - get_deudas ', 'status');
	}*/
	$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);
	curl_close($curl);	
	$response = json_decode($json_response, false);	

	return $response;
}
/**
 * PAGE TEST
*/
function test_page(){
  $ced = '1103756845';
  
  return 'Test with out module';
}
/**
 * VALIDA RESULTADO TABLA
*/
function resultado_valida(){
  global $base_url;
  $data = $_SESSION['dataws'];
  dsm($_SESSION['dataws']);
  if(!empty($data)){
     $len = sizeof((array) $data);
    dsm($data->certificate->identificationNumber);
    $sc = "<table border=1><tbody>";
    $sc .="<tr><th>Número de Certificado</th><th>Cédula Contrib.</th><th>Contribuyente</th><th>Fecha de creación</th><th>Responsable</th><th>Nombre de trámite</th><th>Observación</th><tr>";
    $sc .= "</thead><tbody>";
    dsm($len);
    if($len == 3){
      //$pdf = base64_encode($data[0]->alfrescoURL . "/" .$data[0]->documentName);
      //$p = base64_decode($pdf);
      $sc .= "<tr class='odd'><td>".$data->certificate->certificateNumber."</td>"
      . "<td>". $data->certificate->identificationNumber ."</td>"
      . "<td>". $data->certificate->resident ."</td>"
      . "<td>". $data->certificate->creationDate."</td>"
      . "<td>". $data->certificate->nameResponsible ."</td>"
      . "<td>". $data->certificate->motivation ."</td>"
      . '<td class="valor">'. $data->certificate->observation ."</td></tr>";
    }
    $sc .= "</tbody></table>";
  }else{
    $sc .= '<div>No existen datos a mostrar asociados con la consulta</div>';
   }
    
  // $sc .= '<a href="'.$base_url.'/tramites/valida">Nueva Consulta</a>';

  return $sc;
}
/**
* Decarga de archivo
*/
function descarga_pdf(){
  $p = base64_decode(arg(2));
  $param = explode("/",$p);
	$url = "http://" . IP_TRAMITE . PORT_WS_DOC . QRY_DOCPROCESS.$param[0];		
	$params = array('criteria' => $param[0], 'name' => $param[1]);
	$json_data = json_encode($params);	

	$curl = curl_init($url);
	$headers = array( "Content-Type: application/json;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	//curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM); // With authentication
	////curl_setopt($curl, CURLOPT_POST, false);
	////curl_setopt($curl, CURLOPT_POSTFIELDS, $json_data);
	
	$json_response = curl_exec($curl);
        $path = '/tmp/'. $param[1]; // Temporal files with number document like filename

        // save PDF buffer
        file_put_contents($path, $json_response);

        // ensure we don't have any previous output
        if(headers_sent()){
            exit("PDF stream will be corrupted - there is already output from previous code.");
        }

        header('Cache-Control: public, must-revalidate, max-age=0'); // HTTP/1.1
        header('Pragma: public');
        header('Expires: Sat, 26 Jul 1997 05:00:00 GMT'); // Date in the past
        header('Last-Modified: '.gmdate('D, d M Y H:i:s').' GMT');

        // force download dialog
        header('Content-Type: application/force-download');
        header('Content-Type: application/octet-stream', false);
        header('Content-Type: application/download', false);

        // use the Content-Disposition header to supply a recommended filename
        header('Content-Disposition: attachment; filename="'.basename($path).'";');
        header('Content-Transfer-Encoding: binary');
        header('Content-Length: '.filesize($path));
        header('Content-Type: application/pdf', false);

        // send binary stream directly into buffer rather than into memory
        readfile($path);

        // make sure stream ended
	curl_close($curl);	
        exit();
	

  return 'valor descargado';
}
