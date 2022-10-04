#ifndef REQUEST_H
#define REQUEST_H

#include <QNetworkRequest>


class Request : public QNetworkRequest
{
public:
    Request();
    Request(const QUrl &url);
    virtual ~Request();
private:
    void sslConfig();
};

#endif // REQUEST_H
