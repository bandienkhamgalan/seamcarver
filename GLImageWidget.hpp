#pragma once
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_2_Core>
#include <QOpenGLVertexArrayObject>
#include "cl.hpp"

class GLImageWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	GLImageWidget(QWidget* parent = 0);
	void SetImage(QImage&& image);
	void SetSizeHint(QSize sizeHint);
	QSize GetImageSize() const;
	void SetImageSize(QSize newSize);
	QSize sizeHint() const override;
	QVariant GetNativeGLContext();
	QOpenGLBuffer GetImageBuffer();

protected:
	void initializeGL() override;
	void paintGL() override;

private:
	bool initialized = false;
	QImage image;
	QSize imageSize;
	QSize sizeHintToReturn;
	QOpenGLBuffer imageBuffer;
	QOpenGLBuffer elementsBuffer;
	QOpenGLTexture imageTexture;
	QOpenGLShaderProgram program;
	QOpenGLVertexArrayObject vao;
	QOpenGLFunctions_3_2_Core *glFunctions;
};
