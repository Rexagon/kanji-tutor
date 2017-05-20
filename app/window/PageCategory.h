#ifndef PAGECATEGORY_H
#define PAGECATEGORY_H

#include "../widgets/LessonListItem.h"
#include "../models/Category.h"
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
	void lessonSelected(LessonListItem* listItem, Lesson* lesson);
};

#endif // PAGECATEGORY_H
