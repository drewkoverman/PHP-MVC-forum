<!DOCTYPE HTML>
<html>
    <head>
        <title><?php echo($title); ?></title>
        <link rel="stylesheet" href="/forum/static/style.css" />
    </head>
    <body>
        <div class="content">
        <?php  include_once 'include/util.inc'; ?>
        <?php  if (isLoggedIn()) : ?>
        <span class="username">Welcome, 
        <?php  if (isset($_SESSION['username'])) :  ?>
        	<?php  echo $_SESSION['username']; ?>
        <?php  endif; ?>
        </span>	
        <ul class="login">
	        <!--Session Log in output-->
	    	<li><a href="/forum/index">Home</a></li>
	    	<li><a href="/forum/user/view/<?php echo($_SESSION['user_id']); ?>">MyProfile</a></li>
	    	<li><a href="/forum/logout">Log out</a></li>
	    </ul>	
        <?php  else : ?>
        <ul class="login">
        	<li><a href="/forum/index">Home</a></li>
	    	<li><a href="/forum/user/register">Register</a></li>
	    	<li><a href="/forum/login">Log in</a></li>
	    </ul>	
        <?php  endif; ?>	
        </ul>
		<div class="clear"></div>
<h1><?php echo($title); ?></h1>
<p>Posted on <?php echo($question->getPostedOn()); ?></p>
<?php  
	$tags = $question -> getTags();
	$pattern = '/[ ]/'; 
	
	$tags = preg_split($pattern, $tags);
	if (isset($tags) && $question->getTags() != '') : 
?>
<p>Filed under:
	<?php  foreach($tags as $tag) :?>
		<a href="/forum/tags/view/<?php echo($tag); ?>"><?php echo($tag); ?></a>
	<?php  endforeach; ?>		
</p>

<?php  endif; ?>
<p><?php  echo (markdown($question->getContent())); ?></p>

<?php  if (isLoggedIn() && ($_SESSION['user_id'] == $question->getUserId())) : ?>
	<p><a href="/forum/question/delete/<?php echo($question->getId()); ?>">[Delete]</a> <a href="/forum/question/edit/<?php echo($question->getId()); ?>">[Edit]</a></p>
<?php  endif; ?>

<?php  if (isset($errors)) : ?>
    <p>Oops, please correct these problems:</p>
    <ul>
<?php  foreach ($errors as $error) : ?>
      <li><?php echo($error); ?></li>
<?php  endforeach; ?>
    </ul>
<?php  endif; ?>


<?php  if($files) :?>
	<label>Attachements:</label>
	<div class="value">&nbsp;
		<ul>
			<?php  foreach($files as $file) :?>
				<li>
					<a href="/forum/file/download/<?php echo($file->getId()); ?>">[download]</a> 
					<?php  if (isLoggedIn() && ($_SESSION['user_id'] == $question->getUserId())) : ?>
						<a href="/forum/file/delete/<?php echo($file->getId()); ?>/<?php echo($question->getId()); ?>">[delete]</a>
					<?php  endif; ?>	
					<a href="/forum/file/view/<?php echo($file->getId()); ?>">[view]</a>
					<?php echo( $file->getOrigName() ); ?>
				</li>
			<?php  endforeach; ?>
		</ul>	
	</div>
<?php  endif; ?>

<?php  if (isLoggedIn() && ($_SESSION['user_id'] == $question->getUserId())) : ?>
	<div class="inputs">
		<form action="/forum/file/add" method="post" enctype="multipart/form-data">
			<input type="hidden" id="questionId" name="questionId" value="<?php echo($question->getId()); ?>" />
			<label for="file">Add a file:</label>
			<input type="file" id="file" name="file" /><br />
			<input type="submit" value="Upload" />
		</form>
	</div>
<?php  endif; ?>

<?php  if (isLoggedIn()) : ?>
	
	<div class="inputs">
		<form action="/forum/answer/add" method="post">
			<label>Add an answer</label>
			<textarea name="answer" id="answer"></textarea>
			<input type="hidden" name="question" id="$question" value="<?php echo($question->getId()); ?>" />
			<input type="hidden" name="questionTitle" value="<?php echo($question->getTitle()); ?>" />
			<input type="hidden" name="postedOn" value="<?php echo($question->getPostedOn()); ?>" />
			<input type="hidden" name="content" value="<?php echo($question->getContent()); ?>" />
			<input type="hidden" name="tags" value="<?php echo($question->getTags()); ?>" />
			<input type="hidden" name="id" value="<?php echo($question->getUserId()); ?>" />
			<input type="hidden" name="title" value="<?php echo($title); ?>" />
			<input type="submit" value="submit" />
		</form>
	</div>
<?php  endif; ?>

<h2>Answers:</h2>

<?php foreach($answers as $answer) :?>
	<div class='shortquestion'>
		<span class="date">Posted <?php echo($answer->getPostedOn()); ?> by <?php echo($answer->getFirstName()); ?> <?php echo($answer->getLastName()); ?></span>
		<span class="question">
			<?php echo(markdown($answer->getAnswer())); ?>
			<?php  if (isLoggedIn() && ($_SESSION['user_id'] == $answer->getUserId())) : ?>
				<a href="/forum/answer/delete/<?php echo($answer->getId()); ?>">[Delete]</a>
			<?php  endif; ?>
		</span>
	</div>
<?php  endforeach; ?>

<p><a href="/forum/index"><< Back</a></p>
        <div class="footer">
            Copyright &copy; <script>var d = new Date(); var y = d.getFullYear(); document.write(y); </script> Drew Koverman
        </div>
        </div><!-- content div -->
    </body>
</html>
