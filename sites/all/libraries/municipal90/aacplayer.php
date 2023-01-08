<?php
$dar=isset($_GET['dar'])? $_GET['dar']:"";
$protectedswf="aacplayer.swf";
$swffilesize=0;
date_default_timezone_set('UTC');
$qid = md5(date("H:i")); 

switch($dar){
	case "load":
		$swffilesize=filesize($protectedswf); 
		header ("content-type: text/xml");
		echo "<?xml version='1.0' standalone='yes'?>\n";
		echo "<playerdata>\n";
		echo "<hashtoken>$qid</hashtoken>\n";
		echo "<databytes>$swffilesize</databytes>\n";
		echo "</playerdata>";
	break;
	case $qid:
		header('Content-Type: application/x-shockwave-flash');
		header('Expires: Thu, 01 Jan 1972 00:00:00 GMT, -4');
		header('Cache-Control: no-cache, no-store, must-revalidate');
		header('Pragma: no-cache');
		echo file_get_contents($protectedswf);
	break;
	
    default:
		echo "AAC+ Flash  Player - www.HDRadioStream.com -  ICEcast/ShoutCast";
    break;
 }

?>