#ifndef PAGECATEGORYTESTS_H
#define PAGECATEGORYTESTS_H

#include "page.h"

#include "../models/category.h"

class PageCategoryTests : public Page
{
	Q_OBJECT
public:
	PageCategoryTests(Ui::MainWindow* ui);

	void setCategory(Category* category);
signals:
	void backButtonPressed();
};

#endif // PAGECATEGORYTESTS_H
