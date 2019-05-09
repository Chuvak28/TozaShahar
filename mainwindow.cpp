#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick>
#include <QtQuickWidgets/QQuickWidget>
#include <QSplitter>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createGUI();
    sqlModel = new SqlQueryModel(this);
    bool check = createConnection();
    if(check==true)
    {
        sqlModel->setQuery("select Origin_Time,TIP,"
                           "Description,LATITUDE,LONGTITUDE from dataInfo");
        ui->dataMapView->setModel(sqlModel);

    }
//    else
//    {
//        qDebug() << "Cannot open database:" << db.lastError();
//    }


    //==========QML===============
    //QQuickView *view = new QQuickView();

    //container = QWidget::createWindowContainer(ui->quickWidget,this);


    QQmlContext *ctxt = ui->quickWidget->rootContext();
    ctxt->setContextProperty("sqlModel", sqlModel);
    //ui->quickWidget->setResizeMode(ui->quickWidget->SizeRootObjectToView);
    //view->setResizeMode(QQuickView::SizeRootObjectToView);
    //view->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    //==========QML===============
    //QSplitter *spl = new QSplitter(Qt::Vertical);

    //spl->addWidget(ui->quickWidget);
    //spl->addWidget(ui->dataMapView);





    //ui->tabWidget->addTab(widTableView,"Events");
    //ui->gridLayout->addWidget(tabWidget);


    //connect(btnReadDataBase,&QPushButton::clicked,this,&MainWindow::getDataFromDB);
    showMaximized();
    setWindowTitle("Clean City1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGUI()
{
//    widTableView = new QWidget;
//    meetingEdit = new QDateTimeEdit(QDateTime::currentDateTime());
//    meetingEdit1 = new QDateTimeEdit(QDateTime::currentDateTime());
//    tableEvent = new QTableView;
//    btnReadDataBase = new QPushButton("Read");
//    QHBoxLayout *hBox = new QHBoxLayout;
//    hBox->addStretch(1);
//    hBox->addWidget(new QLabel("From"));

//    hBox->addWidget(meetingEdit);
//    hBox->addWidget(new QLabel("To"));
//    hBox->addWidget(meetingEdit1);
//    hBox->addWidget(btnReadDataBase);
//    QVBoxLayout *vBox = new QVBoxLayout;
//    vBox->addWidget(tableEvent);
//    vBox->addLayout(hBox);
//    widTableView->setLayout(vBox);


    //QTABWIDGET
   // tabWidget = new QTabWidget (this) ;
    //tabWidget->hide();
    //QTABLEVIEW
    //viewTable = new QTableView;
    //viewTable->setMaximumHeight(250);
    //viewTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    //FILE MENU
    quitAction = new QAction(tr("&Quit"),this);
    connect(quitAction,&QAction::triggered,this,&MainWindow::close);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAction);
    //helpMenu = menuBar()->addMenu(tr("&Help"));
}

void MainWindow::getDataFromDB()
{

    sqlModel->setQuery("select * from dataInfo");
    tableEvent->setModel(sqlModel);
}

bool MainWindow::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("toza_shahar");
    db.setUserName("root");
    db.setPassword("Jasur@295");
    if(!db.open())
    {
        return false;

    }
    return true;
}
