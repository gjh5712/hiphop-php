<?php
/* Prototype  : string imap_fetchheader(resource $stream_id, int $msg_no [, int $options])
 * Description: Get the full unfiltered header for a message 
 * Source code: ext/imap/php_imap.c
 */

/*
 * Pass different data types as $msg_no argument to test behaviour of imap_fetchheader()
 */

echo "*** Testing imap_fetchheader() : usage variations ***\n";
require_once(dirname(__FILE__).'/imap_include.inc');

// Initialise function arguments not being substituted
$stream_id = setup_test_mailbox('', 1, $mailbox, 'notSimple'); // set up temp mailbox with 1 msg

//get an unset variable
$unset_var = 10;
unset ($unset_var);

// get a class
class classA
{
  public function __toString() {
    return "Class A object";
  }
}

// heredoc string
$heredoc = <<<EOT
hello world
EOT;

$index_array = array (1, 2, 3);
$assoc_array = array ('one' => 1, 'two' => 2);

// get a resource variable
$fp = fopen(__FILE__, "r");

// unexpected values to be passed to $msg_no argument
$inputs = array(

       // int data
/*1*/  0,
       1,
       12345,
       -2345,

       // float data
/*5*/  10.5,
       -10.5,
       12.3456789000e10,
       12.3456789000E-10,
       .5,

       // null data
/*10*/ NULL,
       null,

       // boolean data
/*12*/ true,
       false,
       TRUE,
       FALSE,
       
       // empty data
/*16*/ "",
       '',

       // string data
/*18*/ "string",
       'string',
       $heredoc,
       
       // array data
/*21*/ array(),
       $index_array,
       $assoc_array,
       array('foo', $index_array, $assoc_array),
       
       
       // object data
/*25*/ new classA(),

       // undefined data
/*26*/ @$undefined_var,

       // unset data
/*27*/ @$unset_var,

       // resource variable
/*28*/ $fp
);

// loop through each element of $inputs to check the behavior of imap_fetchheader()
$iterator = 1;
foreach($inputs as $input) {
  echo "\n-- Iteration $iterator --\n";
  var_dump( imap_fetchheader($stream_id, $input) );
  $iterator++;
};

fclose($fp);
?>
===DONE===<?php
require_once(dirname(__FILE__).'/clean.inc');
?>
===DONE===