#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// ui/1: MainWindow UI element – the main window of NotesApp
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;  // ux/1: Save size on close
    void showEvent(QShowEvent *event) override;    // ux/2: Restore size on show

private:
    void loadWindowSize();  // ux/3: Load saved size for ui/1
    void saveWindowSize();  // ux/4: Save current size of ui/1
};

#endif // MAINWINDOW_H
