# VGL

A small, header-only, dependency free, GPU-accelerated vector graphics renderer for OpenGL 3.3+
- 256x coverage based anti-aliasing
- Fast! (batched drawing using a single draw call)
- Fill modes (non-zero, even-odd, intersection)
- Gradients (linear, box, radial) 
- Stroked paths
- TTF fonts

## USAGE

```c
#define VGL_IMPLEMENTATION
#include <vgl.h>
```

```c
vg_init();
// ...
vg_begin();
vg_clear(0xFF000000);
vg_moveto(100, 100);
vg_lineto(200, 100);
vg_curveto(200, 200, 100, 200);
vg_fill(0xFF0000FF);
vg_end();
```

## RENDERS

![alt text](https://github.com/regularshmo/vgl/blob/main/preview/tiger.png?raw=true)
![alt text](https://github.com/regularshmo/vgl/blob/main/preview/text.png?raw=true)

## IMPLEMENTATION

Inspired by https://hhoppe.com/ravg.pdf

VGL works by cutting paths into tiles and evaluating trapezoidal coverage on the GPU.

Edges use 8bit fixed-point coordinates (x0,y0,x1,y1), totaling 32bits per edge and are uploaded to a texture.

Tiles are rendered with quads using GPU instancing, each tile contains an edge-list pointer, fill-info pointer along with the sign (inside/outside) state of it's bottom-left corner.

A sign buffer is used to track when paths cross the top/bottom of tiles. 
Before filling, the sign buffer is scanned from left to right, accumilating sign per tile.

## TODO
- OpenGL 3.0 Support (no instancing)
- Line Caps & Joins
- TTF Compound Glyph Support
- TTF Kerning
- SVG Image Parser
- Texture Fill
- Texture Caching
