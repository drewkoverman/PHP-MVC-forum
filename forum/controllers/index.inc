<?php
include_once "include/util.inc";
include_once "models/question.inc";
include_once "controllers/question.inc";


function get_index($params) {
	$questions = Question::findRecentQuestions(5);
	
    // @formatter:off
    renderTemplate(
        "views/index.inc",
        array(
            'title' => "My Questions and Answers Forum",
            'questions' => $questions
        )
    );
    // @formatter:on
}
?>