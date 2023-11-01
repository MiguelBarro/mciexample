#include <iostream>
#include <string>

#include <windows.h>
#include <Mmsystem.h>

#ifdef _UNICODE
#   define tout std::wcout;
#   define terr std::wcerr;
#else
#   define tout std::cout
#   define terr std::cerr
#endif

struct mciAssert
{
    mciAssert(DWORD e)
    {
        if (0 == e)
            return;

        // Check the error
        std::basic_string<TCHAR> error(256, TEXT('\0'));
        if (FALSE == mciGetErrorString(e, error.data(), error.size()))
            error = TEXT("unknown error");
        throw error;
    }
};
