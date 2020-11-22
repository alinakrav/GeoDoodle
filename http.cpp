#include "http.h"

Ui::MainWindow ui;
QString type;
// Data used for API calls
int coordPrecision = 17;
QString userLocationUrl = "http://api.ipstack.com/check?access_key=b9a2e73fde34f69ef626c51d53663192";
QString locationUrlFor = "https://maps.googleapis.com/maps/api/place/findplacefromtext/json?fields=geometry&inputtype=textquery&key=AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q&input=";
QString lat1 = "44.234025";
QString lon1 = "-76.502939";
QString lat2 = "44.222802";
QString lon2 = "-76.490321";
QString lat3 = "44.221193";
QString lon3 = "-76.512489";
QString pathURL = "https://roads.googleapis.com/v1/snapToRoads?path=" + lat1 + "," + lon1 + "|" + lat2 + "," + lon2 + "|" + lat3 + "," + lon3 + "&interpolate=true&key=AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";
QString waypointsURL = "https://maps.googleapis.com/maps/api/directions/json?origin=44.234025,-76.502939&destination=44.234025,-76.502939&waypoints=44.222802,-76.490321|44.221193,-76.512489&key=AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";

Http::Http(QString url, QString type_, Ui::MainWindow ui_) {
    ui = ui_;
    type = type_;
    // get response
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(saveResponse(QNetworkReply *)));
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    reply->waitForReadyRead(3000);
}

void Http::saveResponse(QNetworkReply* reply) {
    // prep response
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    jsonObj = jsonResponse.object();

    // parse response in a specific way
    if (type == "userLocation")
        printUserLocation();
    else if (type == "searchLocation")
        printSearchLocation();
    else if (type == "something else")
        return;
}
void Http::printUserLocation() {
    // parse response
    QString latitude = QString::number(jsonObj["latitude"].toDouble(), 'g', coordPrecision);
    QString longitude = QString::number(jsonObj["longitude"].toDouble(), 'g', coordPrecision);
    ui.testArea->appendPlainText("User location...");
    ui.testArea->appendPlainText("Latitude: " + latitude);
    ui.testArea->appendPlainText("Longitude: " + longitude);
}

void Http::printSearchLocation() {
    QJsonObject location = jsonObj["candidates"].toArray().at(0)["geometry"].toObject()["location"].toObject();
    QString latitude = QString::number(location["lat"].toDouble(), 'g', coordPrecision);
    QString longitude = QString::number(location["lng"].toDouble(), 'g', coordPrecision);
    ui.testArea->appendPlainText("Searched location...");
    ui.testArea->appendPlainText("Latitude: " + latitude);
    ui.testArea->appendPlainText("Longitude: " + longitude);
}


Http::~Http() {}
