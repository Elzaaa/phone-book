#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "datamodel.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <iostream>
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>
#include <QMessageBox>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_model = new DataModel(this); 
    ui->setupUi(this);
    ui->tableView->setModel(m_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//тригеры действий на панели управления: добавления, удаления и возврата к начальному состоянию записной книжки
void MainWindow::on_actionAdd_triggered()
{

    AddDialog d(this);
    if(d.exec()== QDialog::Rejected)
    {
        return;
    }
    auto user = d.getUser();
    auto date = QDateTime::currentDateTime().date();
    user.setDay(QString("%1.%2.%3").arg(date.day(), 2, 10, QLatin1Char('0')).arg(date.month(), 2, 10, QLatin1Char('0')).arg(date.year(), 4, 10, QLatin1Char('0')));
    m_model->AddUser(user);
}

void MainWindow::on_actionDelete_triggered()
{
   //берем выбранную строку и удаляем ее
    auto selectionModel = ui->tableView->selectionModel();
    //проверка выделения
    if(selectionModel->hasSelection())
    {
        auto selectedRow = selectionModel->currentIndex();
        m_model->removeRow(selectedRow.row());
    }

}

void MainWindow::on_actionReturn_triggered()
{
    if(sLastOpenProdject.isEmpty())
    {
        return;
    }
    QFile file(sLastOpenProdject);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    //сохраняем путь до файла с начальным состоянием записной книжки
    openFile(&file);
}

//обработка собыйтий действий при нажатии на кнопки
void MainWindow::on_AddButton_clicked()
{
    on_actionAdd_triggered();
}

void MainWindow::on_DeleteButton_clicked()
{
    on_actionDelete_triggered();
}

void MainWindow::on_ReturnButton_clicked()
{
    on_actionReturn_triggered();
}

//добавление пользователя в телефонную книгу


//сохранение пользователей из таблицы в xml файл
void MainWindow::on_actionSave_as_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "Save as", QDir::rootPath(), "XML file (*.xml)");
    QDomDocument doc;
    auto root = doc.createElement("users");
    doc.appendChild(root);


    //запрашиваем у модели юзеров и сохраняем в  xml
    for (const User &user:m_model->GetUsers())
    {
        auto eUser = doc.createElement("user");
        eUser.setAttribute("id",user.getId());

        //создаем поля для xml файла
        auto eFio = doc.createElement("fio");
        auto eEmail = doc.createElement("email");
        auto eNumber = doc.createElement("number");
        auto eBday = doc.createElement("bday");
        auto eDay = doc.createElement("day");

        eFio.appendChild(doc.createTextNode(user.getFIO()));
        eEmail.appendChild(doc.createTextNode(user.getEmail()));
        eNumber.appendChild(doc.createTextNode(user.getNumber()));
        eBday.appendChild(doc.createTextNode(user.getBday()));
        eDay.appendChild(doc.createTextNode(user.getDay()));

        eUser.appendChild(eFio);
        eUser.appendChild(eEmail);
        eUser.appendChild(eNumber);
        eUser.appendChild(eBday);
        eUser.appendChild(eDay);
        root.appendChild(eUser);
    }
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QTextStream xout(&file);
    xout<<doc.toString();
    file.flush();
    file.close();

}
//Открытие данных о пользователях в xml
void MainWindow::openFile(QFile *file)
{
    m_model->setRowCount(0);
    QDomDocument doc;
    doc.setContent(file);
    file->close();
    auto root = doc.firstChild().toElement();
    auto ix = root.firstChild().toElement();
    //пока не дойдем до завершающего "родительсткого элемента" будем вытаскивать значения
    while (!ix.isNull())
    {
        auto id = ix.attribute("id");
        auto fio = ix.firstChild().toElement().text();
        auto email = ix.firstChild().nextSibling().toElement().text();
        auto number = ix.firstChild().nextSibling().nextSibling().toElement().text();
        auto bday = ix.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();
        auto day = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();     
        m_model->AddUser(User(id, fio, email, number, bday, day));
        ix = ix.nextSibling().toElement();
    }
}

//Сохраняем новые данные
void MainWindow::on_actionOpen_triggered()
{

    auto filename = QFileDialog::getOpenFileName(this, "Open", QDir::rootPath(), "XML file (*.xml)");
    if(filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }

    openFile(&file);

    sLastOpenProdject = filename;
}

void MainWindow::on_actionClose_triggered()
{
    close();
}










