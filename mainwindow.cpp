#include "mainwindow.h"
#include "outline.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);
    widget->resize(400, 300);
    QPushButton *m_click = new QPushButton(widget);
    m_click->setGeometry(10, 10, 100, 30);
    m_click->setText("click");
//    connect(m_click, SIGNAL(clicked()), this, SLOT(outlineShow()));
    connect(m_click, SIGNAL(released()), this, SLOT(outlineHide()));
    connect(m_click, SIGNAL(pressed()), this, SLOT(outlineShow()));
    outlineShow();
}

void MainWindow::outlineShow()
{
    tmp::outline()->show();
    qDebug() << "button clicked." << endl;
}

void MainWindow::outlineHide()
{
    tmp::outline()->hide();
    qDebug() << "button released." << endl;
}

MainWindow::~MainWindow()
{
}

