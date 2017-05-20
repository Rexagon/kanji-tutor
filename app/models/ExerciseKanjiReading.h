#ifndef EXERCISEKANJIREADING_H
#define EXERCISEKANJIREADING_H

#include "Exercise.h"

class ExerciseKanjiReading : public Exercise
{
public:
	ExerciseKanjiReading(const QString& categoryName, const QString& title, const std::vector<Hieroglyph*>& hieroglyphs);

	void update() override;

	QAbstractButton* createOptionItem(const QString& text) const override;
};

#endif // EXERCISEKANJIREADING_H
