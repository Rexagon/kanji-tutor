#include "PageCategoryKanji.h"

#include <ui_mainwindow.h>

#include "../widgets/KanjiListItem.h"

PageCategoryKanji::PageCategoryKanji(Ui::MainWindow* ui) :
	Page(ui, Id::CategoryKanjiPage)
{
	connect(ui->categoryKanjiPageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});
}

void PageCategoryKanji::setCategory(Category* category)
{
	m_ui->categoryKanjiPageNameLabel->setText(category->getName() + ". Иероглифы");

	m_ui->categoryKanjiPageKanjiList->clear();
	m_ui->categoryKanjiPageKanjiList->scrollToTop();

	std::vector<Lesson*> lessons = category->getLessons();
	for (unsigned int i = 0; i < lessons.size(); ++i) {
		Lesson* lesson = lessons[i];

		std::vector<Hieroglyph*> hieroglyphs = lesson->getHieroglyphs();
		for (unsigned int j = 0; j < hieroglyphs.size(); ++j) {
			Hieroglyph* hieroglyph = hieroglyphs[j];

			KanjiListItem* widget = new KanjiListItem(hieroglyph);

			connect(widget, &KanjiListItem::pressed, this, [this, hieroglyph]() {
				emit kanjiSelected(hieroglyph);
			});

			QListWidgetItem* item = new QListWidgetItem();
			item->setSizeHint(QSize(0, widget->size().height()));
			m_ui->categoryKanjiPageKanjiList->addItem(item);
			m_ui->categoryKanjiPageKanjiList->setItemWidget(item, widget);
		}
	}
}
