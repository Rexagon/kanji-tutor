#ifndef LESSON_H
#define LESSON_H

#include <vector>
#include <memory>

#include "kanji.h"

class Lesson
{
public:
    Lesson(const QString& path);
    ~Lesson();

    QString getName() const;

    std::vector<Kanji*> getKanji() const;
private:
    QString m_name;

    std::vector<std::unique_ptr<Kanji>> m_kanji;
};

#endif // LESSON_H
