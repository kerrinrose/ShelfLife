<?php
require 'vendor/autoload.php';
require 'config.php';

const DEFAULT_URL = 'https://shelflife.firebaseio.com';



$firebase = new \Firebase\FirebaseLib(DEFAULT_URL, DEFAULT_TOKEN);

if ($_GET["ID"]) {
    $ID = $_GET["ID"];

$intID = (int)$ID;
$intID = $intID - 48;
    

$name = $firebase->set('reader/ID', $intID);
    

    
}

?>