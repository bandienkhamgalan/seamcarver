#pragma once
#include <memory>
#include <QWidget>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QSpinBox>
#include <QImage>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include "GLImageWidget.hpp"
#include "CLSeamCarver.hpp"

class SeamCarverWidget : public QWidget {
	Q_OBJECT

public:
	explicit SeamCarverWidget(QWidget* parent);
	void SetImage(QImage&& image);
	void resizeEvent(QResizeEvent * event) override;
	QImage GetImage() const;

private slots:
	void on_applyButton_clicked();
	void on_widthPicker_valueChanged(int width);

private:
	void UpdateEditorWidget();
	void SetupNewCLSeamCarver();
	void UpdateImageWidgetSizeHint();
	void PerformSeamCarving();
	void SetEditorEnabled(bool enabled);
	void SetStatusVisible(bool visible);

	GLImageWidget* imageWidget;
	QBoxLayout* boxLayout;
	QSpinBox* widthPicker;
	QSpinBox* heightPicker;
	QPushButton* applyButton;
	QProgressBar* progressBar;
	QLabel* progressLabel;
	QPushButton* stopButton;
	std::unique_ptr<CLSeamCarver> seamCarver;
};