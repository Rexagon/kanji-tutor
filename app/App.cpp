#include "App.h"

#include <ctime>

#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonArray>
#include <QFile>

#include "window/MainWindow.h"

std::unique_ptr<QApplication> App::m_qapp = nullptr;
std::vector<std::unique_ptr<Group>> App::m_groups;
QJsonObject App::m_profile;

bool App::init(int argc, char** argv)
{
	srand(time(nullptr));

	static int m_argc = argc;
	m_qapp = std::make_unique<QApplication>(m_argc, argv);

	try {
		// loading lessons
		QFile categoriesFile("data/categories.json");
		if (categoriesFile.open(QIODevice::ReadOnly)) {
			QJsonObject json = QJsonDocument::fromJson(categoriesFile.readAll()).object();

			QJsonArray groups = json["groups"].toArray();
			for (int i = 0; i < groups.size(); ++i) {
				m_groups.push_back(std::make_unique<Group>(groups[i].toObject()));
			}
		}
		else {
			throw QString("Невозможно открыть файл с категориями");
		}

		// loading profile
		QFile profileFile("default.prof");
		if (profileFile.open(QIODevice::ReadOnly)) {
			m_profile = QJsonDocument::fromBinaryData(profileFile.readAll()).object();
		}
	}
	catch (const QString& e) {
		QMessageBox::warning(nullptr, "Ошибка", e);
		return false;
	}

	return true;
}

void App::start()
{
	MainWindow w;
	w.show();

	m_qapp->exec();
}

void App::close()
{
	QFile profileFile("default.prof");
	if (profileFile.open(QIODevice::WriteOnly)) {
		QJsonDocument profile(m_profile);
		profileFile.write(profile.toBinaryData());
	}

	m_qapp.reset();
}

std::vector<Group*> App::getGroups()
{
	std::vector<Group*> groups(m_groups.size());
	for (unsigned int i = 0; i < m_groups.size(); ++i) {
		groups[i] = m_groups[i].get();
	}
	return groups;
}

QString App::getDefaultFont()
{
	return "Tahoma";
}

QString App::getHieroglyphsFont()
{
	return "MS Mincho";
}

QString App::getKanaFont()
{
	return "MS Mincho";
}

void App::setTaskResult(const QString& categoryName, const QString& exercise, int percentage)
{
	QJsonObject category;

	auto categoryIt = m_profile.find(categoryName);
	if (categoryIt != m_profile.end()) {
		category = categoryIt.value().toObject();
	}

	auto exerciseIt = category.find(exercise);
	if (exerciseIt == category.end() ||
		exerciseIt.value().toInt() < percentage){
		category[exercise] = percentage;
	}

	m_profile[categoryName] = category;
}

int App::getTaskResult(const QString& title)
{
	auto it = m_profile.find(title);
	if (it == m_profile.end()) {
		return 0;
	}
	else {
		return it.value().toInt();
	}
}

void App::resetProfile()
{
	m_profile = QJsonObject();
}

QJsonObject& App::getProfile()
{
	return m_profile;
}
