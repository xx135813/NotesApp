#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QPushButton>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQueryModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // ui/1: Constructor for the main window
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;  // ui/1: Event when closing window
    void showEvent(QShowEvent *event) override;    // ui/1: Event when showing window

private:
    void loadWindowSize();  // ui/1: Load window size from settings
    void saveWindowSize();  // ui/1: Save window size to settings
    void createMenuButton();  // ui/2: Create the "three dots" button
    void showMenu();  // ui/2: Show menu when button is clicked
    void dataConnect();  // ux/1: Handle opening/closing database
    void loadDatabase();  // ux/1: Load database from settings
    void saveDatabase();  // ux/1: Save database to settings
    void openDatabase(const QString &dbPath);  // ux/1: Open the database
    void closeDatabase();  // ux/1: Close the database and clear cache
    void clearCache();  // ux/1: Clear cache and reset data

    QPushButton *menuButton;  // ui/2: Button for "three dots"
    QMenu *menu;  // ui/2: Menu for the button
    QSqlDatabase db;  // ux/1: Database object (non-static)
    QSqlQueryModel *model;  // ux/1: Model for database queries (non-static)
    QString currentDatabase;  // ux/1: Store the current database name (non-static)
};

#endif // MAINWINDOW_H
