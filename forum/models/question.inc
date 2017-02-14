<?php
include_once 'models/Model.inc';

//Create question object that inherits the model class
class Question extends Model {
	//Declare private variables
	private $title;
	private $content;
	private $tags;
	private $user_id;
	private $postedOn;
	private $user_fname;
	private $user_lname;
	
	//Call and Define class constructor
	public function __construct($title, $content, $postedOn, $tags='', $user_id='', $user_fname='', $user_lname='') {
		parent::__construct();
		$this -> setTitle($title);
		$this -> setContent($content);
		$this -> setPostedOn($postedOn);
		$this -> setTags($tags);
		$this -> setUserId($user_id);
		$this -> setUserFirstName($user_fname);
		$this -> setUserLastName($user_lname);
	}
	
	public function getTitle() {
		return $this -> title;
	}
	
	public function setTitle($title) {
		$this -> title = $title;
		return $this;
	}
	
	public function getContent() {
		return $this -> content;
	}
	
	public function setContent($content) {
		$this -> content = $content;
		return $this;
	}
	
	public function getPostedOn() {
		return $this -> postedOn;
	}
	
	public function setPostedOn($postedOn) {
		$this -> postedOn = $postedOn;
		return $this;
	}
	
	public function getTags() {
		return $this -> tags;
	}
	
	public function setTags($tags) {
		$this -> tags = $tags;
		return $this;
	}
	
	public function getUserId() {
		return $this -> user_id;
	}
	
	public function setUserId($user_id) {
		$this -> user_id = $user_id;
		return $this;
	}
	
	public function getUserFirstName() {
		return $this -> user_fname;
	}
	
	public function setUserFirstName($user_fname) {
		$this -> user_fname = $user_fname;
		return $this;
	}
	
	public function getUserLastName() {
		return $this -> user_lname;
	}
	
	public function setUserLastName($user_lname) {
		$this -> user_lname = $user_lname;
		return $this;
	}
	
	//Function to return all records in question db, limit to recent five records, and list records by user name
	static function findRecentQuestions($count = 5) {
		$db = self::getDb();
		$sql = 'SELECT questions.id, questions.title, questions.content, questions.postedOn, questions.tags, questions.user_id, 
			users.fname, users.lname FROM questions JOIN users on questions.user_id = users.id ORDER BY questions.id 
			DESC LIMIT :count';
		$st = $db -> prepare($sql);
		$st -> bindParam(':count', $count);
		$st -> execute();
		$rows = $st -> fetchAll(PDO::FETCH_ASSOC);	
		return self::makeQuestionsFromRows($rows);
	}
	
	
	//Function to return a single record from questions by id
	static function findQuestionById($id) {
		$db = self::getDb();
		$sql = 'SELECT questions.id, questions.title, questions.content, questions.postedOn, questions.tags, questions.user_id, users.fname, users.lname 
				FROM questions JOIN users on questions.user_id = users.id
				WHERE questions.id = :id';
		$st = $db -> prepare($sql);
		$st -> bindParam(':id', $id);
	    $st -> execute();
	    $row = $st -> fetch(PDO::FETCH_ASSOC);
		return self::makeQuestionFromRow($row);
	}
	
	//Declare static functions to fetch or fetch all rows for questions and tags
	private static function makeQuestionFromRow($row) {
		$question = new Question($row['title'], $row['content'], $row['postedOn'], $row['tags'], $row['user_id'], $row['fname'], $row['lname']);
		$question -> id = $row['id'];
		return $question;
	}
	
	private static function makeQuestionsFromRows($rows) {
		$result = array();
		foreach ($rows as $row) {
			$result[] = self::makeQuestionFromRow($row);
		}
		return $result;
	}
	
	private static function makeTagFromRow($row) {
		$question = new Question($row['title'], $row['content'], $row['postedOn'], $row['tags'], $row['user_id']);
		$question -> id = $row['id'];
		return $question;
	}
	
	private static function makeTagsFromRows($rows) {
		$result = array();
		foreach ($rows as $row) {
			$result[] = self::makeTagFromRow($row);
		}
		return $result;
	}
	
	//Function to return all records for tag answers	
	static function getByTagName($tags) {
		$db = self::getDb();
		$sql = "SELECT questions.id, questions.title, questions.content, questions.postedOn, questions.tags, 
				questions.user_id, users.fname, users.lname FROM questions JOIN users on questions.user_id = users.id WHERE tags LIKE :tags";
		$statement = $db -> prepare($sql);
		$tags = "%".$tags."%"; // put percent sign on tags. PHP Manual: http://php.net/manual/en/pdostatement.bindparam.php
		$statement -> bindParam(':tags', $tags);
		$statement -> execute();
		$rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
		return self::makeQuestionsFromRows($rows);
	}
	
	//Function to return all records in the questions db
	static function findAllQuestions() {
		$db = self::getDb();
		$sql = 'SELECT questions.id, questions.title, questions.content, questions.postedOn, questions.tags, 
				questions.user_id, users.fname, users.lname FROM questions JOIN users on questions.user_id = users.id';	
		$st = $db -> prepare($sql);
		$st -> execute();
		$rows = $st -> fetchAll(PDO::FETCH_ASSOC); 
		return self::makeQuestionsFromRows($rows);		
				
	}

	//Function to return all questions by user id
	static function findQuestionsByUserId() {
		$db = self::getDb();
		$sql = 'SELECT * FROM questions INNER JOIN users on questions.user_id = users.id';
		$statement = $db -> prepare($sql);
		$statement -> execute();
		return $statement -> fetchAll(PDO::FETCH_ASSOC);
	}
	
	//Function that insert questions into the DB table
	function insert() {
		$db = self::getDb();
		$st = $db -> prepare("INSERT INTO questions (postedOn, title, content, tags, user_id) VALUES (DATE('now'), :title, :content, :tags, :user_id)");
		$st -> bindParam(':title', $this -> title);
	    $st -> bindParam(':content', $this -> content);
	    $st -> bindParam(':tags', $this -> tags);
		$st -> bindParam(':user_id', $this -> user_id);
		$st -> execute();
		$this -> id = $db -> lastInsertId();
		return $this;
	}
	
	//Function that updates questions in the DB table
	function update() {
		$db = self::getDb();
		$sql = "UPDATE questions SET title=:title, content=:content, tags=:tags WHERE id=:id";
		$st = $db -> prepare($sql);
		$st -> bindParam(':title', $this -> title);
		$st -> bindParam(':content', $this -> content);
		$st -> bindParam(':tags', $this -> tags);
		$st -> bindParam(':id', $this -> id);
		$st -> execute();
		return $this;
	}
	
	//Function that deletes questions from the DB table
	function delete() {
		$db = self::getDb();
		$st = $db -> prepare("DELETE FROM questions WHERE id = :id");
		$stAnswer = $db -> prepare("DELETE FROM answers WHERE question_id = :question_id");
		$st -> bindParam(':id', $this -> id);
		$stAnswer -> bindParam(':question_id', $this -> id);
		$st -> execute();
		$stAnswer -> execute();
	}
}
?>