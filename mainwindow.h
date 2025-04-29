#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // Constructor for the main window (ui/1)
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;  // Event for closing the window (ui/1)
    void showEvent(QShowEvent *event) override;    // Event for showing the window (ui/1)

private:
    void loadWindowSize();  // Load the window size from settings (ui/1)
    void saveWindowSize();  // Save the window size to settings (ui/1)
    void createMenuButton();  // Create the "three dots" button (ui/2)
    void showMenu();  // Show the menu when the button (ui/2) is clicked

    QPushButton *menuButton;  // Member variable for the "three dots" button (ui/2)
    QMenu *menu;  // Menu for ui/2
};

#endif // MAINWINDOW_H
