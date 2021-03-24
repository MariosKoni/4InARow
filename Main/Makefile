all:
	#The -lstdc++fs option is only for those with the g++ 8.3.0 or earlier version and prevents a runtime bug from occuring.
	g++ -std=c++17 -lstdc++fs -pthread main.cpp ../Data/getData.cpp ../Game/Game.cpp ../Player/Player.cpp ../NPC/NPC.cpp ../Multiplayer/server.cpp -o 4InARow
debug:
	#Comiling in debug mode.
	g++ -std=c++17 -lstdc++fs -pthread -g main.cpp ../Data/getData.cpp ../Game/Game.cpp ../Player/Player.cpp ../NPC/NPC.cpp ../Multiplayer/server.cpp -o 4InARow_debug
clean:
	rm Play
