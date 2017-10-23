#pragma once
#include <memory>
#include <QWidget>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QSpinBox>
#include <QImage>
#include <QPushButton>
#include <QProgressBar>
#include <QString>
#include <QFileInfo>
#include "MainWindow.hpp"
#include "GLImageWidget.hpp"
#include "CLSeamCarver.hpp"

class SeamCarverWidget : public FileViewerWidget {
	Q_OBJECT

public:
	SeamCarverWidget(QWidget* parent = nullptr);
	void SetImage(QImage&& image);
	void resizeEvent(QResizeEvent * event) override;
	QImage GetImage() const;

	/* FileViewerWidget overrides */
	void OpenFileAction() override;
	void SaveFileAction() override;

private slots:
	void on_applyButton_clicked();
	void on_stopButton_clicked();
	void on_widthPicker_valueChanged(int width);

private:
	void UpdateEditorWidget();
	void SetupNewCLSeamCarver();
	void UpdateImageWidgetSizeHint();
	void PerformSeamCarving();
	void SetEditorEnabled(bool enabled);
	void SetStatusVisible(bool visible);

	QString fileDialogFilterString;
	QFileInfo imageFile;
	GLImageWidget* imageWidget;
	QBoxLayout* boxLayout;
	QSpinBox* widthPicker;
	QSpinBox* heightPicker;
	QPushButton* applyButton;
	QProgressBar* progressBar;
	QPushButton* stopButton;
	std::unique_ptr<CLSeamCarver> seamCarver;
	bool inOperation = false;
	bool shouldStop = false;
};