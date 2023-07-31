<?php
function test_page_ktastro(){
  get_codes_by_ced('1100090420');
  $img = '<img width="250px" src="data:image/png;base64, lkjsl ">';
  return '<h1>Hello world, I told you</h1>'.$img;
}
/**
 * Function that build a form for make a query using DNI
 */
function catastro_form($form, &$form_state){
  if(isset($_SESSION['codes'])){
    unset($_SESSION['codes']); // Clean SESSION variable
  }
  $form['consulta'] = array(
    '#title' => t('Datos del contribuyente'),
    '#type' => 'fieldset',
    '#description' => t('Consulta propiedades del contribuyente a través de su número de cédula')
  );
  $form['consulta']['cedula'] = array(
      '#title' => t('Número de cédula'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 15,
      '#description' => t('Your ID have to 10 characters'),
  );
  $form['consulta']['captcha'] = array(
    '#type' =>  'captcha',
    //'#captcha_type' =>  'recaptcha/reCAPTCHA',  // prod
    '#captcha_type' =>  'captcha/Math', // test
    //'#captcha_type' =>  'image_captcha/Image',
  );
  //$form['#action'] = $base_url . '/consulta/res';
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
 * Validate data from form when the usar submit
 */
function catastro_form_validate($form, &$form_state){  
  $cedula = $form_state['values']['cedula'];
  if(strlen($cedula) < 10 ||(strlen($cedula) > 13) || !is_numeric($cedula)){
    form_set_error('cedula', t('Debe digitar un número de cédula o ruc válido'));
  }
  if(empty($cedula)|| !is_numeric($cedula)){// || strlen($_POST['g-recaptcha-response'])==0){
    form_set_error('cedula', t('Debe digitar un número de cédula o ruc válido'));
  }
}
/**
 * Submit data
 */
function catastro_form_submit($form, &$form_state){
  //dsm($form_state['values']['cedula']);
  //dsm($_POST['cedula']);
  $codes = get_codes_by_ced($_POST['cedula']);
  $_SESSION['codes'] = $codes;
  $_SESSION['ced'] = $_POST['cedula'];
  $form_state['redirect'] = 'ktastro/codes';
  //dsm($codes);
}
/**
* Get taxes from GIM System for each citizen with parameter ID
* @param ced - DNI for each person
* @return response - Multidimmensional array
*/
function get_codes_by_ced($ced){
  //$ced = '1101771804';
  $url = "http://" . IP_GIMSYS . PORT_WS . RESOURCES_CATASTRO . $ced;
	//$url1 = 'http://192.168.1.146:8080/gim/seam/resource/rest/cadaster/1101771804';

  $curl = curl_init($url);
	$headers = array( "Content-Type: application/json;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM); // With authentication
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
 * Function get property by code
 * @param $code 
 *        Integer take it from query with DNI (cedula)
 * @return Multiarray
 */
function get_property_by_code($code){
  $url = "http://" . IP_GIMSYS . PORT_WS . RESOURCES_CATASTRO .'property/' .$code;
  //dsm($url);
  $curl = curl_init($url);
	$headers = array( "Content-Type: application/json;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM); // With authentication
  $json_response = curl_exec($curl);  

	/*if($json_response){
	  drupal_set_message('Se ha emitido con éxito - get_deudas ', 'status');
	}*/
	$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);
	curl_close($curl);
  $response = json_decode($json_response, false);
  //dsm($response);  // uncomment this line if you want to debug the response
	return $response;
}
/**
 * Function that show the result for each citizen with their codes
 * Take argument from URL called from hook_menu
 * */
function show_table_codes(){
  global $base_url;
  //dsm($_SESSION['codes']);
  // $_SESSION['codes'] = (isset($_SESSION['codes']) ? $_SESSION['codes']) : );
  if(sizeof( $_SESSION['codes']) < 1 ){
    drupal_set_message('La cédula ingresada no dispone propiedades','warning');
    return drupal_goto($base_url.'/ktastro/consulta');
  }
  $codes = $_SESSION['codes']; // var take from form
  
  $table = '<table style="border:1px;">';
  $table .= '<caption>'.$codes[0]->residentName. ' - '.$_SESSION['ced'].'</caption>';
  $table .= '<thead><tr><th>Num</th><th>Cédula</th><th>Código (click)</th><th>Descargar PDF</th><th>Barrio</th><th>Referencia</th></tr></thead>';
  for($i=0; $i<sizeof($codes);$i++){
    $table .= '<tr><td>Código propiedad '. ($i+1) .'</td>';
    $table .= '<td>'. $codes[$i]->cadastralCode .'</td>';
    $table .= '<td><a href="/ktastro/code/'. $codes[$i]->propertyId . ' ">'.$codes[$i]->propertyId.'</a></td>';
    $table .= '<td><a class="ckpdf" href="/ktastro/code/'. $codes[$i]->propertyId . '/pdf "></a></td>';
    $table .= '<td>'.$codes[$i]->neighborhood.'</td>';
    $table .= '<td>'.$codes[$i]->addressreference .'</td>';
    $table .= '</tr>';
  }
  //$table .= '<tr><td colspan=2><a href="/ktastro/code/235656">'.$codes[0]->propertyId.'</a></td></tr>';
  $table .= '</table>';
  $table .= '<div class="nuevacon"><a class="nueva" href="'.$base_url.'/ktastro/consulta">Nueva Consulta</a></div>';
  return $table;
}
/**
 * Function to show the property's value from GIM
 */
function show_property(){ 
  global $base_url; 
  $data = get_property_by_code(arg(2));
  return get_htmlformat_ktastro($data, false);
}
/* WRITE PDF 4 KTASTRO
* @param html - render get from another function
*/
function write_pdf_ktastro($html){  
  // module_load_include('php','place2pay','mpdf/mpdf');
  require_once __DIR__ . '/vendor/autoload.php';
  //module_load_include('php','payclub','lib/fpdf');  
  $mode=''; // (Blanco para establecer el valor por defecto)<br>
  $stylesheet = file_get_contents('sites/all/themes/custom/iml2019/css/style.css');  
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
  // $mpdf=new mPDF($mode,'',$font_s,$font_f,$marg_l,$marg_r,$marg_t,$marg_b,$marg_h,$marg_f);  
  $parameters = [
    'tempDir' => '/tmp',
    'mode' => 'utf-8',
    // 'format' => [180, 150],
    'format' => 'A4',
    'orientation' => 'P',
    // 'margin-top' => 25,
    // 'margin-header' => 25,
    // 'margin-bottom' => 25,
    // 'margin-footer' => 25,
    'setAutoBottomMargin' => 'pad',
    'setAutoTopMargin' => 'stretch',
  ];
  $mpdf = new \Mpdf\Mpdf($parameters);
  
  // $mpdf=new mPDF($mode,'',$font_s,$font_f,$marg_l,$marg_r,$marg_t,$marg_b,$marg_h,$marg_f);


  $mpdf->showImageErrors = true;
  //$headerLogo = '<img src="sites/all/modules/custom/payclub/logo.png" width="80" height="80">';  
  $headerLogo = '<img src="sites/all/modules/custom/cktastral/imgs/cedulacatastral.jpg" width="800" height="80">';  
  $mpdf->setHTMLHeader($headerLogo);
  $mpdf->SetWatermarkImage('sites/all/modules/custom/cktastral/imgs/novalido.jpg');
  $mpdf->showWatermarkImage = true;
  $mpdf->defaultfooterline=1;  
  $mpdf->SetHTMLFooter('
    <table width="100%" style="vertical-align: bottom; font-family: serif; 
        font-size: 8pt; color: #000000; font-weight: bold; font-style: italic;">
        <tr>
            <td width="33%">{DATE j-m-Y}</td>
            <td width="33%" align="center">{PAGENO}/{nbpg}</td>
            <td width="33%" style="text-align: right;">Cédula Catastral</td>
        </tr>
    </table>');
    $mpdf->WriteHTML($stylesheet,\Mpdf\HTMLParserMode::HEADER_CSS);
    $mpdf->WriteHTML($html,\Mpdf\HTMLParserMode::HTML_BODY);  
  //$mpdf->WriteHTML($html);
  $filename = "Catastro-".Date("Y-m-d").".pdf";
  $mpdf->Output($filename,'D'); // show for download

}
/**
 * Print PDF file with information about cktastral
 */
function imprime_cktastral(){
  $data = get_property_by_code(arg(2));
  $html = get_htmlformat_ktastro($data, TRUE);
  //dsm($html);
  //$html = "<h1>hola mundo</h1> Mira si funciona el test";
  write_pdf_ktastro($html);
  return "Imprime PDF";
}
/**
 * Only take data
 * @param $data
 *        Array Data get from webservice
 * @param $pdf
 *        Boolean (true) get out buttons, (false) include buttons
 * @return String with html format
 */
function get_htmlformat_ktastro($data, $pdf){
  global$base_url;
  
//  dsm($data);
  $tktastro = '<table border="2" cellspacing="0" cellpadding="0" class="tktastro"><tr>';
  $tktastro .= '<td rowspan="2">Clave Castastral</td><td>'.$data->provincia.'</td>';
  $tktastro .= '<td>'. $data->canton.'</td>';
  $tktastro .= '<td>'.$data->parroquia_code.'</td><td>'.$data->zona.'</td>';
  $tktastro .= '<td>'.$data->sector.'</td><td>'.$data->manzana.'</td>';
  $tktastro .= '<td>'.$data->lote.'</td><td>'.$data->bloque.'</td>';
  $tktastro .= '<td>'.$data->piso.'</td><td>'.$data->unidad.'</td><td></td></tr>';
  $tktastro .= '<tr><td class="titlesection">PROV</td><td class="titlesection">CANT</td><td class="titlesection">PARR</td><td class="titlesection">ZONA</td><td class="titlesection">SECT</td><td class="titlesection">MANZ</td><td class="titlesection">LOT</td><td class="titlesection">BLOQ</td><td class="titlesection">PISO</td><td class="titlesection">UNI</td><td></td></tr>';

  $tktastro .= '<tr><td colspan=13 class="titleblock">CONTRIBUYENTE</td></tr>';
  $tktastro .= '<tr><td colspan=2 class="titlesection">Nombres</td> <td colspan=2>'.$data->nombres.'</td>';
  $tktastro .= '<td colspan=2 class="titlesection">Apellidos</td><td colspan=3>'.$data->apellidos.'</td>';
  $tktastro .= '<td class="titlesection">Cedula</td><td colspan=3>'.$data->cedula.'</td></tr>';
  
  $tktastro .= '<tr><td colspan="13"></td></tr>';

  $tktastro .= '<tr><td colspan=2 class="titlesection">Ubicación</td><td colspan=11>'.$data->ubicacion.'</td></tr>';
  $tktastro .= '<tr><td colspan=2 class="titlesection">Parroquia</td><td colspan=11>'.$data->parroquia.'</td></tr>';
  $tktastro .= '<tr><td colspan=2 class="titlesection">Barrio</td><td colspan=11>'.$data->barrio.'</td></tr>';
  $tktastro .= '<tr><td colspan=2 class="titlesection">Ubanización</td><td colspan=11>'.$data->urbanizacion.'</td></tr>';
  $tktastro .= '<tr><td colspan=2 class="titlesection">Manzana</td><td colspan=2>'.$data->urbanization_block.'</td>';
  $tktastro .= '<td colspan=2 class="titlesection">N&deg; Lote</td><td colspan=2>'.$data->urbanization_property_number.'</td>';
  $tktastro .= '<td colspan=2 class="titlesection">N&deg; Casa</td><td colspan=3>'.$data->numero_casa.'</td></tr>';
  if(strlen($data->foto) > 100 ){
    $tktastro .= '<tr><td colspan=4 class="titlesection">Fotografia</td><td colspan=9><img img width="250px" src="data:image/jpg;base64, '.$data->foto.'"></td></tr>';
  }else{
    $tktastro .= '<tr><td colspan=4 class="titlesection">Fotografia</td><td colspan=9>Sin Fotografia</td></tr>';
  }
  $tktastro .= '<tr><td colspan="13"></td></tr>';
  $tktastro .= '<tr><td colspan=3 class="titlesection">Linderos</td><td colspan=3 class="titlesection">Dimensiones (m)</td><td colspan=7 class="titlesection">Colindantes</td></tr>';
  // linderos norte
  $linorte = (isset($data->linderoNorteJson->length)?$data->linderoNorteJson->length:"Sin definir");
  $linortedes = (isset($data->linderoNorteJson->length)?$data->linderoNorteJson->length:"Sin definir");
  $tktastro .= '<tr><td colspan=3>Norte</td><td colspan=3>'.$linorte.'</td><td colspan=7>'.$linortedes.'</td></tr>';
  // linderos sur
  $lisur = (isset($data->linderoSurJson->length)?$data->linderoSurJson->length:"Sin definir");
  $lisurdes = (isset($data->linderoSurJson->length)?$data->linderoSurJson->length:"Sin definir");
  $tktastro .= '<tr><td colspan=3>Sur</td><td colspan=3>'.$lisur.'</td><td colspan=7>'.$lisurdes.'</td></tr>';
  // linderos este
  $lieste = (isset($data->linderoEsteJson->length)?$data->linderoEsteJson->length:"Sin definir");
  $liestedes = (isset($data->linderoEsteJson->length)?$data->linderoEsteJson->length:"Sin definir");
  $tktastro .= '<tr><td colspan=3>Este</td><td colspan=3>'.$lieste.'</td><td colspan=7>'.$liestedes.'</td></tr>';
  // linderos oeste
  $lioeste = (isset($data->linderoOesteJson->length)?$data->linderoOesteJson->length:"Sin definir");
  $lioestedes = (isset($data->linderoOesteJson->length)?$data->linderoOesteJson->length:"Sin definir");
  $tktastro .= '<tr><td colspan=3>Oeste</td><td colspan=3>'.$lioeste.'</td><td colspan=7>'.$lioestedes.'</td></tr>';
  $tktastro .= '<tr><td colspan="13"></td></tr>';
  $tktastro .= '<tr><td colspan=2 class="titlesection">Área total del terreno</td><td colspan=2>'.$data->area_total_terreno.' m&sup2;</td>';
  $tktastro .= '<td colspan=2 class="titlesection">Área total de construcción</td><td colspan=2>'.$data->area_total_construccion.' m&sup2;</td>';
  $tktastro .= '<td colspan=2 class="titlesection">Ubicación Lote</td><td colspan=3>'.$data->lot_position.'</td></tr>';
  
  $tktastro .= '<tr><td colspan="13"></td></tr>';

  $tktastro .= '<tr><td colspan=13 class="titleblock">CONSTRUCCIONES</td></tr>';
  $tktastro .= '<tr><td class="titlesection">Número Pisos</td><td class="titlesection">Año Construcción</td><td class="titlesection">Terminada</td><td class="titlesection">Equipada</td><td colspan=2 class="titlesection">Material Estructura</td><td colspan=2 class="titlesection">Material Paredes</td><td colspan=2 class="titlesection">Material Cubierta</td><td class="titlesection">Acabados Externos</td><td colspan=2 class="titlesection">Estado Edificación</td></tr>';

  for($i=0; $i<sizeof($data->construccionesJson);$i++){
    $tktastro .= '<tr><td>'.$data->construccionesJson[$i]->floorsnumber.'</td>';
    $tktastro .= '<td>'.$data->construccionesJson[$i]->buildingyear.'</td>';
    $dispone = (($data->construccionesJson[$i]->isfinished)? "X":" ");
    $tktastro .= '<td>'.$dispone.'</td>';
    $dispone = (($data->construccionesJson[$i]->hasequipment)? "X":" ");
    $tktastro .= '<td>'.$dispone.'</td>';
    $tktastro .= '<td colspan=2>'.$data->construccionesJson[$i]->structurematerial.'</td>';
    $tktastro .= '<td colspan=2>'.$data->construccionesJson[$i]->wallmaterial.'</td>';
    $tktastro .= '<td colspan=2>'.$data->construccionesJson[$i]->roofmaterial.'</td>';
    $tktastro .= '<td>'.$data->construccionesJson[$i]->externalfinishing.'</td>';
    $tktastro .= '<td colspan=2>'.$data->construccionesJson[$i]->preservationstate.'</td></tr>';
  }

  $tktastro .= '<tr><td colspan=3 class="titlesection">Tipografía del Terreno</td><td colspan=3 class="titlesection">Tipo de vias</td><td colspan=7></td></tr>';
  $tktastro .= '<tr><td colspan=3>'.$data->topografia_terreno.'</td><td colspan=3>'.$data->material_via.'</td><td colspan=7></td></tr>';

  $tktastro .= '<tr><td colspan=13 align=center class="titleblock" style="background:#036;color:#fff;">INFRAESTRUCTURA</td></tr>';
  $tktastro .= '<tr><td colspan=3 class="titlesection">Agua Potable</td><td colspan=3 class="titlesection">Alcantarillado</td><td colspan=3 class="titlesection">Luz Eléctrica</td><td colspan=4 class="titlesection">Telefonia</td></tr>';
  $dispone = (($data->water_service)? "SI TIENE":"No tiene");
  $tktastro .= '<tr><td colspan=3>'.$dispone.'</td><td colspan=3>'.$data->alcantarillado.'</td>';
  $dispone = (($data->luz_electrica)? "SI TIENE":"NO TIENE");
  $dispone1 = (($data->luz_electrica)? "SI TIENE":"NO TIENE");
  $tktastro .= '<td colspan=3>'.$dispone.'</td><td colspan=4>'.$dispone1.'</td></tr>';

  $tktastro .= '<tr><td colspan=13 align=center class="titleblock" style="background:#036;color:#fff;">PREDIO EN REGIMEN DE PROPIEDAD HORIZONTAL</td></tr>';
  $tktastro .= '<tr><td colspan=3 class="titlesection">Área Parcial de terreno</td><td colspan=3 class="titlesection">Alicuota Terreno</td><td colspan=3 class="titlesection">Área Parcial de construcción</td><td colspan=4 class="titlesection">Alicuota de Construcción</td></tr>';
  $tktastro .= '<tr><td colspan=3>'.$data->water_service.'</td><td colspan=3>'.$data->lotaliquot .'</td>';
  $tktastro .= '<td colspan=3>'.$data->luz_electrica.'</td><td colspan=4>'.$data->buildingaliquot.'</td></tr>';

  $tktastro .= '<tr><td align=center colspan=13 class="titleblock" style="background:#036;color:#fff;">AVALUO PROPIEDAD</td></tr>';
  $tktastro .= '<tr><td colspan=3 class="titlesection">Valor m&sup2 Homogeneo</td><td colspan=3 class="titlesection">Avalúo del terreno</td><td colspan=3 class="titlesection">Avalúo de construcción</td><td colspan=4 class="titlesection">Avalúo total del predio</td></tr>';
  $tktastro .= '<tr><td colspan=3>'.number_format($data->valuebysquaremeter, 2, '.', ',').'</td>';
  $tktastro .= '<td colspan=3>$ '. number_format($data->avaluo_terreno, 2, '.', ',').'</td>';  
  $tktastro .= '<td colspan=3>$ '. number_format($data->avaluo_construccion,2, '.', ',') .'</td><td colspan=4>$ '.number_format($data->avaluo_comercial,2, '.', ',').'</td></tr>';

  $tktastro .= '<tr><td colspan=13 class="titleblock">OBSERVACIONES</td></tr>';
  $tktastro .= '<tr><td colspan=13 >'.$data->observations.'</td></tr>';

  $tktastro .= '</table>';
  //$tktastro .= '<watermarkimage src="sites/all/modules/custom/payclub/logo.png" alpha="0.4" size="200,250" />';
  $tktastro .= '<div><strong>VÁLIDO PARA EL BIENIO 2022-2023</strong></div></br>';
    
  if(!$pdf){
    $tktastro .= '<a class="goback" href="javascript:history.go(-1)">[Regresar]</a><div class="nuevacon"><a class="nueva" href="'.$base_url.'/ktastro/consulta">Nueva Consulta</a></div>';
  }
  return $tktastro;
}
