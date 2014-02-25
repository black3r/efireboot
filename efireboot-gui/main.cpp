#include "efirebootgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EfiRebootGUI w;
    w.show();

    return a.exec();
}
