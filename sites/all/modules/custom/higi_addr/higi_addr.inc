<?php
function consultad_form($form, &$form_state){
  $form['consulta'] = array(
    '#title' => t('Datos del abonado'),
    '#type' => 'fieldset',
    '#description' => t('Consulta datos del usuario a traves de la cedula')
  );
  $form['consulta']['cedula'] = array(
      '#title' => t('Número de cédula'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 15,
      '#description' => t('Your ID have to 10 characters'),
  );
/*$form['consulta']['captcha'] = array(
    '#type' =>  'captcha',
    //'#captcha_type' =>  'recaptcha/reCAPTCHA',
    //'#captcha_type' =>  'captcha/Math',
    '#captcha_type' =>  'image_captcha/Image',
  );*/
  $form['consulta']['save'] = array(
      '#prefix' => '<div class="consulta">',
      '#type' => 'submit',
      '#value' => t('Consultar'),
      '#suffix' => '</div>',
  );
  $form['#method']  = 'get';
  $form['#action']  = '/higiene/consulta/resdir';
  $form['#attributes'] = array('class' => array('ced'));

  return $form;
}
/**
 * Function that get user data using the ID (cedula)
 * @param $ced
 * @return Multiarray
 */
function get_addr_by_ced($ced){
  //$ced = '1101771804';
  $url = "http://" . WS_IP . URL_DIR_HIGIENE . $ced;
	//$url1 = 'http://192.168.1.146:8080/gim/seam/resource/rest/cadaster/1101771804';

  $curl = curl_init($url);
	$headers = array( "Content-Type: application/json;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAMHIG); // With authentication
  $json_response = curl_exec($curl);

	/*if($json_response){
	  drupal_set_message('Se ha emitido con éxito - consulta con datos ', 'status');
	}*/
	$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);
	curl_close($curl);
  $response = json_decode($json_response, false);
  //dsm($response);
	return $response;
}
/**
 * Function to show the result
 */
function resultado_direccion(){
  $result = get_addr_by_ced($_GET['cedula']);
  if(isset($result)){
/*    $com = "<strong>Cedula:</strong> " . $_GET['cedula'] ."</br>";
    $com .= "<strong>Nombre:</strong> " . $result[1]->name."</br>";
    */
    $com = "<br><strong>Dirección:</strong> Comercial</br>";
    $com .= "<table border=1 width='100%' class='table table-responsive'><thead>";
    $com .="<tr><th>Comercio</th><th>Código</th><th>Actividad</th><th>Dirección</th><th>Telefonos</th><tr>";
    $com .= "</thead><tbody>";

    $dom = "<strong>Dirección</strong> Domiciliaria</br>";
    $dom .= "<table class='table table-responsive'><thead>";
    $dom .='<tr><th data-breakpoints="xs">Nombres Contribuyente</th><th>Identificación</th><th>Dirección</th><th>Telf Convencional</th><th>Telf Celular</th><tr>';
    $dom .= "</thead><tbody>";

    $prop = "<br><strong>Dirección</strong>Propiedades</br>";
    $prop .= "<table class='table table-responsive'><thead>";
    $prop .="<tr><th>Calle</th><th>Clave Castastral</th><th>Barrio</th><th>Referencia</th><th>Número de casa</th><tr>";
    $prop .= "</thead><tbody>";

    $med = "<br><strong>Dirección</strong> Medidores</br>";
    $med .= "<table class='table table-responsive'><thead>";
    $med .="<tr><th>Ruta</th><th>Nro Servicio</th><th>Calle Conexión</th><th>Ubicación</th><th>Nro Casa</th><tr>";
    $med .= "</thead><tbody>";
    $lengthB = sizeof($result);
    for($i=0; $i<$lengthB; $i++){
      switch ($result[$i]->directionType){
        case 'Dir. Domiciliaria':
          $dom .= '<tr class="odd">'
          .'<td>'. $result[$i]->name . '</td>'
          . "<td>". $result[$i]->identificationNumber ."</td>"
          . "<td>". $result[$i]->street ."</td>"
          . "<td>". $result[$i]->phoneNumber ."</td>"
          . "<td>". $result[$i]->mobileNumber ."</td></tr>";
          break;
        case 'Dir. Propiedades' :
          $prop .= '<tr class="odd">'
          .'<td>'. $result[$i]->name . '</td>'
          . "<td>". $result[$i]->identificationNumber ."</td>"
          . "<td>". $result[$i]->street ."</td>"
          . "<td>". $result[$i]->phoneNumber ."</td>"
          . "<td>". $result[$i]->mobileNumber ."</td></tr>";
          break;
        case 'Dir. Medidores' :
          $med .= '<tr class="odd">'
          .'<td>'. $result[$i]->name . '</td>'
          . "<td>". $result[$i]->identificationNumber ."</td>"
          . "<td>". $result[$i]->street ."</td>"
          . "<td>". $result[$i]->phoneNumber ."</td>"
          . "<td>". $result[$i]->mobileNumber ."</td></tr>";
          break;
        case 'Dir. Comercial' :
          $com .= '<tr class="odd">'
          .'<td>'. $result[$i]->name . '</td>'
          . "<td>". $result[$i]->identificationNumber ."</td>"
          . "<td>". $result[$i]->street ."</td>"
          . "<td>". $result[$i]->phoneNumber ."</td>"
          . "<td>". $result[$i]->mobileNumber ."</td></tr>";
          break;
      }
    }

    $dom .= "</tbody></table>";
    $com .= "</tbody></table>";
    $med .= "</tbody></table>";
    $prop .= "</tbody></table>";




  }else{
   $com .= "<h2>Verifique su número de cédula, NO EXISTE en el sistema</h2>";
  }
  return $dom . $com . $prop . $med;

}
