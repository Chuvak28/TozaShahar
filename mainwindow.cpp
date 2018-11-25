#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick>
#include <QtQuickWidgets/QQuickWidget>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createGUI();
    sqlModel = new SqlQueryModel(this);
    bool check = createConnection();
    if(check==true)
    {
        sqlModel->setQuery("select Lat,Lon from dataMVD");
        viewTable->setModel(sqlModel);
    }
//    else
//    {
//        qDebug() << "Cannot open database:" << db.lastError();
//    }


    //==========QML===============
    QQuickView *view = new QQuickView();

    container = QWidget::createWindowContainer(view,this);
    //container->setMinimumSize(200,200);
    //container->setMaximumSize(200,200);

    QQmlContext *ctxt = view->rootContext();
    ctxt->setContextProperty("sqlModel", sqlModel);
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    //==========QML===============
    QSplitter *spl = new QSplitter(Qt::Vertical);

    spl->addWidget(container);
    spl->addWidget(viewTable);

    tabWidget->addTab(spl,"MAP");
    ui->gridLayout->addWidget(tabWidget);

    showMaximized();
    setWindowTitle("Clean City");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGUI()
{
    //QTABWIDGET
    tabWidget = new QTabWidget (this) ;
    //tabWidget->hide();
    //QTABLEVIEW
    viewTable = new QTableView;
    viewTable->setMaximumHeight(250);
    viewTable->setSelectionBehavior(QAbstractItemView::SelectRows);


    //FILE MENU
    quitAction = new QAction(tr("&Quit"),this);
    connect(quitAction,&QAction::triggered,this,&MainWindow::close);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(quitAction);
    //helpMenu = menuBar()->addMenu(tr("&Help"));
}

bool MainWindow::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("MVD");
    db.setUserName("root");
    db.setPassword("Jasur@295");
    if(!db.open())
    {
        return false;

    }
    return true;
}
