<?php

	function validaValor($valor)
	{ 
		//if (ereg("^[0-9]{0,12}$", $valor)) 
		if (preg_match("/^[0-9]{0,12}$/", $valor)) 
			return ""; 
		else  
			return "El valor ".$valor." no tiene formato correcto";
		
	}

	function validaCadena($cadena)
	{ 				
		//if (ereg("\-{1,}", $cadena)) 
		if (preg_match("/\-{1,}/", $cadena))
			return "La cadena ".$cadena." no tiene el formato correcto ";
		else  			
			return ""; 
	}

?>
