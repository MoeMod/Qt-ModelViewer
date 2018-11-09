# QtGuiApplication1 CMakeLists.txt
# 使用CMake在各个平台编译本项目
# 作者：梅峰源（MoeMod）

# 2018/10/31 开始这个项目。万圣节快乐！

cmake_minimum_required(VERSION 3.1.3)
project(QtGuiApplication1)

# 属性设置
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 项目使用C++14标准，建议使用msvc2015、clang5.0、gcc7.1以上版本编译
set(CMAKE_CXX_STANDARD 14)

# 头文件查找目录
include_directories (
	./OpenMesh/src/
)

# 添加项目文件
file(GLOB FILE_RES 
	./QtGuiApplication1.qrc
)
file(GLOB FILE_UI 
	./QtGuiApplication1.ui
)
file(GLOB FILE_MOC 
	./QtGuiApplication1.h
	./MyOpenGLWidget.h
)
file(GLOB FILE_SRC 
	./QtGuiApplication1.cpp
	./MyOpenGLWidget.cpp
	
	./main.cpp
	./MeshFile.cpp

)

# 查找Qt5
# 使用MSVC时需要CMakeSettings.json里面添加cmakeCommandArgs参数-DQt5_DIR=D:\\Qt\\Qt5.11.1\\5.11.1\\msvc2017_64\\lib\\cmake\\Qt5
# 否则可能找不到CMake库的位置（msvc2017_64是64位的库，32位请自行更换）
find_package(Qt5 REQUIRED Core Widgets OpenGL)

# 查找OpenGL， linux用apt-get安装libgl1-mesa-dev
find_package( opengl REQUIRED )

# 查找OpenMesh
# 下载以后放到OpenMesh文件夹
# 或者直接git clone https://www.graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh.git
ADD_SUBDIRECTORY(OpenMesh)
# 修复一些莫名其妙的编译错误
add_definitions(-D_USE_MATH_DEFINES)

# 不知道为什么macOS 10.14抛弃了opengl...
if(APPLE)
	add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

# 让Qt生成moc代码
qt5_wrap_cpp( GEN_MOC ${FILE_MOC})
qt5_wrap_ui( GEN_UIC ${FILE_UI})
qt5_add_resources( GEN_RCC ${FILE_RES})

# 指定输出文件
add_executable(QtGuiApplication1 ${FILE_RES} ${FILE_UI} ${FILE_SRC} ${GEN_MOC} ${GEN_UIC} ${GEN_RCC})

# 链接刚才那些库
target_link_libraries(QtGuiApplication1 Qt5::Core Qt5::Widgets Qt5::OpenGL)
target_link_libraries(QtGuiApplication1 ${OPENGL_LIBRARY})
target_link_libraries(QtGuiApplication1 OpenMeshCore)
