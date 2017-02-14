%% views/header.html %%
<h1>{{$title}} &ldquo;{{$subtitle}}&rdquo;</h1>

[[ foreach ($tags as $tag) : ]]
	<div class="shortquestion">
		<span class='title'>
			<a href="@@question/view/{{$tag->getId()}}@@">{{$tag->getTitle()}}</a> by {{$tag->getUserFirstName()}} {{$tag->getUserLastName()}}
		</span>
		<span class='date'>Posted on {{$tag->getPostedOn()}}</span>
		<span class='tags'>Filed under: {{$tag->getTags()}}</span>
		<span class='question'>[[ echo(markdown(substr($tag->getContent(), 0, 200) . '...')); ]]</span>
	</div>
[[ endforeach; ]]

%% views/footer.html %%