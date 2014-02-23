#include <efivar.h>
#include <string.h>
#include <stdlib.h>

#define EFI_GLOBAL_VARIABLE \
    EFI_GUID( 0x8BE4DF61, 0x93CA, 0x11d2, 0xAA0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C)

void efi_init() {

}

int read_efi_variable(const char* name, uint16_t** data) {
    uint16_t *res = NULL;
    efi_guid_t guid = EFI_GLOBAL_VARIABLE;
    uint32_t attributes = 0;
    size_t data_size = 0;

    int rc;
    rc = efi_get_variable(guid, name, (uint8_t **)&res, &data_size, &attributes);
    if (rc < 0) exit(rc);
    *data = res;
    return data_size / 2;
}

int set_efi_variable(const char* name, uint16_t num) {
    printf("Setting variable\n");
    num &= 0xFFFF;
    return efi_set_variable(
                EFI_GLOBAL_VARIABLE,
                name,
                (uint8_t *) &num,
                sizeof(num),
                EFI_VARIABLE_NON_VOLATILE |
                EFI_VARIABLE_BOOTSERVICE_ACCESS |
                EFI_VARIABLE_RUNTIME_ACCESS);
}

char* boot_entry_name(uint16_t id) {
    char buffer[8];
    sprintf(buffer, "Boot%04x", id);
    uint16_t *data = NULL;
    int length = read_efi_variable(buffer, &data);
    char* name = (char *) malloc(64*sizeof(char));
    int i = 0;
    for (i = 3; i < length; i++) {
        if (data[i] == 0) break;
        name[i-3] = data[i];
    }
    name[i-3] = 0;
    return name;
}

int boot_entry_list(uint16_t **list) {
    uint16_t *data = NULL;
    int length = read_efi_variable("BootOrder", &data);
    *list = data;
    return length;
}

int set_boot_next(uint16_t num) {
    return set_efi_variable("BootNext", num);
}
