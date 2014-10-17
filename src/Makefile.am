bin_PROGRAMS = eggs 
eggs_SOURCES = \
			   engine.cpp \
			   screen.cpp \
			   input.cpp \
			   world.cpp \
			   state.cpp \
			   main.cpp

eggs_CPPFLAGS = $(SFML_CFLAGS) -DASSETS_DIR='"$(pkgdatadir)"'
eggs_LDADD = $(SFML_LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system

