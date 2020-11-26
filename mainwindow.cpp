#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "http.cpp"
#include "ImageGraph.h"
#include <vector>
#include <QString>

vector<double> toronto = {43.684921, -79.477013};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Please Select");
    ui->comboBox->addItem("Downtown Toronto");

// all urls processed in one call due to asynchronous restrictions on multiple separate calls
    Http::urls urls;
    urls.searchLocation = locationUrlFor + "Toronto";
    urls.userLocation = userLocationUrl;

    new Http(urls, *ui);
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
    ui -> stackedWidget -> setCurrentIndex(3);
}

void MainWindow::on_cartoon1_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);
    vector<vector<float>> pic_A {{0,2},{1,0},{3,0},{4,2},{2,3}}; //irregular pentagon
    ImageGraph graph_A(pic_A);
    graph_A.place_on_map(toronto, radius);
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
    vector<vector<float>> pic_B {{1,1},{-1,1},{0,-1}}; //triangle
    ImageGraph graph_B(pic_B);
    graph_B.place_on_map(toronto, radius);
    s = QString::fromStdString(graph_B.path());
    qDebug()<<s;
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
    vector<vector<float>> pic_C {{0,0},{0,1},{1,1},{1,0}}; //unit square
    ImageGraph graph_C(pic_C);
    graph_C.place_on_map(toronto, radius);
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
    vector<vector<float>> pic_D {{1,4},{0,2},{1,0},{4,0},{5,2},{4,4}}; //irregular hexagon
    ImageGraph graph_D(pic_D);
    graph_D.place_on_map(toronto, radius);
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
    vector<vector<float>> pic_E {{2,0},{0,2},{-2,0},{0,-2}}; //regular rhombus
    ImageGraph graph_E(pic_E);
    graph_E.place_on_map(toronto, radius);
    s = QString::fromStdString(graph_E.path());
    Http::urls urls;
    urls.searchLocation = locationUrlFor + "Toronto";
    urls.userLocation = userLocationUrl;
    urls.coords = s;
    new Http(urls, *ui);
    ui -> stackedWidget -> setCurrentIndex(5);
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}

void MainWindow::on_spinBox_valueChanged(const int &arg1)
{
    radius = arg1;
}
