#include "request.h"

#include <QSslSocket>
#include <QSslConfiguration>

Request::Request()
{
    sslConfig();
    setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}

Request::Request(const QUrl &url)
{
    sslConfig();
    setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    setUrl(url);
}

Request::~Request()
{
    // nothing to do here
}

void Request::sslConfig()
{
    QSslConfiguration sslConfig = sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    setSslConfiguration(sslConfig);
}
