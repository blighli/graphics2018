@echo off
g++ -c -o main.o src/main.cpp -I"include"
g++ -o bin/main.exe main.o -L"lib" -lfreeglut -lopengl32 -W
del main.o

:: Run
cd bin
main