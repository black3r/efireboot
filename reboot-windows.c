#include <Windows.h>
#include "wincommon.h"

void reboot_init() {
    ObtainPrivileges(SE_SHUTDOWN_NAME);
}

void reboot() {
    int res = ExitWindowsEx(EWX_REBOOT, 0);
    if (res == 0) {
        PrintError(GetLastError());
        exit(GetLastError());
    }
}
