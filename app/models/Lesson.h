#ifndef LESSON_H
#define LESSON_H

#include <vector>
#include <memory>

#include "Hieroglyph.h"

class Category;

class Lesson
{
public:
	Lesson(const QString& path, Category* category = nullptr, int id = 0);
    ~Lesson();

	Category* getCategory() const;
	int getId() const;

	QString getName() const;
	std::vector<Hieroglyph*> getHieroglyphs() const;
private:
	Category* m_category;
	int m_id;

	QString m_name;
	std::vector<std::unique_ptr<Hieroglyph>> m_hieroglyphs;
};

#endif // LESSON_H
