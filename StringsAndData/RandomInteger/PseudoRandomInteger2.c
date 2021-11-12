ULONG Next = 2;

INT PseudoRandomIntegerSubroutine(PULONG Context)
{
	return ((*Context = *Context * 1103515245 + 12345) % ((ULONG)RAND_MAX + 1));
}

INT PseudoRandomInteger(VOID)
{
	return (PseudoRandomIntegerSubroutine(&Next));
}