#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "penmodel.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_editor_textChanged();
    void draw();
    void on_actionAboutQt_triggered();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    PenModel model;
};

#endif // MAINWINDOW_H
