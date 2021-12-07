CC = gcc
OBJ = mainwindow.o helpmenu.o validation.o resolutions.o setorder.o
DEPS = mainwindow.h helpmenu.h validation.h resolutions.h setorder.h
GTKLIB = `pkg-config --cflags --libs gtk+-3.0`

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(GTKLIB)

finalmatrix: $(OBJ)
	$(CC) -o $@ main.c $^ $(GTKLIB)

clean:
	rm -rf *.o
