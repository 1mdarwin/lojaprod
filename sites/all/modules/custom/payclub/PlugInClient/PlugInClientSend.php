<?php

include_once("TripleDESEncryption.php");
include_once("RSAEncryption.php");
include_once("Utilitario.php");



class PlugInClientSend
{
	
	var $LocalID;
	var $MerchantID;
	var $TransacctionID;
	var $CurrencyID;
	var $TransacctionValue;
	var $TaxValue1;
	var $TaxValue2;
	var $TipValue;
	var $SourceDescription;
	var $Referencia1;
	var $Referencia2;
	var $Referencia3;
	var $Referencia4;
	var $Referencia5;

	var $IV;
	var $SignPrivateKey;
        var $CipherPrivateKey;
	var $CipherPublicKey;

	var $xmlGenerateKey;
	var $xmlGenerateKeyEnc;
	var $xmlRequest;
	var $xmlDigitalSign;

	var $AuthorizationState;
	var $AutorizationCode;
	var $ErrorCode;
	var $ErrorDetails;

	var $sizeReference = 30;	
	
	

	
	function PlugInClientSend ()
	{
		$this->sizeReference = 30;
	}

	function setLocalID($localID)
	{
		$this->LocalID = $localID;
	}

	function setMerchantID($merchantID)
	{
		$this->MerchantID = $merchantID;
	}

	function setTransacctionID($transacctionID)
	{	
		if(validaCadena($transacctionID)=="")
		{
		 	$this->TransacctionID = $transacctionID;
			return "";
		}
		else
			return validaCadena($transacctionID);	
	}

	function setTransacctionValue($transacctionValue)
	{		
		
		if (validaValor($transacctionValue) =="")
		{
			$this->TransacctionValue = $transacctionValue;
			return "";
		}
		else 		
			return validaValor($transacctionValue);
	}

	function setTaxValue1($taxValue1)
	{		
		if (validaValor($taxValue1) =="")
		{
			$this->TaxValue1 = $taxValue1;
			return "";
		}
		else 		
			return validaValor($taxValue1);	
	}

	function setTaxValue2($taxValue2)
	{		
		if (validaValor($taxValue2) =="")
		{
			$this->TaxValue2 = $taxValue2;
			return "";
		}
		else 		
			return validaValor($taxValue2);			
	}

	function setTipValue($tipValue)
	{		
		if (validaValor($tipValue) =="")
		{
			$this->TipValue = $tipValue;
			return "";
		}
		else 		
			return validaValor($tipValue);	
	}

	function setCurrencyID($currencyID)
	{
		$this->CurrencyID = $currencyID;
	}

	function setReferencia1($referencia)
	{
		if(strlen($referencia) > $this->sizeReference)
			return "El número de caracteres de la referencia 1 no puede ser mayor a " . $this->sizeReference;
		else
		{
			if (validaCadena($referencia) =="")
			{
				$this->Referencia1 = $referencia;
				return "";
			}
			else 		
				return validaCadena($referencia);
		}

	}

	
	function setReferencia2($referencia)
	{
		if(strlen($referencia) > $this->sizeReference)
			return "El número de caracteres de la referencia 2 no puede ser mayor a " . $this->sizeReference;
		
		else
		{
			if (validaCadena($referencia) =="")
			{	
				$this->Referencia2 = $referencia;
				return "";
			}
			else 		
				return validaCadena($referencia);
		}
	}

	function setReferencia3($referencia)
	{
		if(strlen($referencia) > $this->sizeReference)
			return "El número de caracteres de la referencia 3 no puede ser mayor a " . $this->sizeReference;
		else
		{
			if (validaCadena($referencia) =="")
			{
				$this->Referencia3 = $referencia;
				return "";
			}
			else 		
				return validaCadena($referencia);
		}
	}

