
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BOP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BOP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef BOP_EXPORTS
#define BOP_API __declspec(dllexport)
#else
#define BOP_API __declspec(dllimport)
#endif


BOP_API int __stdcall ToPunyCode( const int ulen, const wchar_t ** utf16, char * punycode, int plen );
BOP_API int __stdcall FromPunyCode( const int plen, const char * punycode, wchar_t ** utf16, int ulen );


