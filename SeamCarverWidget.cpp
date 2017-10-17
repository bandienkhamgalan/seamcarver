#include <iostream>
#include <QApplication>
#include <QGridLayout>
#include <QResizeEvent>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include "SeamCarverWidget.hpp"

#ifdef __APPLE__
	#include "CCocoaGLContext.h"
	#include <OpenCL/cl_gl_ext.h>
	#include <OpenGL/OpenGL.h>
	#include <OpenCL/OpenCL.h>
#endif

using namespace std;

SeamCarverWidget::SeamCarverWidget(QWidget* parent) : QWidget(parent) {
	imageWidget = new GLImageWidget(this);

	auto vboxLayout = new QVBoxLayout;	
	setLayout(vboxLayout);

	/* Image viewer */
	boxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	boxLayout->setSpacing(0);
	boxLayout->setContentsMargins(0, 0, 0, 0);
	boxLayout->addStretch();
	boxLayout->addWidget(imageWidget);
	boxLayout->addStretch();
	vboxLayout->addLayout(boxLayout);

	/* Image editor */
	auto gridLayout = new QGridLayout;
	vboxLayout->addLayout(gridLayout);
	widthPicker = new QSpinBox;
	widthPicker->setSuffix(" px");
	connect(widthPicker, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &SeamCarverWidget::on_widthPicker_valueChanged);
	gridLayout->addWidget(new QLabel("Width"), 1, 1);
	gridLayout->addWidget(widthPicker, 1, 2);

	heightPicker = new QSpinBox;
	heightPicker->setSuffix(" px");
	heightPicker->setDisabled(true);
	gridLayout->addWidget(new QLabel("Height"), 2, 1);
	gridLayout->addWidget(heightPicker, 2, 2);

	applyButton = new QPushButton("Apply");
	connect(applyButton, &QPushButton::clicked, this, &SeamCarverWidget::on_applyButton_clicked);
	applyButton->setEnabled(false);
	gridLayout->addWidget(applyButton, 3, 1, 1, 2);

	SetEditorEnabled(false);

	/* Operation status displayer */
	progressBar = new QProgressBar();
	progressBar->setMinimum(0);
	gridLayout->addWidget(progressBar, 1, 3);
	QSizePolicy sp_retain = progressBar->sizePolicy();
	sp_retain.setRetainSizeWhenHidden(true);
	progressBar->setSizePolicy(sp_retain);

	progressLabel = new QLabel();
	gridLayout->addWidget(progressLabel, 2, 3);

	stopButton = new QPushButton("Stop");
	gridLayout->addWidget(stopButton, 3, 3);

	SetStatusVisible(false);
}

QImage SeamCarverWidget::GetImage() const {
	QSize imageSize = imageWidget->GetImageSize();
	return QImage(seamCarver->GetImageData().data(), imageSize.width(), imageSize.height(), QImage::Format_RGBA8888);
}

void SeamCarverWidget::on_applyButton_clicked() {
	PerformSeamCarving();
}

void SeamCarverWidget::on_widthPicker_valueChanged(int width) {
	if(width != imageWidget->GetImageSize().width()) {
		applyButton->setEnabled(true);
	}
}

void SeamCarverWidget::SetEditorEnabled(bool enabled) {
	widthPicker->setEnabled(enabled);
}
void SeamCarverWidget::SetStatusVisible(bool visible) {
	progressBar->setVisible(visible);
	progressLabel->setVisible(visible);
	stopButton->setVisible(visible);
}

void SeamCarverWidget::PerformSeamCarving() {
	QSize imageSize = imageWidget->GetImageSize();
	int seams = imageSize.width() - widthPicker->value();

	applyButton->setEnabled(false);
	SetEditorEnabled(false);
	SetStatusVisible(true);
	progressBar->reset();
	progressBar->setMaximum(seams);
	for(int i = 0 ; i < seams ; ++i) {
		seamCarver->carve(1);
		imageSize.setWidth(imageSize.width() - 1);
		imageWidget->SetImageSize(imageSize);
		UpdateImageWidgetSizeHint();
		progressBar->setValue(i + 1);
		QApplication::processEvents();
	}
	widthPicker->setMaximum(widthPicker->value());
	SetEditorEnabled(true);
	SetStatusVisible(false);
}

void SeamCarverWidget::UpdateImageWidgetSizeHint() {
	QSize viewerSize = boxLayout->contentsRect().size();
	double aspectRatio = (double)imageWidget->GetImageSize().width() / imageWidget->GetImageSize().height();
	int correctHeight = viewerSize.width() / aspectRatio;
	int correctWidth = aspectRatio * viewerSize.height();
	if(correctHeight <= viewerSize.height()) {
		// use full width
		boxLayout->setDirection(QBoxLayout::TopToBottom);
		imageWidget->SetSizeHint(QSize(viewerSize.width(), correctHeight));
	} else {
		// use full height
		boxLayout->setDirection(QBoxLayout::LeftToRight);
		imageWidget->SetSizeHint(QSize(correctWidth, viewerSize.height()));
	}
}

void SeamCarverWidget::resizeEvent(QResizeEvent* event) {
	UpdateImageWidgetSizeHint();
}

void SeamCarverWidget::UpdateEditorWidget() {
	widthPicker->setMaximum(imageWidget->GetImageSize().width());
	widthPicker->setValue(imageWidget->GetImageSize().width());
	widthPicker->setMinimum(1);
	heightPicker->setMaximum(imageWidget->GetImageSize().height());
	heightPicker->setValue(imageWidget->GetImageSize().height());
	SetEditorEnabled(true);
}

void SeamCarverWidget::SetupNewCLSeamCarver() {
	auto contextVariant = imageWidget->GetNativeGLContext();
	
	if(contextVariant.isNull()) {
		throw runtime_error("Could not get native OpenGL context");
	}

	#ifdef __APPLE__
		CGLContextObj glContext = reinterpret_cast<CGLContextObj>(GetCocoaGLContext(contextVariant.data()));
		CGLShareGroupObj sharegroup = CGLGetShareGroup(glContext);
		gcl_gl_set_sharegroup(sharegroup);
		cl_context_properties properties[] = { CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties)sharegroup, 0 };
		cl::Context context(CL_DEVICE_TYPE_ALL, properties);
		cl_device_id deviceId;
		clGetGLContextInfoAPPLE(context(), glContext, CL_CGL_DEVICE_FOR_CURRENT_VIRTUAL_SCREEN_APPLE, sizeof(cl_device_id), &deviceId, NULL);
		cl::Device device(deviceId);
		cout << device.getInfo<CL_DEVICE_NAME>() << endl;
	#endif
	
	cl_int err;
	cl::BufferGL::BufferGL imageBuffer(context, CL_MEM_READ_WRITE, imageWidget->GetImageBuffer().bufferId(), &err);
	if(err != CL_SUCCESS) {
		cerr << err << endl;
		throw runtime_error("Failed to construct shared OpenCL image buffer");
	}

	seamCarver = make_unique<CLSeamCarver>(context, device, imageBuffer, imageWidget->GetImageSize().width(), imageWidget->GetImageSize().height());
}

void SeamCarverWidget::SetImage(QImage&& image) {
	imageWidget->SetImage(std::move(image));
	UpdateEditorWidget();
	SetupNewCLSeamCarver();
	UpdateImageWidgetSizeHint();
}
