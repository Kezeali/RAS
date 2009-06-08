class ProgressBar : ScriptElement
{
	int _progress;

	void init()
	{
		ScriptElement::SetInnerRML("<progressfill/>");
		SetProgress(0);
		//ScriptElement::AddEventListener("setprogress", "_onSetProgress");
	}

	ProgressBar(Element@ app_element)
	{
		super(app_element);

		init();
	}

	void SetProgress(int progress)
	{
		Element@ progressFill = ScriptElement::GetFirstChild();
		progressFill.SetProperty("width", "" + progress + "%");
		_progress = progress;
	}

	int GetProgress()
	{
		return _progress;
	}
}

int main()
{
	return 0;
}

ProgressBar@ ProgressBar_Factory(Element@ app_element/*, const e_Dictionary &in attributes*/)
{
	//pbar.SetAttributes(attributes);
	return ProgressBar(app_element);
}

void CreateTextElement(const e_String &in text)
{
	Context@ context = GetContext("main");
	Document@ document = context.GetDocument("demo_doc");
	ElementText@ elem = document.CreateTextNode(text);
	document.AppendChild(elem);
}

//void CreateTextElement(Event@ ev)
//{
//	if (ev !is null)
//	{
//		CreateTextElement(ev.GetType());
//	}
//}

void ChangeProgress(int percent)
{
	Context@ context = GetContext("main");
	Document@ document = context.GetDocument("demo_doc");

	Element@ elem = document.GetElementById("a_progressbar");
	if (elem !is null)
	{
		ProgressBar @pbar = cast<ProgressBar>( unwrap(elem) );
		if (pbar !is null)
		{
			pbar.SetProgress(percent);
		}
	}
}

void ChangeProgressRand(int min, int max)
{
	Context@ context = GetContext("main");
	Document@ document = context.GetDocument("demo_doc");

	Element@ elem = document.GetElementById("a_progressbar");
	if (elem !is null)
	{
		ProgressBar @pbar = cast<ProgressBar>( unwrap(elem) );
		if (pbar !is null)
		{
			if (pbar.GetProgress() == min)
				pbar.SetProgress(max);
			else
				pbar.SetProgress(min);
		}
	}
}

Context@ Init()
{
	BindElementFactory("progressbar", "ProgressBar@ ProgressBar_Factory(Element@)");

	e_Vector2i d(1024,768);
	Context@ ctx = CreateContext("main", d);
	return ctx;
}

Document@ LoadDoc()
{
	Context@ context = GetContext("main");
	Document@ document = context.LoadDocument("assets/demo.rml");
	if (document !is null)
	{
		document.SetId("demo_doc");
		document.Show();

		ChangeProgress(50);
	}
	return document;
}

void CloseDoc()
{
	Context@ context = GetContext("main");
	context.GetDocument("demo_doc").Close();
}
