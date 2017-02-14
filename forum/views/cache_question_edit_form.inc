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

<?php  if (isset($errors)) : ?>
    <p>Oops, please correct these problems:</p>
    <ul>
<?php  foreach ($errors as $error) : ?>
      <li><?php echo($error); ?></li>
<?php  endforeach; ?>
    </ul>
<?php  endif; ?>


<div class='inputs'>
    <form action='/forum/question/edit' method='post'>
        <label for='questionTitle'>Title</label>
        <input type='text' id='questionTitle' name='questionTitle' value='<?php echo($question->getTitle()); ?>'/>
        <label for='content'>Content</label>
        <textarea id='content' name='content' rows='20' cols='60'><?php echo($question->getContent()); ?></textarea>
        <label for='tags'>Tags</label>
        <input type='text' id='tags' name='tags' value='<?php echo($question->getTags()); ?>'/>
        <input type='hidden' id='id' name='id' value='<?php echo($question->getId()); ?>' />
        <input type='submit' value='Save' />
    </form>
</div>
        <div class="footer">
            Copyright &copy; <script>var d = new Date(); var y = d.getFullYear(); document.write(y); </script> Drew Koverman
        </div>
        </div><!-- content div -->
    </body>
</html> 