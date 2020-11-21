#include "http.h"
#include <iostream>

// Data used for API calls
int coordPrecision = 17;
QString locationURL = "http://api.ipstack.com/check?access_key=b9a2e73fde34f69ef626c51d53663192";
QString lat1 = "44.234025";
QString lon1 = "-76.502939";
QString lat2 = "44.222802";
QString lon2 = "-76.490321";
QString lat3 = "44.221193";
QString lon3 = "-76.512489";
QString pathURL = "https://roads.googleapis.com/v1/snapToRoads?path=" + lat1 + "," + lon1 + "|" + lat2 + "," + lon2 + "|" + lat3 + "," + lon3 + "&interpolate=true&key=AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";
QString waypointsURL = "https://maps.googleapis.com/maps/api/directions/json?origin=44.234025,-76.502939&destination=44.234025,-76.502939&waypoints=44.222802,-76.490321|44.221193,-76.512489&key=AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";

QString Http::getLongitude() { return longitude; }
QString Http::getLatitude() { return latitude; }

void Http::getResponse(QString url) {
    // get response
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    // I tried connecting to a different slot, the issue is that the signal isn't sent in the first place
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    reply->waitForReadyRead(0);
}

void Http::replyFinished(QNetworkReply* reply) {
    // prep response
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    // parse response
    longitude = QString::number(jsonObj["longitude"].toDouble(), 'g', coordPrecision);
    latitude = QString::number(jsonObj["latitude"].toDouble(), 'g', coordPrecision);
}

Http::Http() {}
