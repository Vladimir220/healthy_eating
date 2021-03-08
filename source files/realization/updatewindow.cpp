#include "updatewindow.h"

UpdateWindow::UpdateWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    setWindowIcon(QIcon("D:\\qt_projects\\Healthy_eating\\icon.png"));
    setWindowTitle("Здоровое питание -- Редактор блюд и совместимостей");
    AddToolBarItems();
    _db = new Db(this);
    _model1 = new QSqlQueryModel(this);
    _model2 = new QSqlQueryModel(this);
    _model3 = new QSqlQueryModel(this);
    listView->setModel(_model1);
    listView_2->setModel(_model2);
    listView_3->setModel(_model3);
    connect(listView, &QListView::clicked, this, &UpdateWindow::UpdateComLists);
}

void UpdateWindow::ChangeWin()
{
    emit GetMainWin(geometry().x(), geometry().y(), geometry().width(), geometry().height());
}


void UpdateWindow::AddToolBarItems()
{
    QPixmap back("D:\\qt_projects\\Healthy_eating\\back.png");
    QPixmap addNew("D:\\qt_projects\\Healthy_eating\\add.png");
    QPixmap download("D:\\qt_projects\\Healthy_eating\\download.png");
    QPixmap addDish("D:\\qt_projects\\Healthy_eating\\update_add.png");
    QPixmap changeDish("D:\\qt_projects\\Healthy_eating\\update_change.png");
    QPixmap deleteDish("D:\\qt_projects\\Healthy_eating\\update_delete.png");
    QPixmap addDishCompatibility("D:\\qt_projects\\Healthy_eating\\update_add_com.png");
    QPixmap changeDishCompatibility("D:\\qt_projects\\Healthy_eating\\update_change_com.png");
    QPixmap deleteDishCompatibility("D:\\qt_projects\\Healthy_eating\\update_delete_com.png");

    toolBar->addAction(QIcon(back), "Вернуться на первую страницу", this, &UpdateWindow::ChangeWin);
    toolBar->addSeparator();
    toolBar->addAction(QIcon(addNew), "Создать новый список блюд и совместимостей", this, &UpdateWindow::CreateMenu);
    toolBar->addAction(QIcon(download), "Загрузить существующий список блюд и совместимостей", this, &UpdateWindow::SetMenu);
    toolBar->addSeparator();
    toolBar->addAction(QIcon(addDish), "Добавить новое блюдо", this, &UpdateWindow::AddDish);
    toolBar->addAction(QIcon(changeDish), "Изменить блюдо", this, &UpdateWindow::UpdateDish);
    toolBar->addAction(QIcon(deleteDish), "Удалить блюдо", this, &UpdateWindow::DeleteDish);
    toolBar->addSeparator();
    toolBar->addAction(QIcon(addDishCompatibility), "Добавить новую совместимость", this, &UpdateWindow::AddDishCompatibility);
    toolBar->addAction(QIcon(changeDishCompatibility), "Изменить совместимость", this, &UpdateWindow::UpdateDishCompatibility);
    toolBar->addAction(QIcon(deleteDishCompatibility), "Удалить совместимость", this, &UpdateWindow::DeleteDishCompatibility);
}

void UpdateWindow::AddDish()
{    
    if(_db->IsOpen())
    {
        Dialog dialog("Выберите тип нового блюда", "Введите название нового блюда", "Введите количество калорий", this);
        if(dialog.exec() == QDialog::Accepted)
        {
            if(_db->AddDish(dialog._line->text(), dialog._spin->value(), dialog._combo1->currentText()))
                UpdateDishesList();
            else
                QMessageBox::warning(this, "Ошибка","Введены недопустимые параметры");
        }
    }
    else
        QMessageBox::warning(this, "Ошибка","Необходимо открыть или создать базу данных");
}

void UpdateWindow::UpdateDish()
{
    if(_db->IsOpen())
    {
        Dialog dialog("Выберите блюдо для изменения", "Тип блюда", "Название блюда", "Количество калорий", this);
        if(dialog.exec() == QDialog::Accepted)
        {
            if(_db->UpdateDish(dialog._combo1->currentText(), dialog._line->text(), dialog._spin->value(), dialog._combo2->currentText()))
                UpdateDishesList();
            else
                QMessageBox::warning(this, "Ошибка","Введены недопустимые параметры");
        }
    }
    else
        QMessageBox::warning(this, "Ошибка","Необходимо открыть или создать базу данных");
}

