cmake_minimum_required (VERSION 4.0) #3.55555
project(main VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -v ") # -std=c++20     // --? -pthread
# Find OpenCV package
find_package (OpenCV REQUIRED)

# Include directories from OpenCV
include_directories (
	${OpenCV_INCLUDE_DIRS}
	"./"
	"/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/include_cpp"
)

set(SOURCE_FILES
	src/main.cpp
	src/functions.cpp
	src/settings.cpp
	src/statistics.cpp
	src/elements_selection.cpp
	src/write_Excel_file.cpp
    src/read_Excel_file.cpp
	src/serialization.cpp    
	src/photo.cpp )

add_executable(main ${SOURCE_FILES})

# Link libraries  "OpenCV"  & others
target_link_libraries(main ${OpenCV_LIBS} "/Users/and/Downloads/DELETE/libxl-mac-4.6.0/lib/libxl.dylib" )
