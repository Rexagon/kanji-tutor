#include "App.h"
#include "window/MainWindow.h"

#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include <ctime>

std::unique_ptr<QApplication> App::m_qapp = nullptr;
std::vector<std::unique_ptr<Group>> App::m_groups;

bool App::init(int argc, char** argv)
{
	srand(time(nullptr));

	static int m_argc = argc;
	m_qapp = std::make_unique<QApplication>(m_argc, argv);

	try {
		QFile file("data/categories.json");
		if (!file.open(QIODevice::ReadOnly)) {
			throw QString("Невозможно открыть файл с категориями");
		}

		QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

		QJsonArray groups = json["groups"].toArray();
		for (int i = 0; i < groups.size(); ++i) {
			m_groups.push_back(std::make_unique<Group>(groups[i].toObject()));
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
	w.setWindowIcon(QIcon("icon.png"));
	w.show();

	m_qapp->exec();
}

void App::close()
{
	// TODO: save profile here

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
