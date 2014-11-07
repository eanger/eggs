# Quick things


# Features

## GUI and interaction
* Set of buttons to perform actions
* Mouse can be in multiple modes: build, select, inspect (right click)
* Visual representation of what button is clicked (depth/color)
* Allow changing of zoom level and movement of viewport

## Entity logic/AI
* Each Entity is in charge of specifying its own behaviour
* Person Entities are in charge of building things and doing work
* Pathfinding for an entity to its target (used for building, finding offices/meetings, bathrooms, etc)
* Some entities can be permanent (ie part of the landscape, and immobile)

## Event management
* A newly constructed object remains in "unbuilt" state until constructed
* Construction requires time and labor and parts
