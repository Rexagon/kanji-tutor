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

	updatePercentage();
}

void LessonListItem::updatePercentage()
{
	int percentage = 0;
	int numExercises = 0;
	std::vector<Exercise*> exercises = m_lesson->getExercises();
	numExercises += exercises.size();
	for (auto exercise : exercises) {
		percentage += exercise->getSavedPercentage();
	}
	exercises = m_lesson->getRevisionExercises();
	numExercises += exercises.size();
	for (auto exercise : exercises) {
		percentage += exercise->getSavedPercentage();
	}
	percentage = std::floor(static_cast<float>(percentage) / static_cast<float>(numExercises));

	m_labelPercentage->setText(QString::number(percentage) + "%");

	if (percentage == 0) {
		m_labelPercentage->setStyleSheet("color: black");
	}
	else if (percentage < 50) {
		m_labelPercentage->setStyleSheet("color: red");
	}
	else if (percentage >= 50 && percentage < 70) {
		m_labelPercentage->setStyleSheet("color: orange");
	}
	else if (percentage >= 70 && percentage < 90) {
		m_labelPercentage->setStyleSheet("color: green");
	}
	else if (percentage >= 90) {
		m_labelPercentage->setStyleSheet("color: #1ece21");
	}
}
