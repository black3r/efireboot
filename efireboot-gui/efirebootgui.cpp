#include "efirebootgui.h"
#include "ui_efirebootgui.h"

EfiRebootGUI::EfiRebootGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EfiRebootGUI)
{
    ui->setupUi(this);
}

EfiRebootGUI::~EfiRebootGUI()
{
    delete ui;
}
