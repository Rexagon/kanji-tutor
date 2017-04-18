#ifndef PAGECATEGORY_H
#define PAGECATEGORY_H

#include "../models/Category.h"
#include "../models/Lesson.h"
#include "Page.h"

class PageCategory : public Page
{
	Q_OBJECT
public:
	PageCategory(Ui::MainWindow* ui);

	void setCategory(Category* category);
signals:
	void backButtonPressed();
	void kanjiButtonPressed(Category* category);
	void testsButtonPressed(Category* category);
	void lessonSelected(Lesson* lesson);
};

#endif // PAGECATEGORY_H
