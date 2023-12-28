<?php
	// 1100048451 varios medidores
	//

	$ced = '';	
	

	function consulta_cem_form($form, &$form_state){
	  global $base_url;

	  $enabledcem =  variable_get('cemquery', 0);
	  if($enabledcem == 1){ // Deactivated CEMs query
		return drupal_goto($base_url .'/cem/consultam');
	  }	  
	  $form['consulta'] = array(
	      '#title' => t('Datos del abonado'),
	      '#type' => 'fieldset',
          '#description' => t('Consulta a través de su cédula'),
          '#suffix' => t('')
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
	  //}
	  $form['#action'] = $base_url . '/cem/consulta/resultado';
	  //$form['#action'] = 'https://www.loja.gob.ec/consulta/resultado';
	  $form['#attached']['js'] = array(drupal_get_path('module','cem').'/js/cem.js',);
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
	function consulta_cem_form_validate(&$form, &$form_state){
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
	function consulta_cem_form_submit(&$form, &$form_state){
		// $_SESSION['ced'] = $form_state['values']['cedula'];
		// unset($_SESSION['firstName']);
		// unset($_SESSION['dataws']);
		// $_SESSION['post'] = $_POST;
		// $_SESSION['dataws'] = _getDataWebs($form_state['values']['cedula']); // Get data from webservice
		$form_state['redirect'] = 'cem/consulta/resultado';
		//if(module_exists('impuestos')){
		//$form_state['redirect'] = 'consulta/res';
		//}
	}
	/**
	 * Function for resultado from consulta
	 * This function display data in a table under the url resultado
	 *  @return
	 *     (String) With data
	 */
	function resultado_page(){  
		global $base_url;	
		//  $ced = variable_get('ced1'); // get variable from form
		if(empty($_POST['cedula'])){
			return drupal_goto($base_url . '/cem/consulta');
		}
		$ced = $_POST['cedula'];
		$txns = db_query("SELECT key_cat_old,
						key_cat_cur,
						ced,
						owners,
						appraisal,
						r_urb,
						ptar,
						total
					FROM cem 
					WHERE ced = :ced",
					array(':ced' => $ced))->fetchall();
		$len = sizeof($txns);
		$table = "<strong>C&eacute;dula:</strong> " . $txns[0]->ced ."</br>";
		$table .= "<strong>Nombre:</strong> " . $txns[0]->owners ."</br>";
		$table .= '<table border=1><thead>'.
		'<tr><th>Num</th>'.
		'<th>Clave catastral Nueva</th>'.	
		'<th>Clave catastral Anterior</th>'.
		'<th>Avalúo</th>'.
		'<th>Regeneracion Urbana (global)</th>'.
		'<th>PTAR</th>'.
		'<th>Total</th>'.	
		'<th>Valor cuota (1/32)<br/> (Valor estimado)</th>'.
		'</tr></thead><tbody>';
		$totales = 0;
		for($i=0; $i<$len; $i++){		
			$table .= '<tr>';
			$table .= '<td>'. ($i + 1) .'</td>';
			$table .= '<td>'. $txns[$i]->key_cat_old .'</td>';
			$table .= '<td>'. $txns[$i]-> key_cat_cur.'</td>';		
			$table .= '<td style="text-align:right">'. number_format($txns[$i]->appraisal, 2, '.', ',') .'</td>';
			$table .= '<td style="text-align:right">'. $txns[$i]->r_urb .'</td>';
			$table .= '<td style="text-align:right">'. $txns[$i]->ptar .'</td>';
			$table .= '<td style="text-align:right">'. $txns[$i]->total .'</td>';
			$table .= '<td style="text-align:right">'. number_format(($txns[$i]->total/32), 2, '.', ',') .'</td>';
			$totales += $txns[$i]->total;	
		}
		$totales = number_format($totales, 2, '.', ',');
		$table .= '<tr><td colspan=6></td><td class="total_cem">'. $totales .'</td></tr>';
		$table .= '</tbody></table>';

		$table .= '<strong>(PTAR):</strong> Planta de tratamiento de aguas residuales';
		$table .= '<div><br/></div>';
		$table .= '<div class="nuevacon"><a class="nueva" href="'.$base_url.'/cem/consulta">Nueva Consulta</a></div>';		  
		
		return $table;
	}
	/**
	* Admin pages with form settings
	*/
	function cem_admin_form($form, &$form_state){
		$form['queries_admin'] = array(
			'#title' => t('Debug Administrator'),
			'#type' => 'fieldset',
			'#description' => t('Consulta solo <strong>el rol administrador</strong>')
		);
		$form['queries_admin']['rol_admin'] = array(
			'#type' => 'checkbox',
			'#title' => t('Allow CEM queries only to administrator rol'),
			//'#required' => TRUE,
			'#default_value' => variable_get('rol_admin', 0),
		);
		$form['endyear'] = array(
			'#title' => t('Maintenance'),
			'#type' => 'fieldset',
			'#description' => t('Deshabilitar consulta por fin de año')
		);
		$form['endyear']['cemquery'] = array(
			'#type' => 'checkbox',
			'#title' => t('Disabled CEM Query'),
			//'#required' => TRUE,
			'#default_value' => variable_get('cemquery', 0),
		);
		$form['endyear']['message_cem'] = array(
			'#type' => 'textarea',
			'#title' => t('Mensaje mostrado al desactivar consultas CEM'),
			'#default_value' => variable_get('message_cem'),
		);
		// system_settings_form allow to save data into table variables from drupal core
		return system_settings_form($form);

	}
	function test_page(){
		return '<h1>Hola test</h1>';
	}


	
