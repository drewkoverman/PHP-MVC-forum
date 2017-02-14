%% views/header.html %%
<h1>{{$title}}</h1>

%% views/errors.html %%

<div class='inputs'>
    <form action='@@question/edit@@' method='post'>
        <label for='questionTitle'>Title</label>
        <input type='text' id='questionTitle' name='questionTitle' value='{{$question->getTitle()}}'/>
        <label for='content'>Content</label>
        <textarea id='content' name='content' rows='20' cols='60'>{{$question->getContent()}}</textarea>
        <label for='tags'>Tags</label>
        <input type='text' id='tags' name='tags' value='{{$question->getTags()}}'/>
        <input type='hidden' id='id' name='id' value='{{$question->getId()}}' />
        <input type='submit' value='Save' />
    </form>
</div>
%% views/footer.html %% 