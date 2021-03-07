#include "db.h"


Db::~Db()
{
    CloseDB();
    qDebug() << "db system is close";
}

Db::Db(QWidget *parent):
    QObject (parent)
{}

bool Db::SetDb(QString path)
{
    CloseDB();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE", "line");
    db.setHostName("hostmenu1");
    db.setDatabaseName(path);
    db.setUserName("admin");
    db.setPassword("admin");
    if(!db.open())
    {
        qDebug() << "false - open";
        return false;
    }
    else
        qDebug() << "true - open";
    QSqlQuery _query(db);
    _maxDishId = -1;
    if(db.tables().isEmpty())
    {
        qDebug() << _query.exec("CREATE TABLE TYPES("
                        "  TYPE VARCHAR (25)   NOT NULL,"
                        " PRIMARY KEY (TYPE)"
                        ");") << " - create tab TYPES";
        qDebug() << _query.exec("INSERT INTO types (type)"
                                "VALUES ('Суп');") << " - add to TYPES";
        qDebug() << _query.exec("INSERT INTO types (type)"
                                "VALUES ('Основное');") << " - add to TYPES";
        qDebug() << _query.exec("INSERT INTO types (type)"
                                "VALUES ('Гарнир');") << " - add to TYPES";
        qDebug() << _query.exec("INSERT INTO types (type)"
                                "VALUES ('Напиток');") << " - add to TYPES";
        qDebug() << _query.exec("INSERT INTO types (type)"
                                "VALUES ('Дополнение');") << " - add to TYPES";
        qDebug() << _query.exec("INSERT INTO types (type)"
                                "VALUES ('Мясное основное');") << " - add to TYPES";

        qDebug() << _query.exec("CREATE TABLE DISHES("
                                "IDDISH  INTEGER  NOT NULL,"
                                "DISH  VARCHAR(25)  NOT NULL,"
                                "CALORIES  INTEGER  NOT NULL,"
                                "TYPE  VARCHAR(25)  NOT NULL,"
                                "PRIMARY KEY (IDDISH, DISH),"
                                "FOREIGN KEY (TYPE) REFERENCES TYPES(TYPE)"
                                ");") << " - create tab DISHES";
        qDebug() << _query.exec("CREATE TABLE COMPATIBILITY("
                        "  IDDISH   INTEGER      NOT NULL,"
                        "  DISH_COMPATIBILITY VARCHAR (25)   NOT NULL,"
                        "  FOREIGN KEY (DISH_COMPATIBILITY) REFERENCES DISHES(DISH),"
                        "  FOREIGN KEY (IDDISH) REFERENCES DISHES(IDDISH)"
                        ");") << " - create tab COMPATIBILITY";
        qDebug() << _query.exec("CREATE TABLE INCOMPATIBILITY("
                        "  IDDISH   INTEGER      NOT NULL,"
                        "  DISH_INCOMPATIBILITY VARCHAR (25)   NOT NULL,"
                        "  FOREIGN KEY (DISH_INCOMPATIBILITY) REFERENCES DISHES(DISH),"
                        "  FOREIGN KEY (IDDISH) REFERENCES DISHES(IDDISH)"
                        ");") << " - create tab INCOMPATIBILITY";
        return true;
    }

    _query.exec("SELECT iddish FROM DISHES");
    if(!db.tables().isEmpty() && _query.at() != -2)
    {
        _query.last();
        _maxDishId = _query.value(0).toInt();
        qDebug() << _maxDishId << " - max index of Dishes";
    }
    else
        qDebug() << "DB is empty";
    return true;
}

void Db::CloseDB()
{
    if(QSqlDatabase::database("line").isOpen())
    {
        QSqlDatabase::database("line").close();
        QSqlDatabase::removeDatabase("line");
    }
}

bool Db::AddDish(QString dish, int calories, QString type)
{
    if((dish != "") && (type != ""))
    {
        qDebug() << dish+' ' << calories << ' '+type+' ' << " iddish:" << _maxDishId+1;
        QSqlQuery _query(QSqlDatabase::database("line"));
        bool r = _query.exec("INSERT INTO dishes "
                             "VALUES ("+QString::number(_maxDishId+1)+",'"+dish+"',"+QString::number(calories)+",'"+type+"');");
        qDebug() << r  << " - Add dish";
        if(r)
        {
            _maxDishId++;
        }
        return r;
    }
    else
        return false;
}

bool Db::IsOpen()
{
    if(QSqlDatabase::database("line").isOpen())
        return true;
    else
        return false;
}

