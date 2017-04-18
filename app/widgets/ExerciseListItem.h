#ifndef EXERCISELISTITEM_H
#define EXERCISELISTITEM_H

#include <QWidget>
#include <QLabel>

class ExerciseListItem : public QWidget
{
	Q_OBJECT
public:
	ExerciseListItem(const QString& title, const QString& description);

	void setPercentage(int percentage);
signals:
    void onStart();
private:
	QLabel* m_labelPercentage;
};

#endif // EXERCISELISTITEM_H
