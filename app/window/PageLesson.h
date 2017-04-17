#ifndef PAGELESSON_H
#define PAGELESSON_H

#include <functional>

#include "Page.h"

#include "../models/Lesson.h"
#include "../window/PageExercise.h"

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

	std::function<void ()> createStartEvent(const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs);

	PageExercise* m_pageExercise;
};

#endif // PAGELESSON_H
