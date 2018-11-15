#pragma once

#include <qgl.h>
#include <memory>

class CMeshFile;

class MyOpenGLWidget : public QGLWidget
{

	Q_OBJECT

public:
	MyOpenGLWidget(QWidget *parent = Q_NULLPTR);
	~MyOpenGLWidget();

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

signals: // signals
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void setLight(bool);
	void setDrawWire(bool);
	void setDrawFace(bool);
	void onActionSnapshot();
	void onUpdateContent(std::shared_ptr<CMeshFile> sp);

private:
	struct impl_t;
	const std::unique_ptr<impl_t> pimpl;

};
