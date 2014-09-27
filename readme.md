# EGGS: Eric's Game Generation System

This project is to make a game engine in C++ with the main game play scripting implemented in Python. The ultimate goal will be something awesome like Dwarf Fortress.

# Features

## Game Play

City-builder style game. Legion of workers that take tasks off a queue and complete them. Maybe something like a combination of Dwarf Fortress, Sim Tower, Theme Hospital, and Prison Architect. Your job is to build an office building so that you can be "productive" enough to output your work. Needs things like offices/desks, conference rooms, break rooms, parking, snacks, bathrooms.

The field is grid-based and work is assigned by the control system and put into place by construction workers. Office workers have performance characteristics affected by environment that rakes in the money for the company.

## Scripting

The goal is to make the engine in C++ (i.e. rendering, object interactions), but with behavior/logic implemented as python scripts. This way the scripts can answer simple questions like "What happens when a worker is idle?".

# To Do
* ~~Main file to start up the game engine.~~
* Infinite game loop, polling ~~logic update~~, drawing, rendering.
* Calling out to python script for game logic.

