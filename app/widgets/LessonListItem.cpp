#include "LessonListItem.h"

#include <QGridLayout>

#include "../App.h"

LessonListItem::LessonListItem(Lesson* lesson, QWidget *parent)
	: QPushButton(parent), m_lesson(lesson)
{
	this->setFixedHeight(65);
	this->setCursor(QCursor(Qt::PointingHandCursor));
	this->setStyleSheet("\
	QPushButton {\
		border: none;\
		border-bottom: 1px solid gray;\
		background: white;\
	}\
	QPushButton:hover {\
		background: #c7ffad;\
		border-bottom: 2px solid gray;\
	}");

	QGridLayout* gridLayout = new QGridLayout();
	this->setLayout(gridLayout);

	// Lesson name
	QLabel* labelName = new QLabel(lesson->getName());
	labelName->setFont(QFont(App::getDefaultFont(), 12, 10));
	gridLayout->addWidget(labelName, 0, 0, 1, 5);

	// Hieroglyphs
	QLabel* labelHieroglyphs = new QLabel("Иероглифы:");
	labelHieroglyphs->setFont(QFont(App::getDefaultFont(), 10, 10));
	gridLayout->addWidget(labelHieroglyphs, 1, 0, 1, 2);

	// Hieroglyphs list
	QString hieroglyphsList;
	std::vector<Hieroglyph*> lessonHieroglyphs = lesson->getHieroglyphs();
	for (const auto& hieroglyph : lessonHieroglyphs) {
		hieroglyphsList += hieroglyph->getSymbol() + " ";
	}
	QLabel* labelHieroglyphsList = new QLabel(hieroglyphsList);
	labelHieroglyphsList->setFont(QFont(App::getHieroglyphsFont(), 10, 10));
	gridLayout->addWidget(labelHieroglyphsList, 1, 2, 1, 6);

	// Lesson completion percentage
	m_labelPercentage = new QLabel();
	m_labelPercentage->setFont(QFont(App::getDefaultFont(), 12, 10));
	m_labelPercentage->setAlignment(Qt::AlignRight);
	gridLayout->addWidget(m_labelPercentage, 0, 7, 1, 1);
}
