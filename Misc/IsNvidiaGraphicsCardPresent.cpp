BOOL IsNvidiaGraphicsCardPresent(VOID)
{
    DISPLAY_DEVICEW DisplayDevice; RtlZeroMemory(&DisplayDevice, sizeof(DISPLAY_DEVICEW));
    DisplayDevice.cb = sizeof(DISPLAY_DEVICEW);

	DWORD dwDeviceId = ERROR_SUCCESS;

	while (EnumDisplayDevicesW(NULL, dwDeviceId, &DisplayDevice, 0))
	{
		if (StringFindSubstringW(DisplayDevice.DeviceString, (PWCHAR)L"NVIDIA") != NULL)
			return TRUE;
	}

	return FALSE;
}