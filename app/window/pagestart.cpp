#include "pagestart.h"

#include <cmath>

#include <ui_mainwindow.h>

#include "app.h"

PageStart::PageStart(Ui::MainWindow *ui) :
    Page(ui, Id::StartPage)
{
	QVBoxLayout* groupsList = new QVBoxLayout();
	groupsList->setAlignment(Qt::AlignTop);
	groupsList->setContentsMargins(0, 12, 0, 0);
	groupsList->setSizeConstraint(QLayout::SetMinimumSize);
	m_ui->startPageScrollArea->setLayout(groupsList);

	std::vector<Group*> groups = App::getGroups();
	for (unsigned int i = 0; i < groups.size(); ++i) {
		Group* group = groups[i];

		// Title
		QLabel* title = new QLabel(group->getTitle());
		title->setMargin(0);
		title->setFont(QFont("Verdana", 12, 10));
		groupsList->addWidget(title);

		// Buttons grid
		QWidget* widget = new QWidget();
		QGridLayout* gridLayout = new QGridLayout();
		gridLayout->setContentsMargins(0,0,16,20);
		widget->setLayout(gridLayout);

		std::vector<Category*> categories = group->getCategories();
		widget->setFixedSize(381, static_cast<int>(std::ceil(categories.size() / 3.0)) * 85 + 20);
		for (unsigned int j = 0; j < categories.size(); j++) {
			Category* category = categories[j];
			QPushButton* button = new QPushButton(category->getName());

			// On category selected
			connect(button, &QPushButton::pressed, this, [this, category]() {
				emit categorySelected(category);
			});

			button->setFont(QFont("Verdana", 10, 10));
			button->setFixedSize(118, 80);

			gridLayout->addWidget(button, j / 3, j % 3, 1, 1);
		}
		groupsList->addWidget(widget);
	}
}
