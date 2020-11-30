#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "http.cpp"
#include "ImageGraph.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Please Select");
    ui->comboBox->addItem("Downtown Toronto");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(2);
}

void MainWindow::on_pushButton_3_clicked()
{
    radius = ui->spinBox->value();
    ui -> stackedWidget -> setCurrentIndex(3);
}

void MainWindow::on_cartoon1_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //irregular pentagon
    ImageGraph graph_A(pentagon);
    graph_A.set_radius(radius);
    graph_A.place_on_map(toronto);
    graph_A.double_density(2);
    s = QString::fromStdString(graph_A.path());
    Http::urls urls;
    urls.searchLocation = locationUrlFor + "Toronto";
    urls.userLocation = userLocationUrl;
    urls.coords = s;
    new Http(urls, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}
void MainWindow::on_cartoon2_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //triangle
    ImageGraph graph_B(triangle);
    graph_B.set_radius(radius);
    graph_B.place_on_map(toronto);
    graph_B.double_density(2);
    s = QString::fromStdString(graph_B.path());
    Http::urls urls;
    urls.searchLocation = locationUrlFor + "Toronto";
    urls.userLocation = userLocationUrl;
    urls.coords = s;
    new Http(urls, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}
void MainWindow::on_cartoon3_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    // square
    ImageGraph graph_C(square);
    graph_C.set_radius(radius);
    graph_C.place_on_map(toronto);
    graph_C.double_density(2);
    s = QString::fromStdString(graph_C.path());
    Http::urls urls;
    urls.searchLocation = locationUrlFor + "Toronto";
    urls.userLocation = userLocationUrl;
    urls.coords = s;
    new Http(urls, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);

}
void MainWindow::on_cartoon4_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //irregular hexagon
    ImageGraph graph_D(hexagon);
    graph_D.set_radius(radius);
    graph_D.place_on_map(toronto);
    graph_D.double_density(2);
    s = QString::fromStdString(graph_D.path());
    Http::urls urls;
    urls.searchLocation = locationUrlFor + "Toronto";
    urls.userLocation = userLocationUrl;
    urls.coords = s;
    new Http(urls, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}
void MainWindow::on_cartoon5_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    //regular rhombus
    ImageGraph graph_E(rhombus);
    graph_E.set_radius(radius);
    graph_E.place_on_map(toronto);
    graph_E.double_density(2);
    s = QString::fromStdString(graph_E.path());
    Http::urls urls;
    urls.searchLocation = locationUrlFor + "Toronto";
    urls.userLocation = userLocationUrl;
    urls.coords = s;
    new Http(urls, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}

void MainWindow::on_restartButton_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(0);
    (QApplication::topLevelWidgets())[0]->close();
}
