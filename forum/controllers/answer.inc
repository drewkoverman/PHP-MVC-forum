<?php
include_once "include/util.inc";
include_once "models/answers.inc";
include_once "models/question.inc";
include_once "models/validator.inc";

function safeParam($arr, $index, $default = '') {
    if ($arr && isset($arr[$index])) {
        return htmlentities($arr[$index]);
    }
    return $default;
}

function post_add($params) {
	ensureLoggedIn();
	
	$user_answer = htmlentities(safeParam($_REQUEST, 'answer'));
	$question_id = htmlentities(safeParam($_REQUEST, 'question'));
	$title = htmlentities(safeParam($_REQUEST, 'questionTitle'));
	$date = htmlentities(safeParam($_REQUEST, 'postedOn'));
	$tags = htmlentities(safeParam($_REQUEST, 'tags'));
	$content = htmlentities(safeParam($_REQUEST, 'content'));
	$title = htmlentities(safeParam($_REQUEST, 'title'));
	$user_id = $_SESSION['user_id'];
	
	//Declare validator class to implement data validation
	$vailadator = new Validator();
	$vailadator -> required('answer', $user_answer, 'Please specify a answer');
	
	$answer = new Answer($user_answer,'',$question_id,$user_id,'','');
	$answer_list = Answer::findAnswersByQuestions($question_id);
	$question = new Question($title, $content, $date, $tags);
	$question -> setId($question_id);
	
	
	if(!$vailadator -> hasErrors()) {
		$answer -> insert();
		redirectRelative("question/view/$question_id");
	} else {
		
		renderTemplate(
			"views/question_view_long.inc",
			array(
				'title' => $title,
				'answers' => $answer_list,
				'question_id' => $answer -> setQuestionId($question_id),
				'question' => $question,
				'errors' => $vailadator -> allErrors()
			)
		);
	}
}

function get_delete($params) {
	ensureLoggedIn();
	$id = safeParam($params, 0, false);
    if ($id === false) {
        die("No question id specified");
    }
	
	$answer = Answer::findAnswersById($id);
	
	$answer -> delete();
	redirectRelative("index");
}

?>