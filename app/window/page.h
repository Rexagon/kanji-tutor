#ifndef PAGE_H
#define PAGE_H

#include <QObject>

namespace Ui
{
    class MainWindow;
}

class Page : public QObject
{
    Q_OBJECT
public:
    enum Id {
        StartPage,
        CategoryPage,
        LessonPage,
        CategoryKanjiPage,
        CategoryTestsPage
    };

    Page(Ui::MainWindow* ui, int pageId);

    void setCurrent();
protected:
    Ui::MainWindow* m_ui;
    int m_id;
};

#endif // PAGE_H
