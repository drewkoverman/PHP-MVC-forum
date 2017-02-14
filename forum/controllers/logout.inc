<?php
include_once "include/util.inc";
include_once "models/user.inc";

function get_index($params) {
	//destroy the session and redirect to index
	$_SESSION = array();
	session_destroy();
	redirectRelative("index");
}
?>