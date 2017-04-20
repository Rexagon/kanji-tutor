#ifndef LESSONLISTITEM_H
#define LESSONLISTITEM_H

#include <QPushButton>
#include <QLabel>

#include "../models/Lesson.h"

class LessonListItem : public QPushButton
{
	Q_OBJECT
public:
	explicit LessonListItem(Lesson* lesson, QWidget *parent = 0);

	void updatePercentage();
private:
	Lesson* m_lesson;

	QLabel* m_labelPercentage;
};

#endif // LESSONLISTITEM_H
