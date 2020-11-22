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
#include "ui_mainwindow.h"

class Http : public QObject
{
    Q_OBJECT

public:
    Http(QString, QString, Ui::MainWindow); // constructor, sends a url to request, keyword that identifies the content, and ui to print content to
    ~Http(); // destructor
    void printLocation(); // parses and prints data from location api response
private slots:
    void saveResponse(QNetworkReply *); // saves json in class to use later
private:
    QJsonObject jsonObj; // json object saved from response
};
#endif // HTTP_H
