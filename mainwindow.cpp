#include "mainwindow.h"
#include <QSettings>
#include <QCloseEvent>
#include <QShowEvent>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    menuButton(nullptr),  // Initialize menuButton for ui/2
    menu(new QMenu(this)) // Initialize menu for ui/2
{
    loadWindowSize();  // Load the window size when the application starts (ui/1)

    createMenuButton();  // Create the "three dots" button (ui/2)
}

MainWindow::~MainWindow()
{
    saveWindowSize();  // Save the window size when the application is closed (ui/1)
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveWindowSize();  // Save the window size before closing (ui/1)
    event->accept();
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    loadWindowSize();  // Load the window size when the window is shown (ui/1)
}

void MainWindow::loadWindowSize()
{
    QSettings settings("MyCompany", "NotesApp");  // Store settings for ui/1
    QSize size = settings.value("window/size", QSize(800, 600)).toSize();  // Default size for ui/1
    this->resize(size);  // Resize the main window (ui/1)
}

void MainWindow::saveWindowSize()
{
    QSettings settings("MyCompany", "NotesApp");  // Store settings for ui/1
    settings.setValue("window/size", this->size());  // Save the current size of ui/1
}

void MainWindow::createMenuButton()
{
    // Create the menu button with "..." icon (ui/2)
    menuButton = new QPushButton("...", this);
    menuButton->setStyleSheet("QPushButton { font-size: 14px; font-weight: bold; padding: 1px 3px; border: none; }");  // Style for button (ui/2) (smaller and bold)
    menuButton->setGeometry(5, 5, 15, 15);  // Position and size of the "three dots" button (ui/2)

    connect(menuButton, &QPushButton::clicked, this, &MainWindow::showMenu);  // Connect button click to show the menu (ui/2)

    // Create the menu items for the button (ui/2)
    menu->addAction("DataConnect");
    menu->addAction("Color scheme");
}

void MainWindow::showMenu()
{
    // Show the menu under the "three dots" button (ui/2)
    menu->exec(menuButton->mapToGlobal(QPoint(0, menuButton->height())));  // Position the menu below the button (ui/2)
}
