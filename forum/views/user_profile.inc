%% views/header.html %%
<h1>{{$title}}</h1>
<p>First Name: {{$userInfo->getFirstName()}}</p>
<p>Last Name: {{$userInfo->getLastName()}}</p>
<p>Email Address: {{$userInfo->getEmail()}}</p>
<p>Password: [[ echo str_repeat('*', strlen($userInfo->getPassword()))]]</p>
<p><a href="@@user/delete/{{$userInfo->getId()}}@@">[Delete]</a> <a href="@@user/edit/{{$userInfo->getId()}}@@">[Edit]</a></p>
<h2>Questions by {{ $userInfo->getFirstName()}} {{ $userInfo->getLastName()}}</h2>
[[ foreach ($questions as $question) : ]]
	[[ if($question->getUserId() == $_SESSION['user_id']) :]]
		%% views/question_view_short.html %%
	[[ endif; ]]
[[ endforeach; ]]
%% views/footer.html %%