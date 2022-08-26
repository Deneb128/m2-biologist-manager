//before void initnet()
//add:
PyObject* netSendBiologistManagerOpenCommand(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream::Instance().SendBiologistManagerOpenCommand();
	return Py_BuildNone();
}

PyObject* netSendBiologistManagerDeliverCommand(PyObject* poSelf, PyObject* poArgs)
{
	int questID = 0;
	if (!PyTuple_GetInteger(poArgs, 0, &questID))
		return Py_BuildException();

	int itemWantedCount = 0;
	if (!PyTuple_GetInteger(poArgs, 1, &itemWantedCount))
		return Py_BuildException();


	int elixirCount = 0;
	if (!PyTuple_GetInteger(poArgs, 2, &elixirCount))
		return Py_BuildException();


	int elixirPlusCount = 0;
	if (!PyTuple_GetInteger(poArgs, 3, &elixirPlusCount))
		return Py_BuildException();


	int timeDeleterCount = 0;
	if (!PyTuple_GetInteger(poArgs, 4, &timeDeleterCount))
		return Py_BuildException();



	CPythonNetworkStream::Instance().BiologistManagerDeliverItems(questID, itemWantedCount, elixirCount, elixirPlusCount, timeDeleterCount);
	return Py_BuildNone();
}

//before:
		{ NULL,										NULL,										NULL },
//add:
		//Biologist Manager
		{ "SendBiologistManagerOpenCommand",		netSendBiologistManagerOpenCommand,			METH_VARARGS },
		{ "SendBiologistManagerDeliverCommand",		netSendBiologistManagerDeliverCommand,		METH_VARARGS },
