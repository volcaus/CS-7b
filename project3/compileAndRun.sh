g++ -c main.cpp src/complx.cpp -Iinclude/
g++ main.o complx.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app

