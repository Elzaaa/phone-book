#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SaveXMLFile();
    void ReadXMLFile();
    void ReadRoomElement();

private slots:
    void on_actionAdd_triggered();

    void on_actionDelete_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionClose_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    enum
    {
        ID,
        FIO,
        EMAIL,
        NUMBER,
        BDAY,
        DAY
    };
    void addUser(const User &user);
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
