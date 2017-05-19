#ifndef PAGELESSON_H
#define PAGELESSON_H

#include "../models/Lesson.h"
#include "PageExercise.h"

class PageLesson : public Page
{
	Q_OBJECT
public:
	PageLesson(Ui::MainWindow* ui, PageExercise* pageExercise);

	void setLesson(Lesson* lesson);
signals:
	void backButtonPressed();
	void kanjiSelected(Hieroglyph* kanji);
private:
	void updateFirstTab(Lesson* lesson);
	void updateSecondTab(Lesson* lesson);
	void updateThirdTab(Lesson* lesson);

	std::vector<std::unique_ptr<Exercise>> m_exercises;
	PageExercise* m_pageExercise;
};

#endif // PAGELESSON_H
