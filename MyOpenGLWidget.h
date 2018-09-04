#pragma once

#include <qgl.h>

class MyOpenGLWidget : public QGLWidget
{

	Q_OBJECT

public:
	MyOpenGLWidget(QWidget *parent = Q_NULLPTR);

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;

public: // slots
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);

signals: // signals
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);

public	slots:
	void setLight(bool);
	void setShowNormals(bool);
	void setNormalMapColor(bool);
	void onActionSnapshot();

private:
	int xRot;
	int yRot;
	int zRot;
	float scale;
	float pointsize;
	QPoint lastPos;
	bool m_bShowNormals;
	bool m_bNormalMapColor;
};
