#include "Page.h"

#include <ui_mainwindow.h>

Page::Page(Ui::MainWindow *ui, int pageId) :
    m_ui(ui), m_id(pageId)
{
}

void Page::setCurrent()
{
    m_ui->pageSelector->setCurrentIndex(m_id);
}
