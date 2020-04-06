#include "autorizationform.h"
#include "ui_autorizationform.h"
#include <qlineedit.h>

AutorizationForm::AutorizationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutorizationForm)
{
    ui->setupUi(this);
    regForm = new RegistrationForm(this);
    regForm->hide();
}

void AutorizationForm::setDatebase(Datebase *db)
{
    datebase = db;
}

AutorizationForm::~AutorizationForm()
{
    delete ui;
}

void AutorizationForm::on_enterButton_clicked()
{
    QString login = ui->loginEdit->text().trimmed();
    QString password = ui->passwordEdit->text();

    if(login.isEmpty() || password.isEmpty()){
        ui->errorLabel->setText("*Enter login and password");
    }

    int access = datebase->querySelectUser(login, password);

    if(access == 2){
        ui->errorLabel->setText("*You attemp to enter with admin account. Please, use application to admin.");
    }
    else if(access == 1){
        emit autorizationOk(User(1, ui->loginEdit->text()));
        this->close();
    }
    else{
        ui->errorLabel->setText("*Incorrect login or password");
    }
}

void AutorizationForm::on_pushButton_clicked()
{
    regForm->show();
}
