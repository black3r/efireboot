#ifndef EFIREBOOTGUI_H
#define EFIREBOOTGUI_H

#include <QDialog>

namespace Ui {
class EfiRebootGUI;
}

class EfiRebootGUI : public QDialog
{
    Q_OBJECT

public:
    explicit EfiRebootGUI(QWidget *parent = 0);
    ~EfiRebootGUI();

private:
    Ui::EfiRebootGUI *ui;
};

#endif // EFIREBOOTGUI_H
