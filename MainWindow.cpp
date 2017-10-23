#include <iostream>
#include <QTimer>
#include <QFileDialog>
#include <QDir>
#include <QImageReader>
#include <QImage>
#include "MainWindow.hpp"

using namespace std;

MainWindow::MainWindow(FileViewerWidget* fileViewerWidget, QWidget* parent)
	: QMainWindow(parent), ui(new Ui::MainWindow), fileViewerWidget(fileViewerWidget) {
	if(!fileViewerWidget) {
		throw invalid_argument("invalid value for fileViewerWidget parameter");
	}

	ui->setupUi(this);
	fileViewerWidget->setParent(this);
	this->setCentralWidget(fileViewerWidget);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_actionOpen_triggered() {
	fileViewerWidget->OpenFileAction();
}

void MainWindow::on_actionSaveAs_triggered() {
	fileViewerWidget->SaveFileAction();
}
