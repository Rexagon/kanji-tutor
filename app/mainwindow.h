#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    enum Pages {
        StartPage,
        CategoryPage,
        LessonPage
    };

    void createMenu();

    void createStartPage();
    void createCategoryPage();
    void createLessonPage();

    QPushButton* createCategoryButton(const QString& text, int id);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
