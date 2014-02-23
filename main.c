#include <stdio.h>
#include <stdint.h>
#include "efi.h"

int main()
{    
    uint16_t *data;
    int l, i;
    data = NULL;
    efi_init();
    l = boot_entry_list(&data);
    for (i = 0; i < l; i++) {
        printf("%s\n", boot_entry_name(data[i]));
    }

    return 0;
}

