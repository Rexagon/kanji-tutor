#ifndef CATEGORY_H
#define CATEGORY_H

#include "Lesson.h"

class Group;

class Category
{
public:
	Category(const QString& path, Group* group = nullptr, int id = -1);
    ~Category();

	Group* getGroup() const;
	int getId() const;

    QString getName() const;
    std::vector<Lesson*> getLessons();
	unsigned int getLessonsNum() const;
private:
	Group* m_group;
	int m_id;

    QString m_name;
    std::vector<std::unique_ptr<Lesson>> m_lessons;
};

#endif // CATEGORY_H
