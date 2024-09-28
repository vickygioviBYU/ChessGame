# Overview

I developed my first Hello World in 2014. I am trying to learn C++, because it is the base language, used to create all the other languages, and to create games.

The software I wrote here is a simple chess game. It has only the basic algorithm of the chess. I learned the diferent movements and algorithms, and I implemented it here. I used the C++ language, and the SFML library, available for Windows, Linux, Android and others. The library is easy to use, and encapsulates the OpenGL, which executes small programs at low level, in the graphics card.

My purpose is to learn C++, how to manage every thing at low level, and perhaps some day start to learn assembly language. I will learn how to manage events and windows, drawing graphics, since shapes to complex drawables. I want to create 2D and 3D games, with C++ and complex game engines.

[Chess Game Demo Video](https://www.youtube.com/watch?v=uXafbOH4Q_Y)

# Compiling on Linux

- Install SFML library:

```
sudo apt-get install libsfml-dev
```

- Go to main directory

- Delete Chess

- Run:

```
g++ main.cpp Piece.cpp Board.cpp UI.cpp -lsfml-system -lsfml-window -lsfml-graphics -o Chess
```

- Execute:

```
./Chess
```

# Development Environment

I used C++, SFML Library, G++ compiler, Linux and VirtualBox Virtual Machine. I used Linux Mint.

C++ is a low-level programming language, that includes an increment of C. It has classes, functions, datastructures, algorithms and OOP, structural programming, and event-oriented programming.

SFML is a library that encapsulates OpenGL, that is a language at a low-level, that runs in the graphics card. It has 5 modules: System, Graphics, Window and Events, Audio and Network. I used the Window and Graphics module. Graphics allows to draw simple shapes, and more complicated drawables. Their primitives are points, lines, triangles, and quads. Window allows to draw drawables in the window, and to handle all types of events, including Mouse, Keyboard, Mouse Position, Key Pressed, Key Released, and others

Linux is an open source operating system. Linux Mint is like an improved Ubuntu, and VirtualBox is an open source virtual machine manager.

# Useful Websites

- [C++ Tutorial](https://www.w3schools.com/cpp/)
- [SFML Library](https://www.sfml-dev.org/)
- [GCC](https://gcc.gnu.org/)
- [Linux Mint](https://linuxmint.com/)
- [VirtualBox](https://www.virtualbox.org/)

# Future Work

- Implement an AI to play against the computer
- Improve texture quality
- Paint posible movements
- Make it 3D
