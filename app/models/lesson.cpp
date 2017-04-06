#include "lesson.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

Lesson::Lesson(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QString message = "Невозможно открыть урок \"" + path + "\"";
        throw std::runtime_error(message.toStdString());
    }

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

    m_name = json["name"].toString();

    QJsonArray kanji = json["kanji"].toArray();
    for (int i = 0; i < kanji.size(); ++i) {
        m_hieroglyphs.push_back(std::make_unique<Hieroglyph>(kanji[i].toObject()));
    }
}

Lesson::~Lesson()
{
    m_hieroglyphs.clear();
}

QString Lesson::getName() const
{
    return m_name;
}

std::vector<Hieroglyph*> Lesson::getHieroglyphs() const
{
    std::vector<Hieroglyph*> result(m_hieroglyphs.size());
    for (unsigned int i = 0; i < m_hieroglyphs.size(); ++i) {
        result[i] = m_hieroglyphs[i].get();
    }
    return result;
}