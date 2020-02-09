#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	QFont static DPI_Font(QFont font);
private slots:
    void on_btnAbout_clicked();

    void on_btnComputer_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
