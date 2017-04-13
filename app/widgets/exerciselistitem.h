#ifndef EXERCISELISTITEM_H
#define EXERCISELISTITEM_H

#include <QWidget>

class ExerciseListItem : public QWidget
{
	Q_OBJECT
public:
	ExerciseListItem(const QString& title, const QString& description);

signals:
    void onStart();
};

#endif // EXERCISELISTITEM_H
