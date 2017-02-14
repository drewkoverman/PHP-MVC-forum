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
<p>First Name: <?php echo($userInfo->getFirstName()); ?></p>
<p>Last Name: <?php echo($userInfo->getLastName()); ?></p>
<p>Email Address: <?php echo($userInfo->getEmail()); ?></p>
<p>Password: <?php  echo str_repeat('*', strlen($userInfo->getPassword()))?></p>
<p><a href="/forum/user/delete/<?php echo($userInfo->getId()); ?>">[Delete]</a> <a href="/forum/user/edit/<?php echo($userInfo->getId()); ?>">[Edit]</a></p>
<h2>Questions by <?php echo( $userInfo->getFirstName()); ?> <?php echo( $userInfo->getLastName()); ?></h2>
<?php  foreach ($questions as $question) : ?>
	<?php  if($question->getUserId() == $_SESSION['user_id']) :?>
		<div class='shortquestion'>
    <span class='title'>
    	<a href="/forum/question/view/<?php echo($question->getId()); ?>"><?php echo($question->getTitle()); ?></a> by <?php echo($question->getUserFirstName()); ?> <?php echo($question->getUserLastName()); ?>
    </span>
    <span class='date'>Posted on: <?php echo($question->getPostedOn()); ?></span>
    <?php 
    	$tags = $question->getTags(); 
    	$pattern = '/[ ]/';
	
		$tags = preg_split($pattern, $tags);
    	
    	if (isset($tags) && $question->getTags() != '') : 
    ?>
    <span class='tags'>Filed under: 
    	<?php  foreach($tags as $tag) :?>
    		<a href="/forum/tags/view/<?php echo($tag); ?>"><?php echo($tag); ?></a>
    	<?php  endforeach; ?>	
    </span>
    <?php  endif; ?>
    <span class='question'><?php  echo(markdown(substr($question->getContent(), 0, 200) . '...')); ?></span>
</div>
	<?php  endif; ?>
<?php  endforeach; ?>
        <div class="footer">
            Copyright &copy; <script>var d = new Date(); var y = d.getFullYear(); document.write(y); </script> Drew Koverman
        </div>
        </div><!-- content div -->
    </body>
</html>