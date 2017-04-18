#ifndef PAGECATEGORYKANJI_H
#define PAGECATEGORYKANJI_H

#include "../models/Hieroglyph.h"
#include "../models/Category.h"
#include "Page.h"

class PageCategoryKanji : public Page
{
	Q_OBJECT
public:
	PageCategoryKanji(Ui::MainWindow* ui);

	void setCategory(Category* category);
signals:
	void backButtonPressed();
	void kanjiSelected(Hieroglyph* kanji);
};

#endif // PAGECATEGORYKANJI_H
