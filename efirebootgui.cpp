#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include "efi.h"
#include "reboot.h"
#include <cstdint>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDialog w;
    w.setWindowTitle("Reboot into:");
    QVBoxLayout layout;
    efi_init();
    reboot_init();
    uint16_t *data;
    int l = boot_entry_list(&data);
    for (int i = 0; i < l; i++) {
        QPushButton *button = new QPushButton(QString(boot_entry_name(data[i])));
        layout.addWidget(button);
        button->connect(button, &QPushButton::clicked, [=]() {
            set_boot_next(data[i]);
            do_reboot();
        });
    }
    w.setLayout(&layout);
    w.show();
    return a.exec();
}
