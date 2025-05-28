TARGET = game_of_life
SRC = main.c functii.c
CC = gcc
CFLAGS = -O2

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
