// BOP.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "BOP.h"
#include "puny.h"
#include "ConvertUTF.h"
#include <malloc.h>

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


int __stdcall ToPunyCode(const int ulen, const wchar_t** utf16, char* punycode, int* plen)
{
	// utf16 a pointer to UTF16 string
	// punycode a pointer to array of byte

	ConversionResult cr;
	punycode_status ps;

	const UTF16* sConvFrom = *utf16;
	const UTF16** pConvFrom = &sConvFrom;

	punycode_uint thing; // = (punycode_uint)*plen;

	UTF32* sTemp = (UTF32*)calloc(ulen * 2, sizeof(UTF32));

	UTF32* sConvTo = sTemp;
	UTF32** pConvTo = &sConvTo;

	cr = ConvertUTF16toUTF32(pConvFrom, sConvFrom + ulen,
		pConvTo, sConvTo + ulen, lenientConversion);

	// have to figure out a way of getting a reasonable length value, esp seeing as 
	// there is an allowance for 0x0 in the in input stream, so length would have
	// to be >= ulen at the least. Poss modify the Convert* to have a global 'charsGenerated' value

	if (cr == conversionOK) {
		ps = punycode_encode((punycode_uint)ulen, (punycode_uint*)sTemp, NULL, &thing, punycode);
	}

	if (ps == punycode_success) {
		*plen = (int)thing;
	}
	free(sTemp);
	return (int)ps;
}

int __stdcall FromPunyCode(const int plen, const char* punycode, wchar_t** utf16, int* ulen)
{
	// puny a pointer to array of byte
	// utf16 a pointer to UTF16 string
	punycode_status ps;
	ConversionResult cr;
	punycode_uint thing;
	UTF32* sTemp = (UTF32*)calloc(plen * 2, sizeof(UTF32));

	const UTF32* sConvFrom = sTemp;
	const UTF32** pConvFrom = &sConvFrom;

	UTF16* sConvTo = *utf16;
	UTF16** pConvTo = &sConvTo;

	ps = punycode_decode((punycode_uint)plen, punycode, &thing, (punycode_uint*)sTemp, NULL);
	if (ps == punycode_success) {
		*ulen = thing;
		cr = ConvertUTF32toUTF16(pConvFrom, sConvFrom + plen,
			pConvTo, sConvTo + plen, lenientConversion);
	}
	return (int)cr;
}


