#include "mainwindow.h"
#include "outline.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);
    widget->resize(900, 300);
    QPushButton *m_click = new QPushButton(widget);
    m_click->setGeometry(10, 10, 100, 30);
    m_click->setText("click");
//    connect(m_click, SIGNAL(released()), this, SLOT(outlineHide()));
//    connect(m_click, SIGNAL(pressed()), this, SLOT(outlineShow()));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug() << "resizeEvent in";
    if (this->width() > 600) {
        outlineShow();
    } else {
        outlineHide();
    }
    return QMainWindow::resizeEvent(event);
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    qDebug() << "moveEvent in";
    return QMainWindow::moveEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";
    outlineShow();
    return QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "mouseReleaseEvent";
    outlineHide();
    return QMainWindow::mouseReleaseEvent(event);
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

