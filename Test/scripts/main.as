class Option
{
	e_String name;
	string value;
}

const uint NUM_OPTS = 11;

class ScriptDS : IDataSource
{
	Option[] options;

	ScriptDS()
	{
		e_String[] names = { "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Many", "Many One", "Many Two"};

		options.resize(NUM_OPTS);
		for (uint i = 0; i < NUM_OPTS; i++)
		{
			options[i].name = names[i];
			options[i].value = i;
		}
	}

	void GetRow(StringList&out row, const e_String&in table, int row_index, const StringList&in columns)
	{
		//row = StringList();
		if (row_index >= NUM_OPTS)
			return;

		if (table == e_String("numbers"))
		{
			for (uint i = 0; i < columns.size(); i++)
			{
				if (columns[i] == e_String("name"))
				{
					row.push_back(options[row_index].name);
				}
				else if (columns[i] == e_String("value"))
				{
					row.push_back( e_String(options[row_index].value) );
				}
			}
		}
	}

	int GetNumRows(const e_String&in table)
	{
		if (table == e_String("numbers"))
		{
			return NUM_OPTS;
		}

		return 0;
	}
}

class ScriptDF : IDataFormatter
{
	e_String FormatData(const StringList &in raw_data)
	{
		string data = raw_data[0];
		data = data.to_int() + 1;
		return e_String(data);
	}
}

int main()
{
	return 0;
}

void CreateTextElement(const e_String &in text)
{
	Context@ context = GetContext("main");
	Document@ document = context.GetDocument("demo_doc");
	ElementText@ elem = document.CreateTextNode(text + e_String("\n"));

	Element@ parent = document.GetElementById("text_target");
	parent.AppendChild(elem);
}

void DSChanged(Event@ e)
{
	CreateTextElement( e_String("Selected index: ") + e.GetParameter('value', e_String("nothing")) );
}

void EventCallback(Event@ ev)
{
	Element@ elem = ev.GetCurrentElement();
	e_String tagName = elem.GetTagName();
	e_String type = ev.GetType();
	e_String text = tagName + e_String(" ") + type;
	CreateTextElement(text);
}

void RefCountTest(Event@ e)
{
	Context@ context = GetContext("main");
	Document@ document = context.GetDocument("demo_doc");
	Element@ elm = document.GetElementById("a_progressbar");
	IElement@ scElm = unwrap(elm);
}

Context@ Init()
{
	AddDataSource("scripted_data", ScriptDS());
	AddDataFormatter("Format_IndexPlusOne", ScriptDF());

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

		context.AddEventListener("testcallback", "void EventCallback(Event@)");
		document.AddEventListener("testcallback", "void EventCallback(Event@)");
		document.DispatchEvent("testcallback", e_Dictionary(), false);
	}
	return document;
}

void CloseDoc()
{
	Context@ context = GetContext("main");
	context.GetDocument("demo_doc").Close();
}
