<?php
include_once "include/util.inc";
include_once "models/user.inc";

function safeParam($arr, $index, $default) {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}

function get_index($params) {
    // @formatter:off
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
        )
    );
    // @formatter:on
}

function post_index($params) {
    $username = safeParam($_REQUEST, 'username', false);
    $password = safeParam($_REQUEST, 'password', false);
	
	$user = User::isValidUser($username, $password);
	
	//validation to determine if user is valid
    if ($user) {
    	//Add session variables
    	$userInfo = User::findUserByUserName($username);
    	
        $_SESSION['loggedin'] = true; //store loggedin status
		$_SESSION['username'] = $userInfo->getFirstName() . " " . $userInfo->getLastName(); //store username 
		$_SESSION['user_id'] = $userInfo->getId(); //store user id
        if (isset($_SESSION['redirect'])) {
            $redirect = $_SESSION['redirect'];
            redirect($redirect);
            exit();
        }
		
		redirectRelative("index");
    } else {
    // @formatter:off
    renderTemplate(
        "views/login_form.inc",
        array(
            'title' => 'Login',
            'errors' => array("Invalid username/password"),
            'username' => $username,
            'password' => $password
        )
    );
    // @formatter:on
    }
}
?>