#include "pagecategory.h"

#include <ui_mainwindow.h>

#include "../widgets/lessonlistitem.h"

PageCategory::PageCategory(Ui::MainWindow* ui) :
	Page(ui, Id::CategoryPage)
{
	connect(m_ui->categoryPageBackButton, &QPushButton::pressed, this, [this]() {
		emit backButtonPressed();
	});
}

void PageCategory::setCategory(Category* category)
{
	m_ui->categoryPageNameLabel->setText(category->getName());

	connect(m_ui->categoryPageKanjiButton, &QPushButton::pressed, this, [this, category]() {
		emit kanjiButtonPressed(category);
	});

	connect(m_ui->categoryPageTestsButton, &QPushButton::pressed, this, [this, category]() {
		emit testsButtonPressed(category);
	});

	m_ui->categoryPageLessonsList->clear();

	std::vector<Lesson*> lessons = category->getLessons();
	for (unsigned int i = 0; i < lessons.size(); ++i) {
		Lesson* lesson = lessons[i];

		LessonListItem* widget = new LessonListItem(lesson);

		connect(widget, &LessonListItem::pressed, this, [this, lesson]() {
			emit lessonSelected(lesson);
		});

		QListWidgetItem* itemWidget = new QListWidgetItem();
		itemWidget->setSizeHint(QSize(0, widget->size().height()));
		m_ui->categoryPageLessonsList->addItem(itemWidget);
		m_ui->categoryPageLessonsList->setItemWidget(itemWidget, widget);
	}
}
