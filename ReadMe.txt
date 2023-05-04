i have implemented 2 main .cpp and 2 .h files. these are:
HankGamemode.h
HankGamemode.cpp
HankCharacter.h
HankCharacter.cpp

The Character contains things such as movement functions, onDeath related functions aswell as a constructor for components

the Gamemode contains the references to tiles that are to be used in the map generation. aswell as mapgen functions.

a significant portion such as Menues, UI, Pickups, parts of the character and mapgen are all made in Blueprints. and where
its been needed i have connected the C++ Scripts with Blueprints using the UFUNCTION and UPROPERTY tag


EDIT: 

When publishing the first part of this assignment there was not any outstanding bugs and i will instead discuss the changes and improvements i made on version 2.
For part 2 i have improved the coin and obstacle spawning. Where the old system simply spawned a random amount in range of coins and obstacles in a collisionbox, 
the new system spawns 2 obstacles in 2 out of 3 random positions of the track. As a reward for not bumping into any obstacles and playing well, 
if the player passes a section of the track without hitting an obstacle, the next piece will spawn a row of coins on the 3rd spawn position. 
this allows the player to collect coins.

when first trying to implement these new features i made alot of the functions in c++ instead of blueprint. 
i have since commented them out of the active code and remade the dropping functions in blueprint. 

Some things that could have made this gameplay element a bit more challenging could be to extend the number of obstacles dodged before coins spawn. 
example: if the player hits an obstacle instead of just missing coins for one section of track, it would be the next 5

I will not implement a second character as i believe it goes against the current format of my game.