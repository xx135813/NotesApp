#include "mainwindow.h"
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QCloseEvent>
#include <QShowEvent>
#include <QSqlDatabase>
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    menuButton(nullptr),
    menu(new QMenu(this)),
    db(QSqlDatabase::addDatabase("QSQLITE")),  // Initialize db object
    model(new QSqlQueryModel())  // Initialize model object
{
    loadWindowSize();  // ui/1: Load the window size when the application starts
    loadDatabase();    // ux/1: Load the database information when the application starts
    createMenuButton();  // ui/2: Create the "three dots" button
}

MainWindow::~MainWindow()
{
    saveWindowSize();  // ui/1: Save the window size before closing
    saveDatabase();    // ux/1: Save the database information before closing
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Check if the database is connected (non-empty currentDatabase means connected)
    if (!currentDatabase.isEmpty()) {
        closeDatabase();  // Call the cleanup function to clear data and close the database connection
        saveDatabase();   // Save the database path so it can be reconnected automatically
    }
    saveWindowSize();  // Save the window size before closing
    event->accept();   // Accept the event and allow the application to close
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);  // ui/1: Call the base class's showEvent
    // No need to call loadWindowSize() here, so the window size doesn't reset on restore after minimize.
}

void MainWindow::createMenuButton()
{
    menuButton = new QPushButton("...", this);  // ui/2: Create the menu button (three dots)
    menuButton->setStyleSheet("QPushButton { font-size: 14px; font-weight: bold; padding: 1px 3px; border: none; }");
    menuButton->setGeometry(5, 5, 15, 15);  // ui/2: Position of the "three dots" button

    connect(menuButton, &QPushButton::clicked, this, &MainWindow::showMenu);  // ui/2: Connect to show the menu
    menu->addAction("DataConnect");  // ux/1: Action for DataConnect
    menu->addAction("Color scheme");  // ux/2: Action for color scheme (placeholder for future functionality)

    connect(menu->actions().at(0), &QAction::triggered, this, &MainWindow::dataConnect);  // ux/1: Connect to DataConnect action
}

void MainWindow::showMenu()
{
    menu->exec(menuButton->mapToGlobal(QPoint(0, menuButton->height())));  // ui/2: Show menu below the button
}

void MainWindow::dataConnect()
{
    if (currentDatabase.isEmpty()) {  // ux/1: If no database is open, show dialog to select one
        QString filePath = QFileDialog::getOpenFileName(this, "Select Database", "", "SQLite Database Files (*.db)");
        if (!filePath.isEmpty()) {
            currentDatabase = filePath;
            setWindowTitle("NotesApp - " + QFileInfo(filePath).fileName());  // ui/1: Set window title to the database name
            openDatabase(filePath);  // Open the selected database
        }
    } else {  // ux/1: If a database is already open, close it
        currentDatabase.clear();
        setWindowTitle("NotesApp");  // ui/1: Reset window title
        closeDatabase();  // Call the cleanup function to clear data and close the database connection
    }
}

void MainWindow::openDatabase(const QString &dbPath)
{
    // Open the database connection and load the data
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (db.open()) {
        // Initialize the model if needed
        model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM your_table_name", db);  // Example query to load data into the model
        // Connect the model to your UI components like a table view
        // ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Error", "Failed to open the database.");
    }
}

void MainWindow::closeDatabase()
{
    // Clear any in-memory data related to the database
    clearCache();  // ux/1: Clear the cache and reset the UI

    // Close the database connection
    if (db.isOpen()) {
        db.close();
        db = QSqlDatabase();  // Reset the database object
    }

    // Optionally, reset any UI elements related to the database
    // ui->tableView->setModel(nullptr);  // Example: reset the table view
}

void MainWindow::clearCache()
{
    // Example: Clear in-memory data structures or cache
    if (model) {
        model->clear();  // Clear the model data
        delete model;  // Delete the model to free memory
        model = nullptr;
    }

    // Clear any other data structures or UI elements holding data from the database
    // For example, if you have custom data structures, clear them here.
}

void MainWindow::loadWindowSize()
{
    QSettings settings("MyCompany", "NotesApp");  // ui/1: Load window size from settings
    QSize size = settings.value("window/size", QSize(800, 600)).toSize();  // ui/1: Default size for the window
    this->resize(size);  // ui/1: Resize the main window to saved size
}

void MainWindow::saveWindowSize()
{
    QSettings settings("MyCompany", "NotesApp");  // ui/1: Save the current size of the window
    settings.setValue("window/size", this->size());  // ui/1: Store the window size
}

void MainWindow::loadDatabase()
{
    QSettings settings("MyCompany", "NotesApp");  // ux/1: Retrieve the last used database
    currentDatabase = settings.value("database/name", "").toString();

    if (!currentDatabase.isEmpty()) {
        setWindowTitle("NotesApp - " + QFileInfo(currentDatabase).fileName());  // ui/1: Set the window title with the opened database name
        openDatabase(currentDatabase);  // Open the last used database
    }
}

void MainWindow::saveDatabase()
{
    QSettings settings("MyCompany", "NotesApp");  // ux/1: Save the database name
    if (!currentDatabase.isEmpty()) {
        settings.setValue("database/name", currentDatabase);  // ux/1: Store the current database name
    } else {
        settings.remove("database/name");  // ux/1: Remove if no database is open
    }
}
