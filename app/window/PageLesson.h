#ifndef PAGELESSON_H
#define PAGELESSON_H

#include "../widgets/LessonListItem.h"
#include "PageExercise.h"

class PageLesson : public Page
{
	Q_OBJECT
public:
	PageLesson(Ui::MainWindow* ui, PageExercise* pageExercise);

	void setLesson(Lesson* lesson);

	void setListItem(LessonListItem* listItem);
	LessonListItem* getListItem();
signals:
	void backButtonPressed();
	void kanjiSelected(Hieroglyph* kanji);
private:
	void updateFirstTab(Lesson* lesson);
	void updateSecondTab(Lesson* lesson);
	void updateThirdTab(Lesson* lesson);

	LessonListItem* m_listItem;
	PageExercise* m_pageExercise;
};

#endif // PAGELESSON_H
