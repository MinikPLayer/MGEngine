# MGEngine
My current, very much Work In Progress attempt at creating a game engine with C++ and OpenGL.

## Design Philosophy
Create a graphics API agnostic game engine with easy support for model loading, physics and graphics rendering.

## Rendering

### Current Design
Graphics API calls are abstracted into the IRenderer interface, currently with a basic OpenGL implementation.

### Target Design
Separate rendering engine receiving only scene description, similiar to the Godot rendering engine.

### Graphics APIs
- OpenGL [WIP]
- Vulkan (Planned)
- DirectX 12 (Planned)
