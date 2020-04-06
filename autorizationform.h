#ifndef AUTORIZATIONFORM_H
#define AUTORIZATIONFORM_H

#include <QWidget>
#include "user.h"
#include "datebase.h"
#include "registrationform.h"

namespace Ui {
class AutorizationForm;
}

class AutorizationForm : public QWidget
{
    Q_OBJECT

public:
    explicit AutorizationForm(QWidget *parent = nullptr);
    void setDatebase(Datebase *db);
    ~AutorizationForm();

signals:
    void autorizationOk(User);

private slots:
    void on_enterButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::AutorizationForm *ui;
    Datebase *datebase;
    RegistrationForm *regForm;
};

#endif // AUTORIZATIONFORM_H
