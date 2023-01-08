<?php
/**
* Building form
*/
function consultacer_form($form, &$form_state){    
  $form['consulta'] = array(
      '#title' => t('Datos del Contribuyente'),
      '#type' => 'fieldset',
      '#description' => t('Asegurese de ingresar con precisión sus datos')
  );
  $form['consulta']['cedula'] = array(
      '#title' => t('Cédula del Contribuyente'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 15,
      '#description' => t('Your ID have to 10 characters'),
    );
  $form['consulta']['ruc'] = array(
        '#title' => t('RUC'),
        '#type' => 'checkbox',
        '#description' => t('Marque si dispone de RUC'),
    );
  $form['consulta']['casada'] = array(
        '#title' => t('Casado (a)'),
        '#type' => 'checkbox',
        '#description' => t('Marque si Ud es casado (a)'),              
    );
  $form['consulta']['cedulaconyuge'] = array(
      '#title' => t('Número de cédula del Conyuge'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 15,
      '#description' => t('Your ID have to 10 characters'),
      '#states' => array(
            'visible' => array(
                'input[name="casada"]' => array('checked' => TRUE),
            ),
        ),
      
    );
  $form['consulta']['ruc-conyuge'] = array(
        '#title' => t('RUC Conyuge'),
        '#type' => 'checkbox',
        '#description' => t('Marque si dispone de RUC'),
        '#states' => array(
            'visible' => array(
                'input[name="casada"]' => array('checked' => TRUE),
            ),
        ),
    );

  $form['consulta']['captcha'] = array(
    '#type' =>  'captcha',
    //'#captcha_type' =>  'recaptcha/reCAPTCHA',
    '#captcha_type' =>  'captcha/Math',
    //'#captcha_type' =>  'image_captcha/Image',    
  );
  //$form['#action'] = 'http://loja71.local.drw/certificados/res';
  $form['#action'] = 'https://www.loja.gob.ec/certificados/res';
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
* Display FORM and convert to PDF
*/
function testpage(){
    return "<h2>Página de Test</h2> Permite evaluar los certificados y el funcionamiento del módulo";
}
/**
* Mensaje para patente Municipal
**/
function msg_patente(){
    $mesg = "<h2>Patente Municipal</h2>";
    $mesg .= "Aviso importante: Le recordamos que usted está obligado a tener patente municipal. ¿Que desea hacer?";
    $mesg .= "<ul>";
    $mesg .= '<li><a class="btn btn-default1" role="button" data-toggle="collapse" href="#collapseInicial" aria-expanded="false" aria-controls="collapseExample" title="Ayuda: Cuando se inicia con la actividad económica.">
  Patente Municipal
</a>';
        $mesg .= '<div class="collapse" id="collapseInicial">
  <div class="well"><ul>';
//            $mesg .= "<li>Ayuda: Cuando se inicia con la actividad económica.</li>";
            $mesg .= "<li>Requisitos:";
                $mesg .= "<ul>";
                    $mesg .= "<li>Copia del RUC</li>";                    
                $mesg .= "</ul>";
            $mesg .= "</li>";
        $mesg .= "</ul></div></div>";
    $mesg .="</li>";
    $mesg .= '<li><a class="btn btn-primary1" role="button" data-toggle="collapse" href="#collapseRenova" aria-expanded="false" aria-controls="collapseExample" title="Ayuda: Se debe realizar cada año">
  Renovación de Patente
</a>';
        $mesg .= '<div class="collapse" id="collapseRenova">
  <div class="well"><ul>';
//            $mesg .= "<li>Ayuda: Se debe realizar cada año</li>";
            $mesg .= "<li>Requisitos:";
                $mesg .= "<ul>";
                    $mesg .= "<li>Copia del RUC</li>";            
                    $mesg .= "<li>Declaración del Impuesto a la Renta, IVA o RISE según sea el caso (año anterior).</li>";            
                    $mesg .= "<li>Copia del pago de bomberos</li>";            
                $mesg .= "</ul>";
            $mesg .= "</li>";
        $mesg .= "</ul></div></div>";
    $mesg .="</li>";
    $mesg .= '<li><a class="btn btn-primary1" role="button" data-toggle="collapse" href="#collapseLiquida" aria-expanded="false" aria-controls="collapseExample">
  Liquidación de patente
</a>';
        $mesg .= '<div class="collapse" id="collapseLiquida">
  <div class="well"><ul>';
        $mesg .= "<li>Ayuda: Cuando se termina con la actividad económica.";
        $mesg .= "</li>";
        $mesg .= "<li>Requisitos:";
            $mesg .= "<ul>";
            $mesg .= "<li>Copia del RUC</li>";            
            $mesg .= "<li>Última declaración del Impuesto a la Renta, IVA o RISE según sea el caso.</li>";
            $mesg .= "<li>Certificado de cierre o suspensión del RUC.</li>";            
            $mesg .= "</ul>";
        $mesg .= "</li>";
        $mesg .= "</ul></div></div>";
    $mesg .= "</li>";
    $mesg .= '<li><a class="btn btn-primary1" role="button" data-toggle="collapse" href="#collapseArtesano" aria-expanded="false" aria-controls="collapseExample" title="Eres artesano">
  ¿Eres Artesano?
</a>';
        $mesg .= '<div class="collapse" id="collapseArtesano">
  <div class="well"><ul>';
        $mesg .= "<li>Requisitos:";
            $mesg .= "<ul>";
            $mesg .= "<li>Certificado calificado por la Junta Nacional de Defensa del Artesano.</li>";
            $mesg .= "</ul>";
        $mesg .= "</li>";
        $mesg .= "</ul></div></div>";
    $mesg .= "</li>";
    $mesg .= "</ul>";
    
    $mesg .= "Usted debe acercarse a cualquiera de nuestras ventanillas en Rentas del Municipio de Loja que será un gusto atenderte.<br><br>";

    return $mesg;

}
/**
* Function for result with out parameters
*/
function res(){
    //dsm($_POST);
    if(!$_POST['cedula']){
        return "<h2>Acceso no autorizado</h2>";
    }
    $result = _impuesto($_POST['cedula']);
    $suma = 0;  // save sum values
  $par = 0;   // Control class table "even" and "odd" for TR element
  $adeuda = false; // If the customer has debt

  
  $sc = '';
  if(!empty($result)){
    $col = ($_POST['casada'] !=1) ? "col-md-12" : "col-md-6";
    $sc = "<div class='". $col ."'><h2>DATOS DEL CONTRIBUYENTE</h2>";
    $sc .= "<strong>C&eacute;dula:</strong> " . $result->return->taxpayer->identificationNumber."</br>";
    $sc .= "<strong>Nombre:</strong> " . $result->return->taxpayer->firstName."</br>";
    $sc .= "<table border=1><tbody>";
    $sc .="<tr><th>Cod Servicio</th><th>Rubro</th><th>Fecha Emisión</th><th>Fecha Expiración</th><th>Total</th><tr>";
    $sc .= "</thead><tbody>";
    
    watchdog('certificados','Consulta realizada para: ced',array('ced'=> $_POST['cedula']),WATCHDOG_DEBUG);
    
    if(isset($result->return->bonds)){
      $adeuda = TRUE;
      // Get size of array
      $lengthB = sizeof($result->return->bonds);

      // if array have just one element      
      if($lengthB == 1){
        $suma = $suma + (float)$result->return->bonds->total;        
        $sc .= '<tr class="odd"><td>'.$result->return->bonds->serviceCode.'</td>'
        . "<td>". $result->return->bonds->account ."</td>"
        . "<td>". substr($result->return->bonds->serviceDate, 0, 10)."</td>"
        . "<td>". substr($result->return->bonds->expirationDate, 0, 10) ."</td>"
        . '<td class="valor">$'. $result->return->bonds->total ."</td></tr>";

      }
      // Multiple values
      else{
        for($i=0; $i<$lengthB; $i++){
          // Set a clase for tr element with even or odd
          $tr = ($par % 2 ? '<tr class="even">' : '<tr class="odd">');
          $suma = $suma + (float)$result->return->bonds[$i]->total; 
          $sc .= $tr."<td>".substr($result->return->bonds[$i]->serviceCode,0,15)."</td>"
          . "<td>". $result->return->bonds[$i]->account ."</td>"     
          . "<td>". substr($result->return->bonds[$i]->serviceDate, 0, 10)."</td>"
          . "<td>". substr($result->return->bonds[$i]->expirationDate, 0, 10) ."</td>"
          . "<td>$". $result->return->bonds[$i]->total ."</td></tr>";
        }        
      }// End else
      $adeuda = TRUE;      
      
    }else{    
      $sc .= "<h3>No adeuda valores</h3>";

    }
    $sc .= '<tr class="totales"><td></td><td></td><td></td><td><strong>Total</strong></td><td class="valor"><strong>$'. (float)$suma ."</strong></td></tr>";
    
    $sc .= "</tbody></table>";
    $sc .= '<a href="/certificados/consulta">Nueva consulta</a>';
    if($adeuda){ $sc .= "<div>* Debe cancelar las obligaciones Pendientes</div>";}
    if($_POST['ruc'] == 1) $sc .= msg_patente();
    $sc .= "</div>";

  }else{
   $sc .= "<h2>Verifique su número de cédula, NO EXISTE en el sistema</h2>";
   $sc .= "<div>Acerquese al departamento de inform&aacute;tica para realizar la actualizaci&oacute;n</div>";
   $sc .= '<a href="/certificados/consulta">Nueva consulta</a>';
   $sc .= "</div>";
  }
  /****************************************** CONYUGE **********************************************/

  if($_POST['casada'] == 1){ 
    
    $result = _impuesto($_POST['cedulaconyuge']);
    $suma = 0;  // save sum values
  $par = 0;   // Control class table "even" and "odd" for TR element
  $adeuda = false; // If the customer has debt  
  
  
  if(!empty($result)){
    $sc .= "<div class='col-md-6'> <h2> DATOS DEL CONYUGE </h2>";
    $sc .= "<strong>C&eacute;dula:</strong> " . $result->return->taxpayer->identificationNumber."</br>";
    $sc .= "<strong>Nombre:</strong> " . $result->return->taxpayer->firstName."</br>";
    $sc .= "<table border=1><tbody>";
    $sc .="<tr><th>Cod Servicio</th><th>Rubro</th><th>Fecha Emisión</th><th>Fecha Expiración</th><th>Total</th><tr>";
    $sc .= "</thead><tbody>";
    
    watchdog('certificados','Consulta realizada para: ced',array('ced'=> $ced),WATCHDOG_DEBUG);
    if(isset($result->return->bonds)){
      $adeuda = TRUE;
      // Get size of array
      $lengthB = sizeof($result->return->bonds);

      // if array have just one element      
      if($lengthB == 1){
        $suma = $suma + (float)$result->return->bonds->total;        
        $sc .= '<tr class="odd"><td>'.$result->return->bonds->serviceCode.'</td>'
        . "<td>". $result->return->bonds->account ."</td>"
        . "<td>". substr($result->return->bonds->serviceDate, 0, 10)."</td>"
        . "<td>". substr($result->return->bonds->expirationDate, 0, 10) ."</td>"
        . '<td class="valor">$'. $result->return->bonds->total ."</td></tr>";

      }
      // Multiple values
      else{
        for($i=0; $i<$lengthB; $i++){
          // Set a clase for tr element with even or odd
          $tr = ($par % 2 ? '<tr class="even">' : '<tr class="odd">');
          $suma = $suma + (float)$result->return->bonds[$i]->total; 
          $sc .= $tr."<td>".substr($result->return->bonds[$i]->serviceCode,0,15)."</td>"
          . "<td>". $result->return->bonds[$i]->account ."</td>"     
          . "<td>". substr($result->return->bonds[$i]->serviceDate, 0, 10)."</td>"
          . "<td>". substr($result->return->bonds[$i]->expirationDate, 0, 10) ."</td>"
          . "<td>$". $result->return->bonds[$i]->total ."</td></tr>";
        }        
      }// End else
      $adeuda = TRUE;      
      
    }else{    
      $sc .= "<h3>No adeuda valores</h3>";

    }
    $sc .= '<tr class="totales"><td></td><td></td><td></td><td><strong>Total</strong></td><td class="valor"><strong>$'. (float)$suma ."</strong></td></tr>";
    
    $sc .= "</tbody></table>";
    $sc .= '</div>';
  }else{
   $sc .= "<h2>Verifique su número de cédula, NO EXISTE en el sistema</h2>";
   $sc .= "<div>Acerquese al departamento de inform&aacute;tica para realizar la actualizaci&oacute;n</div>";
   $sc .= '<a href="/certificados/consulta">Nueva consulta</a>';
   $sc .= "</div>";
  }
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
function _impuesto($cedula){    
  $result = array();
  // Call selected web service with name at next function
  $serv = wsclient_service_load('impuesto');  

  try{    
    $serviceRequest = array(
        'identificationNumber' => (String)$cedula,
        'username' => 'munpayclub',
        'password' => 'bfc2b6f7-9eea-4368-9cb0-cde8e2da37f7',
        'tramitId' => ''
    );
    $findStatement = array(
        'arg0' => $serviceRequest
    );
    // Call operation findStatement with parameters    
    $result = $serv->findStatement($findStatement);    
    // dsm($result);
    
  }catch(WSClientException $f){
    //If the connection is failed the return will be FALSE
    //echo $f;    
  }  
  return $result;
}

function form_pdf(){
  $html = '<h1 style="text-align:center">Generando Test1</h1>
  		  <table style="border=1px solid #036;" class="table"><tr><td>Hola</td></tr></table>mira';
  $html = '
  	<html><head>
<style>
.style-0 {
    width: 555pt; 
    empty-cells: show
}

.style-1 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 10.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-10 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 11.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-11 {
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-12 {
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: 1.399pt solid black
}

.style-13 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: "BankGothic Lt BT"; 
    font-size: 12.0pt; 
    font-weight: bold; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-14 {
    background-color: white; 
    border-top: none; 
    border-left: 1.399pt solid black; 
    border-bottom: 1.399pt solid black; 
    border-right: none
}

.style-15 {
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: 1.399pt solid black; 
    border-right: none
}

.style-16 {
    color: black; 
    font-family: serif; 
    font-size: 10.0pt; 
    font-weight: bold; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: 1.399pt solid black; 
    border-right: none
}

.style-17 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 10.0pt; 
    font-weight: bold; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-18 {
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: 1.399pt solid black; 
    border-right: 1.399pt solid black
}

.style-19 {
    color: black; 
    font-family: "BankGothic Lt BT"; 
    font-size: 12.0pt; 
    font-weight: bold; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: #ff6666; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-2 {
    width: 60pt; 
    height: 62pt
}

.style-20 {
    background-color: #ff6666; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-21 {
    background-color: #ff9966; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-22 {
    color: black; 
    font-family: "BankGothic Lt BT"; 
    font-size: 10.0pt; 
    font-weight: bold; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: #ff9966; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-23 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: "BankGothic Lt BT"; 
    font-size: 10.0pt; 
    font-weight: bold; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-24 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: #cccccc; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-25 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-26 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    border-top: 0.5pt solid black; 
    border-left: 0.5pt solid black; 
    border-bottom: 0.5pt solid black; 
    border-right: 0.5pt solid black
}

.style-27 {
    border-top: 0.5pt solid black; 
    border-left: 0.5pt solid black; 
    border-bottom: 0.5pt solid black; 
    border-right: none
}

.style-28 {
    border-top: 0.5pt solid black; 
    border-left: none; 
    border-bottom: 0.5pt solid black; 
    border-right: none
}

.style-29 {
    border-top: 0.5pt solid black; 
    border-left: none; 
    border-bottom: 0.5pt solid black; 
    border-right: 0.5pt solid black
}

.style-3 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 11.0pt; 
    font-weight: bold; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-30 {
    border-top: 0.5pt solid black; 
    border-left: 0.5pt solid black; 
    border-bottom: none; 
    border-right: none
}

.style-31 {
    border-top: 0.5pt solid black; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-32 {
    border-top: 0.5pt solid black; 
    border-left: none; 
    border-bottom: none; 
    border-right: 0.5pt solid black
}

.style-33 {
    border-top: none; 
    border-left: 0.5pt solid black; 
    border-bottom: 0.5pt solid black; 
    border-right: none
}

.style-34 {
    color: black; 
    font-family: serif; 
    font-size: 10.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    border-top: none; 
    border-left: none; 
    border-bottom: 0.5pt solid black; 
    border-right: none
}

.style-35 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 10.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-36 {
    border-top: none; 
    border-left: none; 
    border-bottom: 0.5pt solid black; 
    border-right: none
}

.style-37 {
    border-top: none; 
    border-left: none; 
    border-bottom: 0.5pt solid black; 
    border-right: 0.5pt solid black
}

.style-38 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: #cccccc; 
    border-top: 0.5pt solid black; 
    border-left: 0.5pt solid black; 
    border-bottom: 0.5pt solid black; 
    border-right: 0.5pt solid black
}

.style-39 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: #dcdcdc; 
    border-top: 0.5pt solid black; 
    border-left: 0.5pt solid black; 
    border-bottom: 0.5pt solid black; 
    border-right: 0.5pt solid black
}

.style-4 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 8.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-40 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-41 {
    border-top: none; 
    border-left: 0.5pt solid black; 
    border-bottom: none; 
    border-right: none
}

.style-42 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-43 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: 0.5pt solid black
}

.style-44 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    border-top: 0.3pt solid black; 
    border-left: 0.3pt solid black; 
    border-bottom: 0.3pt solid black; 
    border-right: 0.3pt solid black
}

.style-45 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    border-top: 0.4pt solid black; 
    border-left: 0.4pt solid black; 
    border-bottom: 0.4pt solid black; 
    border-right: 0.4pt solid black
}

.style-46 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: #cccccc; 
    border-top: 0.5pt solid black; 
    border-left: 0.5pt solid black; 
    border-bottom: 0.5pt solid black; 
    border-right: 0.5pt solid black
}

.style-47 {
    border-top: 0.4pt solid black; 
    border-left: 0.4pt solid black; 
    border-bottom: 0.4pt solid black; 
    border-right: none
}

.style-48 {
    border-top: 0.4pt solid black; 
    border-left: none; 
    border-bottom: 0.4pt solid black; 
    border-right: none
}

.style-49 {
    border-top: 0.4pt solid black; 
    border-left: none; 
    border-bottom: 0.4pt solid black; 
    border-right: 0.4pt solid black
}

.style-5 {
    background-color: white; 
    border-top: 1.399pt solid black; 
    border-left: 1.399pt solid black; 
    border-bottom: none; 
    border-right: none
}

.style-50 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-51 {
    background-color: white; 
    border-top: 0.699pt solid black; 
    border-left: 0.699pt solid black; 
    border-bottom: none; 
    border-right: none
}

.style-52 {
    background-color: white; 
    border-top: 0.699pt solid black; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-53 {
    background-color: white; 
    border-top: 0.699pt solid black; 
    border-left: none; 
    border-bottom: none; 
    border-right: 0.699pt solid black
}

.style-54 {
    background-color: white; 
    border-top: none; 
    border-left: 0.699pt solid black; 
    border-bottom: none; 
    border-right: none
}

.style-55 {
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: 0.699pt solid black
}

.style-56 {
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-57 {
    border-top: none; 
    border-left: none; 
    border-bottom: 0.6pt solid black; 
    border-right: none
}

.style-58 {
    background-color: #dcdcdc; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-59 {
    width: 71.885pt; 
    height: 34pt
}

.style-6 {
    background-color: white; 
    border-top: 1.399pt solid black; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-60 {
    color: black; 
    font-family: serif; 
    font-size: 7.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: #dcdcdc; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}

.style-61 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 7.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-62 {
    background-color: white; 
    border-top: none; 
    border-left: 0.699pt solid black; 
    border-bottom: 0.699pt solid black; 
    border-right: none
}

.style-63 {
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: 0.699pt solid black; 
    border-right: none
}

.style-64 {
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: 0.699pt solid black; 
    border-right: 0.699pt solid black
}

.style-65 {
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none; 
    color: black; 
    font-family: serif; 
    font-size: 9.0pt; 
    font-weight: bold; 
    font-style: italic; 
    text-decoration: none; 
    text-align: left; 
    word-spacing: 0pt; 
    letter-spacing: 0pt
}

.style-7 {
    background-color: white; 
    border-top: 1.399pt solid black; 
    border-left: none; 
    border-bottom: none; 
    border-right: 1.399pt solid black
}

.style-8 {
    background-color: white; 
    border-top: none; 
    border-left: 1.399pt solid black; 
    border-bottom: none; 
    border-right: none
}

.style-9 {
    color: black; 
    font-family: serif; 
    font-size: 11.0pt; 
    font-weight: normal; 
    font-style: normal; 
    text-decoration: none; 
    text-align: center; 
    word-spacing: 0pt; 
    letter-spacing: 0pt; 
    background-color: white; 
    border-top: none; 
    border-left: none; 
    border-bottom: none; 
    border-right: none
}



</style>
  	<head>
  	<body>
<table cellspacing="0" cellpadding="0" class="style-0">
      <col style="width: 4pt" /><col style="width: 0pt" /><col style="width: 0pt" />
      <col style="width: 5pt" />      <col style="width: 0pt" />
      <col style="width: 4pt" />      <col style="width: 55pt" />
      <col style="width: 5pt" />      <col style="width: 5pt" />
      <col style="width: 2pt" />      <col style="width: 0pt" />
      <col style="width: 1pt" />      <col style="width: 0pt" />
      <col style="width: 0pt" />      <col style="width: 0pt" />
      <col style="width: 0pt" />      <col style="width: 14pt" />
      <col style="width: 26pt" />      <col style="width: 15pt" />
      <col style="width: 1pt" />      <col style="width: 28pt" />
      <col style="width: 4pt" />      <col style="width: 0pt" />
      <col style="width: 1pt" />      <col style="width: 0pt" />
      <col style="width: 9pt" />      <col style="width: 0pt" />
      <col style="width: 5pt" />     <col style="width: 1pt" />
      <col style="width: 3pt" />      <col style="width: 1pt" />
      <col style="width: 13pt" /><col style="width: 0pt" />      <col style="width: 5pt" />
      <col style="width: 1pt" />      <col style="width: 3pt" />
      <col style="width: 3pt" />      <col style="width: 1pt" />
      <col style="width: 1pt" />      <col style="width: 1pt" />
      <col style="width: 8pt" />      <col style="width: 1pt" />
      <col style="width: 2pt" />      <col style="width: 3pt" />
      <col style="width: 1pt" />      <col style="width: 18pt" />
      <col style="width: 2pt" />      <col style="width: 0pt" />
      <col style="width: 0pt" />      <col style="width: 2pt" />
      <col style="width: 0pt" />      <col style="width: 0pt" />
      <col style="width: 0pt" />      <col style="width: 0pt" />
      <col style="width: 8pt" />      <col style="width: 1pt" />
      <col style="width: 14pt" />      <col style="width: 11pt" />
      <col style="width: 0pt" />      <col style="width: 14pt" />
      <col style="width: 1pt" />      <col style="width: 8pt" />
      <col style="width: 3pt" />      <col style="width: 8pt" />
      <col style="width: 10pt" />      <col style="width: 0pt" />
      <col style="width: 7pt" />      <col style="width: 3pt" />
      <col style="width: 1pt" />      <col style="width: 1pt" />
      <col style="width: 6pt" />      <col style="width: 5pt" />
      <col style="width: 1pt" />      <col style="width: 11pt" />
      <col style="width: 5pt" />      <col style="width: 8pt" />
      <col style="width: 2pt" />      <col style="width: 1pt" />
      <col style="width: 1pt" />      <col style="width: 22pt" />
      <col style="width: 3pt" />      <col style="width: 1pt" />
      <col style="width: 1pt" />      <col style="width: 2pt" />
      <col style="width: 0pt" />      <col style="width: 2pt" />
      <col style="width: 12pt" />      <col style="width: 0pt" />
      <col style="width: 0pt" />      <col style="width: 1pt" />
      <col style="width: 1pt" />      <col style="width: 4pt" />
      <col style="width: 0pt" />      <col style="width: 13pt" />
      <col style="width: 9pt" />      <col style="width: 7pt" />
      <col style="width: 12pt" />      <col style="width: 0pt" />
      <col style="width: 2pt" />      <col style="width: 28pt" />
      <col style="width: 21pt" />      <col style="width: 0pt" />
      <col style="width: 0pt" />      <col style="width: 0pt" />
      <col style="width: 0pt" />      <col style="width: 4pt" />
      <tr style="height: 1pt">        <td />
        <td />        <td />         <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />      </tr>
      <tr style="height: 3pt">
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td rowspan="8" colspan="2" valign="top" class="style-1"><img src="/files/image/banners/escudo.jpg" class="style-2" /></td>
        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />      </tr>
      <tr style="height: 16pt">
        <td />        <td />        <td />        <td />
        <td />        <td />
        <td />        <td colspan="86" valign="top" class="style-3"><span class="style-3">GOBIERNO AUTONOMO DESCENTRALIZADO MUNICIPAL DE LOJA</span> </td>
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />      </tr>
      <tr style="height: 6pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />
        <td />        <td rowspan="3" colspan="73" valign="top" class="style-4"><span class="style-4">RUC: 1160000240001</span> </td>
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
      </tr>
      <tr style="height: 2pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td class="style-5" />      <td class="style-6" />
        <td class="style-6" />        <td class="style-6" />
        <td class="style-6" />        <td class="style-6" />
        <td class="style-6" />        <td class="style-6" />
        <td class="style-6" />        <td class="style-6" />
        <td class="style-6" />        <td class="style-6" />
        <td class="style-7" />        <td />
        <td />
      </tr>
      <tr style="height: 4pt">
        <td />        <td />         <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td class="style-8" />
        <td rowspan="2" colspan="9" valign="top" class="style-9"><span class="style-10">Solicitud N&deg;</span> </td>
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-12" />
        <td />        <td />
      </tr>
      <tr style="height: 13pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />
        <td rowspan="3" colspan="73" valign="top" class="style-13"><span class="style-13">DEPARTAMENTO DE REGULACION Y CONTROL URBANO</span> </td>
        <td />
        <td class="style-8" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-12" />
        <td />
        <td />
      </tr>
      <tr style="height: 16pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td class="style-14" />
        <td class="style-15" />
        <td colspan="8" valign="top" class="style-16"><span class="style-17">75749</span> </td>
        <td class="style-15" />
        <td class="style-15" />
        <td class="style-18" />
        <td />
        <td />
      </tr>
      <tr style="height: 2pt">
        <td />        <td />         <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />
      </tr>
      <tr style="height: 15pt">
        <td />        <td />
        <td />
        <td colspan="98" valign="top" class="style-19"><span class="style-13">CERTIFICADO DE REGULACION URBANA</span> </td>
        <td class="style-20" />
        <td class="style-20" />
        <td class="style-20" />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td class="style-21" />
        <td class="style-21" />        <td />
        <td />        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td colspan="99" valign="top" class="style-22"><span class="style-23">A. INFORMACION CATASTRAL DEL PREDIO</span> </td>
        <td class="style-21" />
        <td class="style-21" />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 2pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td colspan="11" valign="top" class="style-24"><span class="style-25">Clave Catastral</span> </td>
        <td colspan="91" valign="top" class="style-26"><span class="style-25">601505030661500</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />
      </tr>      <tr style="height: 13pt">
        <td/>
        <td />
        <td rowspan="3" colspan="11" valign="top" class="style-24"><span class="style-25">Propietario</span> </td>
        <td rowspan="3" colspan="59" valign="top" class="style-26"><span class="style-25">DANNY RENE ALVAREZ PARDO</span> </td>
        <td />
        <td colspan="9" valign="top" class="style-24"><span class="style-25">Cedula</span> </td>
        <td />
        <td rowspan="2" colspan="21" valign="top" class="style-26"><span class="style-25">1103360549</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />      </tr>
      <tr style="height: 0pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
      </tr>
      <tr style="height: 1pt">
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />        <td />        <td />
        <td />        <td />
       </tr>      <tr style="height: 13pt">
        <td />
        <td />
        <td colspan="11" valign="top" class="style-24"><span class="style-25">Parroquia</span> </td>
        <td colspan="24" valign="top" class="style-26"><span class="style-25">SAN SEBASTIAN</span> </td>
        <td />
        <td colspan="8" valign="top" class="style-24"><span class="style-25">Barrio</span> </td>
        <td colspan="26" valign="top" class="style-26"><span class="style-25">ELECTRICISTA</span> </td>
        <td />
        <td colspan="9" valign="top" class="style-24"><span class="style-25">Manzana</span> </td>
        <td />
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td colspan="4" valign="top" class="style-24"><span class="style-25">Lote</span> </td>
        <td colspan="6" valign="top" class="style-26"><span class="style-25">1</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 2pt">
        
        <td colspan=99/>
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td rowspan="2" colspan="10" valign="top" class="style-24"><span class="style-25">Calle Prin.</span> </td>
        <td colspan="42" valign="top" class="style-26"><span class="style-25">TEODORO WOLF</span> </td>
        <td />
        <td colspan="6" valign="top" class="style-24"><span class="style-25">Y / Entre</span> </td>
        <td colspan="42" valign="top" class="style-26"><span class="style-25">KEPLER</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 10pt">
        <td colspan=96 />

      </tr>
      <tr style="height: 1pt">
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td colspan="11" valign="top" class="style-24"><span class="style-25">Y</span> </td>
        <td colspan="25" valign="top" class="style-26"><span class="style-25">-</span> </td>
        <td colspan="20" valign="top" class="style-24"><span class="style-25">Ubicacion MZ</span> </td>
        <td />
        <td colspan="13" valign="top" class="style-26"><span class="style-25">X</span> </td>
        <td />
        <td colspan="10" valign="top" class="style-24"><span class="style-25">Esquina</span> </td>
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td colspan="7" valign="top" class="style-24"><span class="style-25">Intermedio</span> </td>
        <td />
        <td />
      </tr>
      <tr styl="height: 6pt">
        <td />       <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
        <td />        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td colspan="99" valign="top" class="style-22"><span class="style-23">B. INFORMACION URBANA DEL PREDIO</span> </td>
        <td class="style-21" />
        <td class="style-21" />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td rowspan="5" colspan="8" valign="top" class="style-24"><span class="style-25">Area Total (M)</span> </td>
        <td />
        <td rowspan="4" colspan="19" valign="top" class="style-26"><span class="style-25">214.00m2</span> </td>
        <td />
        <td rowspan="5" colspan="16" valign="top" class="style-24"><span class="style-25">Frente (M)</span> </td>
        <td rowspan="2" colspan="28" valign="top" class="style-26"><span class="style-25">11.00M</span> </td>
        <td rowspan="3" colspan="15" valign="top" class="style-24"><span class="style-25">Fondo (m)</span> </td>
        <td colspan="14" valign="top" class="style-26"><span class="style-25">19.00M</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td class="style-30" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-32" />
        <td />
        <td />
      </tr>
      <tr style="height: 16pt">
        <td />
        <td />
        <td />
        <td class="style-33" />
        <td colspan="97" valign="top" class="style-34"><span class="style-35">B.1. Vias</span> </td>
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-37" />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 14pt">
        <td />
        <td />
        <td />
        <td colspan="36" valign="top" class="style-38"><span class="style-25">Nombre de Calle</span> </td>
        <td />
        <td colspan="28" valign="top" class="style-38"><span class="style-25">Ancho (m)</span> </td>
        <td />
        <td colspan="35" valign="top" class="style-38"><span class="style-25">Referencia de L&iacute;nea de Fabrica</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td />
        <td colspan="36" valign="top" class="style-25"><span class="style-25">CALLE TEODORO WOLF</span> </td>
        <td />
        <td colspan="28" valign="top" class="style-25"><span class="style-25">9.00M</span> </td>
        <td />
        <td colspan="35" valign="top" class="style-25"><span class="style-25">A 1.50M DEL BORDILLO</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td />
        <td colspan="36" valign="top" class="style-25"><span class="style-25">CALLE KEPLER</span> </td>
        <td />
        <td colspan="28" valign="top" class="style-25"><span class="style-25">9.00M</span> </td>
        <td />
        <td colspan="35" valign="top" class="style-25"><span class="style-25">A 1.50M DEL BORDILLO</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td colspan="101" valign="top" class="style-39"><span class="style-40">RETIROS</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td colspan="5" valign="top" class="style-24"><span class="style-25">Frontal</span> </td>
        <td colspan="57" valign="top" class="style-26"><span class="style-25">3.00 M C /CALLE</span> </td>
        <td />
        <td colspan="10" valign="top" class="style-24"><span class="style-25">Posterior</span> </td>
        <td colspan="28" valign="top" class="style-26"><span class="style-25">4.00 M</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td colspan="5" valign="top" class="style-24"><span class="style-25">Lateral</span> </td>
        <td colspan="31" valign="top" class="style-26"><span class="style-25">XX</span> </td>
        <td colspan="16" valign="top" class="style-24"><span class="style-25">Otros</span> </td>
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td colspan="5" valign="top" class="style-24"><span class="style-25">Afectacion</span> </td>
        <td class="style-30" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-32" />
        <td rowspan="2" colspan="16" valign="top" class="style-24"><span class="style-25">Tipo</span> </td>
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td class="style-41" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-42" />
        <td class="style-43" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td class="style-33" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-37" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td class="style-30" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-32" />
        <td />
        <td />
      </tr>
      <tr style="height: 15pt">
        <td />
        <td />
        <td />
        <td class="style-33" />
        <td colspan="97" valign="top" class="style-34"><span class="style-35">B.2. Ocupaci&oacute;n del Suelo</span> </td>
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-37" />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td colspan="6" valign="top" class="style-24"><span class="style-25">Parroquia</span> </td>
        <td colspan="26" valign="top" class="style-44"><span class="style-25">SAN SEBASTIAN</span> </td>
        <td colspan="11" valign="top" class="style-24"><span class="style-25">Zona</span> </td>
        <td />
        <td colspan="18" valign="top" class="style-45"><span class="style-25">Z 3</span> </td>
        <td colspan="21" valign="top" class="style-24"><span class="style-25">Sector y Subsector</span> </td>
        <td />
        <td colspan="19" valign="top" class="style-45"><span class="style-25">S 2A</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td rowspan="3" colspan="6" valign="top" class="style-24"><span class="style-25">Uso Principal</span> </td>
        <td colspan="25" valign="top" class="style-44"><span class="style-25">Vivienda</span> </td>
        <td />
        <td rowspan="2" colspan="71" valign="top" class="style-46"><span class="style-40">Usos Complementarios</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 32pt">
        <td />
        <td rowspan="2" colspan="6" valign="top" class="style-24"><span class="style-25">Unidades de</span> <span class="style-25">vivienda</span> </td>
        <td colspan="25" valign="top" class="style-26"><span class="style-25">-</span> </td>
        <td />
        <td rowspan="4" colspan="71" valign="top" class="style-26"><span class="style-25">Producci&ograve;n de Bienes Artesanales compatibles con la vivienda</span><br /><span class="style-25">Financieros</span><br /><span class="style-25">Servicios Industriales</span><br /><span class="style-25">Turismo y Afines</span><br /><span class="style-25">Alimentacion</span><br /><span class="style-25">Servicios Personales y  Afines a la Vivienda</span><br /><span class="style-25">IntercambioEquipamientoComunal</span><br /></td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 31pt">
        <td />
        <td colspan="6" valign="top" class="style-24"><span class="style-25">Tipo</span> <span class="style-25">Implantacion</span> </td>
        <td colspan="25" valign="top" class="style-26"><span class="style-25">CONTINUA CON RETIRO</span> <span class="style-25">FRONTAL</span> </td>
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td colspan="6" valign="top" class="style-24"><span class="style-25">Cos %</span> </td>
        <td colspan="16" valign="top" class="style-44"><span class="style-25">70%</span> </td>
        <td />
        <td colspan="10" valign="top" class="style-24"><span class="style-25">Cus %</span> </td>
        <td />
        <td colspan="25" valign="top" class="style-45"><span class="style-25">210%</span> </td>
        <td />
        <td colspan="8" valign="top" class="style-24"><span class="style-25">N&deg; Pisos</span> </td>
        <td colspan="35" valign="top" class="style-26"><span class="style-25">3</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 14pt">
        <td />
        <td colspan="6" valign="top" class="style-24"><span class="style-25">Lote Min. (m2)</span> </td>
        <td colspan="16" valign="top" class="style-44"><span class="style-25">200 M2</span> </td>
        <td />
        <td colspan="24" valign="top" class="style-24"><span class="style-25">Lote Max. (m2)</span> </td>
        <td />
        <td rowspan="2" colspan="21" valign="top" class="style-45"><span class="style-25">340 M2</span> </td>
        <td colspan="21" valign="top" class="style-24"><span class="style-25">Lote Prom. (m2)</span> </td>
        <td colspan="13" valign="top" class="style-26"><span class="style-25">270 M2</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 14pt">
        <td />
        <td colspan="6" valign="top" class="style-24"><span class="style-25">Frente Min. (m)</span> </td>
        <td colspan="15" valign="top" class="style-44"><span class="style-25">10 M</span> </td>
        <td />
        <td />
        <td colspan="24" valign="top" class="style-24"><span class="style-25">Frente Max. (m)</span> </td>
        <td />
        <td colspan="21" valign="top" class="style-45"><span class="style-25">15 M</span> </td>
        <td colspan="21" valign="top" class="style-24"><span class="style-25">Frente P. H. (m)</span> </td>
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td class="style-30" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-32" />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 15pt">
        <td />
        <td class="style-33" />
        <td class="style-36" />
        <td class="style-36" />
        <td colspan="97" valign="top" class="style-34"><span class="style-35">B.3. Observaciones Especiales</span> </td>
        <td class="style-37" />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 2pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td rowspan="2" colspan="11" valign="top" class="style-24"><span class="style-25">Lote M&iacute;nimo (m2)</span> </td>
        <td />
        <td />
        <td />
        <td class="style-47" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-49" />
        <td />
        <td rowspan="2" colspan="26" valign="top" class="style-24"><span class="style-25">N&deg; Pisos</span> </td>
        <td />
        <td class="style-47" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-49" />
        <td rowspan="2" colspan="16" valign="top" class="style-24"><span class="style-25">Retiro Frontal</span> </td>
        <td />
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td rowspan="2" colspan="11" valign="top" class="style-24"><span class="style-25">Frente M&iacute;nimo (m)</span> </td>
        <td />
        <td />
        <td />
        <td class="style-47" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-49" />
        <td />
        <td rowspan="2" colspan="26" valign="top" class="style-24"><span class="style-25">Implantaci&oacute;n</span> </td>
        <td />
        <td class="style-47" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-48" />
        <td class="style-49" />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td class="style-30" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-32" />
        <td />
        <td />
      </tr>
      <tr style="height: 15pt">
        <td />
        <td />
        <td />
        <td class="style-33" />
        <td class="style-36" />
        <td colspan="96" valign="top" class="style-34"><span class="style-35">B.4. Zona Patrimonial</span> </td>
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-37" />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td rowspan="2" colspan="11" valign="top" class="style-24"><span class="style-25">Inventariado</span> </td>
        <td />
        <td />
        <td />
        <td />
        <td rowspan="2" valign="top" class="style-50"><span class="style-25">SI</span> </td>
        <td />
        <td class="style-36" />
        <td />
        <td />
        <td />
        <td />
        <td rowspan="2" colspan="3" valign="top" class="style-50"><span class="style-25">NO</span> </td>
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td rowspan="2" colspan="17" valign="top" class="style-24"><span class="style-25">Nivel de conservaci&oacute;n</span> </td>
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td rowspan="2" colspan="3" valign="top" class="style-50"><span class="style-25">A</span> </td>
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td rowspan="2" colspan="4" valign="top" class="style-50"><span class="style-25">B</span> </td>
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td />
        <td rowspan="2" colspan="3" valign="top" class="style-50"><span class="style-25">T</span> </td>
        <td class="style-36" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 2pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td class="style-30" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-31" />
        <td class="style-32" />
        <td />
        <td />
      </tr>
      <tr style="height: 15pt">
        <td />
        <td />
        <td />
        <td class="style-33" />
        <td class="style-36" />
        <td colspan="96" valign="top" class="style-34"><span class="style-35">B.5. Infraestructura B&aacute;sica</span> </td>
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-37" />
        <td />
        <td />
      </tr>
      <tr style="height: 2pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 13pt">
        <td />
        <td />
        <td />
        <td rowspan="2" colspan="11" valign="top" class="style-24"><span class="style-25">Agua Potable</span> </td>
        <td />
        <td />
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td />
        <td rowspan="2" colspan="15" valign="top" class="style-24"><span class="style-25">Alcantarillado</span> </td>
        <td class="style-27" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-28" />
        <td class="style-29" />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 3pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td />
        <td colspan="98" valign="top" class="style-22"><span class="style-23">C. UBICACION DEL PREDIO</span> </td>
        <td class="style-21" />
        <td class="style-21" />
        <td class="style-21" />
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td class="style-51" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-52" />
        <td class="style-53" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 14pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td colspan="62" valign="top" class="style-56"><span class="style-40">OBSERVACIONES</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 42pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td class="style-57" />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 21pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td class="style-36" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 2pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 14pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td colspan="62" valign="top" class="style-4"><span class="style-4">JEFE DE LINEA DE FABRICA</span> </td>
        <td />
        <td />
      </tr>
      <tr style="height: 1pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td class="style-58" />
        <td />
        <td rowspan="4" colspan="24" valign="top" class="style-1"><img src="/files/image/banners/barcode.png" class="style-59" /></td>
        <td />
        <td />
      </tr>
      <tr style="height: 10pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td class="style-58" />
        <td colspan="34" valign="top" class="style-60"><span class="style-61">1. Este documento tiene 6 mese de validez</span> </td>
        <td class="style-58" />
        <td class="style-58" />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 11pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td class="style-58" />
        <td colspan="34" valign="top" class="style-60"><span class="style-61">2. Cualquier alteraci&oacute;n o enmendadura lo anulara</span> </td>
        <td class="style-58" />
        <td class="style-58" />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 11pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td class="style-58" />
        <td colspan="34" valign="top" class="style-60"><span class="style-61">3. Este documento no autoriza ning&uacute;n trabajo</span> </td>
        <td class="style-58" />
        <td class="style-58" />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 0pt">
        <td />
        <td />
        <td />
        <td class="style-54" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-11" />
        <td class="style-55" />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
      <tr style="height: 12pt">
        <td />
        <td />
        <td />
        <td class="style-62" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-63" />
        <td class="style-64" />
        <td />
        <td colspan="20" valign="top" class="style-65"><span class="style-65">FECHA ENTREGA:</span> </td>
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
        <td />
      </tr>
    </table>

    </body>
    </html>
  ';

  pdf_using_mpdf_api($html);
  return $html;
}



