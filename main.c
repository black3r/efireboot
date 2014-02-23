#include <stdio.h>
#include <stdint.h>
#include "efi.h"

int main()
{    
    uint16_t *data;
    int l, i, c;
    data = NULL;
    efi_init();
    l = boot_entry_list(&data);
    for (i = 0; i < l; i++) {
        printf("%d: %s\n", i, boot_entry_name(data[i]));
    }
    printf("Input your choice: ");
    scanf("%d", &c);
    if (c < 0 || c >= l) {
        printf("ERROR: Invalid choice\n");
        exit(-1);
    }
    set_boot_next(data[c]);
    printf("Set next boot target to: %s\n", boot_entry_name(data[c]));

    return 0;
}