void UpdateWindow::DeleteDish()
{
    if(_db->IsOpen())
    {
        Dialog dialog("Выберите блюдо для удаления", this);
        if(dialog.exec() == QDialog::Accepted)
        {
            if(_db->DelDish(dialog._combo1->currentText()))
                UpdateDishesList();
            else
                QMessageBox::warning(this, "Ошибка","Введены недопустимые параметры");
        }
    }
    else
        QMessageBox::warning(this, "Ошибка","Необходимо открыть или создать базу данных");
}

void UpdateWindow::AddDishCompatibility()
{
    if(_db->IsOpen())
    {
        Dialog dialog("Выберите блюдо для добавления к нему совместимости",
                             "Выбирите выберите блюдо для добавления в список совместимостей",this, true);
        if(dialog.exec() == QDialog::Accepted)
        {
            if(dialog._radio1->isChecked())
            {
                if(_db->AddCom("COMPATIBILITY", dialog._combo2->currentText(), dialog._combo1->currentText()))
                    UpdateDishesList();
                else
                    QMessageBox::warning(this, "Ошибка","Введены недопустимые параметры");
            }
            else
            {
                if(_db->AddCom("INCOMPATIBILITY", dialog._combo2->currentText(), dialog._combo1->currentText()))
                    UpdateDishesList();
                else
                    QMessageBox::warning(this, "Ошибка","Введены недопустимые параметры");
            }
        }
    }
    else
        QMessageBox::warning(this, "Ошибка","Необходимо открыть или создать базу данных");
}

void UpdateWindow::UpdateDishCompatibility()
{
    if(_db->IsOpen())
    {
        Dialog dialog("Выберите блюдо, в котором Вы хотите изменить совместимость", "Выберите совмстимость", this);
        if(dialog.exec() == QDialog::Accepted)
        {
            if(_db->UpdateCom(dialog._combo1->currentText(), dialog._combo2->currentText(), dialog._radio1->isChecked()))
                UpdateDishesList();
            else
                QMessageBox::warning(this, "Ошибка","Введены недопустимые параметры");
        }
    }
    else
        QMessageBox::warning(this, "Ошибка","Необходимо открыть или создать базу данных");
}

void UpdateWindow::DeleteDishCompatibility()
{
    if(_db->IsOpen())
    {
        Dialog dialog("Выберите блюдо, в котором Вы хотите удалить совместимость", "Выберите совместимость", this, false, true);
        if(dialog.exec() == QDialog::Accepted)
        {
            if(_db->DelCom(dialog._combo1->currentText(), dialog._combo2->currentText()))
                UpdateDishesList();
            else
                QMessageBox::warning(this, "Ошибка","Введены недопустимые параметры");
        }
    }
    else
        QMessageBox::warning(this, "Ошибка","Необходимо открыть или создать базу данных");
}

void UpdateWindow::CreateMenu()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                "Создать меню",
                                QDir::currentPath(),
                                "Файлы базы данных (*.db)");

    if(!fileName.isEmpty())
    {
        if(_db->SetDb(fileName))
        {
            QMessageBox::information(this, "Успех","Файл успешно создан");
            UpdateDishesList();
        }
        else
            QMessageBox::warning(this, "Ошибка","Не удалось создать файл");
    }

}

void UpdateWindow::SetMenu()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                "Открыть меню",
                                QDir::currentPath(),
                                "Файлы базы данных (*.db)");
    if(!fileName.isEmpty())
    {
        _model2->clear();
        _model3->clear();
        if(_db->SetDb(fileName))
        {
            QMessageBox::information(this, "Успех","Файл успешно открыт");
            QString query = "SELECT dish FROM DISHES";
            _model1->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
        }
        else
            QMessageBox::warning(this, "Ошибка","Не удалось открыть файл");
    }
}

void UpdateWindow::UpdateDishesList()
{
    _model2->clear();
    _model3->clear();
    QString query = "SELECT dish FROM DISHES";
    _model1->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
}

void UpdateWindow::UpdateComLists(const QModelIndex &index)
{
    QString query = "SELECT DISH_COMPATIBILITY FROM COMPATIBILITY WHERE iddish = ("
                    "SELECT iddish FROM dishes WHERE dish = '"+index.data(Qt::DisplayRole).toString()+"');";
    _model2->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
    query = "SELECT DISH_INCOMPATIBILITY FROM INCOMPATIBILITY WHERE iddish = ("
            "SELECT iddish FROM dishes WHERE dish = '"+index.data(Qt::DisplayRole).toString()+"');";
    _model3->setQuery(QSqlQuery(query, QSqlDatabase::database("line")));
    QSqlQuery q("SELECT calories, type FROM dishes WHERE dish = '"+index.data(Qt::DisplayRole).toString()+"';",
                QSqlDatabase::database("line"));
    q.next();
    label_4->setText("Калории блюда: " + q.value(0).toString());
    label_5->setText("Тип блюда: " + q.value(1).toString());
}
