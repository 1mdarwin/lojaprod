<?php
// 1100048451 varios medidores
//
function consultatra_form($form, &$form_state){
  global $base_url;    
  $form['consulta'] = array(
      '#title' => t('Datos de trámite del abonado'),
      '#type' => 'fieldset',
      '#description' => t('Consulta a través de su número de trámite')
  );
  $form['consulta']['criteria'] = array(
      '#title' => t('Número de trámite'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 15,
      '#description' => t('Ingrese su número de trámite. Ej: 2020-ext-678'),
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
function consultatra_form_validate(&$form, &$form_state){
  $cedula = $form_state['values']['cedula'];
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
function consultatra_form_submit(&$form, &$form_state){
  $_SESSION['criteria'] = $form_state['values']['criteria'];  
  unset($_SESSION['dataws']);
  $_SESSION['post'] = $_POST;  
  $_SESSION['dataws'] = get_tramites($form_state['values']['criteria']); // Get data from webservice
  $form_state['redirect'] = 'tramites/valida/resultado';
  //if(module_exists('impuestos')){
    //$form_state['redirect'] = 'consulta/res';
  //}  
}

/**
* Get Details from process for each citizen with parameter ID process like 2020-ext-678
* @param ced - DNI for each person
* @return response - Multidimmensional array
*/
function get_tramites($ced){
	$url = "http://" . IP_TRAMITE . PORT_WS_DOC . QRY_DETAILPROCESS;		
        dsm($ced);
        dsm($url);
	$params = array('criteria' => $ced);
	$json_data = json_encode($params);	

	$curl = curl_init($url);
	$headers = array( "Content-Type: application/json;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	//curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM); // With authentication
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
function resultado_consulta(){
  global $base_url;
  $data = $_SESSION['dataws'];
  //dsm($_SESSION['dataws']);
  if(!empty($data)){
    $len = sizeof($data);
    dsm($data);
    $sc = "<table border=1><tbody>";
    $sc .="<tr><th>Número de trámite</th><th>Cédula</th><th>Fecha de creación</th><th>Atendido por</th><th>Nombre de trámite</th><th>Departamento</th><tr>";
    $sc .= "</thead><tbody>";
    if($len == 1){
      $pdf = base64_encode($data[0]->alfrescoURL . "/" .$data[0]->documentName);
      $p = base64_decode($pdf);
      $sc .= "<tr class='odd'><td><a href='".$base_url."/tramites/descarga/".$pdf."'>".$data[0]->pplessNumber."</a></td>"
      . "<td>". $data[0]->residentName."</td>"
      . "<td>". $data[0]->creationDate."</td>"
      . "<td>". $data[0]->attentionUser."</td>"
      . "<td>". $data[0]->procedureName ."</td>"
      . '<td class="valor">'. $data[0]->departmentName ."</td></tr>";
    }else{
      for($i=0; $i<$len; $i++){
        // Set a clase for tr element with even or odd
        $pdf = base64_encode($data[$i]->alfrescoURL . "/" .$data[$i]->documentName);
        $p = base64_decode($pdf);
        $tr = ($par % 2 ? '<tr class="even">' : '<tr class="odd">');         
        $sc .= $tr . "<td><a href='".$base_url."/tramites/descarga/".$pdf. "'>". $data[$i]->pplessNumber ."</a></td>"
        . "<td>". $data[$i]->residentName."</td>"
        . "<td>". $data[$i]->creationDate."</td>"
        . "<td>". $data[$i]->attentionUser."</td>"
        . "<td>". $data[$i]->procedureName ."</td>"
        . '<td class="valor">'. $data[$i]->departmentName ."</td></tr>";        
        $par+=1;          
      }
    }
    $sc .= "</tbody></table>";
  }else{
    $sc .= '<div>No existen datos a mostrar asociados con la consulta</div>';
  }
    
  $sc .= '<a href="'.$base_url.'/tramites/valida">Nueva Consulta</a>';

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
