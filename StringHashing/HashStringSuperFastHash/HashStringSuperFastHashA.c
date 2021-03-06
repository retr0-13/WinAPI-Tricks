#if !defined (Get16Bits)
#define Get16Bits(d) ((((UINT32)(((const UINT8*)(d))[1])) << 8)\
                       +(UINT32)(((const UINT8*)(d))[0]) )
#endif

SIZE_T StringLengthA(LPCSTR String)
{
	LPCSTR String2;

	for (String2 = String; *String2; ++String2);

	return (String2 - String);
}

UINT32 HashStringSuperFastHashA(PCHAR String)
{
	INT Length = StringLengthA(String);
	UINT32 Hash = Length;
	INT Tmp = 0;

	INT Rem = Length & 3;
	Length >>= 2;

	for (; Length > 0; Length--)
	{
		Hash += Get16Bits(String);
		Tmp = (Get16Bits(String + 2) << 11) ^ Hash;
		Hash = (Hash << 16) ^ Tmp;
#pragma warning( push )
#pragma warning( disable : 6305)
		String += 2 * sizeof(UINT16);
#pragma warning( pop ) 
		Hash += Hash >> 11;
	}

	switch (Rem)
	{
		case 3:
		{
			Hash += Get16Bits(String);
			Hash ^= Hash << 16;
			Hash ^= ((UCHAR)String[sizeof(UINT16)]) << 18;
			Hash += Hash >> 11;
			break;
		}
		case 2:
		{
			Hash += Get16Bits(String);
			Hash ^= Hash << 11;
			Hash ^= Hash >> 17;
			break;
		}
		case 1:
		{
			Hash += (UCHAR)*String;
			Hash ^= Hash << 10;
			Hash += Hash >> 1;
		}
	}

	Hash ^= Hash << 3;
	Hash += Hash >> 5;
	Hash ^= Hash << 4;
	Hash += Hash >> 17;
	Hash ^= Hash << 25;
	Hash += Hash >> 6;

	return Hash;
}