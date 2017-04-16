#ifndef CATEGORY_H
#define CATEGORY_H

#include "Lesson.h"

class Group;

class Category
{
public:
	Category(const QString& path, Group* group = nullptr);
    ~Category();

	Group* getGroup() const;

    QString getName() const;
    std::vector<Lesson*> getLessons();
private:
	Group* m_group;

    QString m_name;
    std::vector<std::unique_ptr<Lesson>> m_lessons;
};

#endif // CATEGORY_H
