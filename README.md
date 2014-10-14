## 3.2-Asteroid-cocos2d-x
======================

## * What is this project?

This is the updated version (to v3.2 cocos2d-x) of existing project https://github.com/clawoo/AsteroidsCocos2D-x 
which seems to be for v2.x

I updated the project from and checked it on android device. 
The game is working and not crashing. However, there are a thing I need to check because I think the game logic needs to be
refined. I'll do this in coming future. Wait till the time.... Once it is done from my side, I'll add a TAG 'Fully UPGRADED'
at the top of this README.md file.

NOTE: Additional features for extending the game play won't be added by me.
If you want, you can obviously do it yourself.

* Who can use this repository?
This game is very basic implementation for the beginners. Anyone can use it, however, it may not be much beneficial 
for the people who understands and can write atleast a basic game using simple APIs of cocos2d-x (v3.x)


## *Features(API of cocos2d-x v3.2 used) of this project:

1) Sprites
2) Single and Multiple layers on one scene
3) Menu
4) Multiple Touches (Tap, gesture, slide). 
Note: Single Touch not implemented.
5) Basic collision detection without physics framework (Using interesection-Rect class of cocos2d-x v3.2)
6) Data Structure- Vectors, which is newly implemented and extended from the native Vector class avaialble in C++
7) Default Transition to the next scene.

Once, you're done with understanding of this code, then you can gain confidence with atleast writing basic game logic and
can complete your own game single handedly.

Post Advice and suggestions:
1) You still have to learn rest of the APIs and plugins of cocos2d-x which will make you able to publish professional games
on the store.
2) Do read and understand code of game examples like this, so that you have clear picture of what is happening, and
it will help you gain confidence. It will also help you get familiar with the strategy and way which which other people write 
their own games.


## * Want to try it?

Follow the below steps:
* Make a new cocos2d-x v3.2 project
* Import in eclipse and make sure it is imported correctly by running it as an android application and checking whether 
the default HelloWorld scene is appearing.
* Is the basic project working!! Great... 
Now, simply copy and replace the Classes and Resources folder with those which are present in the project that you set up.
* Look, in project explorer of Eclipse, Under your project find jni/Android.mk and open and all the classes that are now
present in the latest Classes folder.
* Also, change the device orientation from landscape to portrait in AndroidManifest.xml file which you can find in the
project explorer only.

Now, run the project as the Android application.


## * Already setup and run the project with above steps, Here is WHAT YOUR GAME LOOKS LIKE:

1) A Main Screen- showing 3 options-Play,Controls, Scores
2) Play Button takes you to actual game where you use touch(tap, gesture, slide to control bullets and motion of ship)
3) Game Over Screen after asteroid collide/touch the ship
4) Controls shows you the control options
5) Scores is dummy scene showing scores.

Any suggestions and doubts are always welcome..

Cheers

Enjoy ...
