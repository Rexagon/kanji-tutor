#ifndef LESSONLISTITEM_H
#define LESSONLISTITEM_H

#include <QPushButton>
#include <QLabel>

#include "../models/lesson.h"

class LessonListItem : public QPushButton
{
	Q_OBJECT
public:
	explicit LessonListItem(Lesson* lesson, QWidget *parent = 0);

private:

};

#endif // LESSONLISTITEM_H
