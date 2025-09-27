
#BUILD_DIR := /Users/and/Downloads/Verpackungsplan
#SRC_DIRS := /Users/and/workspace/Verpackungsplan/Verpackungsplan
# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
#SOURCES := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')



#files := main.cpp function.cpp
#some_file: $(files)
#echo "Look at this variable: " $(files)
#	touch some_file

DATE	 = ` date "+%Y.%m.%d	%H:%M:%S" `

# Определяем компилятор C++ (clang на macOS)
CXX = clang++



# Определяем флаги компиляции
# -std=c++11: использовать стандарт C++11
# -g: включить отладочную информацию
# -Wall: включить все предупреждения
#works CXXFLAGS = -std=c++20 -Wall -g
CXXFLAGS = -Wall -Wpedantic -Wextra -fdiagnostics-color=always  -std=c++20 -g


# Директории для поиска заголовочных файлов (необязательно)
#INCLUDE_DIRS = -I/путь/к/заголовкам
#works  INCLUDE_DIRS =  -I.
INCLUDE_DIRS =  -I $(shell pwd)


# Директории для поиска библиотек
#LIBRARY_DIRS = -L/путь/к/вашим/библиотекам -L/usr/local/lib
# works LIBRARY_DIRS = -L./libxl/lib
LIBRARY_DIRS = -L $(shell pwd)/libxl/lib


# Флаг -l указывает, какую библиотеку нужно подключить.
# Например, -lmylib подключает библиотеку libmylib.a или libmylib.dylib
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

# Имя исполняемого файла, который будет создан
EXECUTABLE = main

#.RECIPEPREFIX := :
	#	:@echo "recipe prefix symbol is set to '$(.RECIPEPREFIX)' "

# Правила сборки

# Цель по умолчанию: создать исполняемый файл (первая цель в файле)
# При выполнении 'make' без аргументов, эта цель будет выполнена
all: $(EXECUTABLE)
	- @rm -f $(OBJECTS)
	@echo "\n"
	@echo "Clearing...🚿\n"
	@#${CXX} --version
	@echo "\n"
	- @mv -f $(EXECUTABLE) ~/Downloads/Verpackungsplan
	@echo "\n"
	-@echo  $(DATE) "Completed...💯\n"
	@#- @echo "Completed...💯\n"


# Правило для создания исполняемого файла из объектных файлов
$(EXECUTABLE): $(OBJECTS)
	- @ $(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBRARY_DIRS) -o $(EXECUTABLE) $(LIBRARIES)




settings.o: settings.cpp
	- @ $(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

main.o: main.cpp settings.cpp functions.cpp statistics.cpp elements_selection.cpp write_Excel_file.cpp
	- @ $(CXX) $(CXXFLAGS)  $(INCLUDE_DIRS) -c $< -o $@


# Правило для компиляции .cpp файлов в .o файлы
# При компиляции файла source.cpp, создается файл source.o
%.o: %.cpp
	- @ $(CXX) $(CXXFLAGS) -c $< -o $@


# Правило для очистки (удаления скомпилированных файлов)
# Пример: 'make clean'
clean:
	- @ rm -f $(OBJECTS) $(EXECUTABLE)
	- @ rm -f ~/Downloads/Verpackungsplan/main ~/Downloads/Verpackungsplan/example.xls ~/Downloads/Verpackungsplan/OUT.rtf
	- @ echo "Clearing...🚿\n"
	
# Правило для запуска исполняемого файла
# Пример: 'make run'
run: $(EXECUTABLE)
	./$(EXECUTABLE)








