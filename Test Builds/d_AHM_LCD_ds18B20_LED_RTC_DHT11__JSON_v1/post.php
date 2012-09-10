<?php


  //--------------------------------------------------------------------------------------
  // Data poster!
  //--------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------------------
  // Fetch the json string
  //---------------------------------------------------------------------------------------
  $json = $_GET["json"];
  $json = str_replace(chr(92), "", $json);
  //Pass in json example:
  //$json = '{"house1":"502.5","house1":"0.31","power":"121.1","rpm":"333.1","life":"32.1"}';

    echo "<br>json string received: " . $json;
    $log .= "\n" . $json . "\n\n";
  //---------------------------------------------------------------------------------------------------
  // Custom json_decode function, specially designed to allow storage of repeated variable keys
  // for example when realPower is included twice in the same string
  //---------------------------------------------------------------------------------------------------
  $json = str_replace('"', '', $json);                    //Remove quote characters "
  $json = str_replace('{', '', $json);                    //Remove JSON start characters
  $json = str_replace('}', '', $json);                    //Remove JSON end characters

  $datapairs = explode(",", $json);                       //Seperate JSON string into individual data pairs. 

  //---------------------------------------------------------------------------------------------------
  //For all datapairs
  //---------------------------------------------------------------------------------------------------
  foreach ($datapairs as $datapair)            
  {
    $datapair = explode(":", $datapair);                       //Divide them into their key and value contituent parts
    $key_plus_timeoffset = $datapair[0];                       //Get the key plus time offset
    $value = $datapair[1];                                     //Get the value

//***
//create variables
//http://php.net/manual/es/language.variables.variable.php
// With the objective of working with the data acquired we need to put each data in a variable with the correct variable name to distinguis it from 
// other data. This allows to send and receive new variables in any order without having to map each variable in a specific order.
    // This works by using an extra $ sign. after the 2 $ signs we put the variable that contains the string which will be the new variable name
    // All this is equal = to the value we want to assign to that variable that we have created.
    $$datapair[0] = $datapair[1];
//***


//*********************************************************************
// *****  CREATE THE MYSQL QUERY **************************************
    $log .= "Data name: " . $datapair[0] . " Value: " . $value . "\n";
    //echo "<br>" . $log;
    
    $query_insert .= $datapair[0] . ",";
    $query_values .= $datapair[1] . ",";
//*********************************************************************
  }


echo "<br>";
echo "<br>El valor dentro de la variable dinamica $ temp_box es: " . $temp_box;
echo "<br>El valor dentro de la variable dinamica $ temp_amb es: "   . $temp_amb;
echo "<br>";


//*********************************************************************
// *****  FINISH THE MYSQL QUERY **************************************
$query_start = "INSERT INTO data (";
    $query_insert = "B, "           . substr($query_insert,0,-1);
    $query_values = time() .", "    . substr($query_values,0,-1);
    
$query = $query_start . $query_insert . ") VALUES (" . $query_values . ")"; 
echo "<br>" . $query;
//*********************************************************************

?>





<?php

$create_columns_automatically = true;       // Creates automatically new columns based on new parameters send by the arduino
$send_email = false;                         // sends an email on each data upload

include 'mysql_connection.php';

$con = mysql_connect($db_host, $db_user, $db_pass); //$db_host,"ArduinoHMonitor","AHM130984ahm");
if (!$con)
  {
  die('Could not connect: ' . mysql_error());
  }

mysql_select_db($db_name, $con);

//***************************************************
//************* CREATE TABLE IF NOT EXIST ***********
$check_table =  mysql_query("
CREATE TABLE IF NOT EXISTS `data` (
  `ID` int(11) NOT NULL auto_increment,
  `date_uploaded` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `B` bigint(20) NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=MyISAM AUTO_INCREMENT=151 DEFAULT CHARSET=utf8
");
echo "<br>Table creation: " . mysql_error();
//***************************************************


//***************************************************
//************* PERFORM THE MYSQL QUERY * ***********
mysql_query($query);
$mysql_error_info = mysql_error();
echo "<br>Mysql Error check: " . $mysql_error_info;
//***************************************************


//***************************************************
//*********** CREATE COLUMNS IF NECCESARY ***********
if ($create_columns_automatically == true)
{
      // CHECK IF THE VALUE WAS NOT UPLOADED BECAUSE A NEW PARAMETER WAS SEND
            $haystack = $mysql_error_info;
            $needle = "Unknown column";
            $pos = strpos($haystack,$needle);
            
            if($pos === false) {
             // string needle NOT found in haystack
             if (mysql_error() == false) echo "<br>No error found.";
            }
            else {
                
                    $fullstring = $mysql_error_info;
                    $parsed = get_string_between($fullstring, "column '", "' in");   //echo "Columna nueva: " . $parsed; // (result = dog)
             // string needle found in haystack
                echo "<h2>New parameter in the query, requires assistance to add it to the table.</h2>";
                 mail("sergioescuder@gmail.com","NEW PARAMETER RECEIVED","THERE IS A NEW PARAMETER IN THE QUERY" . $query);
                echo "<br> Columna nueva: " . $parsed;
                
                $query_column = "ALTER TABLE " . $table . " ADD `$parsed` float NULL";
                echo "<br>" . $query_column;   echo mysql_query($query_column);
            }
}
//***************************************************


mysql_close($con);


// This function is used to extract the column name from the mysql error returned when the column does not exist. It is then used to create the column
function get_string_between($string, $start, $end){
	$string = " ".$string;
	$ini = strpos($string,$start);
	if ($ini == 0) return "";
	$ini += strlen($start);
	$len = strpos($string,$end,$ini) - $ini;
	return substr($string,$ini,$len);
}


?>

























<?
// send email  
IF ($send_email == true)
{
  echo "<br>sending email...";
        mail('sergioescuder@gmail.com',"Json example",$log . "\n\n\n" . "query:\n" . $query);
  echo "email send!!";
}
?>






<?
/*
// Save to file
$log = "" . date("Y_m_d-H:i:s",time()) . " - " . $log . "\n";		//$log = "\n".$date." - IP ".$ip." caused the following log in ".$page." on line ".$line." ".$log."\n";
$handle = fopen("_log_json.txt","a+");  //w+  // http://php.net/manual/es/function.fopen.php
fwrite($handle,$log);
fclose($handle);
*/
?>


