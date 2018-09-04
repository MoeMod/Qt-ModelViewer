#include "MyOpenGLWidget.h"
#include "PointManager.h"

#include <QEvent.h>
#include <QApplication.h>
#include <QClipboard.h>
#include <QBitmap.h>
#include <QMessageBox.h>
#include <QFileDialog.h>

#include <qgl.h>
#include <vector>

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : 
	scale(1.0f), pointsize(1.0f), 
	m_bShowNormals(false), m_bNormalMapColor(false), 
	xRot(0), yRot(0), zRot(0)
{
	
}

void MyOpenGLWidget::initializeGL()
{
	glClearColor(255, 255, 255, 255);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	float ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
	int side = qMin(w, h);
	glViewport((w - side) / 2, (h - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
/*#ifdef QT_OPENGL_ES_1
	glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
	glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif*/
	glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glScalef(scale, scale, scale);
	glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

	glPointSize(pointsize);
	
	if (m_bNormalMapColor)
	{
		for (auto &poi : PointManager())
		{
			glColor3fv(poi.normal * 0.5f + Vector(0.5f, 0.5f, 0.5f));
			glBegin(GL_POINTS);
			glVertex3fv(poi.verticle);
			glEnd();
		}

	}
	else
	{
		glColor4ub(0, 0, 0, 255);
		glBegin(GL_POINTS);
		std::for_each(PointManager().verticles().begin(), PointManager().verticles().end(), glVertex3fv);
		glEnd();
	}

	

	if (m_bShowNormals)
	{
		glColor4ub(0, 0, 255, 255);
		glBegin(GL_LINES);
		for (auto &poi : PointManager())
		{
			glVertex3fv(poi.verticle);
			glVertex3fv(poi.verticle + poi.normal * 0.0625f);
		}
		glEnd();
	}

	
	
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}

	lastPos = event->pos();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{
	if (event->modifiers() & Qt::CTRL)
		pointsize = std::fabs(pointsize + 0.001f * event->delta());
	else
		scale *= std::pow(1.001f, event->delta());
	updateGL();
}

void MyOpenGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

void MyOpenGLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

void MyOpenGLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void MyOpenGLWidget::setLight(bool b)
{
	b ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
	b ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);
	updateGL();
}

void MyOpenGLWidget::setShowNormals(bool b)
{
	m_bShowNormals = b;
	updateGL();
}

void MyOpenGLWidget::setNormalMapColor(bool b)
{
	m_bNormalMapColor = b;
	updateGL();
}

void MyOpenGLWidget::onActionSnapshot()
{
	int w = this->width();
	int h = this->height();
	size_t iDataSize = w * h * 4;
	//std::vector<GLubyte> data(iDataSize);

	QImage qi( w, h, QImage::Format::Format_RGBA8888);

	glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, qi.bits());

	qi = std::move(qi).mirrored();
	//QImage qi(data.data(), w, h, QImage::Format::Format_RGBA8888);
	

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setPixmap(QPixmap::fromImage(qi));

	if(QMessageBox::question(this, "Save", "Image has been copied to clipboard.\nDo you want to save it to a file?") == QMessageBox::Yes)
	{
		QString filename = QFileDialog::getSaveFileName(this, {}, {}, tr("BMP file (*.bmp)"));
		if(!filename.isEmpty())
			qi.save(filename);
	}
}