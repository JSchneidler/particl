### Requirements
- SFML (required for desktop)

### Concepts
- [Verlet integration](https://lisyarus.github.io/blog/posts/perfect-collisions.html#section-position-based-verlet)  
- [Spatial hashing](https://www.gorillasun.de/blog/particle-system-optimization-grid-lookup-spatial-hashing/)

### Optimizations
The following tradeoffs/design decisions were made to balance performance with correctness (it's a toy):
- TODO: Avoid sqrt and pow (TODO: why)
- TODO: Build spatial grid once per frame instead of each collision resolving iteration (potentially misses a collision)
- TODO: Inlining most functions to minimize overhead?