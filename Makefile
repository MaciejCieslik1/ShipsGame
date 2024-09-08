# List of source files
SOURCES = main.cpp \
          Ships/Board.cpp \
          Ships/Coords.cpp \
          Ships/Field.cpp \
          Ships/FunctionsM.cpp \
          Ships/Game.cpp \
          Ships/LanguageManager.cpp \
          Ships/Player.cpp \
          Ships/Ship.cpp \
          Ships/Shoal.cpp\
          Ships/CruiseMissile.cpp \
          Ships/Menu.cpp \
          Ships/Process.cpp \
          Ships/ShipsExceptions.cpp \

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Executable name
EXECUTABLE = program

# Build rule
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	g++ $(OBJECTS) -o $@

# Compile rule
%.o: %.cpp
	g++ -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
