ULONG Next = 2;

INT PseudoRandomIntegerSubroutine(PULONG Context)
{
	return ((*Context = *Context * 1103515245 + 12345) % ((ULONG)RAND_MAX + 1));
}

INT PseudoRandomInteger(VOID)
{
	return (PseudoRandomIntegerSubroutine(&Next));
}

PWCHAR GeneratePseudoRandomStringW(SIZE_T dwLength)
{
	WCHAR DataSet[] = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	PWCHAR String = NULL;

	String = (PWCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (sizeof(WCHAR) * (dwLength + 1)));
	if (String == NULL)
		return NULL;

	for (INT dwN = 0; dwN < dwLength; dwN++)
	{
		INT Key = PseudoRandomInteger() % (INT)(StringLengthW(DataSet) - 1);
		String[dwN] = DataSet[Key];
	}

#pragma warning (push)
#pragma warning (disable: 6386)
	String[dwLength] = '\0';
#pragma warning (pop)

	//YOU MUST FREE THE RETURNED STRING WITH HeapFree
	
	return String;
} 
