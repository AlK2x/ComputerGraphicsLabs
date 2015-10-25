#include "insertrowdialog.h"
#include "ui_insertrowdialog.h"

InsertRowDialog::InsertRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertRowDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(onAccepted()));
    connect(ui->editName, SIGNAL(textEdited(QString)), this, SLOT(onNameChanged(QString)));
    connect(ui->editValue, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
}

InsertRowDialog::~InsertRowDialog()
{
    delete ui;
}

void InsertRowDialog::onAccepted()
{
    emit rowReady(ui->editName->text(), ui->editValue->value());
}

void InsertRowDialog::onNameChanged(QString name)
{
    bool isCorrect = isNameCorrect(name) && isValueCorrect(ui->editValue->value());
    isCorrect ? ui->buttonBox->setDisabled(false) : ui->buttonBox->setDisabled(true);
}

void InsertRowDialog::onValueChanged(int value)
{
    bool isCorrect = isNameCorrect(ui->editName->text()) && isValueCorrect(value);
    isCorrect ? ui->buttonBox->setDisabled(false) : ui->buttonBox->setDisabled(true);
}

bool InsertRowDialog::isNameCorrect(QString name)
{
    return name.length() > 0 && name.length() < 20;
}

bool InsertRowDialog::isValueCorrect(int value)
{
    return value > 0 && value < 10000;
}
