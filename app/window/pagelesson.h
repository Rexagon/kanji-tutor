#ifndef PAGELESSON_H
#define PAGELESSON_H

#include "page.h"

#include "../models/lesson.h"

class PageLesson : public Page
{
	Q_OBJECT
public:
	PageLesson(Ui::MainWindow* ui);

	void setLesson(Lesson* lesson);
signals:
	void backButtonPressed();
	void kanjiSelected(Hieroglyph* kanji);
};

#endif // PAGELESSON_H
