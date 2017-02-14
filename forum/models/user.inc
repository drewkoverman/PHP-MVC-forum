<?php
include_once 'models/Model.inc';
include_once 'models/validator.inc';

//Create user object that inherits the model class
class User extends Model {
	//Declare private variables
	private $fname;
	private $lname;
	private $email;
	private $password;
	
	//Call and Define class constructor
	public function __construct($fname, $lname, $email, $password) {
		parent::__construct();
		$this -> setFirstName($fname);
		$this -> setLastName($lname);
		$this -> setEmail($email);
		$this -> setPassword($password);
	}
	
	public function getFirstName() {
		return $this -> fname;
	}
	
	public function setFirstName($fname) {
		$this -> fname = $fname;
		return $this;
	}
	
	public function getLastName() {
		return $this -> lname;
	}
	
	public function setLastName($lname) {
		$this -> lname = $lname;
		return $this;
	}
	
	public function getEmail() {
		return $this -> email;
	}
	
	public function setEmail($email) {
		$this -> email = $email;
		return $this;
	}
	
	public function getPassword() {
		return $this -> password;
	}
	
	public function setPassword($password) {
		$this -> password = $password;
		return $this;
	}
	
	//Function that returns a email address by a specific user
	static function findByEmail($email) {
		$db = self::getDb();
		$sql = 'SELECT * FROM users WHERE email = :email';
		$st = $db -> prepare($sql);
		$st -> bindParam(':email', $email);
		$st -> execute();
		$row = $st -> fetch(PDO::FETCH_ASSOC);
		return self::makeUserFromRow($row);
	}
	
	//Function that determines if the user is a valid user
	static function isValidUser($username, $password) {
		$db = self::getDb();
		$sql = 'SELECT * FROM users WHERE email = :email AND password = :password';
		$st = $db -> prepare($sql);
	    $st -> bindParam(':email', $username);
		$st -> bindParam(':password', $password);
	    $st -> execute();
		return $st -> fetchAll(PDO::FETCH_ASSOC);	
	}
	
	//Function that finds user by email address
	static function findUserByUserName($username) {
		$db = self::getDb();
		$sql = 'SELECT * FROM users WHERE email = :email';
		$st = $db -> prepare($sql);
	    $st -> bindParam(':email', $username);
	    $st -> execute();
	    $row =  $st -> fetch(PDO::FETCH_ASSOC);
		return self::makeUserFromRow($row);
	}
	
	//Function that return users by id in the users db
	static function getUserId($id) {
		$db = self::getDb();
		$sql = 'SELECT * FROM users WHERE id = :id';
		$st = $db -> prepare($sql);
	    $st -> bindParam(':id', $id);
	    $st -> execute();
	    $row = $st -> fetch(PDO::FETCH_ASSOC);
		return self::makeUserFromRow($row);
	}
	
	//Declare static functions to fetch or fetch all rows for users
	private static function makeUserFromRow($row) {
		$user = new User($row['fname'], $row['lname'], $row['email'], $row['password']);
		$user -> id = $row['id'];
		return $user;
	}
	
	private static function makeUsersFromRows($rows) {
		$result = array();
		foreach ($rows as $row) {
			$result[] = self::makeUserFromRow($row);
		}
		return $result;
	}
	
	//Function that insert users to the DB table
	function insert() {
		$db = self::getDb();
		$sql = 'INSERT INTO users(fname, lname, password, email) VALUES (:fname, :lname, :password, :email);';
		$st = $db -> prepare($sql);
		$st -> bindParam(':fname', $this -> fname);
		$st -> bindParam(':lname', $this -> lname);
		$st -> bindParam(':password', $this -> password);
		$st -> bindParam(':email', $this -> email);
		$st -> execute();
		$id = $db -> lastInsertId();
		$_SESSION['user_id'] = $id;
		$this -> id = $db -> lastInsertId();
		return $this;
	}
	
	//Function that updates user info in the DB table
	function update() {
		$db = self::getDb();
		$sql = 'UPDATE users SET fname=:fname, lname=:lname, email=:email, password=:password WHERE id=:id';
		$st = $db -> prepare($sql);
		$st -> bindParam(':fname', $this -> fname);
		$st -> bindParam(':lname', $this -> lname);
		$st -> bindParam(':email', $this -> email);
		$st -> bindParam(':password', $this -> password);
		$st -> bindParam(':id', $this -> id);
		$st -> execute();
		return $this;
	}
	
	//Function that deletes user info in the DB table
	function delete() {
		$db = self::getDb();
		$stUser = $db -> prepare("DELETE FROM users WHERE id = :id");
		$stQuestion = $db -> prepare("DELETE FROM questions WHERE user_id = :user_id");
		$stAnswer = $db -> prepare("DELETE FROM answers WHERE user_id = :user_id");
		$stUser -> bindParam(':id', $this -> id);
		$stQuestion -> bindParam(':user_id', $_SESSION['user_id']);
		$stAnswer -> bindParam('user_id', $_SESSION['user_id']);
		$stUser -> execute();
		$stQuestion -> execute();
		$stAnswer -> execute();
	}
	
	
	
}
?>