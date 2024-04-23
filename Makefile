run:
	g++ -c ./src/main.cpp -o ./obj/main.o -I"C:\SFML-2.6.0\include"
	g++ -c ./src/Text.cpp -o ./obj/Text.o -I"C:\SFML-2.6.0\include"
	g++ -c ./src/Button.cpp -o ./obj/Button.o -I"C:\SFML-2.6.0\include"
	g++ -c ./src/Table.cpp -o ./obj/Table.o -I"C:\SFML-2.6.0\include"
	g++ -c ./src/Player.cpp -o ./obj/Player.o -I"C:\SFML-2.6.0\include"
	g++ -c ./src/Bullet.cpp -o ./obj/Bullet.o -I"C:\SFML-2.6.0\include"
	g++ -c ./src/Game.cpp -o ./obj/Game.o -I"C:\SFML-2.6.0\include"
	g++ ./obj/main.o ./obj/Text.o ./obj/Button.o ./obj/Table.o ./obj/Bullet.o ./obj/Game.o ./obj/Player.o -o ./bin/app.exe -L"C:\SFML-2.6.0\lib" -lsfml-graphics -lsfml-window -lsfml-system
	./bin/app.exe