#ifndef CATEGORY_H
#define CATEGORY_H

#include "lesson.h"

class Category
{
public:
    Category(const QString& path);
    ~Category();

    QString getName() const;

    std::vector<Lesson*> getLessons();
private:
    QString m_name;

    std::vector<std::unique_ptr<Lesson>> m_lessons;
};

#endif // CATEGORY_H