bool Db::UpdateDish(QString lastname, QString newname, int newcalories, QString newtype)
{
    if((lastname != "") && (newname != "") && (newtype != ""))
    {
        qDebug() << lastname << newname << newcalories << newtype;
        QSqlQuery query(QSqlDatabase::database("line"));
        bool r1 = query.exec("UPDATE Dishes "
                             "SET dish = '"+newname+"', "
                             "calories = "+QString::number(newcalories)+", "
                             "type = '"+newtype+"' "
                             "WHERE dish = '"+lastname+"';");
        qDebug()  << r1 << "1/3";
        bool r2 = query.exec("UPDATE COMPATIBILITY "
                             "SET DISH_COMPATIBILITY = '"+newname+"' "
                             "WHERE DISH_COMPATIBILITY = '"+lastname+"';");
        qDebug()  << r2 << "2/3";
        bool r3 = query.exec("UPDATE INCOMPATIBILITY "
                             "SET DISH_INCOMPATIBILITY = '"+newname+"' "
                             "WHERE DISH_INCOMPATIBILITY = '"+lastname+"';");
        qDebug()  << r3 << "3/3";
        qDebug() << (r1&&r2&&r3)  << " - Update dish";
        return (r1&&r2&&r3);
    }
    else
        return false;
}

bool Db::DelDish(QString dish)
{
    if(dish != "")
    {
        qDebug() << dish;
        QSqlQuery query(QSqlDatabase::database("line"));
        bool r1 = query.exec("DELETE FROM COMPATIBILITY "
                             "WHERE iddish = ("
                             "SELECT iddish FROM dishes WHERE dish = '"+dish+"');");
        qDebug()  << r1 << "1/5";
        bool r2 = query.exec("DELETE FROM INCOMPATIBILITY "
                             "WHERE iddish = ("
                             "SELECT iddish FROM dishes WHERE dish = '"+dish+"');");
        qDebug()  << r2 << "2/5";
        bool r3 = query.exec("DELETE FROM COMPATIBILITY "
                             "WHERE DISH_COMPATIBILITY = '"+dish+"';");
        qDebug()  << r3 << "3/5";
        bool r4 = query.exec("DELETE FROM INCOMPATIBILITY "
                             "WHERE DISH_INCOMPATIBILITY = '"+dish+"';");
        qDebug()  << r4 << "4/5";
        bool r5 = query.exec("DELETE FROM dishes "
                             "WHERE dish = '"+dish+"';");
        qDebug()  << r5 << "5/5";
        qDebug() << (r1&&r2&&r3&&r4&&r5)  << " - Delete dish";
        return (r1&&r2&&r3&&r4&&r5);
    }
    else
        return false;
}

bool Db::AddCom(QString table, QString newcom, QString parentDish)
{
    if((table != "") && (newcom != "") && (parentDish != ""))
    {
        qDebug() << table << parentDish << newcom;
        QSqlQuery query(QSqlDatabase::database("line"));
        bool r1 = query.exec("INSERT INTO "+table+" "
                             "VALUES ("
                             "(SELECT iddish FROM dishes WHERE dish = '" +parentDish+"'),"
                             " '"+newcom+"');");
        qDebug()  << r1 << "1/2";
        bool r2 = query.exec("INSERT INTO "+table+" "
                             "VALUES ("
                             "(SELECT iddish FROM dishes WHERE dish = '" +newcom+"'),"
                             " '"+parentDish+"');");
        qDebug()  << r2 << "2/2";
        qDebug() << (r1&&r2)  << " - Add com";
        return (r1&&r2);
    }
    else
        return false;
}

bool Db::UpdateCom(QString dish, QString com, bool isCom)
{
    if((dish != "") && (com != ""))
    {
        qDebug() << isCom << "- isCom";
        QSqlQuery query(QSqlDatabase::database("line"));
        bool r1 = DelCom(dish, com);
        bool r2;
        bool r3;
        if(isCom)
        {
            r2 = query.exec("INSERT INTO COMPATIBILITY "
                            "VALUES ((SELECT iddish FROM dishes WHERE dish = '"+dish+"'),"
                            " '"+com+"');");
            r3 = query.exec("INSERT INTO COMPATIBILITY "
                            "VALUES ((SELECT iddish FROM dishes WHERE dish = '"+com+"'),"
                            " '"+dish+"');");
        }
        else
        {
            r2 = query.exec("INSERT INTO INCOMPATIBILITY "
                            "VALUES ((SELECT iddish FROM dishes WHERE dish = '"+dish+"'),"
                            " '"+com+"');");
            r3 = query.exec("INSERT INTO INCOMPATIBILITY "
                            "VALUES ((SELECT iddish FROM dishes WHERE dish = '"+com+"'),"
                            " '"+dish+"');");
        }
        qDebug()  << r1 << "1/3";
        qDebug()  << r2 << "2/3";
        qDebug()  << r3 << "3/3";
        qDebug() << (r1&&r2&&r3)  << " - Apt com";
        return (r1&&r2&&r3);
    }
    else
        return false;
}

