<?php
include_once 'models/Model.inc';

//Create answer object that inherits model class
class Answer extends Model {
	//Declare private variables
	private $answer;
	private $postedOn;
	private $question_id;
	private $user_id;
	private $fname;
	private $lname;
	
	//Call and Define class constructor
	public function __construct($answer, $postedOn, $question_id, $user_id, $fname, $lname) {
		parent::__construct();
		$this -> setAnswer($answer);
		$this -> setPostedOn($postedOn);
		$this -> setQuestionId($question_id);
		$this -> setUserId($user_id);
		$this -> setFirstName($fname);
		$this -> setLastName($lname);
	}
	
	public function getAnswer() {
		return $this -> answer;
	}
	
	public function setAnswer($answer) {
		$this -> answer = $answer;
		return $this;
	}
	
	public function getPostedOn() {
		return $this -> postedOn;
	}
	
	public function setPostedOn($postedOn) {
		$this -> postedOn = $postedOn;
		return $this;
	}
	
	public function getQuestionId() {
		return $this -> question_id;
	}
	
	public function setQuestionId($question_id) {
		$this -> question_id = $question_id;
		return $this;
	}
	
	public function getUserId() {
		return $this -> user_id;
	}
	
	public function setUserId($user_id) {
		$this -> user_id = $user_id;
		return $this;
	}
	
	public function getFirstName() {
		return $this ->fname;
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
	
	//Function that finds all answers for a specific question
	static function findAnswersByQuestions($question_id) {
		$db = self::getDb();
		$sql = "SELECT answers.id, answers.answer, answers.postedOn, answers.question_id, answers.user_id, users.fname, users.lname
				FROM answers JOIN users on answers.user_id = users.id
				WHERE answers.question_id = :question_id";
		$st = $db -> prepare($sql);
		$st -> bindParam(':question_id', $question_id);
		$st -> execute();
		$rows = $st -> fetchAll(PDO::FETCH_ASSOC);
		return self::makeAnswersFromRow($rows);
	}
	
	//Function that find answers by answer id
	static function findAnswersById($id) {
		$db = self::getDb();
		$sql = "SELECT answers.id, answers.answer, answers.postedOn, answers.question_id, answers.user_id, users.fname, users.lname
				FROM answers JOIN users on answers.user_id = users.id
				WHERE answers.id = :id";
		$st = $db -> prepare($sql);
		$st -> bindParam(':id', $id);
		$st -> execute();
		$row = $st -> fetch(PDO::FETCH_ASSOC);
		return self::makeAnswerFromRow($row);
	}
	
	//Declare static functions to fetch or fetch all answer rows
	private static function makeAnswerFromRow($row) {
		$answer = new Answer($row['answer'], $row['postedOn'], $row['question_id'], $row['user_id'], $row['fname'], $row['lname']);
		$answer -> id = $row['id'];
		return $answer;
	}
	
	private static function makeAnswersFromRow($rows) {
		$result = array();
		foreach ($rows as $row) {
			$result[] = self::makeAnswerFromRow($row);
		}
		return $result;
	}
	
	//Function that inserts answer in the DB table
	function insert() {
		$db = self::getDb();
		$st = $db -> prepare("INSERT INTO answers (answer, postedOn, question_id, user_id) VALUES (:answer, DATE('now'), :question_id, :user_id)");
		$st -> bindParam(':answer', $this -> answer);
		$st -> bindParam(':question_id', $this -> question_id);
		$st -> bindParam(':user_id', $this -> user_id);
		$st -> execute();
		$this -> id = $db -> lastInsertId();
		return $this;
	}
	
	//Function that deletes answer from the DB table
	function delete() {
		$db = self::getDb();
		$st = $db -> prepare("DELETE FROM answers WHERE id = :id");
		$st -> bindParam(':id', $this -> id);
		$st -> execute();
	}
}
?>