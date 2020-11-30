#include "http.h"
#include "ImageGraph.h"

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

// shape will be passed to ImageGraph class, typeOfRequest specifies what url to construct and call, ui is to modify output asynchronously
Http::Http(QString typeOfRequest_, std::vector<std::vector<float>> shape_, Ui::MainWindow ui_) : ui(ui_), typeOfRequest(typeOfRequest_), shape(shape_) {
    QString url;
    if (typeOfRequest == "snapRoads") {
        QString baseURL = "https://roads.googleapis.com/v1/snapToRoads";
//        QString path = "?path=" + "";
//        QString queryURL = baseURL + path + "&interpolate=true&key=" + MAPS_KEY;
//        url = queryURL;
    }
    else if (typeOfRequest == "My Location")
        url = userLocationUrl;
    else
        // city selected
        url = locationUrlFor + typeOfRequest;

    sendRequest(url);

}

void Http::sendRequest(QString url) {
    // get response
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getResponse(QNetworkReply *)));
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    reply->waitForReadyRead(3000);
}

void Http::getResponse(QNetworkReply* reply) {
    if (typeOfRequest == "snapRoads")
        parseSnapRoadsResponse(reply);
    else if (typeOfRequest == "My Location")
        parseUserLocationResponse(reply);
    else
        parseSearchLocationResponse(reply);
}

void Http::parseSnapRoadsResponse(QNetworkReply* reply) {
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

void Http::displayURL(QString s) {

    QString routeURL = "https://www.google.ca/maps/dir/" + s + "/data=!4m2!4m1!3e2";
    ui.output_url->clear();
    ui.output_url->appendPlainText(routeURL);

    // open maps link in new window
    QWebEngineView *view = new QWebEngineView();
    view->resize(QApplication::desktop()->screenGeometry().width()/3*2, QApplication::desktop()->screenGeometry().height());
    view->load(QUrl(routeURL));
    view->show();
}

void Http::parseUserLocationResponse(QNetworkReply* reply) {
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    // parse response
    latitude = jsonObj["latitude"].toDouble();
    longitude = jsonObj["longitude"].toDouble();

    graphShape();
}

void Http::parseSearchLocationResponse(QNetworkReply* reply) {
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    // parse response
    QJsonObject location = jsonObj["candidates"].toArray().at(0)["geometry"].toObject()["location"].toObject();
    latitude = location["lat"].toDouble();
    longitude = location["lng"].toDouble();

    graphShape();
}
void Http::graphShape() {
    ImageGraph graph(shape);
    graph.set_radius(ui.spinBox->value());
    graph.place_on_map({latitude, longitude});
    graph.double_density(2);
    QString s = QString::fromStdString(graph.path());
    QString baseURL = "https://roads.googleapis.com/v1/snapToRoads";
    QString path = "?path=" + s;
    QString queryURL = baseURL + path + "&interpolate=true&key=" + MAPS_KEY;
    displayURL(s);
}

Http::~Http() {}
