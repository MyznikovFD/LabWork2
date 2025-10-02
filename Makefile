PROJECT = GwentSimplified

CXX = g++

# Включаем корневой каталог и все подкаталоги в include
CXXFLAGS = -I. -Iinclude -Iinclude/core -Iinclude/players -Iinclude/cards -Iinclude/display -Iinclude/utility -std=c++17 -Werror -Wall -Wpedantic -g -fPIC

SRCDIR = src
OBJDIR = $(SRCDIR)/obj

# 1. Рекурсивный список всех исходных файлов
SRC = $(wildcard $(SRCDIR)/core/*.cpp) \
	  $(wildcard $(SRCDIR)/players/*.cpp) \
	  $(wildcard $(SRCDIR)/cards/*.cpp) \
	  $(wildcard $(SRCDIR)/display/*.cpp) \
	  $(wildcard $(SRCDIR)/utility/*.cpp) \
	  $(SRCDIR)/main.cpp

# 2. Плоский список объектных файлов в OBJDIR
# Пример: src/core/Game.cpp -> Game.cpp -> Game.o -> src/obj/Game.o
OBJ = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SRC)))

# 3. VPATH: Указываем make, где искать исходные файлы (.cpp)
VPATH_DIRS = $(SRCDIR)/core $(SRCDIR)/players $(SRCDIR)/cards $(SRCDIR)/display $(SRCDIR)/utility $(SRCDIR)
VPATH := $(VPATH_DIRS)

# Рекурсивный список всех заголовочных файлов для зависимостей
DEPS = $(wildcard include/*/*.h)


.PHONY: default all clean

default: all

all: $(PROJECT)

# Правило для линковки (использует плоский список OBJ)
$(PROJECT): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

# Правило для компиляции:
# - Цель: $(OBJDIR)/%.o (например, src/obj/Game.o)
# - Предпосылка: %.cpp (например, Game.cpp, который будет найден через VPATH)
# - | $(OBJDIR) гарантирует, что каталог src/obj будет создан перед компиляцией
$(OBJDIR)/%.o: %.cpp $(DEPS) | $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Простое правило для создания базового каталога
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -f $(PROJECT)
