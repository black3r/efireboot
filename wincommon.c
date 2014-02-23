#include <Windows.h>
#include <stdio.h>

void PrintError(DWORD errorCode) {
    LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        NULL);

    printf("Error code was: %ld\n", errorCode);
    printf("Error message was: %ws", lpMsgBuf);
    LocalFree(lpMsgBuf);
}

const wchar_t* GetWChar(const char* c) {
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = (wchar_t *)malloc(sizeof(wchar_t)*cSize);
    //mbstowcs(wc, c, cSize);
    size_t result;
    mbstowcs_s(&result, wc, cSize, c, cSize);
    return wc;
}

void ObtainPrivileges(LPCTSTR privilege) {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;
    BOOL res;
    DWORD error;
    // Obtain required privileges
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        printf("OpenProcessToken failed!\n");
        PrintError(GetLastError());
        exit(GetLastError());
    }

    res = LookupPrivilegeValue(NULL, privilege, &tkp.Privileges[0].Luid);
    if (!res) {
        printf("LookupPrivilegeValue failed!\n");
        PrintError(GetLastError());
        exit(GetLastError());
    }
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

    error = GetLastError();
    if (error != ERROR_SUCCESS) {
        printf("AdjustTokenPrivileges failed\n");
        PrintError(error);
        exit(error);
    }

}
