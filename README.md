# Cub3d

First-person 3D representation of a maze using raycasting, similar to Wolfenstein 3D (1992).


### Prerequisites

The project runs using the MiniLibX, a simplified version of the Xlib. It can therefore only run in MacOSX, preferably on a computer with a solid CPU !

### The game

Just like B.J. Blazkowicz in Wolfenstein 3D, you have infiltrated a nazi stronghold.

You got what you needed, but you won't get out unnoticed. You're gonna have to fight your way out !

You should be able to survive if you get to the third floor, and kill everyone there. Good luck !

<p align="center">
  <img src="https://i.imgur.com/ll5P9RN.png" width="60%" />
</p>

### How to run it

Using ``make`` will build the executable and run it.

To run it again without remaking, you can simply run the executable with ``./cub3D``.

### Controls

You can move around the maze with ``W`` ``A`` ``S`` ``D``.

You can also rotate the view with the directional arrows ``←`` and ``→``.

You can shoot/stab with ``SPACE`` and open doors with ``SHIFT``.

To exit the game, press ``ESC`` or click the red cross.

### The mandatory part

The basic program that was required to pass. It only includes wall textures and a sprite.

<p align="center">
  <img src="e1N8tiqgKd0.jpg" width="60%" />
</p>
<p align="center">
  <img src="Cub3D2.png" width="60%" />
</p>

### Acknowledgments

* The Coding Train (raycasting inspiration)
* Wolfenstein 3D (for the controversial textures)
* And macrespo (for this beautiful life bar)


## Ressources

* [Playable Wolfenstein 3D](http://users.atw.hu/wolf3d/)
* [Raycasting in JS](http://www.playfuljs.com/a-first-person-engine-in-265-lines/)
* [Some X11 event numbers](https://github.com/qst0/ft_libgfx)
* [Full tutorial in English](https://lodev.org/cgtutor/raycasting.html)
* [Full tutorial in French (translation of the English tutorial)](http://forums.mediabox.fr/wiki/tutoriaux/flashplatform/affichage/3d/raycasting)
* [Images in minilibx](https://github.com/keuhdall/images_example)
* [BMP format on StackOverflow](https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries)
* [BMP format explanation](https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html)
