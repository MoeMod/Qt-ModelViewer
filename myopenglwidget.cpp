#include "myopenglwidget.h"
#include "MeshFile.h"

#include <QEvent>
#include <QApplication>
#include <QClipboard>
#include <QBitmap>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector3D>
#include <QMouseEvent>

#include <vector>
#include "gl_list.h"

template<class T>
constexpr void qNormalizeAngle(T &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360)
		angle -= 360 * 16;
}

struct MyOpenGLWidget::impl_t
{
	QVector3D vecRot{0,0,0};
	float scale = 1;
	float pointsize = 1;
	QPoint m_LastMousePos;

	std::shared_ptr<CMeshFile> m_spFile;

	bool m_bDrawWire = false;
	bool m_bDrawFace = true;

	struct GLDrawLists
	{
		GL_List showWireList;
		GL_List showFaceList;
	};
	std::unique_ptr<GLDrawLists> m_upGL_List;
};

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) :
	pimpl(std::make_unique<impl_t>())
{
	
}

MyOpenGLWidget::~MyOpenGLWidget()
{
	// unique_ptr的析构函数需要impl_t的完整定义，所以这个空析构函数要留下来。
}

void MyOpenGLWidget::initializeGL()
{
	glClearColor(255, 255, 255, 255);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	setLight(true);

	float ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
	int side = qMin(w, h);
	glViewport((w - side) / 2, (h - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	float scale = pimpl->scale;
	glScalef(scale, scale, scale);
	glRotatef(pimpl->vecRot.x() / 16.0, 1.0, 0.0, 0.0);
	glRotatef(pimpl->vecRot.y() / 16.0, 0.0, 1.0, 0.0);
	glRotatef(pimpl->vecRot.z() / 16.0, 0.0, 0.0, 1.0);

	// nothing to draw
	if (!pimpl->m_upGL_List)
		return;

	// draw line
	if(pimpl->m_bDrawWire)
		pimpl->m_upGL_List->showWireList.Call();

	// draw face
	if(pimpl->m_bDrawFace)
		pimpl->m_upGL_List->showFaceList.Call();
}

void MyOpenGLWidget::onUpdateContent(std::shared_ptr<CMeshFile> sp)
{
	pimpl->m_spFile = sp;
	pimpl->m_upGL_List = nullptr; // resets

	if (pimpl->m_spFile)
	{
		auto &mesh = pimpl->m_spFile->Data();
		pimpl->m_upGL_List = std::make_unique<impl_t::GLDrawLists>();

		pimpl->m_upGL_List->showFaceList.New();
		for (auto &&face : mesh.faces())
		{
			glBegin(GL_TRIANGLES);
			for (auto &&fv : mesh.fv_range(face))
			{
				glNormal3fv(mesh.normal(fv).data());
				glVertex3fv(mesh.point(fv).data());
			}
			glEnd();
		}
		pimpl->m_upGL_List->showFaceList.End();

		pimpl->m_upGL_List->showWireList.New();
		glDisable(GL_LIGHTING);
		glLineWidth(1.0f);
		glColor3f(0.5f, 0.5f, 0.5f);
		glBegin(GL_LINES);
		for (auto &&he : mesh.halfedges())
		{
			//链接这个有向边的起点和终点
			glVertex3fv(mesh.point(mesh.from_vertex_handle(he)).data());
			glVertex3fv(mesh.point(mesh.to_vertex_handle(he)).data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
		pimpl->m_upGL_List->showWireList.End();
	}

	updateGL();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
	pimpl->m_LastMousePos = event->pos();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - pimpl->m_LastMousePos.x();
	int dy = event->y() - pimpl->m_LastMousePos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(pimpl->vecRot.x() + 8 * dy);
		setYRotation(pimpl->vecRot.y() + 8 * dx);
	}
	else if (event->buttons() & Qt::RightButton) {
		setXRotation(pimpl->vecRot.x() + 8 * dy);
		setZRotation(pimpl->vecRot.z() + 8 * dx);
	}

	pimpl->m_LastMousePos = event->pos();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{
	if (event->modifiers() & Qt::CTRL)
		pimpl->pointsize = std::fabs(pimpl->pointsize + 0.001f * event->delta());
	else
		pimpl->scale *= std::pow(1.001f, event->delta());
	updateGL();
}

void MyOpenGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != pimpl->vecRot.x()) {
		pimpl->vecRot.setX(angle);
		emit xRotationChanged(angle);
		updateGL();
	}
}

void MyOpenGLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != pimpl->vecRot.y()) {
		pimpl->vecRot.setY(angle);
		emit yRotationChanged(angle);
		updateGL();
	}
}

void MyOpenGLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != pimpl->vecRot.z()) {
		pimpl->vecRot.setZ(angle);
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

void MyOpenGLWidget::setDrawWire(bool b)
{
	pimpl->m_bDrawWire = b;
	updateGL();
}

void MyOpenGLWidget::setDrawFace(bool b)
{
	pimpl->m_bDrawFace = b;
	updateGL();
}

// TODO(MoeMod) : macOS上面截图为空白，Windows测试成功，需要修复。另外除了支持BMP以外还要支持其他图片格式的输出。
void MyOpenGLWidget::onActionSnapshot()
{
	int w = this->width();
	int h = this->height();
	size_t iDataSize = w * h * 4;
	//std::vector<GLubyte> data(iDataSize);

	QImage qi( w, h, QImage::Format::Format_RGBA8888);

	updateGL();
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