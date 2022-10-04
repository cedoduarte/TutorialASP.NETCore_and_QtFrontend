#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "user.h"

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class QNetworkReply;
class QNetworkAccessManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum MethodEnum
    {
        Post,
        GetById,
        GetAll,
        Put,
        DeleteById
    };

    enum ColumnEnum
    {
        Id,
        Name,
        Email,
        Age,
        Salary
    };

    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
private slots:
    void finished(QNetworkReply *reply);
    void on_actionClose_triggered();
    void on_postButton_clicked();
    void on_getAllButton_clicked();

    void on_getByIdButton_clicked();

    void on_putButton_clicked();

    void on_deleteByIdButton_clicked();

private:
    void displayUser(const User &user) const;
    void showInTable(const std::vector<User> &users) const;

    Ui::MainWindow *ui;
    QNetworkAccessManager *m_manager;
    MethodEnum m_method;
};

#endif // MAINWINDOW_H
