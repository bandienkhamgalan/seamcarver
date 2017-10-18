#include <iostream>
#include <stdexcept>
#include <QImage>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QApplication>
#include "glShaders.hpp"
#include "GLImageWidget.hpp"

using namespace std;

GLImageWidget::GLImageWidget(QWidget* parent)
	: QOpenGLWidget(parent), imageSize(1, 1), imageTexture(QOpenGLTexture::TargetBuffer) {
	sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
	sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
}

QSize GLImageWidget::sizeHint() const {
	return sizeHintToReturn;
}

QSize GLImageWidget::GetImageSize() const {
	return imageSize;
}

void GLImageWidget::SetImageSize(QSize newSize) {
	imageSize = newSize;
	program.bind();
	program.setUniformValue("imageWidth", imageSize.width());
	program.setUniformValue("imageHeight", imageSize.height());
	program.release();
	update();
}

void GLImageWidget::SetSizeHint(QSize sizeHint) {
	sizeHintToReturn = sizeHint;
	updateGeometry();
}

void GLImageWidget::SetImage(QImage&& newImage) {
	if(!initialized) {
		throw runtime_error("Cannot set image before OpenGL is initialized");
	}

	image = std::move(newImage);
	imageSize = image.size();

	program.bind();

	imageBuffer.create();
	imageBuffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
	imageBuffer.bind();
	imageBuffer.allocate(image.bits(), image.width() * image.height() * 4 * sizeof(uint8_t));

	imageTexture.create();
	imageTexture.bind(0);
	glFunctions->glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8UI, imageBuffer.bufferId());	

	program.setUniformValue("imageRowPitch", image.width());
	program.setUniformValue("imageWidth", image.width());
	program.setUniformValue("imageHeight", image.height());
	
	program.release();

	update();
}

QVariant GLImageWidget::GetNativeGLContext() {
	if(!initialized) {
		throw runtime_error("Cannot create OpenCL context before OpenGL is initialized");
	}

	return QOpenGLContext::currentContext()->nativeHandle();
}

QOpenGLBuffer GLImageWidget::GetImageBuffer() {
	if(!initialized) {
		throw runtime_error("Cannot get image bbuffer before OpenGL is initialized");
	}

	return imageBuffer;
}

void GLImageWidget::initializeGL() {
	initialized = true;

	glFunctions = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();
	glFunctions->glClearColor(0.0, 0.0, 0.0, 1.0);

	if(!program.addShaderFromSourceCode(QOpenGLShader::Vertex, GLShaders::vertexShader)
		|| !program.addShaderFromSourceCode(QOpenGLShader::Fragment, GLShaders::fragmentShader)) {
		throw runtime_error("Could not compile OpenGL shaders: " + program.log().toStdString());
	}
	program.link();
	program.bind();

	vao.create();
	vao.bind();
	
	const GLfloat vertexPositions[] = {	-1.0f, 1.0f, 0.0f,
										 1.0f, 1.0f, 0.0f,
										 1.0f, -1.0f, 0.0f,
										-1.0f,  -1.0f, 0.0f  };
	QOpenGLBuffer positionsBuffer(QOpenGLBuffer::VertexBuffer);
	positionsBuffer.create();
	positionsBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	positionsBuffer.bind();
	positionsBuffer.allocate(vertexPositions, 12 * sizeof(GLfloat));
	
	program.setAttributeBuffer("position", GL_FLOAT, 0, 3);
	program.enableAttributeArray("position");

	const GLuint elements[] = { 0, 1, 2,
								0, 2, 3 };
	QOpenGLBuffer elementsBuffer(QOpenGLBuffer::IndexBuffer);
	elementsBuffer.create();
	elementsBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	elementsBuffer.bind();
	elementsBuffer.allocate(elements, 6 * sizeof(GLuint));

	vao.release();

	SetImage(QImage(1, 1, QImage::Format_RGBX8888));
	positionsBuffer.release();
	program.release();
	elementsBuffer.release();
	imageBuffer.release();
	imageTexture.release();
}

void GLImageWidget::paintGL() {
	// cout << "in paintGL()" << endl;

	program.bind();
	vao.bind();
	imageTexture.bind(0);

	glFunctions->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	GLint viewport[4];
	glFunctions->glGetIntegerv(GL_VIEWPORT, viewport);
	program.setUniformValue("screenWidth", viewport[2]);
	program.setUniformValue("screenHeight", viewport[3]);

	vao.release();
	program.release();
}
