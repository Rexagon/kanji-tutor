#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QJsonObject>

#include "models/Group.h"

class App
{
public:
	static bool init(int argc, char** argv);
	static void start();
	static void close();

	static std::vector<Group*> getGroups();

	static QString getDefaultFont();
	static QString getHieroglyphsFont();
	static QString getKanaFont();

	static void setTaskResult(const QString& title, int percentage);
	static int getTaskResult(const QString& title);

	static QJsonObject& getProfile();
	static void resetProfile();
private:
	static std::unique_ptr<QApplication> m_qapp;

	static std::vector<std::unique_ptr<Group>> m_groups;

	static QJsonObject m_profile;
};

#endif // APP_H
