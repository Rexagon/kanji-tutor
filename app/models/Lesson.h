#ifndef LESSON_H
#define LESSON_H

#include <vector>
#include <memory>

#include "Hieroglyph.h"
#include "Exercise.h"

class Category;

class Lesson
{
public:
	Lesson(const QString& path, Category* category = nullptr, int id = -1);
    ~Lesson();

	Category* getCategory() const;
	int getId() const;

	QString getName() const;
	std::vector<Hieroglyph*> getHieroglyphs() const;
	unsigned int getHieroglyphsNum() const;

	std::vector<Exercise*> getExercises() const;
	std::vector<Exercise*> getRevisionExercises() const;
private:
	Category* m_category;
	int m_id;

	QString m_name;
	std::vector<std::unique_ptr<Hieroglyph>> m_hieroglyphs;

	std::vector<std::unique_ptr<Exercise>> m_exercises;
	std::vector<std::unique_ptr<Exercise>> m_revisionExercises;
};

#endif // LESSON_H
