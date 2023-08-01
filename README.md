

# VGL

A small, header-only, GPU-accelerated vector graphics renderer for OpenGL.

![alt text](https://github.com/regularshmo/vgl/blob/main/preview/tiger.png?raw=true)
![alt text](https://github.com/regularshmo/vgl/blob/main/preview/text.png?raw=true)

# IMPLEMENTATION

Inspired by https://hhoppe.com/ravg.pdf

VGL works by cutting paths into tiles and evaluating trapezoidal coverage on the GPU.

Edges use 8bit fixed-point coordinates (x0,y0,x1,y1), totaling 32bits per edge and are uploaded to a texture.

Tiles are rendered with quads using GPU instancing, each tile contains an edge-list pointer, fill-info pointer along with the sign (inside/outside) state of it's bottom-left corner.

A sign buffer is used to track when paths cross the top/bottom of tiles. 
Before filling, the sign buffer is scanned from left to right, accumilating sign per tile.

# TODO
- Line Caps & Joins
- TTF Compound Glyph Support
- TTF Alignment / Kerning
- SVG Image Parser
- Texture Fill
- Texture Caching
