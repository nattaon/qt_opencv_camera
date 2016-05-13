cmake_minimum_required(VERSION 2.8)
project( CameraStream )

if(CMAKE_CONFIGURATION_TYPES)
    message("Multi-configuration generator")
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" 
	CACHE STRING "My multi config types" FORCE)
else()
    message("Single-configuration generator")
endif()

SET("OpenCV_DIR" "C:/opencv249/build")
find_package( OpenCV REQUIRED )
find_package (VTK REQUIRED) #for QT5_WRAP_CPP command 


set  (project_SOURCES main.cpp webcam.cpp imgproc.cpp)
set  (project_HEADERS webcam.h imgproc.h)
#set  (project_FORMS   mainwindow.ui)

QT5_WRAP_CPP (project_HEADERS_MOC   ${project_HEADERS})
#QT5_WRAP_UI  (project_FORMS_HEADERS ${project_FORMS})

ADD_DEFINITIONS (${QT_DEFINITIONS})

ADD_EXECUTABLE  (CameraStream 
${project_SOURCES} 
${project_FORMS_HEADERS} 
${project_HEADERS_MOC})

target_link_libraries( CameraStream ${OpenCV_LIBS} )
qt5_use_modules (CameraStream Widgets)
