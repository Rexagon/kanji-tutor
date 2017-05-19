#ifndef EXERCISETRANSLATIONKANJI_H
#define EXERCISETRANSLATIONKANJI_H

#include "Exercise.h"

class ExerciseTranslationKanji : public Exercise
{
public:
	ExerciseTranslationKanji(const QString& categoryName, const QString& title, const std::vector<Hieroglyph*>& hieroglyphs);

	void update() override;

	QAbstractButton* createOptionItem(const QString& text) const override;
};

#endif // EXERCISETRANSLATIONKANJI_H
