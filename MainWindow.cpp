#include "MainWindow.hpp"
#include <iostream>
#include <QTimer>
#include <QFileDialog>
#include <QDir>
#include <QImageReader>
#include <sstream>
#include <QImage>

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), seamCarverWidget(new SeamCarverWidget(this)) {
	ui->setupUi(this);
	this->setCentralWidget(seamCarverWidget);

	stringstream ss;
	ss << "Image Files ( ";
	for(auto format : QImageReader::supportedImageFormats()) {
		ss << "*." << format.toStdString() << " ";
	}
	ss << ")";
	fileDialogFilterString = QString::fromStdString(ss.str());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_actionOpen_triggered() {
	QString fileName; 
	do {
		fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::homePath(), fileDialogFilterString);
	} while(fileName.isNull());

	imageFile = QFileInfo(fileName);

	QImage image = QImage(fileName).convertToFormat(QImage::Format_RGBX8888);
	// cout << image.width() << "x" << image.height() << " " << image.format() << endl;
	seamCarverWidget->SetImage(std::move(image));
}

void MainWindow::on_actionSaveAs_triggered() {
	auto defaultFilename = QDir::cleanPath(imageFile.dir().absolutePath() + QDir::separator() + imageFile.baseName() + "_carved.png");
	auto fileName = QFileDialog::getSaveFileName(this, "Save Image As", defaultFilename, fileDialogFilterString);

	auto image = seamCarverWidget->GetImage();
	image.save(fileName);
}
