#include "category.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

Category::Category(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QString message = "Невозможно открыть файл \"" + path + "\"";
        throw std::runtime_error(message.toStdString());
    }

    QString currentFolder = path.left(path.lastIndexOf('/') + 1);

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

    m_name = json["name"].toString();

    QJsonArray lessons = json["lessons"].toArray();
    for (int i = 0; i < lessons.size(); ++i) {
        m_lessons.push_back(std::make_unique<Lesson>(currentFolder + lessons[i].toString()));
    }
}

Category::~Category()
{
    m_lessons.clear();
}

QString Category::getName() const
{
    return m_name;
}

std::vector<Lesson*> Category::getLessons()
{
    std::vector<Lesson*> result(m_lessons.size());
    for (unsigned int i = 0; i < m_lessons.size(); ++i) {
        result[i] = m_lessons[i].get();
    }
    return result;
}