#include "Group.h"

#include <QJsonArray>

Group::Group(const QJsonObject &json)
{
    m_name = json["name"].toString();
    m_title = json["title"].toString();

    QJsonArray categories = json["categories"].toArray();
    for (int i = 0; i < categories.size(); ++i) {
		m_categories.push_back(std::make_unique<Category>("data/" + categories[i].toString(), this, i));
    }
}

Group::~Group()
{
    m_categories.clear();
}

QString Group::getName() const
{
    return m_name;
}

QString Group::getTitle() const
{
    return m_title;
}

std::vector<Category*> Group::getCategories()
{
    std::vector<Category*> result(m_categories.size());
    for (unsigned int i = 0; i < m_categories.size(); ++i) {
        result[i] = m_categories[i].get();
    }
	return result;
}

unsigned int Group::getCategoriesNum() const
{
	return m_categories.size();
}
