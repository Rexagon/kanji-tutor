#ifndef PAGESTART_H
#define PAGESTART_H

#include "../models/Category.h"
#include "Page.h"

class PageStart : public Page
{
    Q_OBJECT
public:
    PageStart(Ui::MainWindow* ui);
signals:
    void categorySelected(Category* category);
};

#endif // PAGESTART_H
