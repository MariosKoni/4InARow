# 4InARow
Terminal based board-game with full functionality.

The creation of "4InARow" was inpired some day in April when bored I decided to search for a game to play online and accidentaly found myself playing it. It was a chill and easy game to play. I wanted to expand my C++ knowledge so I thought why not and made it.

The game is terminal based ofcourse. So it's not so appealing to the eye BUT I have plans to make a GUI version of it. Nonetheless, it has a full menu with the ability to load a game or start a new one, save a game while playing it if you need to leave and delete a save file aswell. You can also play against a friend or against A.I (basic ofcourse nothing really special). It is also combatible with Linux, Windows, Mac.

So the game is not so complex, though I made sure I give it a great polish look. Sure the code could be better and the game aswell but for me was great and considering from where I started back in April (it didn't take that long but I had to abandoned it for a month to focus in my work at Uni) it's a great achievement.

Lastly, what you need to build and play the game is `make`, `g++` (for linux and mac with c++17 support) and that's about it for the linux-mac side of it. You just run make. For Windows, as a native approach (for sure I could have used linuxish tools) I played around and saw that `cl` is a great tool to compile the game and play it, though, you will need the latest visual studio (any edition). Open the start menu and navigate to the visual studio folder and open the "Developer Command Prompt for VS". After that type `cl /W4 /EHsc /std:c++17 main.cpp ../Data/getData.cpp ../Game/Game.cpp ../Player/Player.cpp ../NPC/NPC.cpp /link /out:4InARow.exe`. It'll spit out some warnings that will not be seen in g++ but don't worry. I hope it works, it worked for me.
