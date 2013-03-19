all:
	mkdir -p bin
	gcc `find src -name '*.c'` -o bin/test -Isrc/include
