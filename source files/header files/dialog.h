#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialog.h"
#include "QtWidgets/QLineEdit"
#include "QtWidgets/QLabel"
#include "QtWidgets/QComboBox"
#include "QtWidgets/QRadioButton"
#include "QtWidgets/QSpinBox"
#include "QVBoxLayout"
#include "QIcon"
#include "QString"
#include "QtSql"

class Dialog : public QDialog, private Ui::Dialog
{
    Q_OBJECT


public:
    QLineEdit * _line;
    QRadioButton * _radio1;
    QRadioButton * _radio2;
    QLabel * _label1;
    QLabel * _label2;
    QLabel * _label3;
    QLabel * _label4;
    QComboBox * _combo1;
    QComboBox * _combo2;
    QComboBox * _combo3;
    QSqlQueryModel * _model1;
    QSqlQueryModel * _model2;
    QSqlQueryModel * _model3;
    QSpinBox * _spin;
    QVBoxLayout * _vLayout;

    Dialog(QWidget *parent = nullptr);
    //удаление блюда
    Dialog(QString label1, QWidget *parent = nullptr);
    //добавление, обновление, удаление совместимости
    Dialog(QString label1, QString label2, QWidget *parent = nullptr, bool isAdd = false, bool isDel = false);
    //добавление блюда, обновление совместимости
    Dialog(QString label1, QString label2, QString label3, QWidget *parent = nullptr);
    //обновление блюда
    Dialog(QString label1, QString label2, QString label3, QString label4, QWidget *parent = nullptr);
signals:


private slots:
    //заполнение всех полей информацией о выбранном блюде (окно изменения блюда)
    void GetCurrentDishParams();
    //заполнение выподающего списка блюдами, которые могут быть совместимы с выделенным блюдом
    void GetComAdd();
    //заполнение выподающего списка блюдами, которые совместимы с выделенным блюдом
    void GetCom();
    //выбор радиокнопки, которая соответствует выбранной совместимости
    void GetRadio();
};

#endif // DIALOG_H