bool Db::DelCom(QString dish, QString com)
{
    if((dish != "") && (com != ""))
    {
        qDebug() << dish << com;
        QSqlQuery query(QSqlDatabase::database("line"));

        bool r1 = query.exec("DELETE FROM COMPATIBILITY "
                             "WHERE iddish = ("
                             "SELECT iddish FROM dishes WHERE dish = '"+dish+"') "
                                                                             "AND DISH_COMPATIBILITY = '"+com+"';");
        qDebug()  << r1 << "1/4";
        bool r2 = query.exec("DELETE FROM INCOMPATIBILITY "
                             "WHERE iddish = ("
                             "SELECT iddish FROM dishes WHERE dish = '"+dish+"') "
                                                                             "AND DISH_INCOMPATIBILITY = '"+com+"';");
        qDebug()  << r2 << "2/4";
        bool r3 = query.exec("DELETE FROM COMPATIBILITY "
                             "WHERE iddish = ("
                             "SELECT iddish FROM dishes WHERE dish = '"+com+"') "
                                                                            "AND DISH_COMPATIBILITY = '"+dish+"';");
        qDebug()  << r3 << "3/4";
        bool r4 = query.exec("DELETE FROM INCOMPATIBILITY "
                             "WHERE iddish = ("
                             "SELECT iddish FROM dishes WHERE dish = '"+com+"') "
                                                                            "AND DISH_INCOMPATIBILITY = '"+dish+"';");
        qDebug()  << r4 << "4/4";
        qDebug() << (r1&&r2&&r3&&r4) << " - Del com";
        return (r1&&r2&&r3&&r4);
    }
    else
        return false;
}

QString Db::GetComDish(QStringList list, QString dish1, QString dish2, QString dish3)
{
    QSqlQuery query(QSqlDatabase::database("line"));
    QStringList thebest;
    if(dish1 != "")
    {
        foreach(QString str, list)
            if(IsIncom(str, dish1))
                list.removeOne(str);
    }
    if(dish2 != "")
    {
        foreach(QString str, list)
            if(IsIncom(str, dish2))
                list.removeOne(str);
    }
    if(dish3 != "")
    {
        foreach(QString str, list)
            if(IsIncom(str, dish3))
                list.removeOne(str);
    }
    if(dish1 != "")
    {
        foreach(QString str, list)
            if(IsCom(str, dish1))
                thebest.append(str);
    }
    if(dish2 != "")
    {
        foreach(QString str, list)
            if(IsCom(str, dish2))
                thebest.append(str);
    }
    if(dish3 != "")
    {
        foreach(QString str, list)
            if(IsCom(str, dish3))
                thebest.append(str);
    }

    thebest.removeDuplicates();
    qDebug() << "--------";
    qDebug() << list << "- допустимые блюда";
    qDebug() << thebest << "- совместимые блюда";


    if(!thebest.isEmpty())
        return thebest.at(randomBetween(0, thebest.size()-1));
    else if(!list.isEmpty())
        return list.at(randomBetween(0, list.size()-1));
    else
        return "";
}

void Db::GetItems(QString type, QStringList &list)
{
    QSqlQuery query("SELECT dish FROM dishes WHERE type = '"+type+"';", QSqlDatabase::database("line"));
    while(query.next())
    {
        list.append(query.value(0).toString());
    }
}

int Db::randomBetween(int low, int high)
{
    //qsrand(QDateTime::currentMSecsSinceEpoch());
    return (qrand() % ((high + 1) - low) + low);
}

bool Db::IsIncom(QString dish1, QString dish2)
{
    QSqlQuery query("SELECT DISH_INCOMPATIBILITY FROM INCOMPATIBILITY "
                    "WHERE iddish = ("
                    "SELECT iddish FROM dishes WHERE dish = '"+dish2+"') "
                    "AND DISH_INCOMPATIBILITY = '"+dish1+"';", QSqlDatabase::database("line"));
    if(query.next())
        return true;
    else
        return false;
}

bool Db::IsCom(QString dish1, QString dish2)
{
    QSqlQuery query("SELECT DISH_COMPATIBILITY FROM COMPATIBILITY "
                    "WHERE iddish = ("
                    "SELECT iddish FROM dishes WHERE dish = '"+dish2+"') "
                    "AND DISH_COMPATIBILITY = '"+dish1+"';", QSqlDatabase::database("line"));
    if(query.next())
        return true;
    else
        return false;
}

int Db::GetSumCaliries(QStringList list)
{
    int c = 0;
    QSqlQuery query(QSqlDatabase::database("line"));
    foreach(QString str, list)
    {
        query.exec("SELECT calories FROM dishes WHERE dish = '"+str+"';");
        if(query.next())
            c += query.value(0).toInt();
        else
            return 0;
    }
    return c;
}
