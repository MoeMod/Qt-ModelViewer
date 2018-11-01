#pragma once

#include <qgl.h>
#include <memory>

#include "gl_list.h"

class CMeshFile;

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

public slots:
	void setLight(bool);
	void setShowNormals(bool);
	void setNormalMapColor(bool);
	void onActionSnapshot();
	void onUpdateContent(std::shared_ptr<CMeshFile> sp);

private:
	int xRot;
	int yRot;
	int zRot;
	float scale;
	float pointsize;
	QPoint m_LastMousePos;
	bool m_bShowNormals;
	bool m_bNormalMapColor;

	std::shared_ptr<CMeshFile> m_spFile;

	struct Lists
	{
		GL_List showWireList;
		GL_List showFaceList;
	};
	std::unique_ptr<Lists> m_upGL_List;
};
