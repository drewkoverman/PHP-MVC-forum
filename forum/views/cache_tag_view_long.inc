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
<h1><?php echo($title); ?> &ldquo;<?php echo($subtitle); ?>&rdquo;</h1>

<?php  foreach ($tags as $tag) : ?>
	<div class="shortquestion">
		<span class='title'>
			<a href="/forum/question/view/<?php echo($tag->getId()); ?>"><?php echo($tag->getTitle()); ?></a> by <?php echo($tag->getUserFirstName()); ?> <?php echo($tag->getUserLastName()); ?>
		</span>
		<span class='date'>Posted on <?php echo($tag->getPostedOn()); ?></span>
		<span class='tags'>Filed under: <?php echo($tag->getTags()); ?></span>
		<span class='question'><?php  echo(markdown(substr($tag->getContent(), 0, 200) . '...')); ?></span>
	</div>
<?php  endforeach; ?>

        <div class="footer">
            Copyright &copy; <script>var d = new Date(); var y = d.getFullYear(); document.write(y); </script> Drew Koverman
        </div>
        </div><!-- content div -->
    </body>
</html>