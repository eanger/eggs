# Quick things
* Switch screen to update method
* timer class that abstracts sdl timer obj with start/stop/read/reset fns

# Bigger Tasks
* Make whole frame tiled, but not rendered as tiles
* Buildables (size/sprite/etc) (person, desk chair, wall, floor)
* Button (pressed, or clickable) that opens up menu of buildables. Click to place buildable.
* The World will have to know about entity sizes, which the screen will then have to figure out. If the sprite size doesn't match, that's the renderer's problem, not it's perogative.
* The renderer should be agnostic of game state. The World will populate the entities with the correct menu items (including animations or whatever) by specifying which entity and its location. The Screen just plops out whatever it sees.
