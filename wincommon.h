#ifndef WINERROR_H
#define WINERROR_H

const wchar_t* GetWChar(const char* c);
void PrintError(DWORD errorCode);
void ObtainPrivileges(LPCTSTR privilege);

#endif // WINERROR_H
