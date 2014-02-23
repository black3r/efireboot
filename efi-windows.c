#include <Windows.h>
#include <stdint.h>
#include <stdio.h>
#include "wincommon.h"

#define _CRT_SECURE_NO_WARNINGS 1
const char* EFI_GLOBAL_VARIABLE = "{8BE4DF61-93CA-11D2-AA0D-00E098032B8C}";

#ifdef UNICODE
#define ___T(str) GetWChar(str)
#else
#define ___T(str) str
#endif

void efi_init() {
    // Determine if running UEFI. If no -> then exit
    FIRMWARE_TYPE fwtype;    
    DWORD dwRet;
    GetFirmwareType(&fwtype);
    if (fwtype != FirmwareTypeUefi) {
        printf("You are not running UEFI!\n");
        exit(-1);
    }

    ObtainPrivileges(SE_SYSTEM_ENVIRONMENT_NAME);

    // Perform check if UEFI variables are present.
    // If not, we get ERROR_INVALID_FUNCTION on this.
    // If yes, we get ERROR_NOACCESS because we are accessing not-existing variable.
    // Any other errors are unexpected.
    dwRet = 0;
    if (GetFirmwareEnvironmentVariable(___T(""), ___T("{00000000-0000-0000-0000-000000000000}"), NULL, 0) == 0) {
        if (GetLastError() == ERROR_INVALID_FUNCTION) {
            printf("Cannot access UEFI (are you running BIOS?)\n");
            exit(-1);
        }
        else if (GetLastError() == ERROR_NOACCESS) {
            // Expected
        }
        else {
            PrintError(GetLastError());
            exit(GetLastError());
        }
    }
}

int read_efi_variable(const char* name, uint16_t** data) {
    // Windows does not allocate memory for it so we have to do it
    uint16_t* res = (uint16_t *)malloc(sizeof(uint16_t)* 1024);
    int data_size = GetFirmwareEnvironmentVariable(
        ___T(name),
        ___T(EFI_GLOBAL_VARIABLE),
        res,
        sizeof(uint16_t)* 1024);
    if (data_size) {
        *data = res;
        return data_size / 2;
    }
    else {
        PrintError(GetLastError());
        exit(GetLastError());
    }
}

int set_efi_variable(const char* name, uint16_t num) {
    // Let's try to set the BootNext to DWORD 3 (Linux)
    int res = SetFirmwareEnvironmentVariable(
        ___T(name),
        ___T(EFI_GLOBAL_VARIABLE),
        (PVOID)&num,
        sizeof(uint16_t));
    if (res) {
        return res;
    }
    else {
        PrintError(GetLastError());
        exit(GetLastError());
    }
}

int set_boot_next(uint16_t num) {
    return set_efi_variable("BootNext", num);
}

int boot_entry_list(uint16_t** list) {
    uint16_t *data = NULL;
    int length = read_efi_variable("BootOrder", &data);
    *list = data;
    return length;
}

char* boot_entry_name(uint16_t id) {
    char buffer[9];
    uint16_t *data = NULL;
    int length, i;
    char* name = (char *)malloc(64 * sizeof(char));
    sprintf_s(buffer, 9, "Boot%04x", id);
    length = read_efi_variable(buffer, &data);
    for (i = 3; i < length; i++) {
        if (data[i] == 0) break;
        name[i - 3] = data[i];
    }
    name[i - 3] = 0;
    return name;
}
