%% views/header.html %%
<h1>{{$title}}</h1>

%% views/errors.html %%
<div class="inputs">
	<form action="@@user/edit@@" method="post">
		<label for="fname">First Name</label>
		<input type="text" name="fname" id="fname" value="{{$user->getFirstName()}}" />	
		<label for="lname">Last Name</label>
		<input type="text" name="lname" id="lname" value="{{$user->getLastName()}}" />
		<label for="fname">Email address</label>
		<input type="text" name="email" id="email" value="{{$user->getEmail()}}" />
		<label for="fname">Password</label>
		<input type="password" name="password" id="password" value="{{$user->getPassword()}}" />
		<input type="hidden" name="id" id="id" value="{{$user->getId()}}" />
		<input type="submit" value="Save" />
	</form>
</div>	
%% views/footer.html %%