	function setReferencia4($referencia)
	{
		if(strlen($referencia) > $this->sizeReference)
			return "El número de caracteres de la referencia 4 no puede ser mayor a " . $this->sizeReference;
		else
		{
			if (validaCadena($referencia) =="")
			{
				$this->Referencia4 = $referencia;	
				return "";
			}
			else 		
				return validaCadena($referencia);
		}
	}

	function setReferencia5($referencia)
	{
		if(strlen($referencia) > $this->sizeReference)
			return "El número de caracteres de la referencia 5 no puede ser mayor a " . $this->sizeReference;
		
		else
		{
			if (validaCadena($referencia) =="")
			{
				$this->Referencia5 = $referencia;
				return "";
			}
			else 		
				return validaCadena($referencia);
		}
	}

	


	function setIV($iv)
	{
		$this->IV = $iv;
	}

	function setIVFromFile($file)
	{
		$rsa = new RSAEncryption();
		$this->IV = $rsa->readFile($file);
	}

	function setSignPrivateKey($signPrivateKey)
	{
		$this->SignPrivateKey = $signPrivateKey;
	}

	function setCipherPrivateKey($cipherPrivateKey)
	{
		$this->CipherPrivateKey = $cipherPrivateKey;
	}

	function setCipherPublicKey($cipherPublicKey)
	{
		$this->CipherPublicKey = $cipherPublicKey;
	}

	function setCipherPublicKeyFromFile($file)
	{
		$this->CipherPublicKey = RSAEncryption.readFile($file);
	}

	function validaNulo($sDato)
	{
		if($sDato == null)
			return "";
		return $sDato;
	}


	
	function XMLProcess($url)
	{
		$this->xmlRequest = "";
			$this->SourceDescription = $url;

			$cadena = $this->validaNulo($this->LocalID) . ";" .
			//$this->validaNulo(MerchantID) + ";" +
			$this->validaNulo($this->TransacctionID) . ";" .
			$this->validaNulo($this->CurrencyID) . ";" .
			$this->validaNulo($this->TransacctionValue) . ";" .
			$this->validaNulo($this->TaxValue1) . ";" .
			$this->validaNulo($this->TaxValue2) . ";" .
			$this->validaNulo($this->TipValue) . ";" .
			$this->validaNulo($this->SourceDescription) . ";" .
			$this->validaNulo($this->Referencia1) . ";" .
			$this->validaNulo($this->Referencia2) . ";" .
			$this->validaNulo($this->Referencia3) . ";" .
			$this->validaNulo($this->Referencia4) . ";" .
			$this->validaNulo($this->Referencia5);

			$this->procesosEncripcion($cadena);

	}



	function procesosEncripcion($cadena)
	{
		$d3 = new TripleDESEncryption();
		$cadena = $d3->encrypt($cadena, $this->xmlGenerateKey, $this->IV);
		$cadena = urlencode($cadena);
		$this->xmlRequest = $cadena;

		// Se firma la cadena encriptada
		$this->xmlDigitalSign = "";

		openssl_sign($this->xmlRequest, $this->xmlDigitalSign, $this->SignPrivateKey);
		$this->xmlDigitalSign = base64_encode($this->xmlDigitalSign);
		$this->xmlDigitalSign = urlencode($this->xmlDigitalSign);
	}

	function CreateXMLGENERATEKEY()
	{
		$this->xmlGenerateKeyEnc = "";

		$d3 = new TripleDESEncryption();

		$this->xmlGenerateKey = $d3->generateKey();

		//encripta la llave
		$rsa = new RSAEncryption();
		$rsa->setPublicKey($this->CipherPublicKey);
		$this->xmlGenerateKeyEnc = $rsa->encrypt($this->xmlGenerateKey);
		$this->xmlGenerateKeyEnc = urlencode($this->xmlGenerateKeyEnc);

		return $this->xmlGenerateKeyEnc;
	}

	function getXMLREQUEST()
	{
		return $this->xmlRequest;
	}

	function getXMLDIGITALSIGN()
	{
		return $this->xmlDigitalSign;
	}

}


?>
