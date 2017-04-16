#ifndef PAGECATEGORYTESTS_H
#define PAGECATEGORYTESTS_H

#include "page.h"

#include "../models/Category.h"

#include "PageExercise.h"

class PageCategoryTests : public Page
{
	Q_OBJECT
public:
	PageCategoryTests(Ui::MainWindow* ui, PageExercise* pageExercise);

	void setCategory(Category* category);
signals:
	void backButtonPressed();
private:
	PageExercise* m_pageExercise;
};

#endif // PAGECATEGORYTESTS_H
