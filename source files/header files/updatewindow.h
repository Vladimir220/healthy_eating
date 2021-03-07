#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include "ui_update_window.h"
#include "dialog.h"
#include "db.h"
#include "QFileDialog"
#include <QMessageBox>
#include "QString"

class UpdateWindow : public QMainWindow, private Ui::UpdateWindow
{
    Q_OBJECT
    //настраивает кнопки панели инструментов
    void AddToolBarItems();
    //модель для работы с бд
    Db * _db;
    //модели для выпадающих списков
    QSqlQueryModel * _model1;
    QSqlQueryModel * _model2;
    QSqlQueryModel * _model3;
    //обновление визуального списка блюд
    void UpdateDishesList();

public:
    explicit UpdateWindow(QWidget *parent = nullptr);

signals:
    //открыть окно генерации с заданной геометрией
    void GetMainWin(int x, int y, int w, int h);

private slots:
    //открыть окно генерации с заданной геометрией
    void ChangeWin();
    //вызов необходимого диалогового окна и добавления блюда
    void AddDish();
    //вызов необходимого диалогового окна и обновление блюда
    void UpdateDish();
    //вызов необходимого диалогового окна и удаление блюда
    void DeleteDish();
    //вызов необходимого диалогового окна и добавление совместимости
    void AddDishCompatibility();
    //вызов необходимого диалогового окна и обновление совместимости
    void UpdateDishCompatibility();
    //вызов необходимого диалогового окна и удаление совместимости
    void DeleteDishCompatibility();
    //создание файла бд
    void CreateMenu();
    //загрузка файла бд
    void SetMenu();
    //обновление визуальных списков совместимостей и несовместимостей
    void UpdateComLists(const QModelIndex &index);
};

#endif // UPDATEWINDOW_H
