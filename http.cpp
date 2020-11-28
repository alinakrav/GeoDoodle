#include "http.h"

// Data used for API calls
const QString MAPS_KEY = "AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";
const QString IP_KEY = "b9a2e73fde34f69ef626c51d53663192";

int coordPrecision = 17;
QString userLocationUrl = "http://api.ipstack.com/check?access_key=" + IP_KEY;
QString locationUrlFor = "https://maps.googleapis.com/maps/api/place/findplacefromtext/json?fields=geometry&inputtype=textquery&key=" + MAPS_KEY + "&input=";

struct cartesianCoordinate
{
    QString lat;
    QString lon;
};

Http::Http(Http::urls urls, Ui::MainWindow ui_) : ui(ui_) {

    QString baseURL = "https://roads.googleapis.com/v1/snapToRoads";
    QString path = "?path=" + urls.coords;
//    qDebug() << urls.coords;

    QString queryURL = baseURL + path + "&interpolate=true&key=" + MAPS_KEY;

    displayURL(urls.coords);
//    sendRequest(queryURL, "snapRoads");

//    sendRequest(urls.userLocation, "userLocation");
//    sendRequest(urls.searchLocation, "searchLocation");
}

void Http::sendRequest(QString url, QString type) {
    // get response
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    if (type == "userLocation")
        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getUserLocationResponse(QNetworkReply *)));
    else if (type == "searchLocation")
        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getSearchLocationResponse(QNetworkReply *)));
    else if (type == "snapRoads")
        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getSnapRoadsResponse(QNetworkReply *)));
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    reply->waitForReadyRead(3000);
}
void Http::getSnapRoadsResponse(QNetworkReply* reply) {
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    QJsonArray jsonArray = jsonObj["snappedPoints"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value["location"].toObject();
        QJsonValue jsonLat = obj.value("latitude");
        QJsonValue jsonLon = obj.value("longitude");
        double lat = jsonLat.toDouble();
        double lon = jsonLon.toDouble();
        cartesianCoordinate coord = { QString::number(lat), QString::number(lon)};
        snappedPoints.append(coord);
    }
    createRouteURL();
}

void Http::displayURL(QString s) {
    QString routeURL = "https://www.google.ca/maps/dir/" + s + "/data=!4m2!4m1!3e2";
    ui.output_url->clear();
    ui.output_url->appendPlainText(routeURL);

    QWebEngineView *view = new QWebEngineView();
    view->resize(QApplication::desktop()->screenGeometry().width()/3*2, QApplication::desktop()->screenGeometry().height());
    view->load(QUrl(routeURL));
    view->show();
}

QString Http::createRouteURL() {
    QString routeURL = "https://www.google.ca/maps/dir/";
    QString lat, lon;
    for(cartesianCoordinate coord : snappedPoints){
        lat = coord.lat;
        lon = coord.lon;
        routeURL.append("'" + lat + "," + lon + "'" + "/");
    }
    ui.output_url->clear();
    ui.output_url->appendPlainText(routeURL);
    return routeURL;
}

void Http::getUserLocationResponse(QNetworkReply* reply) {
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    jsonObj = jsonResponse.object();
    printUserLocation();
}

void Http::getSearchLocationResponse(QNetworkReply* reply) {
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    jsonObj = jsonResponse.object();
    printSearchLocation();
}
void Http::printUserLocation() {
    // parse response
    QString latitude = QString::number(jsonObj["latitude"].toDouble(), 'g', coordPrecision);
    QString longitude = QString::number(jsonObj["longitude"].toDouble(), 'g', coordPrecision);
//    ui.testArea->appendPlainText("User location...");
//    ui.testArea->appendPlainText("Latitude: " + latitude);
//    ui.testArea->appendPlainText("Longitude: " + longitude);
}

void Http::printSearchLocation() {
    QJsonObject location = jsonObj["candidates"].toArray().at(0)["geometry"].toObject()["location"].toObject();
    QString latitude = QString::number(location["lat"].toDouble(), 'g', coordPrecision);
    QString longitude = QString::number(location["lng"].toDouble(), 'g', coordPrecision);
//    ui.testArea->appendPlainText("Searched location...");
//    ui.testArea->appendPlainText("Latitude: " + latitude);
//    ui.testArea->appendPlainText("Longitude: " + longitude);
}



Http::~Http() {}
