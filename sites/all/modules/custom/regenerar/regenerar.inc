<?php

	function regenerar_form($form, &$form_status){
		$form['regenerar'] = array(
			'#title' => t('Datos del abonado'),
			'#type' => 'fieldset',
			'#description' => t('Consulta con su numero de cédula o RUC')
		);
		$form['regenerar']['cedula'] = array(
			'#title' => t('Número de cédula'),
			'#type' => 'textfield',
			'#required' => true,
			'#maxlenght' => 10,
			'#size' => 15,
			'#description' => t('Your ID have to 10 characters'),
		);	
		$form['regenerar']['captcha'] = array(
			'#type' =>  'captcha',
			// '#captcha_type' =>  'recaptcha/reCAPTCHA',  // prod
			'#captcha_type' =>  'captcha/Math', // test	
		);
		//$form['#action'] = $base_url . '/consulta/res';  
		//$form['#action'] = 'https://www.loja.gob.ec/consulta/resultado';
		//$form['#attached']['js'] = array(drupal_get_path('module','impuestos').'/js/impuestos.js',); // desactiva javascript
		$form['regenerar']['save'] = array(
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
    function regenerar_form_validate(&$form, &$form_state){
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
    function regenerar_form_submit(&$form, &$form_state){
      // $_SESSION['ced'] = $form_state['values']['cedula'];
      // unset($_SESSION['firstName']);
      // unset($_SESSION['dataws']);
      // $_SESSION['post'] = $_POST;
      $query = db_select('regenera','rgn')
      			->fields('rgn')
      			->condition('identificacion', $form_state['values']['cedula'], '=')
      			->execute()
      			->fetchAll();  
      // dsm($query);
      if (sizeof($query) > 0){
         $_SESSION['regenerards'] = $query; // Get data from webservice
         // 1100014370
         $form_state['redirect'] = 'regenerar/resultado';
      }else{
         drupal_set_message('No dispone de valores a pagar');
      }
      
      //if(module_exists('impuestos')){
        //$form_state['redirect'] = 'consulta/res';
      //}  
    }

/**
 * Show result from query
 */
function resultado_page(){
	global $base_url;
	if(!isset($_SESSION['regenerards'])){
		return drupal_goto($base_url . '/regenerar/consulta');
	}
	
	$html = '';
	$datos = '<div><strong>Cedula:</strong> '. $_SESSION['regenerards'][0]->identificacion .'</div>';
	$datos .= '<div><strong>Contribuyente: </strong>'. $_SESSION['regenerards'][0]->contribuyente .'</div>';

	foreach($_SESSION['regenerards'] as $values){
 		// dsm($values);
		$showTable = '<div><strong>Avaluo Comercial:</strong> $ '. number_format($values->avaluo_comercial, 2,'.',',') .'</div>';
		$showTable .= '<div><strong>Clave Catastral:</strong> '. $values->clave_catastral .'</div>';
		$showTable .= '<div><strong>Cuotas:</strong> '. $values->cuotas .'</div>';
		$showTable .= '<table border=1>';
		$showTable .= '<thead><tr>';
		$showTable .= '<th>Pavimento</th>';
		$showTable .= '<th>Agua</th>';
		$showTable .= '<th>Alc. Sanitario</th>';
		$showTable .= '<th>Alc. Pluvial</th>';
		$showTable .= '<th>Bordillo</th>';
		if ($values->aceras_estructura != '0.00'){ $showTable .= '<th>Aceras Estructura</th>'; }
		if ($values->aceras_adoquin != '0.00'){ $showTable .= '<th>Aceras Adoquin</th>'; }
		if ($values->adoquin_biselado != '0.00'){ $showTable .= '<th>Adoquin Biselado</th>'; }
		if ($values->aceras_baldosa != '0.00'){ $showTable .= '<th>Aceras Baldosa</th>'; }
		if ($values->aceras_gress != '0.00'){ $showTable .= '<th>Aceras Gress</th>'; }
		if ($values->aceras_porcelanato != '0.00'){ $showTable .= '<th>Aceras Porcelanato</th>'; }
		$showTable .= '<th class="total">Total</th>';
		$showTable .= '<th>Valor Cuota</th>';
		$showTable .= '</tr><thead>';
		$showTable .= '<tbody><tr>';
		//-------------------------------------------------------------------------
		$showTable .= '<td class="total">'. $values->pavimento .'</td>';
		$showTable .= '<td class="total">'. $values->agua .'</td>';
		$showTable .= '<td class="total">'. $values->alc_Sanitario .'</td>';
		$showTable .= '<td class="total">'. $values->alc_pluvial .'</td>';
		$showTable .= '<td class="total">'. $values->bordillo .'</td>';
		if ($values->aceras_estructura != '0.00'){ $showTable .= '<td class="total">'. $values->aceras_estructura .'</td>'; }
		if ($values->aceras_adoquin != '0.00'){ $showTable .= '<td class="total">'. $values->aceras_adoquin .'</td>'; }
		if ($values->adoquin_biselado != '0.00'){ $showTable .= '<td class="total">'. $values->adoquin_biselado .'</td>'; }
		if ($values->aceras_baldosa != '0.00'){ $showTable .= '<td class="total">'. $values->aceras_baldosa .'</td>'; }
		if ($values->aceras_gress != '0.00'){ $showTable .= '<td class="total">'. $values->aceras_gress.'</td>'; }
		if ($values->aceras_porcelanato != '0.00'){ $showTable .= '<td class="total">'. $values->aceras_porcelanato .'</td>'; }
		$showTable .= '<td class="total">'. $values->total .'</td>';
		$showTable .= '<td class="total">'. round($values->total/$values->cuotas, 2) .'</td>';
		$showTable .= '</tr></tbody>';
		$showTable .= '</table>';	
		$html .= $showTable;
		$html .= '<br/><br/>';
	}
	$html = $datos . $html;
	$html .= '<div class="nuevacon"><a class="nueva" href="'. $base_url .'/regenerar/consulta">Nueva Consulta</a></div>';
	$html .= '<div class="nuevacon"><a class="nueva" href="'. $base_url .'/formulario/reclamos-regeneracion-urbana">Presentar reclamos por valores</a></div>';

	
	return $html;

}
