#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    ui -> stackedWidget -> setCurrentIndex(3);
}

void MainWindow::on_cartoon1_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);

}
void MainWindow::on_cartoon2_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);

}
void MainWindow::on_cartoon3_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);

}
void MainWindow::on_cartoon4_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);

}
void MainWindow::on_cartoon5_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(4);

}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}

void MainWindow::on_spinBox_valueChanged(const int &arg1)
{
    radius = arg1;
}
