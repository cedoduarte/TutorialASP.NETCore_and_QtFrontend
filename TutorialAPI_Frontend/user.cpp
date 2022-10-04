#include "user.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

void User::registerMetaType()
{
    qRegisterMetaType<User>("User");
}

User User::fromJsonPost(const QByteArray &json)
{
    User user;
    QJsonObject object = QJsonDocument::fromJson(json).object();
    user.m_id = object["id"].toInt();
    user.m_name = object["name"].toString();
    user.m_email = object["email"].toString();
    user.m_age = object["age"].toInt();
    user.m_salary = object["salary"].toDouble();
    return user;
}

User User::fromJsonGetById(const QByteArray &json)
{
    return fromJsonPost(json);
}

User User::fromJsonPut(const QByteArray &json)
{
    return fromJsonPost(json);
}

User User::fromJsonDelete(const QByteArray &json)
{
    return fromJsonPut(json);
}

std::vector<User> User::fromJsonGetAll(const QByteArray &json)
{
    std::vector<User> users;
    QJsonArray array = QJsonDocument::fromJson(json).array();
    for (const QJsonValue &value : array)
    {
        QJsonObject object = value.toObject();
        User user;
        user.m_id = object["id"].toInt();
        user.m_name = object["name"].toString();
        user.m_email = object["email"].toString();
        user.m_age = object["age"].toInt();
        user.m_salary = object["salary"].toDouble();
        users.push_back(user);
    }
    return users;
}

QByteArray User::toJsonPost() const
{
    QJsonDocument doc;
    QJsonObject object;

    object["name"] = m_name;
    object["email"] = m_email;
    object["age"] = m_age;
    object["salary"] = m_salary;

    doc.setObject(object);
    return doc.toJson(QJsonDocument::Compact);
}

QByteArray User::toJsonPut() const
{
    QJsonDocument doc;
    QJsonObject object;

    object["id"] = m_id;
    object["name"] = m_name;
    object["email"] = m_email;
    object["age"] = m_age;
    object["salary"] = m_salary;

    doc.setObject(object);
    return doc.toJson(QJsonDocument::Compact);
}

void User::print() const
{
    qDebug() << "id:" << m_id;
    qDebug() << "name:" << m_name;
    qDebug() << "email:" << m_email;
    qDebug() << "age:" << m_age;
    qDebug() << "salary:" << m_salary;
}

User::User(QObject *parent) : QObject(parent)
{
    m_id = -1;
    m_name = "";
    m_email = "";
    m_age = -1;
    m_salary = 0.0;
}

User::User(const User &other) : QObject(other.parent())
{
    m_id = other.m_id;
    m_name = other.m_name;
    m_email = other.m_email;
    m_age = other.m_age;
    m_salary = other.m_salary;
}

User::User(int id, const QString &name, const QString &email, int age, double salary, QObject *parent)
    : QObject(parent)
{
    m_id = id;
    m_name = name;
    m_email = email;
    m_age = age;
    m_salary = salary;
}

void User::operator=(const User &other)
{
    setParent(other.parent());
    m_id = other.m_id;
    m_name = other.m_name;
    m_email = other.m_email;
    m_age = other.m_age;
    m_salary = other.m_salary;
}

User::~User()
{
    // nothing to do here
}

void User::setId(int id)
{
    if (m_id != id)
    {
        m_id = id;
        emit idChanged(m_id);
    }
}

void User::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void User::setEmail(const QString &email)
{
    if (m_email != email)
    {
        m_email = email;
        emit emailChanged(m_email);
    }
}

void User::setAge(int age)
{
    if (m_age != age)
    {
        m_age = age;
        emit ageChanged(m_age);
    }
}

void User::setSalary(double salary)
{
    if (m_salary != salary)
    {
        m_salary = salary;
        emit salaryChanged(m_salary);
    }
}

int User::id() const
{
    return m_id;
}

QString User::name() const
{
    return m_name;
}

QString User::email() const
{
    return m_email;
}

int User::age() const
{
    return m_age;
}

double User::salary() const
{
    return m_salary;
}
