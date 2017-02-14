%% views/header.html %%
<h1>{{$title}}</h1>
%% views/errors.html %%
<div class="inputs">
	<form action="@@user/register@@" method="post">
		<label for="fname">First Name</label>
		<input type="text" name="fname" id="fname" value="{{isset($fname) ? $fname : ''}}" />	
		<label for="lname">Last Name</label>
		<input type="text" name="lname" id="lname" value="{{isset($lname) ? $lname : ''}}" />
		<label for="fname">Email address</label>
		<input type="text" name="email" id="email" value="{{isset($email) ? $email : ''}}" />
		<label for="fname">Password</label>
		<input type="password" name="password" id="password" value="{{isset($password) ? $password : ''}}" />
		<input type="submit" value="Save" />
	</form>
</div>		
%% views/footer.html %%