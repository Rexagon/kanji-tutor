#include "LessonListItem.h"

#include <QGridLayout>

LessonListItem::LessonListItem(Lesson* lesson, QWidget *parent) : QPushButton(parent)
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
	labelName->setFont(QFont("Tahoma", 12, 10));
	gridLayout->addWidget(labelName, 0, 0, 1, 5);

	// Hieroglyphs
	QLabel* labelHieroglyphs = new QLabel("Иероглифы:");
	labelHieroglyphs->setFont(QFont("Tahoma", 10, 10));
	gridLayout->addWidget(labelHieroglyphs, 1, 0, 1, 1);

	// Hieroglyphs list
	QString hieroglyphsList;
	std::vector<Hieroglyph*> lessonHieroglyphs = lesson->getHieroglyphs();
	for (const auto& hieroglyph : lessonHieroglyphs) {
		hieroglyphsList += hieroglyph->getSymbol() + " ";
	}
	QLabel* labelHieroglyphsList = new QLabel(hieroglyphsList);
	labelHieroglyphsList->setFont(QFont("Batang", 10, 10));
	gridLayout->addWidget(labelHieroglyphsList, 1, 1, 1, 4);

	// Lesson complete percent
	//TODO: create lesson completion percentage
}
