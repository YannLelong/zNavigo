#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLineEdit *addressBar = new QLineEdit;
    QProgressBar *loadingProgress = new QProgressBar();
    loadingProgress->setVisible(true);
    loadingProgress->setMaximumHeight(14);
    loadingProgress->setTextVisible(true);
    ui->toolBarFichier->insertWidget(ui->actionHome, addressBar);
    ui->statusBar->addWidget(loadingProgress, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
