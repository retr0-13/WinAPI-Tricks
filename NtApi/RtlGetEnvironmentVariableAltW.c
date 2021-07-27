BOOL RtlGetEnvironmentVariableAltW(LPCWSTR lpName, LPWSTR lpBuffer, DWORD Length)
{
	UNICODE_STRING EnvironmentVariable = { 0 };
	UNICODE_STRING ReturnedVariable = { 0 };
	NTSTATUS Status = STATUS_SUCCESS;

	RtlInitUnicodeString(&EnvironmentVariable, lpName);
	
	RtlInitEmptyUnicodeString(&ReturnedVariable, lpBuffer, (USHORT)Length);
	
	Status = RtlQueryEnvironmentVariable_U(NULL, &EnvironmentVariable, &ReturnedVariable);
	if (!NT_SUCCESS(Status))
		return FALSE;

	return TRUE;
}
