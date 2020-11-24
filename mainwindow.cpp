#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "http.cpp"

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

void MainWindow::on_cartoon1_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_cartoon2_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_cartoon3_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_cartoon4_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_cartoon5_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}
