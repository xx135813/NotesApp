#include "mainwindow.h"
#include <QSettings>
#include <QCloseEvent>
#include <QShowEvent>

// ui/1: MainWindow UI element implementation
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    loadWindowSize();  // ux/3: Restore last size of ui/1 when created
}

MainWindow::~MainWindow()
{
    saveWindowSize();  // ux/4: Persist size of ui/1 on destruction
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveWindowSize();  // ux/4: Persist size of ui/1 on close
    event->accept();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    loadWindowSize();  // ux/3: Ensure ui/1 is sized correctly on show
}

void MainWindow::loadWindowSize()
{
    QSettings settings("MyCompany", "NotesApp");
    QSize sz = settings.value("window/size", QSize(800, 600)).toSize();
    this->resize(sz);  // Apply size to ui/1
}

void MainWindow::saveWindowSize()
{
    QSettings settings("MyCompany", "NotesApp");
    settings.setValue("window/size", this->size());  // Store size of ui/1
}
