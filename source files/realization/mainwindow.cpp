#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    setupUi(this);
    setWindowIcon(QIcon("D:\\qt_projects\\Healthy_eating\\icon.png"));
    setWindowTitle("Здоровое питание");

    connect(&_upW, &UpdateWindow::GetMainWin, this, &MainWindow::OpenMainWin);
    _db = new Db(this);
    AddToolBarItems();
}

void MainWindow::AddToolBarItems()
{
    QPixmap add("D:\\qt_projects\\Healthy_eating\\add.png");
    QPixmap update("D:\\qt_projects\\Healthy_eating\\update.png");
    mainToolBar->addAction(QIcon(add), "Сгенерировать меню на день", this, &MainWindow::GenerateMenu);
    mainToolBar->addAction(QIcon(update), "Редактор блюд и совместимостей", this, &MainWindow::OpenUpdateWin);
}

void MainWindow::OpenUpdateWin()
{
    _upW.setGeometry(geometry().x(), geometry().y(), geometry().width(), geometry().height());
    _upW.show();
    hide();
}

void MainWindow::OpenMainWin(int x, int y, int w, int h)
{
    setGeometry(x, y, w, h);
    show();
    _upW.close();
}

void MainWindow::GenerateMenu()
{
    if(_db->IsOpen())
    {
        listWidget->clear();
        listWidget_2->clear();
        listWidget_3->clear();
        qDebug() << "Breakfast";
        GenerateBreakfast();
        listWidget->addItems(_list);
        label_4->setText("Количество калорий:" + QString::number(_db->GetSumCaliries(_list)));
        _list.clear();
        qDebug() << "Lunch";
        GenerateLunch();
        listWidget_2->addItems(_list);
        label_5->setText("Количество калорий:" + QString::number(_db->GetSumCaliries(_list)));
        _list.clear();
        qDebug() << "Dinner";
        GenerateDinner();
        listWidget_3->addItems(_list);
        label_6->setText("Количество калорий:" + QString::number(_db->GetSumCaliries(_list)));
        _list.clear();
    }
    else
        QMessageBox::warning(this, "Ошибка","Необходимо открыть базу данных");
}

bool MainWindow::GenerateBreakfast()
{
    //выбираем основное или гарнир
    QStringList list;
    if(HeadsandTails() == 1)
        _db->GetItems("Основное", list);
    else
        _db->GetItems("Гарнир", list);
    QString dish1 = _db->GetComDish(list);
    if(dish1 != "")
        _list.append(dish1);
    else
    {
        QMessageBox::warning(this, "Ошибка","Не хватает блюд в базе данных: гарнира или основного");
        return false;
    }

    //выбираем напиток
    list.clear();
    _db->GetItems("Напиток", list);
    QString dish2 = _db->GetComDish(list, dish1);
    if(dish2 != "")
        _list.append(dish2);
    else
    {
        QMessageBox::warning(this, "Ошибка","Не хватает блюд в базе данных: напитка");
        return false;
    }

    //выбираем дополнение (необязательно наличие)
    list.clear();
    _db->GetItems("Дополнение", list);
    QString dish3 = _db->GetComDish(list, dish1, dish2);
    if(dish3 != "")
        _list.append(dish3);
    return true;
}

bool MainWindow::GenerateLunch()
{
    //выбираем основное мясное+гарнир или основное
    QStringList list;
    QString dish1_1;
    QString dish1_2 = "";
    QString dish2;
    QString dish3;
    if(HeadsandTails() == 1)
    {
        _db->GetItems("Основное", list);
        dish1_1 = _db->GetComDish(list);
    }
    else
    {
        _db->GetItems("Мясное основное", list);
        dish1_1 = _db->GetComDish(list);
        list.clear();
        _db->GetItems("Гарнир", list);
        dish1_2 = _db->GetComDish(list, dish1_1);
    }

    if((dish1_1 != "") && (dish1_2 != ""))
    {
        _list.append(dish1_1);
        _list.append(dish1_2);
    }
    else if(dish1_1 != "")
        _list.append((dish1_1));
    else
    {
        QMessageBox::warning(this, "Ошибка","Не хватает блюд в базе данных: основного мясного+гарнира или основного");
        return false;
    }

    //выбираем суп
    list.clear();
    _db->GetItems("Суп", list);
    if(dish1_2 == "")
        dish2 = _db->GetComDish(list, dish1_1);
    else
        dish2 = _db->GetComDish(list, dish1_1, dish1_2);
    if(dish2 != "")
        _list.append(dish2);
    else
    {
        QMessageBox::warning(this, "Ошибка","Не хватает блюд в базе данных: супа");
        return false;
    }

    //выбираем напиток
    list.clear();
    _db->GetItems("Напиток", list);
    if(dish1_2 == "")
        dish3 = _db->GetComDish(list, dish1_1, dish2);
    else
        dish3 = _db->GetComDish(list, dish1_1, dish1_2, dish2);
    if(dish3 != "")
        _list.append(dish3);
    else
    {
        QMessageBox::warning(this, "Ошибка","Не хватает блюд в базе данных: напитка");
        return false;
    }
    return true;
}

bool MainWindow::GenerateDinner()
{
    //выбираем основное мясное+гарнир или основное
    QStringList list;
    QString dish1_1;
    QString dish1_2 = "";
    QString dish2;
    QString dish3;
    if(HeadsandTails() == 1)
    {
        _db->GetItems("Основное", list);
        dish1_1 = _db->GetComDish(list);
    }
    else
    {
        _db->GetItems("Мясное основное", list);
        dish1_1 = _db->GetComDish(list);
        list.clear();
        _db->GetItems("Гарнир", list);
        dish1_2 = _db->GetComDish(list, dish1_1);
    }

    if((dish1_1 != "") && (dish1_2 != ""))
    {
        _list.append(dish1_1);
        _list.append(dish1_2);
    }
    else if(dish1_1 != "")
        _list.append((dish1_1));
    else
    {
        QMessageBox::warning(this, "Ошибка","Не хватает блюд в базе данных: основного мясного+гарнира или основного");
        return false;
    }

    //выбираем напиток
    list.clear();
    _db->GetItems("Напиток", list);
    if(dish1_2 == "")
        dish2 = _db->GetComDish(list, dish1_1);
    else
        dish2 = _db->GetComDish(list, dish1_1, dish1_2);
    if(dish2 != "")
        _list.append(dish2);
    else
    {
        QMessageBox::warning(this, "Ошибка","Не хватает блюд в базе данных: напитка");
        return false;
    }

    //выбираем дополнение (необязательно наличие)
    list.clear();
    _db->GetItems("Дополнение", list);
    if(dish1_2 == "")
        dish3 = _db->GetComDish(list, dish1_1, dish2);
    else
        dish3 = _db->GetComDish(list, dish1_1, dish1_2, dish2);
    if(dish3 != "")
        _list.append(dish3);
    return true;
}

char MainWindow::HeadsandTails()
{
  //  qsrand(QDateTime::currentMSecsSinceEpoch());
    return (qrand() % 2 + 1);
}
