<?php
# Author: Drew Koverman
# Date: 6/5/2016
# Project Name: WEBD236 Lab 5
# Project Description: Create a MVC question and answer forum that adds/edits/deletes new/existing forum post
# Notes: Only implement File Uploads and Minimarkdown solution
#		 RBAC functionality has not been implemented for this lab

include_once 'include/util.inc';

// This is the "home page", which redirects to the index controller
// (controllers/index.inc) get_index() function, which may redirect to
// the actual home page controller/function...
redirect("index");

// Alternatively, you could just include your home page controller directly,
// include_once 'controllers/sample.inc';
// and then call the home-page function (get_index, in this case)
// get_index();
?>
