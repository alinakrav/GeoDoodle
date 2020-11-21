#ifndef HTTP_H
#define HTTP_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>

class Http : public QObject
{
    Q_OBJECT

public:
    Http();
    void getResponse(QString);
    QString getLongitude();
    QString getLatitude();
private slots:
    void replyFinished(QNetworkReply *, bool);
private:
    QString longitude;
    QString latitude;
};
#endif // HTTP_H
