<?php
include_once "include/util.inc";
include_once "models/user.inc";
include_once "models/question.inc";
include_once "models/validator.inc";

function safeParam($arr, $index, $default = '') {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}

function validatePresent($key, $error, &$errors, $default = '') {
    if (!isset($_REQUEST[$key]) || trim($_REQUEST[$key]) == '') {
        $errors[] = $error;
        return $default;
    }
    return htmlentities($_REQUEST[$key]);
}

function get_register($params) {
	renderTemplate(
        "views/user_form.inc",
        array(
            'title' => 'Register',
        )
    );
}

function post_register($params) {		
	$validator = new Validator();
	$fname = htmlentities(safeParam($_REQUEST, 'fname', 0));
	$lname = htmlentities(safeParam($_REQUEST, 'lname', 0));
	$email = htmlentities(safeParam($_REQUEST, 'email', 0));
	$password = htmlentities(safeParam($_REQUEST, 'password', 0));
	
	//Implement validator class to implement data validation
	$validator -> required('fname', $fname, 'First name is required');
	$validator -> required('lname', $lname, 'Last name is required');
	$validator -> required('email', $email, 'Email address required');
	$validator -> required('password', $password, 'Please enter a password');
	$validator -> email('email', $email);
	$validator -> password('password', $password, 'Password must be at least 8 chars, have an upper case character, 
							a symbol, and a number');
	
	$user = new User($fname, $lname, $email, $password);
	
	$other = User::findByEmail($user -> getEmail());
	
	if ($other && $other -> getId() != $user -> getId()) {
		$validator -> addError('email', "Email address is already in use.");
	}
	
	if(!$validator -> hasErrors()) {
		$user -> insert();
		//Create session and username once user is created
		$_SESSION['loggedin'] = true;
		$_SESSION['username'] = $user->getFirstName() . " " . $user->getLastName();
		redirectRelative("index");
	} else {
		renderTemplate(
			"views/user_form.inc",
			array(
				'title' => 'Register',
				'fname' => $fname,
				'lname' => $lname,
				'email' => $email,
				'password' => $password,
				'errors' => $validator -> allErrors()
			)
		);
		return;
	} 
}

function get_edit($params) {
	ensureLoggedIn();
	$id = safeParam($params, 0, false);
	if ($id === false) {
        die("No question id specified");
    }
	
	$user = User::getUserId($id);
	
	if (!$user) {
		die("no user with $id found.");
	}
	
	renderTemplate(
		"views/user_edit_form.inc",
		array(
			'title' => 'Edit User',
			'user' => $user
		)
	);
}

function post_edit($params) {
	ensureLoggedIn();
	$id = trim(safeParam($_REQUEST, 'id', ''));
	$fname = trim(safeParam($_POST, 'fname'));
	$lname = trim(safeParam($_POST, 'lname'));
	$email = trim(safeParam($_POST, 'email'));
	$password = trim(safeParam($_POST, 'password'));
	
	//Declare validator class to implement data validation
	$validator = new Validator();
	$validator -> required('id', $id, 'No ID specified');
	$validator -> required('fname', $fname, 'First Name required');
	$validator -> required('lname', $lname, 'Last Name required');
	$validator -> required('email', $email, 'Email Address required');
	$validator -> required('password', $id, 'Passworld field required');	
	$validator -> email('email', $email);
	$validator -> password('password', $password, 'Password must be at least 8 chars, have an upper case character, 
							a symbol, and a number');
	
	$user = User::getUserId($id);
	
	$other = User::findByEmail($user -> getEmail());
	
	if ($other && $other -> getId() != $user -> getId()) {
		$validator -> addError('email', "Email address is already in use.");
	}						
	
	if (!$validator -> hasErrors()) {
		if ($user) {
			$user -> setFirstName($fname);
			$user -> setLastName($lname);
			$user -> setEmail($email);
			$user -> setPassword($password);
			$user -> update();
		}
		//Create user and session id
		$_SESSION['username'] = $user -> getFirstName() . " " . $user -> getLastName();
		$user_id = $_SESSION['user_id'];
		redirectRelative("user/view/$user_id");
	} else {
		$user = new User($fname, $lname, $email, $password, $id);
		$user -> setId($id);
		renderTemplate(
			"views/user_edit_form.inc",
			array(
				'title' => 'Edit User',
				'user' => $user,
				'errors' => $validator -> allErrors()
			)
		);
	}
}

function get_view($params) {
	$id = safeParam($params, 0, false);
	if ($id === false) {
		die("No id spcified");
	}
	
	$userInfo = User::getUserId($id);
	$questions = Question::findAllQuestions();
	
	if(!$userInfo) {
		die("No user with id $id found.");
	}
	
	renderTemplate(
		"views/user_profile.inc",
		array(
			'title' => 'View user',
			'userInfo' => $userInfo,
			'questions' => $questions
		)
	);
}

function get_delete($params) {
	ensureLoggedIn();
	$id = safeParam($params, 0, false);
	
	if ($id === false) {
		die("No user id specified");
	}
	
	$user = User::getUserId($id);
	
	if (!$user) {
		die("no user with $id found");
	}
	
	$user ->delete();
	redirectRelative("logout");
}

?>