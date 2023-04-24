i have implemented 2 main .cpp and 2 .h files. these are:
HankGamemode.h
HankGamemode.cpp
HankCharacter.h
HankCharacter.cpp

The Character contains things such as movement functions, onDeath related functions aswell as a constructor for components

the Gamemode contains the references to tiles that are to be used in the map generation. aswell as mapgen functions.

a significant portion such as Menues, UI, Pickups, parts of the character and mapgen are all made in Blueprints. and where
its been needed i have connected the C++ Scripts with Blueprints using the UFUNCTION and UPROPERTY tag