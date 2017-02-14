<?php
include_once "include/util.inc";
include_once "models/question.inc";
include_once "models/validator.inc";

function safeParam($arr, $index, $default = '') {
    if ($arr && isset($arr[$index])) {
        return htmlentities($arr[$index]);
    }
    return $default;
}

function get_view($params) {
	$tags = safeParam($params, 0, false);
    if ($tags === "") {
        die("No tag name specified");
    }
	
	$subTitle = $tags;
	
	$tags = Question::getByTagName($tags);
	
	renderTemplate(
		"views/tag_view_long.inc",
		array(
			'title' => 'Questions tagged',
			'subtitle' => $subTitle,
			'tags' => $tags
		)
	);
	
	
	
}
?>