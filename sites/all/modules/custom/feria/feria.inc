<?php

function presenta_ganador(){ 

  if(isset($_SESSION['id'])){
    $mensaje = "<h2> Ud ha resultado ganador!!! " . $_SESSION['winner'] . "</h2>";
    $mensaje = $mensaje . "Por ser el visitante registrado número: <strong>" . $_SESSION['id'] . "</strong>";  
  }else{
    $mensaje = "<strong>Operación no válida</strong> debe estar registrado !!";
  }
  
	return $mensaje;
}
/**
* Form by conciliation and verification values between Municipality and VPOS (interdin)
*/
function registro_form($form, &$form_state){  
  $form['registro'] = array(
    '#title' => t('Puede ganar una canasta con varios productos'),
    '#description' => t('Participe con su número de cédula por una sola vez'),
    '#type' => 'fieldset',    
  );
  $form['registro']['ticket'] = array(
      '#title' => t('Número de cédula'),
      '#type' => 'textfield',
      '#required' => true,
      '#maxlenght' => 10,
      '#size' => 10,
      '#description' => t('El ganador debe presentar la cédula para reclamar el premio'),
      /*'#ajax' => array(
        'callback' => 'registro_form_callback',
        'wrapper' => 'yaingresado',
        'method' => 'replace',
        'effect' => 'slide',
        
      ),*/
      '#prefix' => '<div id="yaingresado">',
      '#suffix' => '</div>',
	);
  //$form['registro']['ticket']['#description'] = "Hola";

  /*$form['registro']['captcha'] = array(
    '#type' =>  'captcha',
    //'#captcha_type' =>  'recaptcha/reCAPTCHA',
    //'#captcha_type' =>  'captcha/Math',
    //'#captcha_type' =>  'image_captcha/Image',    
  );*/
  $form['registro']['enviar'] = array(
    '#type' => 'submit',
    /*'#ajax' => array(
        'callback' => 'registro_form_callback',
        'wrapper' => 'registro',
        'effect' => 'fade',
        'name'  => 'submit',
      ),*/
    '#value' => t('Registarse'),    
  );  

  return $form;

}
function registro_form_callback($form, &$form_state){
  //return "validando";
  //return $form['registro']['ticket'];
  dsm("ajax activo");
  if (form_get_errors()) {
    //return $form;
    return "hola";
  }

  # Create a new markup field and return it. It will replace the form output.
  $element = $form['registro'];
  $element['#type'] = 'markup';
  $element['#markup'] = "Thank you for submitting our form!";

  return $element;
}
/**
* Validate the form sent
*/
function registro_form_validate($form, &$form_state){
  // Verficiar que no haya sido registrado
  //dsm($_POST['ticket']);
  $cedula = $_POST['ticket'];

  $tickets = db_query('SELECT ticket 
                  FROM feria f                  
                  WHERE f.ticket =  :tic',
                  array('tic' => $cedula ))->fetchall();
  if(count($tickets) > 0){
    form_set_error('ticket', t('La cédula ya ha sido registrada'));
  }
  if(!validacedula($cedula)){
      form_set_error('cedula', t('No es un número de cédula valido'));
  }

}
/**
* Sent Data after validated them
*/
function registro_form_submit($form, &$form_state){
  $intervalo_win = array(1,5,10,100,150,200,300); // Winner Pattern

  $idTicket = $_POST['ticket'];  
  
  $ticket = array();  
  $ticket['fecnow'] = Date("Y-m-d H:i:s");  
  $ticket['vpos_txn_id'] = 0;
  $ticket['ticket'] = $_POST['ticket'];  
  $ticket['winner'] = '0';     
  drupal_write_record('feria',$ticket);
  drupal_set_message("Ud ha sido registrado");

  $tickets = db_query('SELECT id, ticket 
                  FROM feria f                  
                  ORDER by id desc limit 1'
                  )->fetchall();
  foreach ($tickets as $key) {
    //dsm($key->id);
  }
  if(in_array($key->id, $intervalo_win))
  {    
    $_SESSION['id'] = $key->id;
    $_SESSION['winner'] = $key->ticket;
    $form_state['redirect'] = 'feria/win';
  }
  else{
    dsm("Gracias por participar");
  //dsm($intervalo_win);
  }
   
}
/**
* Validation ID
* @return $cedula
* (Boolean) Return TRUE if is valid, else FALSE
**/
function validacedula($cedula){
  $total = 0;
  $coe = array(2,1,2,1,2,1,2,1,2);
  $numprov = 24;  // states number
  $terdig = 6;    // third number
  if(is_numeric($cedula) || strlen($cedula) == 10){
    $prov = (int)substr($cedula, 0, 1);
      if( $prov > 0 && $prov <= $numprov && substr($cedula, 2,1) < $terdig){
        $rec = (int) substr($cedula, 9,1);
        for($i=0; $i < sizeof($coe); $i++){
            $val = (int) $coe[$i] * (int) substr($cedula, $i, 1);
            $total = $val >= 10 ? $total + $val-9 : $total + $val;
        }
        $obt = $total >= 10 ? ($total % 10) != 0 ? 10 - ($total % 10) : ($total % 10) : $total;
        if($rec == $obt){
            return true;
        }
      }
      return false;
  }
  return false;
}

