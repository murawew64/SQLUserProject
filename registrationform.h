#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include "datebase.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    void setDatebase(Datebase *db);
    ~RegistrationForm();

private slots:
    void on_closeButton_clicked();

    void on_regButton_clicked();

private:
    Ui::RegistrationForm *ui;
    Datebase *datebase;
};

#endif // REGISTRATIONFORM_H
