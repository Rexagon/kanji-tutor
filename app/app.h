#ifndef APP_H
#define APP_H

#include <QApplication>

#include "models/group.h"

class App
{
public:
	static bool init(int argc, char** argv);
	static void start();
	static void close();

	static std::vector<Group*> getGroups();
private:
	static std::unique_ptr<QApplication> m_qapp;

	static std::vector<std::unique_ptr<Group>> m_groups;
};

#endif // APP_H
