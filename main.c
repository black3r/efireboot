#include <stdio.h>
#include "efi.h"

int main()
{
    uint16_t *data = NULL;
    int l = boot_entry_list(&data);
    int i;
    for (i = 0; i < l; i++) {
        printf("%s\n", boot_entry_name(data[i]));
    }

    return 0;
}

