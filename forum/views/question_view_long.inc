%% views/header.html %%
<h1>{{$title}}</h1>
<p>Posted on {{$question->getPostedOn()}}</p>
[[ 
	$tags = $question -> getTags();
	$pattern = '/[ ]/'; 
	
	$tags = preg_split($pattern, $tags);
	if (isset($tags) && $question->getTags() != '') : 
]]
<p>Filed under:
	[[ foreach($tags as $tag) :]]
		<a href="@@tags/view/{{$tag}}@@">{{$tag}}</a>
	[[ endforeach; ]]		
</p>

[[ endif; ]]
<p>[[ echo (markdown($question->getContent())); ]]</p>

[[ if (isLoggedIn() && ($_SESSION['user_id'] == $question->getUserId())) : ]]
	<p><a href="@@question/delete/{{$question->getId()}}@@">[Delete]</a> <a href="@@question/edit/{{$question->getId()}}@@">[Edit]</a></p>
[[ endif; ]]

%% views/errors.html %%

[[ if($files) :]]
	<label>Attachements:</label>
	<div class="value">&nbsp;
		<ul>
			[[ foreach($files as $file) :]]
				<li>
					<a href="@@file/download/{{$file->getId()}}@@">[download]</a> 
					[[ if (isLoggedIn() && ($_SESSION['user_id'] == $question->getUserId())) : ]]
						<a href="@@file/delete/{{$file->getId()}}/{{$question->getId()}}@@">[delete]</a>
					[[ endif; ]]	
					<a href="@@file/view/{{$file->getId()}}@@">[view]</a>
					{{ $file->getOrigName() }}
				</li>
			[[ endforeach; ]]
		</ul>	
	</div>
[[ endif; ]]

[[ if (isLoggedIn() && ($_SESSION['user_id'] == $question->getUserId())) : ]]
	<div class="inputs">
		<form action="@@file/add@@" method="post" enctype="multipart/form-data">
			<input type="hidden" id="questionId" name="questionId" value="{{$question->getId()}}" />
			<label for="file">Add a file:</label>
			<input type="file" id="file" name="file" /><br />
			<input type="submit" value="Upload" />
		</form>
	</div>
[[ endif; ]]

[[ if (isLoggedIn()) : ]]
	
	<div class="inputs">
		<form action="@@answer/add@@" method="post">
			<label>Add an answer</label>
			<textarea name="answer" id="answer"></textarea>
			<input type="hidden" name="question" id="$question" value="{{$question->getId()}}" />
			<input type="hidden" name="questionTitle" value="{{$question->getTitle()}}" />
			<input type="hidden" name="postedOn" value="{{$question->getPostedOn()}}" />
			<input type="hidden" name="content" value="{{$question->getContent()}}" />
			<input type="hidden" name="tags" value="{{$question->getTags()}}" />
			<input type="hidden" name="id" value="{{$question->getUserId()}}" />
			<input type="hidden" name="title" value="{{$title}}" />
			<input type="submit" value="submit" />
		</form>
	</div>
[[ endif; ]]

<h2>Answers:</h2>

[[foreach($answers as $answer) :]]
	<div class='shortquestion'>
		<span class="date">Posted {{$answer->getPostedOn()}} by {{$answer->getFirstName()}} {{$answer->getLastName()}}</span>
		<span class="question">
			{{markdown($answer->getAnswer())}}
			[[ if (isLoggedIn() && ($_SESSION['user_id'] == $answer->getUserId())) : ]]
				<a href="@@answer/delete/{{$answer->getId()}}@@">[Delete]</a>
			[[ endif; ]]
		</span>
	</div>
[[ endforeach; ]]

<p><a href="@@index@@"><< Back</a></p>
%% views/footer.html %%
