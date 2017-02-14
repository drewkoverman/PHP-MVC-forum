<?php
include_once "include/util.inc";
include_once "models/question.inc";
include_once "models/answers.inc";
include_once "models/validator.inc";
include_once "models/File.inc";

function safeParam($arr, $index, $default = '') {
    if ($arr && isset($arr[$index])) {
        return htmlentities($arr[$index]);
    }
    return $default;
}

function get_add($params) {
    // @formatter:off
    renderTemplate(
        "views/question_add_form.inc",
        array(
            'title' => 'Add a question'
        )
    );
    // @formatter:on
}

function validatePresent($key, $error, &$errors, $default = '') {
    if (!isset($_REQUEST[$key]) || trim($_REQUEST[$key]) == '') {
        $errors[] = $error;
        return $default;
    }
    return htmlentities($_REQUEST[$key]);
}

function post_add($params) {
	ensureLoggedIn();
	
	$questionTitle = htmlentities(safeParam($_REQUEST, 'questionTitle', ''));	
	$content = htmlentities(safeParam($_REQUEST, 'content', ''));
	$tags = htmlentities(safeParam($_REQUEST, 'tags', ''));
	$user_id = $_SESSION['user_id'];
	
	//Declare validator class to implement data validation
	$validator = new Validator();
	$validator -> required('questionTitle', $questionTitle, 'Please specify a title');
	$validator -> required('content', $content, 'Please enter some content');
	
	$question = new Question($questionTitle, $content, '', $tags, $user_id);
	
	if(!$validator -> hasErrors()) {		
		$question -> insert();
		redirectRelative("index");
	} else {
		
		renderTemplate(
			"views/question_add_form.inc",
			array(
				'title' => 'Add a question',
				'questionTitle' => $question->getTitle(),
				'content' => $question->getContent(),
				'tags' => $question->getTags(),
				'errors' => $validator -> allErrors()
			)
		);
		return;
	}
	
		
}

function get_view($params) {
	
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No question id specified");
    }

	$question = Question::findQuestionById($id);
	$answer = Answer::findAnswersByQuestions($id);
	$files = File::findByQuestionId($question->getId());
	
    if (!$question) {
        die("No question with id $id found.");
    }
    // @formatter:off
    renderTemplate(
        "views/question_view_long.inc",
        array(
            'title' => $question->getTitle(),
            'question' => $question,
            'answers' => $answer,
            'files' => $files
        )
    );
    // @formatter:on
}

function get_edit($params) {
	ensureLoggedIn();
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No question id specified");
    }

    $question = Question::findQuestionById($id);
	
    if (!$question) {
        die("No question with id $id found.");
    }
    // @formatter:off
    renderTemplate(
        "views/question_edit_form.inc",
        array(
            'title' => 'Edit a question',
            'question' => $question
        )
    );
    // @formatter:on
}

function post_edit($params) {
	ensureLoggedIn();
	$id = trim(safeParam($_REQUEST, 'id', ''));
	$questionTitle = trim(safeParam($_REQUEST, 'questionTitle', ''));
	$content = trim(safeParam($_REQUEST, 'content', ''));
	$tags = trim(safeParam($_REQUEST, 'tags', ''));
	
	//Declare validator class to implement data validation
	$validator = new Validator();
	$validator -> required('id', $id, 'No ID specified');
	$validator -> required('questionTitle', $questionTitle, 'Please specify a title');
	$validator -> required('content', $content, 'Please enter some content');
	
	if(!$validator -> hasErrors()) {
		$question = Question::findQuestionById($id);
		if($question) {
			$question -> setTitle($questionTitle);
			$question -> setContent($content);
			$question -> setTags($tags);
			$question -> update();
			redirectRelative("index");
		}
	} else {
		$question = new Question($questionTitle, $content, '', $tags);
		$question -> setId($id);
		renderTemplate(
			"views/question_edit_form.inc",
			array(
				'title' => 'Edit a question',
				'errors' => $validator -> allErrors(),
				'question' => $question
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

    $question = Question::findQuestionById($id);
	$answer = Answer::findAnswersById($id);
	
    if (!$question) {
        die("No question with id $id found.");
    }
    
	$question ->delete();
	$answer -> delete();
    redirectRelative('index');
}

?>