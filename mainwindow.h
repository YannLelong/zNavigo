#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtWebKit>
#include <QWebView>

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
    void loadPage();

    void aboutUs();

    void finishedLoading(bool ok);
    void progressLoading(int progress);
    void startedLoading();
    void changedTitle(QString newTitle);
    void changedUrl(const QUrl &url);

private:
    Ui::MainWindow *ui;

    QLineEdit *addressBar;
    QLineEdit *getAddressBar();

    QProgressBar *loadingProgress;
    QProgressBar *getLoadingProgress();

    QTabWidget *tabs;
    QTabWidget *getTabs();

    QWidget *createNewPage(QString url = "");

    QWebView *currentPage();
};

#endif // MAINWINDOW_H
