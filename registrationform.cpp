#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

void RegistrationForm::setDatebase(Datebase *db)
{
    datebase = db;
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_closeButton_clicked()
{
    this->close();
}

void RegistrationForm::on_regButton_clicked()
{
    QString login = ui->loginEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if(login.isEmpty() || password.isEmpty()){
        ui->errorLabel->setText("*Enter login and password");
        return;
    }

    datebase->queryInsertUser(login, password, 1);
    ui->errorLabel->setText("*You succesfully registrated");
}
