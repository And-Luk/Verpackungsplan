cmake_minimum_required (VERSION 4.0) #3.55555
project(Example VERSION 1.0)

#set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -v -std=c++20 ") #-lxl

#set ("XL_DIR"	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/lib" )
#set_property(Example PROPERTY CXX_STANDARD 20)

# Find OpenCV package
find_package (OpenCV REQUIRED)

#find_package (libxl REQUIRED)



#target_include_directories(Example PRIVATE 
#	#${YOUR_DIRECTORY}
#	${OpenCV_INCLUDE_DIRS}
#	${LIBXL_INCLUDE_DIR}
#	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/src"
#	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl"
#	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/lib"
#	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/include_cpp"
#)

# Include directories from OpenCV
include_directories (
	${OpenCV_INCLUDE_DIRS}
	${LIBXL_INCLUDE_DIR}
	"./"
	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/src"
	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl"
	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/lib"
	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/include_cpp"
)

#set(SOURCES file.cpp file2.cpp ${YOUR_DIRECTORY}/file1.h ${YOUR_DIRECTORY}/file2.h)

#LINK_DIRECTORIES ("/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/include_cpp" )



set(SOURCE_FILES
	src/main.cpp
	src/functions.cpp
	src/settings.cpp
	src/statistics.cpp
	src/elements_selection.cpp
	src/write_Excel_file.cpp
	src/read_Excel_file.cpp
	src/photo.cpp )

add_executable(Example ${SOURCE_FILES})
#add_executable(Example ${SOURCES})


set(HEADER_FILES "/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/include_cpp"
	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl"
	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/lib"
 )
 #find_package (libXL REQUIRED)

# Link OpenCV libraries
target_link_libraries( Example ${OpenCV_LIBS} ${XL_LIBS}	"/Users/and/Downloads/DELETE/libxl-mac-4.6.0/lib/libxl.dylib" )


 # add_library(XL SHARED "/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/include_cpp" )



# Create an executable
#add_executable(Example src/main.cpp)


#add_subdirectory(libxl)
#add_subdirectory(cereal)
#add_subdirectory(usr/local/include/opencv4)

        








#target_include_directories(Example PUBLIC cereal )
#target_link_libraries(Example PUBLIC libxl/lib)







#find_package (OpenCV REQUIRED)
#include_directories( ${0penCV_INCLUDE_DIRS} )
#add_executable( Open_CV_Project main.cpp )
#target_link_libraries( Open_CV_Project ${OpenCV_LIBS})
