#ifndef LESSONSLISTITEM_H
#define LESSONSLISTITEM_H

#include <QWidget>

class LessonsListItem : public QWidget
{
	Q_OBJECT
public:
	explicit LessonsListItem(QWidget *parent = 0);

protected:
	void mousePressEvent(QMouseEvent *event) override;

};

#endif // LESSONSLISTITEM_H
