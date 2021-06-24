#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <iostream>
#include "adddialog.h"
#include <QDomDocument>
#include <QDomElement>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList titles { "ID", "ФИО", "Email", "Телефон", "День рождения", "День внесения" };
    ui->tableWidget->setColumnCount(titles.size());
    ui->tableWidget->setHorizontalHeaderLabels(titles);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAdd_triggered()
{
    AddDialog d(this);
    if(d.exec()== QDialog::Rejected)
    {
        return;
    }
    //auto user = d.getUser();
    addUser(d.getUser());
}


void MainWindow::on_actionDelete_triggered()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void MainWindow::addUser(const User &user)
{
    const int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, ID, new QTableWidgetItem(user.getId()));
    ui->tableWidget->setItem(row, FIO, new QTableWidgetItem(user.getFIO()));
    ui->tableWidget->setItem(row, EMAIL, new QTableWidgetItem(user.getEmail()));
    ui->tableWidget->setItem(row, NUMBER, new QTableWidgetItem(user.getNumber()));
    ui->tableWidget->setItem(row, BDAY, new QTableWidgetItem(user.getBday()));
    ui->tableWidget->setItem(row, DAY, new QTableWidgetItem(user.getDay()));
}


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
    QDomDocument doc;
    doc.setContent(&file);
    file.close();
    auto root = doc.firstChild().toElement();
    auto ix = doc.firstChild().toElement();
    while (!ix.isNull())
    {
        auto id = ix.attribute("id");
        auto fio = ix.firstChild().toElement().text();
        auto email = ix.firstChild().nextSibling().toElement().text();
        auto number = ix.firstChild().nextSibling().nextSibling().toElement().text();
        auto bday = ix.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();
        auto day = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();
        addUser(User(id, fio, email, number, bday, day));
        ix = ix.nextSibling().toElement();
    }
}


void MainWindow::on_actionSave_as_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "Save as", QDir::rootPath(), "XML file (*.xml)");
    QDomDocument doc;
    auto root = doc.createElement("users");
    doc.appendChild(root);
    const int rowCount = ui->tableWidget->rowCount();

    for (int ix = 0; ix < rowCount; ix++)
    {
        User user( ui->tableWidget->item(ix, ID)->text(),
                ui->tableWidget->item(ix, FIO)->text(),
                ui->tableWidget->item(ix, EMAIL)->text(),
                ui->tableWidget->item(ix, NUMBER)->text(),
                ui->tableWidget->item(ix, BDAY)->text(),
                ui->tableWidget->item(ix, DAY)->text());
        auto eUser = doc.createElement("user");
        eUser.setAttribute("id",user.getId());

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


void MainWindow::on_actionClose_triggered()
{
    close();
}


void MainWindow::on_pushButton_clicked()
{
    on_actionAdd_triggered();
}


void MainWindow::on_pushButton_2_clicked()
{
    on_actionDelete_triggered();
}


void MainWindow::on_pushButton_3_clicked()
{

}

