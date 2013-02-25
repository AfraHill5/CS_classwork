
void listAllAuxiliary(string path, const Domain* d)
{
	if (d->subdomains().empty()) // if leaf node, print out contents
	{
		cout << path << endl;
		return;
	}
	for (int i = 0; i < d->subdomains().size(); i++)
	{
		Domain* curr = d->subdomains().at(i);
		string nextPath;
		if (path == "") //if this is a head pointer, just ignore the current path
			nextPath = curr->label();
		else
			nextPath = curr->label() + "." + path;

		listAllAuxiliary(nextPath, d->subdomains().at(i));
	}
	
}