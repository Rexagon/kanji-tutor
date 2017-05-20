#ifndef GROUP_H
#define GROUP_H

#include "Category.h"

class Group
{
public:
    Group(const QJsonObject& json);
    ~Group();

    QString getName() const;
    QString getTitle() const;
    std::vector<Category*> getCategories();
	unsigned int getNumCategories() const;
private:
    QString m_name;
    QString m_title;

    std::vector<std::unique_ptr<Category>> m_categories;
};

#endif // GROUP_H
