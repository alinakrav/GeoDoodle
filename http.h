#ifndef HTTP_H
#define HTTP_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QApplication>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include "ui_mainwindow.h"

class Http : public QObject
{
    Q_OBJECT

public:
    // contains all urls passed from mainwindow
    struct urls {
        QString searchLocation;
        QString userLocation;
        QString coords;

    };
    Http(struct Http::urls, Ui::MainWindow); // constructor, sends a url to request, keyword that identifies the content, and ui to print content to
    ~Http(); // destructor
    void printUserLocation(); // parses and prints data from response
    void printSearchLocation();
    QString createRouteURL();
    void displayURL(QString);
private slots:
    void getUserLocationResponse(QNetworkReply *); // gets and prepares response
    void getSearchLocationResponse(QNetworkReply *);
    void getSnapRoadsResponse(QNetworkReply *);

private:
    void sendRequest(QString, QString);
    Ui::MainWindow ui; // ui will be modified within aync process
    QJsonObject jsonObj; // json object saved from response
    QVector<struct cartesianCoordinate> snappedPoints;
};
#endif // HTTP_H
