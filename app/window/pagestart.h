#ifndef PAGESTART_H
#define PAGESTART_H

#include "page.h"

#include "../models/category.h"

class PageStart : public Page
{
    Q_OBJECT
public:
    PageStart(Ui::MainWindow* ui);
signals:
    void categorySelected(Category* category);
};

#endif // PAGESTART_H
