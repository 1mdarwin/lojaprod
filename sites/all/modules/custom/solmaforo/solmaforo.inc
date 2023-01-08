<?php
function get_press(){
	return get_service();
	//return '<h1>Titulo</h1>';
}
function get_service(){
	$url = "http://wsgesol.goia-services.com/Servicio/GetDataDisUser/";		
	$email = 'wludena@loja.gob.ec';
	$pass = 'monitorloja';
	
	$urlGET = $url . "?email=" . $email . "&password=" . $pass;	
	//dsm($urlGET);

	$curl = curl_init($urlGET);	
	$headers = array( "Content-Type: application/json;");
	//$headers = array( "Content-Type: application/x-www-form-urlencoded;");
	//curl_setopt($curl, CURLOPT_HEADER, true); // return headers with true
	curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
	//curl_setopt($curl, CURLOPT_USERPWD, AUTH_PARAM); // With authentication
	$json_response = curl_exec($curl);
	
	if($json_response){
	  //drupal_set_message('Se ha emitido con éxito - get_facturas_file ', 'status');
	}	
	$status = curl_getinfo($curl, CURLINFO_HTTP_CODE);	
	curl_close($curl);
	
	$response = json_decode($json_response, false);	
	
	$data = array();
	// levels array
	$muybajo = array(); 
	$bajo = array();
	$moderado = array();
	$alto = array();
	$muyalto = array();
	$extremo = array();
	
	$imb = 0;
	$iba = 0;
	$imo = 0;
	$ial = 0;
	$ima = 0;
	$iex = 0;
	
	for($s=0;$s<sizeof($response);$s++){		
		$hora = substr($response[$s]->FECHA, 0, 5);
		$hora = str_replace(":", ".", $hora);

		$data[$s] = array($hora, $response[$s]->IUV);		
		if ($response[$s]->IUV < 4 ){
			$muybajo[$imb] = array($hora, $response[$s]->IUV);
			$imb +=1;
		}
		if ($response[$s]->IUV > 3 && $response[$s]->IUV < 6 ){
			$bajo[$iba] = array($hora, $response[$s]->IUV);
			$iba +=1;
		}
		if ($response[$s]->IUV > 5 && $response[$s]->IUV < 8 ){
			$moderado[$imo] = array($hora, $response[$s]->IUV);
			$imo +=1;
		}
		if ($response[$s]->IUV > 7 && $response[$s]->IUV < 11 ){
			$alto[$ial] = array($hora, $response[$s]->IUV);
			$ial +=1;
		}
		if ($response[$s]->IUV > 10 && $response[$s]->IUV < 16 ){
			$muyalto[$ima] = array($hora, $response[$s]->IUV);
			$ima +=1;			
		}
		if ($response[$s]->IUV > 15 && $response[$s]->IUV < 20 ){
			$extremo[$iex] = array($hora, $response[$s]->IUV);
			$iex +=1;			
		}
	}
	//dsm("hola debug");
	//dsm(array_pop($data));
	$ultimo = array_pop($data);


	for ($i=0;$i<4;$i++){
		$horas[$i] = date("H") - $i;
	}
	$datos = array(array(10.30, 4),array(11.12, 1),array(12.06, 7));
	/*dsm($muybajo);
	dsm($bajo);
	dsm($moderado);
	dsm($alto);
	dsm($muyalto);
	dsm($extremo);*/

	
  
	$chart = array(
	   '#type' => 'chart',
	   '#chart_id' => 'solmaforo',
	   '#chart_type' => 'area',
	   '#chart_library' => 'google', // Allowed values: 'google' or 'highcharts'
	   '#title' => t('Solmaforo Test with JSON data'),
	   //'#title_position' => 'right',
	   '#stacking' => TRUE,
	   //'#legend_title' => 'Niveles ultravioleta',
	   //'#colors' => array('#006400', '#003366'),
	   '#colors' => array('#788000', '#4eb400', '#FFe400', '#F85900', '#d8001d', '#BA55D3'),
  	);
  
  $chart['muybajo'] = array(
    '#type' => 'chart_data',
    '#title' => t('Muy Bajo (0 - 3)'),    
    //'#data' => array(array(7.30, 1),array(11.12, 3),array(12.06, 2)),
    '#data' => $muybajo,
    //'#suffix' => 'lbs',
  );
  if(sizeof($bajo) > 0){ 
	   $chart['bajo'] = array(
	    '#type' => 'chart_data',
	    '#title' => t('Bajo (4 - 5)'),    
	    //'#data' => array(array(8.30, 5),array(9.12, 4),array(10.06, 6)),
	    '#data' => $bajo,
	    //'#suffix' => 'lbs',
	   );
	}
   if(sizeof($moderado) > 0){ 
	  	$chart['moderado'] = array(
	    	'#type' => 'chart_data',
	    	'#title' => t('Moderado (6 - 7)'),    
	    	//'#data' => array(array(11.30, 7),array(13.12, 7),array(15.06, 8)),
	    	'#data' => $moderado,
	    	//'#suffix' => 'lbs',
	  	);
	}
	if(sizeof($alto) > 0){ 
	  	$chart['alto'] = array(
		   '#type' => 'chart_data',
		   '#title' => t('Alto (8 - 10)'),    
		   //'#data' => array(array(10.20, 9),array(12.12, 10),array(13.06, 11)),
		   '#data' => $alto,
		   //'#suffix' => 'lbs',
	  	);
	}
   if(sizeof($muyalto) > 0){ 
	  	$chart['muyalto'] = array(
	    '#type' => 'chart_data',
	    '#title' => t('Muy Alto (11 - 15)'),    
	    //'#data' => array(array(9.30, 12),array(11.12, 12),array(13.06, 13)),
	    '#data' => $muyalto,
	    //'#suffix' => 'lbs',
	  	);
	}
  	if(sizeof($extremo) > 0){
	  	$chart['extremo'] = array(
	    	'#type' => 'chart_data',
	    	'#title' => t('Extremo (16)'),    
	    	//'#data' => array(array(8.30, 16),array(11.50, 17),array(13.06, 18)),
	    	'#data' => $extremo,
	    	//'#suffix' => 'lbs',
	  	);
	}
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    //'#labels' => array('Jan', 'Feb', 'Mar'),
    '#labels' => $horas,
    '#title' => t('Horas'),
  );    

  	$solmaforo['chart'] = $chart;  	
  	
  	$page['page_bottom']["notices"]['notices-placeholder'] = array(
  '#suffix' => "<div id='notices-placeholder'>Aqui va",
  '#prefix' => '</div>',
);
  	$tabladesc = '<table><thead><tr><th>Color</th><th>Rango de radiación UV(*)</th><th>Recomendaciones</th><tr></thead><tbody>';
  	$tabladesc .= '<tr><td class="muybajo">Muy bajo</td><td>1 a 3</td><td>Puede permanecer en el exterior sin riesgo</td><tr>';
  	$tabladesc .= '<tr><td class="bajo">Bajo</td><td>4 a 5</td><td>Use gafas, gorra o sombrero</td><tr>';
  	$tabladesc .= '<tr><td class="moderado">Moderado</td><td>6 a 7</td><td>Use bloqueador, gorra o sombrero, gafas</td><tr>';
  	$tabladesc .= '<tr><td class="alto">Alto</td><td>8 a 10</td><td>Use bloqueador, gorra o sombrero, ropa manga larga, gafas</td><tr>';
  	$tabladesc .= '<tr><td class="muyalto" >Muy Alto</td><td>11 a 15</td><td>Use bloqueador, gorra o sombrero, ropa manga larga, gafas, use sombrilla</td><tr>';
  	$tabladesc .= '<tr><td class="extremo">Extremo</td><td>16 y superior</td><td>Use bloqueador, gorra o sombrero, ropa manga larga, gafas, use sombrilla, mantengase en la sombra</td><tr>';
  	$tabladesc .= '</tbody></table> <div>(*) UV: Ultra Violeta</div>';


  	$tabladesc .= '<br><table><thead><tr><th class="col-md-3">Hora de último registro</th><th class="col-md-3">Nivel de radiación UV</th></tr></thead>';
  	$horaultima = str_replace(".",":",$ultimo[0]);  	
  	$tabladesc .= '<tbody><tr><td>' . $horaultima . '</td><td class="col-md-3 '. get_color($ultimo[1]) . '">'. $ultimo[1].'</td></tr></tbody></table>';
  	
  	//drupal_render_page($page);
  	drupal_set_message($tabladesc);  	
  	//drupal_set_message($actual);

 	return drupal_render($solmaforo);	
}
/**
* Retorna un color dependiendo del rango
*/
function get_color($rango){
	if ($rango < 4 ){
		$color = 'muybajo';
	}
	if ($rango > 3 && $rango < 6 ){
		$color = 'bajo';		
	}
	if ($rango > 5 && $rango < 8 ){
		$color = 'moderado';
	}
	if ($rango > 7 && $rango < 11 ){
		$color = 'alto';
	}
	if ($rango > 10 && $rango < 16 ){
		$color = 'muyalto';
	}
	if ($rango > 15 && $rango < 20 ){
		$color = 'extremo';
	}
	return $color;
}
