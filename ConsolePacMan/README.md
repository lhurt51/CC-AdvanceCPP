# Simple Console Pac Man Remake

## Board Sprite

```
#########################################
# o . . . # . . . . . . . . . # . . . . #
# . ### . # . ############# . # . ### . #
# . # . . . . . . . . . . . . . . . # . #
# . # . ### . ##         ## . ### . # . #
# . . . . . . #           # . . . . . . #
# . # . ### . ############# . ### . # . #
# . # . . . . . . . . . . . . . . . # . #
# . ### . # . ############# . # . ### . #
# . . . . # . . . . . . . . . # . . . o #
#########################################
```

## Requirements

1. We will be designing and coding a Pacman game over the next three homework. This home you will be able to draw the board in a ~~separate thread~~ (make it thread safe) and put class stubs for the remaining design which include a description of what you will intend them to perform.

2. Take the pacman board and add player control with player sprite.

## Todo: List

### Systems
- [x] Entry Point System
- [x] Event System
- [x] Layer/Overlay System
- [x] Entity Component System

### Systems & Abstractions
- [x] Application System/Abstraction
- [x] Window System/Abstraction
- [x] Input System/Wrapper/Abstraction
- [x] Renderer System/Abstraction
- [ ] ECS Rendering System

### Wrappers
- [x] Debug Log Wrapper
- [x] Console Window Wrapper
- [x] Console Input Wrapper
- [x] Console Renderer Wrapper

### Managers
- [x] Asset Manager
- [ ] Sprite Manager
- [ ] Scene Manager

### Components/Entities
- [ ] Basic Transform Component
- [ ] Scene Component
- [ ] Sprite Component
- [ ] Player Entity
- [ ] Enemy/AI Entity

### Extra Features
- [ ] Advance 2D Transforms (Rotation, Scale)
- [ ] Advance Rendering (Cameras, Lights)
- [ ] Advance Console Wrapper(Resizing, Better Event handling)
- [ ] Collisions