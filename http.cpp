#include "http.h"

// Data used for API calls
const QString MAPS_KEY = "AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";
const QString IP_KEY = "b9a2e73fde34f69ef626c51d53663192";

int coordPrecision = 17;
QString userLocationUrl = "http://api.ipstack.com/check?access_key=" + IP_KEY;
QString locationUrlFor = "https://maps.googleapis.com/maps/api/place/findplacefromtext/json?fields=geometry&inputtype=textquery&key=" + MAPS_KEY + "&input=";
QString lat1 = "44.234025";
QString lon1 = "-76.502939";
QString lat2 = "44.222802";
QString lon2 = "-76.490321";
QString lat3 = "44.221193";
QString lon3 = "-76.512489";
QString pathURL = "https://roads.googleapis.com/v1/snapToRoads?path=" + lat1 + "," + lon1 + "|" + lat2 + "," + lon2 + "|" + lat3 + "," + lon3 + "&interpolate=true&key=AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";
QString waypointsURL = "https://maps.googleapis.com/maps/api/directions/json?origin=44.234025,-76.502939&destination=44.234025,-76.502939&waypoints=44.222802,-76.490321|44.221193,-76.512489&key=AIzaSyBq5Lv-ZfLXrNmcDt-fN3koYi-vcV4vU4Q";

//------------------------ zack
struct cartesianCoordinate
{
    QString lat;
    QString lon;
};
//------------------------

Http::Http(Http::urls urls, Ui::MainWindow ui_) : ui(ui_) {
    //------------------------ zack

    //HARDCODED VALUE
    //This shouldn't be needed after this class is merged with the coordinate image class
    struct cartesianCoordinate input [3] = {{"44.234025","-76.502939"},{"44.222802","-76.490321"},{"44.221193","-76.512489"}};

    QString baseURL = "https://roads.googleapis.com/v1/snapToRoads";
    QString path = "?path=";

    //HARDCODED VALUE
    //This shouldn't be needed after this class is merged with the coordinate image class
    for (int i = 0; i < 3; i++ ) {
        path.append(input[i].lat + "," + input[i].lon);
        if(i < 2){
            path.append("|");
        }
    }
    QString queryURL = baseURL + path + "&interpolate=true&key=" + MAPS_KEY;

    sendRequest(queryURL, "snapRoads");
    //------------------------

    sendRequest(urls.userLocation, "userLocation");
    sendRequest(urls.searchLocation, "searchLocation");
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
//------------------------ zack
void Http::getSnapRoadsResponse(QNetworkReply* reply) {
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    QJsonArray jsonArray = jsonObj["snappedPoints"].toArray();
    QVector<struct cartesianCoordinate> snappedPoints;
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value["location"].toObject();
        QJsonValue jsonLat = obj.value("latitude");
        QJsonValue jsonLon = obj.value("longitude");

        //This statement doesn't work as intended.
        snappedPoints.append({ jsonLat.toString(), jsonLon.toString()});
    }
}

QString Http::createRouteURL() {
    QString routeURL = "https://www.google.ca/maps/dir/";
    QString lat, lon;
    cartesianCoordinate snappedPointsArray[] = {{"41.8507300","-87.6512600"},{"41.8525800","-87.6514100"},{"41.0507300","-87.6512600"}};
    for(cartesianCoordinate coord : snappedPointsArray){
        lat = coord.lat;
        lon = coord.lon;
        routeURL.append("'" + lat + "," + lon + "'" + "/");
    }
    ui.testArea->appendPlainText("createRouteURL...\n" + routeURL);
    return routeURL;
}
//------------------------

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
