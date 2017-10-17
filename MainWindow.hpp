#pragma once
#include "SeamCarverWidget.hpp"
#include <QMainWindow>
#include <QString>
#include <QFileInfo>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void on_actionOpen_triggered();
	void on_actionSaveAs_triggered();

private:
	Ui::MainWindow* ui;
	SeamCarverWidget* seamCarverWidget;
	QString fileDialogFilterString;
	QFileInfo imageFile;
};