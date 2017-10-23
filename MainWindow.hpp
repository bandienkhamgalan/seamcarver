#pragma once
#include "ui_MainWindow.h"
#include <QMainWindow>
#include <QWidget>

namespace Ui {
	class MainWindow;
}

class FileViewerWidget  : public QWidget {
	Q_OBJECT
public:
	FileViewerWidget(QWidget* parent = nullptr) : QWidget(parent) {}
	virtual void OpenFileAction() {}
	virtual void SaveFileAction() {}
};

class MainWindow : public QMainWindow {
	Q_OBJECT
	
public:
	explicit MainWindow(FileViewerWidget* fileViewerWidget, QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void on_actionOpen_triggered();
	void on_actionSaveAs_triggered();

private:
	Ui::MainWindow* ui;
	FileViewerWidget* fileViewerWidget;
};