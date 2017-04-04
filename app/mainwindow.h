#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "group.h"

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

    void loadData();

    void createMenu();

    void createStartPage();
    void createCategoryPage();
    void createLessonPage();

    QPushButton* createCategoryButton(Category* category);

    Ui::MainWindow *ui;

    std::vector<std::unique_ptr<Group>> m_groups;
};

#endif // MAINWINDOW_H
