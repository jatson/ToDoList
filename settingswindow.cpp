#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    QSettings settings;
    ui->autoSaveCheckBox->setChecked(settings.value("GeneralSettings/AutoSaveEnabled", "false").toBool());
    ui->spinBox->setValue(settings.value("GeneralSettings/AutoSaveMinutes", 0).toInt());
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_autoSaveCheckBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) ui->spinBox->setEnabled(false);
    else if(arg1 == Qt::Checked) ui->spinBox->setEnabled(true);
}

void SettingsWindow::on_okPushButton_clicked()
{
    QSettings settings;
    settings.setValue("GeneralSettings/AutoSaveEnabled", ui->autoSaveCheckBox->checkState());
    settings.setValue("GeneralSettings/AutoSaveMinutes", ui->spinBox->value());
    this->done(QDialog::Accepted);
}
