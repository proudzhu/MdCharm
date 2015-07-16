#include "checkupdates.h"
#include "version.h"

CheckUpdates::CheckUpdates(QObject *parent) :
    QObject(parent)
{
    hasError = false;
    reply = NULL;
}

void CheckUpdates::error(QNetworkReply::NetworkError err)
{
    if(err!=QNetworkReply::NoError)
    {
        hasError = true;
        qDebug("network error is %d", err);
    }
}

bool CheckUpdates::isHasError()
{
    return hasError;
}

void CheckUpdates::check()
{
    QNetworkRequest request;
    QUrl url = QUrl::fromUserInput("http://www.mdcharm.com/checkupdate"); 
    QUrlQuery query;
    query.addQueryItem(QString::fromLatin1("current_version"), QString::fromLatin1(VERSION_STR));
#ifdef Q_OS_LINUX
    QString type("Linux");
#elif defined Q_OS_WIN
    QString type("Windows");
#else
    QString type("Unknow");
#endif

    query.addQueryItem(QString::fromLatin1("type"), type);
    url.setQuery(query);

    request.setUrl(url);
    reply = manager.get(request);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(error(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()),
            this, SLOT(httpFinished()));
}

void CheckUpdates::httpFinished()
{
    if(isHasError())
        return;
    if(reply==NULL)
        return;
    QString contents = reply->readAll();
    qDebug("%s",contents.toLatin1().constData());
    emit finished(contents);
}
