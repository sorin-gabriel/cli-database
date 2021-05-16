src = database.c functions.c
headers = functions.h
flags = -Wall

build:
	gcc $(src) $(flags) -o tema1

clean:
	rm tema1