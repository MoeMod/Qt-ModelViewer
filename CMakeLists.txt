
# ʹ��CMake�ڸ���ƽ̨���뱾��Ŀ
# ���ߣ�÷��Դ��MoeMod��

# 2018/10/31 ��ʼ�����Ŀ����ʥ�ڿ��֣�

cmake_minimum_required(VERSION 3.1.3)
project(QtGuiApplication1)

# ��������
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ��Ŀʹ��C++14��׼������ʹ��msvc2015��clang5.0��gcc7.1���ϰ汾����
set(CMAKE_CXX_STANDARD 14)

# ͷ�ļ�����Ŀ¼
include_directories (
	./OpenMesh/src/
)

# �����Ŀ�ļ�
file(GLOB FILE_RES 
	./QtGuiApplication1.qrc
)
file(GLOB FILE_UI 
	./QtGuiApplication1.ui
)
file(GLOB FILE_MOC 
	./QtGuiApplication1.h
		myopenglwidget.h
)
file(GLOB FILE_SRC 
	./QtGuiApplication1.cpp
		myopenglwidget.cpp
	
	./main.cpp
	./MeshFile.cpp

)

# ����Qt5
# ʹ��MSVCʱ��ҪCMakeSettings.json�������cmakeCommandArgs����-DQt5_DIR=D:\\Qt\\Qt5.11.1\\5.11.1\\msvc2017_64\\lib\\cmake\\Qt5
# ��������Ҳ���CMake���λ�ã�msvc2017_64��64λ�Ŀ⣬32λ�����и�����
find_package(Qt5 REQUIRED Core Widgets OpenGL)

# ����OpenMesh
# �����Ժ�ŵ�OpenMesh�ļ���
# ����ֱ��git clone https://www.graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh.git
ADD_SUBDIRECTORY(OpenMesh)
# �޸�һЩĪ������ı������
add_definitions(-D_USE_MATH_DEFINES)

# ��֪��ΪʲômacOS 10.14������opengl...
if(APPLE)
	find_package( opengl REQUIRED )
	add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

# ��Qt����moc����
qt5_wrap_cpp( GEN_MOC ${FILE_MOC})
qt5_wrap_ui( GEN_UIC ${FILE_UI})
qt5_add_resources( GEN_RCC ${FILE_RES})

# ָ������ļ�
add_executable(QtGuiApplication1 ${FILE_RES} ${FILE_UI} ${FILE_SRC} ${GEN_MOC} ${GEN_UIC} ${GEN_RCC})

# ���Ӹղ���Щ��
target_link_libraries(QtGuiApplication1 Qt5::Core Qt5::Widgets Qt5::OpenGL)
target_link_libraries(QtGuiApplication1 GL)
target_link_libraries(QtGuiApplication1 OpenMeshCore)
