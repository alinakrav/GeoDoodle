#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_cartoon1_clicked();
    void on_cartoon2_clicked();
    void on_cartoon3_clicked();
    void on_cartoon4_clicked();
    void on_cartoon5_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_spinBox_valueChanged(const int &arg1);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int radius;
    QString s;
    QString url;
};
#endif // MAINWINDOW_H
