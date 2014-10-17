# Eggs: Eric's Game Generation System

This project is to make a game engine in C++ with the main game play scripting implemented in Python. The ultimate goal will be something awesome like Dwarf Fortress.

# Features

## Game Play

City-builder style game. Legion of workers that take tasks off a queue and complete them. Maybe something like a combination of Dwarf Fortress, Sim Tower, Theme Hospital, and Prison Architect. Your job is to build an office building so that you can be "productive" enough to output your work. Needs things like offices/desks, conference rooms, break rooms, parking, snacks, bathrooms.

The field is grid-based and work is assigned by the control system and put into place by construction workers. Office workers have performance characteristics affected by environment that rakes in the money for the company.

* Big empty space, with screen as view into it.
* Different keys for different mouse tools: walls, desks, chairs, etc.
* Click and drag to draw things.
* Each clicked thing will put a new "tasks" into a queue, and workers will have to go make it.
* Each thing will take time/materials to make, modulated by character skill (generated randomly?)
* Start with a set of workers, but can buy/make more.
* Set of workers that sit at desks and do work. Need food/orders/breaks/bathrooms/etc.
* Make "rooms" from items in it? Are things rejected from rooms (ie bathrooms don't work if you have no privacy?)
* Maybe like sim tower, but you have to build the tower and the workers?

## Scripting

The goal is to make the engine in C++ (i.e. rendering, object interactions), but with behavior/logic implemented as python scripts. This should make game logic design much quicker, with the generic stuff (drawing and rendering) implemented in fast languages while the logic stuff can be handled in a more exploratory way. Hard-coding decisions into compiled logic might just obscure gameplay.

A key motivator for this should be Data-Driven design, where logic decides how data is manipulated, but that rendering happens quickly and easily.

A python Game object contains all the state, and can be passed to individual object update() functions. For example if we want some logic to state that a room is only an office if it is bounded by walls and contains a desk, we give the desk the isOffice() function, which takes the World as an argument and searches the local state to see if it's in a room. Or we could just make that a user tool, where you select what squares make up a Room, and that Room object has to make it's own checks for validity.

Maybe scripting's function is just to create game objects. The engine then performs the important work. For example the Worker unit might have to do pathfinding, so we mark that as a characteristic in the script, but let the actual pathfinding algo be implemented in c++. Similarly for the office, we have to make sure it is bounded by walls, so the isBoundedByWalls() func is implemented in c++ but specified as a requirement in the script.

* Hit 'r' to reload all scripts.
* Script to create world
    * On genWorld() c++ call, make python calls to augment world environment with appropriate structures (ie resources, nothing, etc).
* Script to describe 

# To Do
* Game loop: input -> update -> "render"(draw/refresh)
* Use std::chrono::high_resolution_clock: now() for cur time, duration_cast() for difference
* nodelay(stdscr, true): get_wch returns ERR if no key is ready.
* Render knows about objects and locations. Update doesn't actually do anything with scene.
* Maximum refresh rate (300 hz?) 
* Logical map (ie 50 x 50) plus view frame into game (boardered window).
