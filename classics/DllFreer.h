// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\DllFreer.h
// Revision: public build 8, shipped on 11-July-2006
#ifndef CLASSICS_DLLFREER_H
#define CLASSICS_DLLFREER_H

#include <imagehlp.h>
//#include <winbase.h>


class DLLFreer
{
	const char* name;
public:
	DLLFreer(const char* name) : name(name) {}
	~DLLFreer();
};

DLLFreer::~DLLFreer()
{
	HMODULE h = GetModuleHandle(name);
	if (h)
	{
		try
		{
			IMAGE_NT_HEADERS* p= ImageNtHeader(h);
			typedef BOOL (WINAPI* entrypoint_t) (
				HINSTANCE hinstDLL,
				DWORD fdwReason,
				LPVOID lpvReserved);
			entrypoint_t entrypoint = reinterpret_cast<entrypoint_t> (
				long(h) + long(p->OptionalHeader.AddressOfEntryPoint));
			int retval = entrypoint (h, DLL_PROCESS_DETACH, 0);
		}
		catch(...)
		{
		}
	}
}



#endif