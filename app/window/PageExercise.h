#ifndef PAGEEXERCISE_H
#define PAGEEXERCISE_H

#include "Page.h"

#include "../models/Hieroglyph.h"

#include <QAbstractButton>
#include <QTimer>

enum ExerciseType {
	KanjiTranslation,
	TranslationKanji,
	KanjiReading
};

class PageExercise : public Page
{
	Q_OBJECT
public:
	PageExercise(Ui::MainWindow* ui);

	void setExercise(const QString& title, int type, const std::vector<Hieroglyph*>& hieroglyphs);
signals:
	void backButtonPressed();
	void exerciseCompleted(int score);
private:
	void updateTask();

	QTimer* m_timer;

	std::vector<Hieroglyph*> m_hieroglyphs;
	int m_maximumScore;

	std::vector<QAbstractButton*> m_currentOptions;
	std::vector<QString> m_currentAnswer;
	QString m_currentTask;

	unsigned int m_currentHieroglyph;
	int m_currentExerciseType;
	int m_currentScore;
};

#endif // PAGEEXERCISE_H
