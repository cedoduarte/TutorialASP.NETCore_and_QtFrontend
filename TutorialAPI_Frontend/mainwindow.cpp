#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "request.h"

#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList labels { "ID", "Name", "Email", "Age", "Salary" };
    ui->getAllUserTable->setColumnCount(labels.size());
    ui->getAllUserTable->setHorizontalHeaderLabels(labels);
    ui->spinnerId->setRange(0, std::numeric_limits<int>::max());
    ui->spinnerId_2->setRange(0, std::numeric_limits<int>::max());
    ui->spinnerId_3->setRange(0, std::numeric_limits<int>::max());
    ui->spinnerAge->setRange(1, 120);
    ui->spinnerAge_2->setRange(1, 120);
    ui->spinnerAge_3->setRange(1, 120);
    ui->spinnerSalary->setRange(1.0, std::numeric_limits<double>::max());
    ui->spinnerSalary_2->setRange(1.0, std::numeric_limits<double>::max());
    ui->spinnerSalary_3->setRange(1.0, std::numeric_limits<double>::max());
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &MainWindow::finished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::finished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        switch (m_method)
        {
            case Post:
            {
                User::fromJsonPost(reply->readAll()).print();
                break;
            }
            case GetById:
            {
                displayUser(User::fromJsonGetById(reply->readAll()));
                break;
            }
            case GetAll:
            {
                showInTable(User::fromJsonGetAll(reply->readAll()));
                break;
            }
            case Put:
            {
                User::fromJsonPut(reply->readAll()).print();
                break;
            }
            case DeleteById:
            {
                User::fromJsonDelete(reply->readAll()).print();
                break;
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", reply->errorString());
    }
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_postButton_clicked()
{
    User user;
    user.setName(ui->txtName->text());
    user.setEmail(ui->txtEmail->text());
    user.setAge(ui->spinnerAge->value());
    user.setSalary(ui->spinnerSalary->value());

    m_method = Post;
    Request request;
    request.setUrl(QUrl("https://localhost:7013/api/user"));
    m_manager->post(request, user.toJsonPost());
}

void MainWindow::on_getAllButton_clicked()
{
    ui->getAllUserTable->setRowCount(0);

    m_method = GetAll;
    Request request;
    request.setUrl(QUrl("https://localhost:7013/api/user"));
    m_manager->get(request);
}

void MainWindow::on_getByIdButton_clicked()
{
    const int id = ui->spinnerId->value();
    m_method = GetById;
    Request request;
    request.setUrl("https://localhost:7013/api/user/" + QString::number(id));
    m_manager->get(request);
}

void MainWindow::on_putButton_clicked()
{
    const int id = ui->spinnerId_2->value();

    User user;
    user.setId(id);
    user.setName(ui->txtName_3->text());
    user.setEmail(ui->txtEmail_3->text());
    user.setAge(ui->spinnerAge_3->value());
    user.setSalary(ui->spinnerSalary_3->value());

    m_method = Put;
    Request request;
    request.setUrl("https://localhost:7013/api/user/" + QString::number(id));
    m_manager->put(request, user.toJsonPut());
}

void MainWindow::on_deleteByIdButton_clicked()
{
    const int id = ui->spinnerId_3->value();

    m_method = DeleteById;
    Request request;
    request.setUrl("https://localhost:7013/api/user/" + QString::number(id));
    m_manager->deleteResource(request);
}

void MainWindow::displayUser(const User &user) const
{
    ui->txtName_2->setText(user.name());
    ui->txtEmail_2->setText(user.email());
    ui->spinnerAge_2->setValue(user.age());
    ui->spinnerSalary_2->setValue(user.salary());
}

void MainWindow::showInTable(const std::vector<User> &users) const
{
    for (const User &user : users)
    {
        const int row = ui->getAllUserTable->rowCount();
        ui->getAllUserTable->insertRow(row);
        ui->getAllUserTable->setItem(row, Id, new QTableWidgetItem(QString::number(user.id())));
        ui->getAllUserTable->setItem(row, Name, new QTableWidgetItem(user.name()));
        ui->getAllUserTable->setItem(row, Email, new QTableWidgetItem(user.email()));
        ui->getAllUserTable->setItem(row, Age, new QTableWidgetItem(QString::number(user.age())));
        ui->getAllUserTable->setItem(row, Salary, new QTableWidgetItem(QString::number(user.salary())));
    }
}
