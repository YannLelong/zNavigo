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
    loadingProgress->setVisible(true);
    loadingProgress->setMaximumHeight(14);
    loadingProgress->setTextVisible(true);
    ui->statusBar->addWidget(loadingProgress, 1);

    //TABS
    QTabWidget *tabs = new QTabWidget();
    tabs->addTab(createNewPage("http://www.google.com/"),"TITRE");
    setCentralWidget(tabs);


    //OTHER ACTIONS
    connect(ui->actionClose,SIGNAL(triggered()),qApp,SLOT(quit())); //close
    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));   //aboutQt
    connect(ui->actionAbout_zNavigo,SIGNAL(triggered()),this,SLOT(aboutUs()));	//about us
    connect(ui->actionPrevious_page,SIGNAL(triggered()),this,SLOT(previous()));	//previous page
    connect(ui->actionNext_page,SIGNAL(triggered()),this,SLOT(next()));	//next page
    connect(ui->actionStop,SIGNAL(triggered()),this,SLOT(stop()));	//stop loading
    connect(ui->actionRefresh_page,SIGNAL(triggered()),this,SLOT(refresh()));	//refresh page
    connect(ui->actionGo,SIGNAL(triggered()),this,SLOT(loadPage()));	//go to URL
    connect(ui->actionHome,SIGNAL(triggered()),this,SLOT(home()));	//home page
    connect(ui->actionClose_Tab,SIGNAL(triggered()),this,SLOT(closeTab()));	//close tab
}

MainWindow::~MainWindow()
{
    delete ui;
}

//GETTERS
QLineEdit *MainWindow::getAddressBar()
{
    return ui->toolBarFichier->findChild<QLineEdit *>();
}

QProgressBar *MainWindow::getLoadingProgress()
{
    return ui->statusBar->findChild<QProgressBar *>();
}

QTabWidget *MainWindow::getTabs()
{
    return ui->centralwidget->findChild<QTabWidget *>();
}

//SLOTS
void MainWindow::newTab()
{
    QTabWidget *tabBar = getTabs();
    QLineEdit *address = getAddressBar();

    int newTabIndex = tabBar->addTab(createNewPage(),"New Tab");
    tabBar->setCurrentIndex(newTabIndex);

    address->setText("");
    address->setFocus();
}

void MainWindow::closeTab()
{
    getTabs()->removeTab(getTabs()->currentIndex());
}

void MainWindow::previous()
{
    currentPage()->back();
}

void MainWindow::next()
{
    currentPage()->forward();
}

void MainWindow::stop()
{
    currentPage()->stop();
}

void MainWindow::refresh()
{
    currentPage()->reload();
}

void MainWindow::home()
{
    currentPage()->load(QUrl("home.html"));
}

void MainWindow::loadPage()
{
    QString url = getAddressBar()->text();

    if(url.isEmpty()){
        currentPage()->load(QUrl("_blank.html"));
    }
    else{
        if((url.left(7) != "http://") && (url.left(8) != "https://")){
            url += "http://" + url;
        }
    }
    currentPage()->load(QUrl(url));
}

void MainWindow::aboutUs()
{
    QMessageBox::information(this,"About us...","This is a lab from Open Classroom's lesson on how to program in C++.");
}


void MainWindow::finishedLoading(bool ok)
{
    getLoadingProgress()->setVisible(false);
    if(ok){
        statusBar()->showMessage("Ready",3000);
    }
    else{
        statusBar()->showMessage("Loading failed",5000);
    }
}

void MainWindow::progressLoading(int progress)
{
    getLoadingProgress()->setValue(progress);
}

void MainWindow::startedLoading()
{
    getLoadingProgress()->setVisible(true);
}

void MainWindow::changedTitle(QString newTitle)
{
    QTabWidget *tabBar = new QTabWidget;
    tabBar = ui->centralwidget->findChild<QTabWidget *>();
    //tabBar->setTabText(tabBar->currentIndex(),newTitle);
    setWindowTitle(newTitle + " - zNavigo");
}

void MainWindow::changedUrl(const QUrl &url)
{
    getAddressBar()->setText(url.toString());
}

//GENERAL METHODS
QWidget *MainWindow::createNewPage(QString url)
{
    QWidget *tabPage = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QWebView *webPage = new QWebView;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(webPage);
    tabPage->setLayout(layout);

    //USE OF THE GENERATED SIGNALS
    connect(webPage,SIGNAL(loadFinished(bool)),this,SLOT(finishedLoading(bool)));
    connect(webPage,SIGNAL(loadProgress(int)),this,SLOT(progressLoading(int)));
    connect(webPage,SIGNAL(loadStarted()),this,SLOT(startedLoading()));
    //connect(webPage,SIGNAL(titleChanged(QString)),this,SLOT(changedTitle(QString)));
    connect(webPage,SIGNAL(urlChanged(QUrl)),this,SLOT(changedUrl(QUrl)));

    if(url.isEmpty()){
        webPage->load(QUrl("_blank.html"));
    }
    else{
        if((url.left(7) != "http://") && (url.left(8) != "https://")){
            url += "http://" + url;
        }
        webPage->load(QUrl(url));
    }

    return tabPage;
}

QWebView *MainWindow::currentPage()
{
    return getTabs()->currentWidget()->findChild<QWebView *>();
}
