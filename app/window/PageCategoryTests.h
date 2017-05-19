#ifndef PAGECATEGORYTESTS_H
#define PAGECATEGORYTESTS_H

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
	std::vector<std::unique_ptr<Exercise>> m_exercises;
	PageExercise* m_pageExercise;
};

#endif // PAGECATEGORYTESTS_H
