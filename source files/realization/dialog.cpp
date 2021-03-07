#include "dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    qDebug() << QSqlDatabase::connectionNames();
}

//удаление блюда
Dialog::Dialog(QString label1, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    _label1 = new QLabel(label1, this);
    _combo1 = new QComboBox(this);
    _model1 = new QSqlQueryModel(this);
    QString query = "SELECT dish FROM DISHES";
    _model1->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
    _combo1->setModel(_model1);

    _vLayout = new QVBoxLayout(this);
    _vLayout->addWidget(_label1);
    _vLayout->addWidget(_combo1);
    _vLayout->addStretch();
    _vLayout->addWidget(buttonBox);
}

//добавление, обновление, удаление совместимости
Dialog::Dialog(QString label1, QString label2, QWidget *parent, bool isAdd, bool isDel) :
    QDialog(parent)
{
    setupUi(this);
    _model1 = new QSqlQueryModel(this);
    _model2 = new QSqlQueryModel(this);
    _label1 = new QLabel(label1, this);
    _combo1 = new QComboBox(this);
    QString query = "SELECT dish FROM dishes";
    _model1->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
    _combo1->setModel(_model1);

    _label2 = new QLabel(label2 ,this);
    _combo2 = new QComboBox(this);
    _combo2->setModel(_model2);

    _radio1 = new QRadioButton("Положительная совместимость", this);
    _radio2 = new QRadioButton("Отрицательная совместимость", this);
    _vLayout = new QVBoxLayout(this);
    _radio1->setChecked(true);
    _vLayout->addWidget(_label1);
    _vLayout->addWidget(_combo1);
    _vLayout->addWidget(_label2);
    _vLayout->addWidget(_combo2);
    _vLayout->addWidget(_radio1);
    _vLayout->addWidget(_radio2);
    _vLayout->addStretch();
    _vLayout->addWidget(buttonBox);
    if(isAdd)
    {
        connect(_combo1, &QComboBox::currentTextChanged, this, &Dialog::GetComAdd);
        GetComAdd();
    }
    else
    {
        connect(_combo1, &QComboBox::currentTextChanged, this, &Dialog::GetCom);
        connect(_combo2, &QComboBox::currentTextChanged, this, &Dialog::GetRadio);
        GetCom();
    }
    if(isDel)
    {
        _radio1->setDisabled(true);
        _radio2->setDisabled(true);
    }
}

//добавление блюда, обновление совместимости
Dialog::Dialog(QString label1, QString label2, QString label3, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    _label1 = new QLabel(label1, this);
    _combo1 = new QComboBox(this);
    _model1 = new QSqlQueryModel(this);
    QString queryStr;
    _label2 = new QLabel(label2, this);
    _vLayout = new QVBoxLayout(this);
    _vLayout->addWidget(_label1);
    _vLayout->addWidget(_combo1);
    _vLayout->addWidget(_label2);
    queryStr = "SELECT type FROM TYPES";
    _line = new QLineEdit(this);
    _label3 = new QLabel(label3, this);
    _spin = new QSpinBox(this);
    _spin->setRange(0, 20000);
    _vLayout->addWidget(_line);
    _vLayout->addWidget(_label3);
    _vLayout->addWidget(_spin);

    _model1->setQuery(QSqlQuery(queryStr, QSqlDatabase::database("line")));
    _combo1->setModel(_model1);

    _vLayout->addStretch();
    _vLayout->addWidget(buttonBox);
}

//обновление блюда
Dialog::Dialog(QString label1, QString label2, QString label3, QString label4, QWidget *parent):
    QDialog(parent)
{
    setupUi(this);
    _label1 = new QLabel(label1, this);
    _combo1 = new QComboBox(this);
    _model1 = new QSqlQueryModel(this);
    QString queryStr = "SELECT dish FROM dishes";
    _model1->setQuery(QSqlQuery(queryStr, QSqlDatabase::database("line")));
    _combo1->setModel(_model1);
    _label2 = new QLabel(label2, this);
    _combo2 = new QComboBox(this);
    _model2 = new QSqlQueryModel(this);
    queryStr = "SELECT type FROM types";
    _model2->setQuery(QSqlQuery(queryStr, QSqlDatabase::database("line")));
    _combo2->setModel(_model2);
    connect(_combo1, &QComboBox::currentTextChanged, this, &Dialog::GetCurrentDishParams);
    _label3 = new QLabel(label3, this);
    _line = new QLineEdit(this);
    _label4 = new QLabel(label4, this);
    _spin = new QSpinBox(this);
    _spin->setRange(0, 20000);
    _vLayout = new QVBoxLayout(this);
    _vLayout->addWidget(_label1);
    _vLayout->addWidget(_combo1);
    _vLayout->addWidget(_label2);
    _vLayout->addWidget(_combo2);
    _vLayout->addWidget(_label3);
    _vLayout->addWidget(_line);
    _vLayout->addWidget(_label4);
    _vLayout->addWidget(_spin);
    _vLayout->addStretch();
    _vLayout->addWidget(buttonBox);
    GetCurrentDishParams();
}

void Dialog::GetCurrentDishParams()
{
    QString queryStr = "SELECT * FROM dishes WHERE dish = '"+_combo1->currentText()+"';";
    QSqlQuery query(queryStr, QSqlDatabase::database("line"));
    if(query.next())
    {
        _combo2->setCurrentIndex(_combo2->findText(query.value(3).toString()));
        _line->setText(query.value(1).toString());
        _spin->setValue(query.value(2).toInt());
    }
}

void Dialog::GetComAdd()
{
    QString dish = _combo1->currentText();
    QString query = "SELECT dish FROM dishes "
                    "WHERE NOT iddish IN ("
                    "SELECT iddish FROM dishes WHERE dish = '"+dish+"') "
                    "AND NOT type IN ("
                    "SELECT type FROM dishes WHERE dish = '"+dish+"') "
                    "AND NOT iddish IN ("
                    "SELECT iddish FROM COMPATIBILITY WHERE DISH_COMPATIBILITY = '"+dish+"') "
                    "AND NOT iddish IN ("
                    "SELECT iddish FROM INCOMPATIBILITY WHERE DISH_INCOMPATIBILITY = '"+dish+"');";
    _model2->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
}


void Dialog::GetCom()
{
    QString dish = _combo1->currentText();
    QString query = "SELECT DISH_COMPATIBILITY FROM COMPATIBILITY "
                    "WHERE iddish = ("
                    "SELECT iddish FROM dishes WHERE dish = '"+dish+"') "
                    "UNION "
                    "SELECT DISH_INCOMPATIBILITY FROM INCOMPATIBILITY "
                    "WHERE iddish = ("
                    "SELECT iddish FROM dishes WHERE dish = '"+dish+"');";
    _model2->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
}

void Dialog::GetRadio()
{
    QString com = _combo2->currentText();
    QString dish = _combo1->currentText();
    QSqlQuery query ("SELECT DISH_COMPATIBILITY FROM COMPATIBILITY WHERE DISH_COMPATIBILITY = '"+com+"' "
                     "AND iddish = (SELECT iddish FROM dishes WHERE dish = '"+dish+"');", QSqlDatabase::database("line"));
    query.last();
    if(query.at() == 0)
        _radio1->setChecked(true);
    else
        _radio2->setChecked(true);

}
