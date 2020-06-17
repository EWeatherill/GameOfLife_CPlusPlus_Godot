# Conway's Game of Life in Godot
This personal project intends to put newly acquire knowledge (thanks to COVID furlough), of C++17 and the [Godot Engine](https://godotengine.org/), to use.  It's a work-in-progress.  Any feedback is welcome.

[Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a popular programming exercise and implementing it is a great way to get to grips with a new language (C++17 in this case).

The [Godot](https://godotengine.org/) is a free and open source game engine (see its license [here](https://godotengine.org/license)).  It has its own GDScript programming language but supports additional languages such as C++, C#, and Python.

This project intends to integrate a C++ implementation of Conway's Game of Life with a user interface (UI) built in Godot (using GDScript).

## TODO
- [ ] API-ise the C++ GoL code
  - [ ] Make the grid size 'user-defined'
  - [ ] Unit test + code coverage
- [ ] Create the Godot infrastructure
  - [ ] Incorporate C++ GoL into Godot
  - [ ] Implement the UI

## Design

The following is the design for the UI and its interactions:
![UI design and interactions](/design/UIDesign.jpg)
