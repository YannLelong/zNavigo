#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newTab();
    void closeTab();

    void previous();
    void next();
    void stop();
    void refresh();
    void home();

    void aboutUs();

private:
    Ui::MainWindow *ui;

    QLineEdit *addressBar;

    QProgressBar *loadingProgress;

    QTabWidget *tabs;
};

#endif // MAINWINDOW_H
