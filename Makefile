CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -I.
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system


SRCS = \
    main.cpp \
    jeu/Game.cpp \
    cellule/Cellule.cpp \
    grille/Grille.cpp \
    grille/GrilleClassique.cpp

OBJDIR = build
# place object files under build/ preserving subdirs (eg. build/jeu/Game.o)
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

# list of directories to create for object files
DIRS := $(sort $(dir $(OBJS)))

TARGET = main

.PHONY: all clean distclean run


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)


$(OBJDIR)/%.o: %.cpp | $(DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# create required directories for object files
$(DIRS):
	mkdir -p $@

run: all
	./$(TARGET)


clean:
	rm -f $(OBJS) $(TARGET)

distclean: clean
	rm -rf $(OBJDIR)
