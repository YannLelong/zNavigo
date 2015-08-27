#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ADDRESS BAR
    QLineEdit *addressBar = new QLineEdit;
    ui->toolBarFichier->insertWidget(ui->actionHome, addressBar);

    //PROGRESS BAR
    QProgressBar *loadingProgress = new QProgressBar();
    loadingProgress->setVisible(false);
    loadingProgress->setMaximumHeight(14);
    loadingProgress->setTextVisible(true);
    ui->statusBar->addWidget(loadingProgress, 1);

    //OTHER ACTIONS
    connect(ui->actionClose,SIGNAL(triggered()),qApp,SLOT(quit())); //close
    connect(ui->actionAbout_Qt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));   //aboutQt
}

MainWindow::~MainWindow()
{
    delete ui;
}
