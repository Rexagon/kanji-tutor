#ifndef EXERCISEKANJITRANSLATION_H
#define EXERCISEKANJITRANSLATION_H

#include "Exercise.h"

class ExerciseKanjiTranslation : public Exercise
{
public:
	ExerciseKanjiTranslation(const QString& categoryName, const QString& title, const std::vector<Hieroglyph*>& hieroglyphs);

	void update() override;

	QAbstractButton* createOptionItem(const QString& text) const override;
};

#endif // EXERCISEKANJITRANSLATION_H
