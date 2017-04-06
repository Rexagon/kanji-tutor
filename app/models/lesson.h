#ifndef LESSON_H
#define LESSON_H

#include <vector>
#include <memory>

#include "hieroglyph.h"

class Lesson
{
public:
    Lesson(const QString& path);
    ~Lesson();

    QString getName() const;

	std::vector<Hieroglyph*> getHieroglyphs() const;
private:
    QString m_name;

	std::vector<std::unique_ptr<Hieroglyph>> m_hieroglyphs;
};

#endif // LESSON_H
