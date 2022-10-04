#ifndef USER_H
#define USER_H

#include <QObject>
#include <QMetaType>
#include <vector>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(double salary READ salary WRITE setSalary NOTIFY salaryChanged)
public:
    static void registerMetaType();
    static User fromJsonPost(const QByteArray &json);
    static User fromJsonGetById(const QByteArray &json);
    static User fromJsonPut(const QByteArray &json);
    static User fromJsonDelete(const QByteArray &json);
    static std::vector<User> fromJsonGetAll(const QByteArray &json);
    QByteArray toJsonPost() const;
    QByteArray toJsonPut() const;
    void print() const;

    User(QObject *parent = nullptr);
    User(const User &other);
    User(int id, const QString &name, const QString &email, int age, double salary, QObject *parent = nullptr);
    void operator=(const User &other);
    virtual ~User();

    void setId(int id);
    void setName(const QString &name);
    void setEmail(const QString &email);
    void setAge(int age);
    void setSalary(double salary);

    int id() const;
    QString name() const;
    QString email() const;
    int age() const;
    double salary() const;
signals:
    void idChanged(int id);
    void nameChanged(const QString &name);
    void emailChanged(const QString &email);
    void ageChanged(int age);
    void salaryChanged(double salary);
private:
    int m_id;
    QString m_name;
    QString m_email;
    int m_age;
    double m_salary;
};
Q_DECLARE_METATYPE(User)

#endif // USER_H
