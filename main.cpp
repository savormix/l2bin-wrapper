#include "customization.h"
#include "src/args.h"
#include "src/paths.h"

/*
#include <libloaderapi.h>
#include <processthreadsapi.h>
#include <WinBase.h>
*/
#include <Windows.h>

#define CMDLINE_BUFFER_SIZE 4096

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    WCHAR binPath[PATH_BUFFER_SIZE];
    // Get path to this executable
    GetModuleFileNameW(nullptr, binPath, PATH_BUFFER_SIZE);
    // discard L2.bin
    binPath[GetFilename(binPath) - binPath] = '\0';
    // append L2.exe
    wcscat_s(binPath, PATH_BUFFER_SIZE, TARGET_EXECUTABLE);

#ifdef DISCARD_IP
    removeArgument(pCmdLine, L"ip=");
#endif
#ifdef DISCARD_L2_INI
    removeArgument(pCmdLine, L"-ini");
#endif
#ifdef DISCARD_USER_INI
    removeArgument(pCmdLine, L"-userini");
#endif

    WCHAR newCmdLine[CMDLINE_BUFFER_SIZE];
    newCmdLine[0] = 0;
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, REPLACEMENT_EXECUTABLE);
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, L" ");
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, pCmdLine);
#ifdef OVERRIDE_IP
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, L" IP=");
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, TARGET_IP);
#endif
#ifdef OVERRIDE_L2_INI
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, L" -INI=");
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, TARGET_L2_INI);
#endif
#ifdef OVERRIDE_USER_INI
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, L" -USERINI=");
    wcscat_s(newCmdLine, CMDLINE_BUFFER_SIZE, TARGET_USER_INI);
#endif

    PROCESS_INFORMATION procInfo;
    STARTUPINFOW startupInfo;
    memset(&startupInfo, 0, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    CreateProcessW(binPath, newCmdLine, nullptr, nullptr, false, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &startupInfo, &procInfo);

    return 0;
}
