
#EXECUTABLE_EXEC := final_program
#BUILD_DIR := /Users/and/Downloads/Verpackungsplan
#SRC_DIRS := /Users/and/workspace/Verpackungsplan/Verpackungsplan
# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
#SOURCES := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')



#files := main.cpp function.cpp
#some_file: $(files)
#echo "Look at this variable: " $(files)
#	touch some_file

# Имя исполняемого файла, который будет создан
EXECUTABLE = main


# Определяем компилятор C++ (clang на macOS)
CXX = clang++
	

#s


# Определяем флаги компиляции
# -std=c++11: использовать стандарт C++11
# -g: включить отладочную информацию
# -Wall: включить все предупреждения
CXXFLAGS = -std=c++20 -Wall -g
#CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -g


# Директории для поиска заголовочных файлов (необязательно)
#INCLUDE_DIRS = -I/путь/к/заголовкам
# -I/Users/and/workspace/Verpackungsplan/Verpackungsplan/cereal/include
# -I/Users/and/workspace/Verpackungsplan/Verpackungsplan/cereal
# -I/cereal/include
# "/Users/and/workspace/Verpackungsplan/Verpackungsplan/cereal/include"
# -I/Users/and/workspace/Verpackungsplan/Verpackungsplan
#CFLAGS=-I/path/to/first/directory -I/path/to/second/directory
#INCLUDE_DIRS =  -I/Users/and/workspace/Verpackungsplan/Verpackungsplan/cereal/include
INCLUDE_DIRS =  -I.

#BUILD_DIR       =       $(shell pwd)






# Директории для поиска библиотек
#LIBRARY_DIRS = -L/путь/к/вашим/библиотекам -L/usr/local/lib
# -L/Users/and/workspace/Verpackungsplan/Verpackungsplan/cereal/include
# "/Users/and/workspace/Verpackungsplan/Verpackungsplan/cereal/include"
LIBRARY_DIRS = -L/Users/and/workspace/Verpackungsplan/Verpackungsplan/libxl/lib
#LIBRARY_DIRS = -L/libxl/lib



# Имена библиотек для линковки (без префикса lib и расширения)
# Например, для libmylib.a используйте -lmylib
#LIBRARIES = -lmylib -lother_lib
LIBRARIES = -lxl


# Имена исходных файлов проекта (например, main.cpp, my_class.cpp)
SOURCES = main.cpp functions.cpp settings.cpp statistics.cpp elements_selection.cpp write_Excel_file.cpp


# Файлы объектов
# Автоматически генерируем имена объектных файлов из имен исходных файлов
# Например, main.cpp -> main.o, my_class.cpp -> my_class.o
OBJECTS = $(SOURCES:.cpp=.o)


# Правила сборки






# Цель по умолчанию: создать исполняемый файл (первая цель в файле)
# При выполнении 'make' без аргументов, эта цель будет выполнена
all: $(EXECUTABLE)
	${CXX} --version
	rm -f $(OBJECTS)
	#clear; echo "Clearing...🚿";
	#rm ~/Downloads/Verpackungsplan/main;
	cp $(EXECUTABLE)	 ~/Downloads/Verpackungsplan/main;
	rm -f $(EXECUTABLE)
	#shell


# Правило для создания исполняемого файла из объектных файлов
$(EXECUTABLE): $(OBJECTS)
	#$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)  $(LIBRARY_DIRS)  $(LIBRARIES) $(INCLUDE_DIRS)
	#$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)  $(LIBRARY_DIRS)
	# works $(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)  $(LIBRARY_DIRS) $(LIBRARIES)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBRARY_DIRS) $(LIBRARIES) -o $(EXECUTABLE)
	
# Правило для компиляции .cpp файлов в .o файлы
# При компиляции файла source.cpp, создается файл source.o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	#$(CXX) $(CXXFLAGS) -c $< -o $@





# Правило для очистки (удаления скомпилированных файлов)
# Пример: 'make clean'
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	
# Правило для запуска исполняемого файла
# Пример: 'make run'
run: $(EXECUTABLE)
	./$(EXECUTABLE)


#______________________________________________________________________________________________________________







