#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "updatewindow.h"
#include "db.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    //окно редактора блюд и совместимостей
    UpdateWindow _upW;
    //модель для работы с бд
    Db * _db;
    //промежуточное хранилище списка сгенерированных блюд
    QStringList _list;

    //настраивает кнопки панели инструментов
    void AddToolBarItems();
    //генерация завтрака
    bool GenerateBreakfast();
    //генерация обеда
    bool GenerateLunch();
    //генерация ужина
    bool GenerateDinner();
    //орёл и решка/получение на рандом 1 или 2
    char HeadsandTails();

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    //открытие окна редактора блюд и совместимостей
    void OpenUpdateWin();
    //открытие текущего окна с заданной геометрии
    void OpenMainWin(int x,int y, int w, int h);
    //генерация рациона питания на день
    void GenerateMenu();
};

#endif // MAINWINDOW_H
