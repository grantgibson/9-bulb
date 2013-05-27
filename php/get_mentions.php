<?php

require_once('tmhoauth/tmhOAuth.php');
require_once('maxid.php');

$count = 10;
$newmaxid = "";

$result = get_mentions($count, $maxid);


if($result) {
  exec("echo \"" . $result . "\" > com3"); // Change the Com port here to the com / serial port your Ardunio is connected to
	echo("Done.  Sent: " . $result);
} else {
	echo("Nothing to process");
}


/*************************************************************/

function get_mentions($c, $m) {

  $outputString = "";
      
  $connection = new tmhOAuth(array(
    'consumer_key' => 'KEY_HERE',
    'consumer_secret' => 'KEY_HERE',
    'user_token' => 'KEY_HERE',
    'user_secret' => 'KEY_HERE',
  )); 
  
  // Make the API call
  //echo "test " . $m;
  $connection->request('GET', 
    $connection->url('1/statuses/mentions'), 
    array('count' => $c, 'since_id' => "$m" ));

  //print_r($connection->response['response']);
  
  $incoming = $connection->response['response'];
  if($incoming) {
    $incoming = preg_replace('/"id":([0-9]*)/', '"id":"\1"', $incoming);

    $response = json_decode($incoming);
    foreach ($response as $r) {
      if($r->{'id'} > $newmaxid) {
        $newmaxid = $r->{'id'};
      }
      $t = $r->{'text'};
      $t = str_replace("|"," ",$t);
      $outputString .= "|" . $t;
    }
    if($newmaxid != "") {
      update_max_id($newmaxid);
    }
  }
  return $outputString;
}

function update_max_id($id) {
  $myFile = "maxid.php";
  $fh = fopen($myFile, 'w') or die("can't open file");
  $stringData = "<?php \$maxid = \"" . $id . "\"; ?>";
  fwrite($fh, $stringData);
  fclose($fh);
}

?>
