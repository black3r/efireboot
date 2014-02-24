#include <unistd.h>
#include <sys/reboot.h>

void reboot_init() {

}

void do_reboot() {
//    reboot(RB_AUTOBOOT);
    system("reboot");
}
