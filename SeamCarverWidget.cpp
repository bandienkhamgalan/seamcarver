#include <iostream>
#include <sstream>
#include <QApplication>
#include <QGridLayout>
#include <QResizeEvent>
#include <QFormLayout>
#include <QImageReader>
#include <QLabel>
#include <QWindow>
#include <QFileDialog>
#include "SeamCarverWidget.hpp"

#ifdef __APPLE__
	#include "CCocoaGLContext.h"
	#include <OpenCL/cl_gl_ext.h>
	#include <OpenGL/OpenGL.h>
	#include <OpenCL/OpenCL.h>
#elif _WIN32
	#include <QWGLNativeContext>
	#include <Windows.h>
#endif

using namespace std;

SeamCarverWidget::SeamCarverWidget(QWidget* parent) : FileViewerWidget(parent) {
	imageWidget = new GLImageWidget(this);

	auto vboxLayout = new QVBoxLayout;	
	setLayout(vboxLayout);
	
	/* Initialize file dialog filter string */
	stringstream ss;
	ss << "Image Files ( ";
	for(auto format : QImageReader::supportedImageFormats()) {
		ss << "*." << format.toStdString() << " ";
	}
	ss << ")";
	fileDialogFilterString = QString::fromStdString(ss.str());

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

	stopButton = new QPushButton("Stop");
	connect(stopButton, &QPushButton::clicked, this, &SeamCarverWidget::on_stopButton_clicked);
	gridLayout->addWidget(stopButton, 3, 3);

	SetStatusVisible(false);
}

void SeamCarverWidget::OpenFileAction() {
	if(!inOperation) {
		QString fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::homePath(), fileDialogFilterString);
		if(!fileName.isNull()) {
			imageFile = QFileInfo(fileName);
			SetImage(QImage(fileName).convertToFormat(QImage::Format_RGBX8888));
		}
	}
}

void SeamCarverWidget::SaveFileAction() {
	if(!inOperation) {
		auto defaultFilename = QDir::cleanPath(imageFile.dir().absolutePath() + QDir::separator() + imageFile.baseName() + "_carved.png");
		auto fileName = QFileDialog::getSaveFileName(this, "Save Image As", defaultFilename, fileDialogFilterString);
		if(!fileName.isNull()) {
			GetImage().save(fileName);
		}
	}
}

QImage SeamCarverWidget::GetImage() const {
	QSize imageSize = imageWidget->GetImageSize();
	return QImage(seamCarver->GetImageData().data(), imageSize.width(), imageSize.height(), QImage::Format_RGBA8888);
}

void SeamCarverWidget::on_applyButton_clicked() {
	PerformSeamCarving();
}

void SeamCarverWidget::on_stopButton_clicked() {
	shouldStop = true;
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
	stopButton->setVisible(visible);
}

void SeamCarverWidget::PerformSeamCarving() {
	inOperation = true;
	QSize imageSize = imageWidget->GetImageSize();
	int seams = imageSize.width() - widthPicker->value();

	applyButton->setEnabled(false);
	SetEditorEnabled(false);
	SetStatusVisible(true);
	progressBar->reset();
	progressBar->setMaximum(seams);
	for(int i = 0 ; i < seams && !shouldStop ; ++i) {
		seamCarver->carve(1);
		imageSize.setWidth(imageSize.width() - 1);
		imageWidget->SetImageSize(imageSize);
		widthPicker->setValue(imageSize.width());
		UpdateImageWidgetSizeHint();
		progressBar->setValue(i + 1);
		QApplication::processEvents();
	}
	shouldStop = false;
	widthPicker->setMaximum(widthPicker->value());
	SetEditorEnabled(true);
	SetStatusVisible(false);
	inOperation = false;
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
	#else
		HGLRC glContext = wglGetCurrentContext();
		HDC hdc = wglGetCurrentDC();
		typedef cl_int(*clGetGLContextInfoKHRType)(const cl_context_properties*, cl_gl_context_info, size_t, void*, size_t*);
		auto getGLContextInfo = reinterpret_cast<clGetGLContextInfoKHRType>(clGetExtensionFunctionAddress("clGetGLContextInfoKHR"));

		if (!getGLContextInfo) {
			throw runtime_error("Could not initialize OpenCL/OpenGL interop (extension not supported)");
		}

		vector<cl::Platform> platforms;
		if (cl::Platform::get(&platforms) != CL_SUCCESS) {
			throw runtime_error("Failed to get OpenCL platforms");
		}

		cl_device_id deviceId;
		cl_context contextId;
		bool found = false;

		for(auto& platform : platforms) {
			cl_context_properties properties[] = { 	CL_CONTEXT_PLATFORM, (cl_context_properties)platform(),
													CL_GL_CONTEXT_KHR, (cl_context_properties)glContext,
												    CL_WGL_HDC_KHR, (cl_context_properties)hdc, 0 };
			size_t bytes = 0;
			(*getGLContextInfo)(properties, CL_CURRENT_DEVICE_FOR_GL_CONTEXT_KHR, 0, NULL, &bytes);
			if (bytes > 0) {
				(*getGLContextInfo)(properties, CL_CURRENT_DEVICE_FOR_GL_CONTEXT_KHR, bytes, &deviceId, NULL);
				cl_int err;
				contextId = clCreateContext(properties, 1, &deviceId, NULL, NULL, &err);
				if (err != CL_SUCCESS) {
					throw runtime_error("Could not initialize shared context: " + to_string(err));
				}
				found = true;
				goto done;
			}
		}

		done: if (!found) {
			throw runtime_error("Could not initialize OpenCL/OpenGL interop (no capable devices found)");
		}

		cl::Device device(deviceId);
		cl::Context context(contextId);
	#endif

	cl_int err;
	cl::BufferGL imageBuffer(context, CL_MEM_READ_WRITE, imageWidget->GetImageBuffer().bufferId(), &err);
	if (err != CL_SUCCESS) {
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
