<?php
/**
 * Checkout pane callback: presents a completion message on the complete page.
 */
function place2pay_completion_message_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $pane_form = array();

  // Load the completion message.
/*  $message = variable_get('commerce_checkout_completion_message', commerce_checkout_completion_message_default());

  // Perform translation.
  $message['value'] = commerce_i18n_string('commerce:checkout:complete:message', $message['value'], array('sanitize' => FALSE));

  // Perform token replacement.
  $message['value'] = token_replace($message['value'], array('commerce-order' => $order), array('clear' => TRUE));

  // Apply the proper text format.
  $message['value'] = check_markup($message['value'], $message['format']);

  $pane_form['message'] = array(
    '#markup' => '<div class="checkout-completion-message">' . $message['value'] . '</div>',
  );
*/
  module_load_include('inc','place2pay');
  $query = db_query('SELECT * from place2pay WHERE order_id = :orderid ORDER BY fecha DESC',array(':orderid' => $order->order_id))->fetchAll();
  switch($query[0]->estado){
     case 'APPROVED': $msg = 'Felicitaciones su pago ha sido aprobado y su compra fue exitosa';
	 	      $msg .= '<h3>Resumen de la transacción</h3>';
	 	      $msg .= '<ul><li>Referencia: '. $query[0]->order_id;
	 	      $msg .= '</li><li>Tarjeta: '. get_nameccp2p($query[0]->cct);
	 	      $msg .= '</li></ul>';
		      $msg .= '<div>Municipio de Loja</div>';
                      break;
     case 'PENDING': $msg = 'Su pago esta siendo procesado, va a tomar algunos minutos...<br> Por favor espere un correo de confirmacion';
	 	     $msg .= '<h3>Resumen de la transacción</h3>';
	 	     $msg .= '<ul><li>Referencia: '. $query[0]->order_id;
	 	     $msg .= '</li><li>Tarjeta: '. get_nameccp2p($query[0]->cct);
	 	     $msg .= '</li><li>Estado: PENDIENTE';
	 	     $msg .= '</li></ul>';
		     $msg .= '<div>Municipio de Loja</div>';
		     $url = 'place2pay/' . $query[0]->order_id . '/pending';
		     drupal_goto($url);
     	 	     break;
     default: $msg = 'No hay procesamiento';
		     break;
  }
  //dsm($pane_form); // cambio 06 ago 2020
  $pane_form['message'] = array(
    '#markup' => '<div class="checkout-completion-message">' . $msg . '</div>',
  );
//  dsm($order);
  return $pane_form;
}
