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

void MainWindow::on_pentagon_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_triangle_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_square_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_hexagon_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}
void MainWindow::on_rhombus_clicked()
{
    ui -> stackedWidget -> setCurrentIndex(3);

}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}
