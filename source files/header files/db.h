#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql>
#include <QListView>
#include "QString"

class Db: public QObject
{
    Q_OBJECT

    //Закрытие бд
    void CloseDB();
    //максимальный id бд нужен для добавлениянового элемента
    int _maxDishId;
    //рандомное чсло между...
    int randomBetween(int low, int high);

public:
    //создание/открытие бд
    bool SetDb(QString path);
    Db(QWidget *parent = nullptr);
    ~Db();
    //добавление блюда
    bool AddDish(QString dish, int calories, QString type);
    //добавление совместимости
    bool AddCom(QString table, QString newcom, QString parentDish);
    //изменение блюда
    bool UpdateDish(QString lastname, QString newname, int newcalories, QString newtype);
    //изменение совместимости
    bool UpdateCom(QString dish, QString com, bool isCom = false);
    //удаление блюда
    bool DelDish(QString dish);
    //удаление совместимости
    bool DelCom(QString dish, QString com);
    //проверка открыта ли бд
    bool IsOpen();
    //получение случайного наиболее совместимого блюда с переданными блюдами
    QString GetComDish(QStringList list, QString dish1 = "", QString dish2 = "", QString dish3 = "");
    //проверка есть ли совместимость блюд
    bool IsCom(QString dish1, QString dish2);
    //проверка есть ли несовместимость блюд
    bool IsIncom(QString dish1, QString dish2);
    //получение блюд заданного типа
    void GetItems(QString type, QStringList &list);
    //получение суммы калорий блюд из списка
    int GetSumCaliries(QStringList list);
};

#endif // DB_H
