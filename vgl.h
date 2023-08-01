/*////////////////////////////////////////////////////
// Public domain, vector-graphics library.
//////////////////////////////////////////////////////

CREATOR: Josian Marriott (josianjames@gmail.com)

LICENSE: This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.

////////////////////////////////////////////////////*/

#ifndef VGL_H
#define VGL_H

#ifndef VGL_API
#define VGL_API extern
#endif

/*//////////////////////////
// DRIVER
//////////////////////////*/

#define VGL_OPENGL  (1)
#define VGL_VULKAN  (2) // not implemented
#define VGL_DIRECTX (3) // not implemented

#ifndef VGL_DRIVER
#define VGL_DRIVER VGL_OPENGL
#endif

/*//////////////////////////
// API
//////////////////////////*/

#define VG_NEGATIVE     (-1)
#define VG_POSITIVE     (1)
#define VG_NONZERO      (2)
#define VG_EVENODD      (3)
#define VG_INTERSECTION (4)

typedef unsigned vgColor;
typedef struct   vgPoint  vgPoint;
typedef union    vgMatrix vgMatrix;
typedef struct   vgFont   vgFont;

VGL_API void  vg_init       ();
VGL_API void  vg_begin      ();
VGL_API void  vg_flush      ();
VGL_API void  vg_clear      (unsigned color);
VGL_API void  vg_end        ();
			  
VGL_API void  vg_path       ();
VGL_API void  vg_moveto     (float x, float y);
VGL_API void  vg_lineto     (float x, float y);
VGL_API void  vg_curveto    (float x0, float y0, float x1, float y1);
VGL_API void  vg_cubicto    (float x0, float y0, float x1, float y1, float x2, float y2);
VGL_API void  vg_arcto      (float x0, float y0, float x1, float y1, float radius);
VGL_API void  vg_line       (float x0, float y0, float x1, float y1);
VGL_API void  vg_vline      (float x, float y0, float y1);
VGL_API void  vg_hline      (float y, float x0, float x1);
VGL_API void  vg_arc        (float x, float y, float a0, float a1, float r);
VGL_API void  vg_circle     (float x, float y, float r);
VGL_API void  vg_ellipse    (float x, float y, float rx, float ry);
VGL_API void  vg_rect       (float x, float y, float w, float h);
VGL_API void  vg_rectr      (float x, float y, float w, float h, float rx, float ry);
VGL_API void  vg_char       (float x, float y, float size, int c);
VGL_API void  vg_text       (float x, float y, float size, const char *str);
VGL_API void  vg_textf      (float x, float y, float size, const char *format, ...);
VGL_API float vg_textw      (float size, const char *str);
VGL_API void  vg_close      ();
						   
VGL_API void  vg_fill       (unsigned color);
VGL_API void  vg_fillr      (unsigned c0, unsigned c1, float x, float y, float r0, float r1);
VGL_API void  vg_fillb      (unsigned c0, unsigned c1, float x, float y, float w, float h, float r0, float r1);
VGL_API void  vg_fillg      (unsigned c0, unsigned c1, float x0, float y0, float x1, float y1);
VGL_API void  vg_fillgr     (unsigned c0, unsigned c1, float x, float y, float w, float h, float r);
VGL_API void  vg_fillbh     (float x, float y, float w, float h, float sat, float val);
VGL_API void  vg_fillbs     (float x, float y, float w, float h, float hue);
VGL_API void  vg_stroke     (unsigned color, float width);
VGL_API void  vg_strokeg    (unsigned c0, unsigned c1, unsigned c2, float width);

VGL_API void  vg_push       ();
VGL_API void  vg_reset      ();
VGL_API void  vg_mode       (int mode);
VGL_API void  vg_winding    (int winding);
VGL_API void  vg_spaa       (float spaa);
VGL_API void  vg_alpha      (float alpha);
VGL_API void  vg_font       (vgFont *font);
VGL_API void  vg_matrix     (float *matrix);
VGL_API void  vg_identity   ();
VGL_API void  vg_translate  (float x, float y);
VGL_API void  vg_rotate     (float degs);
VGL_API void  vg_rotater    (float rads);
VGL_API void  vg_scale      (float x, float y);
VGL_API void  vg_project    (float *x, float *y);
VGL_API void  vg_unproject  (float *x, float *y);
VGL_API void  vg_projectn   (float *x, float *y);
VGL_API void  vg_unprojectn (float *x, float *y);
VGL_API void  vg_clip       (float x, float y, float w, float h);
VGL_API void  vg_noclip     ();
VGL_API void  vg_pop(); 

VGL_API void  vg_size       (int *w, int *h);

/*//////////////////////////
// MATH
//////////////////////////*/

#define VG_PI  (3.14159265358979323846f)
#define VG_PI2 (VG_PI*2.0f)
#define VG_RAD (VG_PI/180.0f)
#define VG_DEG (180.0f/VG_PI)

/*//////////////////////////
// POINT
//////////////////////////*/

struct vgPoint {
	float x, y;
};

int vg_point_norm(vgPoint *v, float *l);

/*//////////////////////////
// MATRIX
//////////////////////////*/

union vgMatrix {
	float v[6];
	float m[3][3];
	struct {
		float xx, xy, xt;
		float yx, yy, yt;
	};
};

VGL_API void vg_matrix_identity   (float *m);
VGL_API void vg_matrix_translate  (float *m, float x, float y);
VGL_API void vg_matrix_rotate     (float *m, float a);
VGL_API void vg_matrix_scale      (float *m, float x, float y);
VGL_API void vg_matrix_multiply   (float *m, float *mul);
VGL_API int  vg_matrix_inverse    (float *m, float *src);
VGL_API void vg_matrix_lerp       (float *m, float *mat, float t);
VGL_API void vg_matrix_project    (float *m, float *x, float *y);
VGL_API void vg_matrix_unproject  (float *m, float *x, float *y);
VGL_API void vg_matrix_projectn   (float *m, float *x, float *y);
VGL_API void vg_matrix_unprojectn (float *m, float *x, float *y);
VGL_API void vg_matrix_pan        (float *m, float x, float y, float speed);
VGL_API void vg_matrix_zoom       (float *m, float x, float y, float zoom);

/*//////////////////////////
// COLOR
//////////////////////////*/

#define VG_R(c)                   (((c) >>  0) & 0xFF)
#define VG_G(c)                   (((c) >>  8) & 0xFF)
#define VG_B(c)                   (((c) >> 16) & 0xFF)
#define VG_A(c)                   (((c) >> 24) & 0xFF)
#define VG_RGBA(r, g, b, a)       ((vgColor)((r) | (g) << 8 | (b) << 16 | (a) << 24))
#define VG_RGB(r, g, b)           VG_RGBA((r), (g), (b), 0xFF)
#define VG_RGBAF(r, g, b, a)      VG_RGBA((vgColor)(r*0xFF),(vgColor)(g*0xFF),(vgColor)(b*0xFF),(vgColor)(a*0xFF))
#define VG_RGBF(r, g, b)          VG_RGBA((vgColor)(r*0xFF),(vgColor)(g*0xFF),(vgColor)(b*0xFF),0xFF)
#define VG_ALPHA(c, a)            ((vgColor)((c & 0x00FFFFFF) | ((VG_A(c) * (a) / 0xFF) << 24)))
#define VG_ALPHAF(c, a)           VG_ALPHA(c, (vgColor)(a*0xFF))
#define VG_HSV(h, s, v)           vg_color_hsv((h), (s), (v))
#define VG_BLEND(src, dst)        vg_color_blend(src, dst)
#define VG_LERP(src, dst, a)      vg_color_lerp(src, dst, a)
#define VG_LERPF(src, dst, a)     vg_color_lerpf(src, dst, a)

VGL_API vgColor vg_color_hsv   (float h, float s, float v);
VGL_API vgColor vg_color_blend (vgColor src, vgColor dst);
VGL_API vgColor vg_color_lerp  (vgColor src, vgColor dst, vgColor a);
VGL_API vgColor vg_color_lerpf (vgColor src, vgColor dst, float a);

/*//////////////////////////
// FONT
//////////////////////////*/

VGL_API vgFont* vg_font_load         (const char *filename);
VGL_API vgFont* vg_font_loadp        (void *data, int size);
VGL_API vgFont* vg_font_default      ();
VGL_API void    vg_font_draw_char    (vgFont *font, float x, float y, float size, int c);
VGL_API void    vg_font_draw_text    (vgFont *font, float x, float y, float size, const char *str);
VGL_API float   vg_font_measure_text (vgFont *font, float size, const char *str);

/*//////////////////////////
// COMMANDS
//////////////////////////*/

enum {
	VG_CMD_END,
	VG_CMD_MOVETO,
	VG_CMD_LINETO,
	VG_CMD_CURVETO,
	VG_CMD_CUBICTO,
	VG_CMD_ALPHA,
	VG_CMD_FILL,
	VG_CMD_STROKE,
	// TODO: extend
};

typedef union vgCommand {
	unsigned char type;
	struct { unsigned char type; float coords[2];            } moveto;
	struct { unsigned char type; float coords[2];            } lineto;
	struct { unsigned char type; float coords[4];            } curveto;
	struct { unsigned char type; float coords[6];            } cubicto;
	struct { unsigned char type; float value;                } alpha;
	struct { unsigned char type; vgColor color;              } fill;
	struct { unsigned char type; vgColor color; float width; } stroke;
} vgCommand;

void vg_eval(vgCommand *commands);

/*//////////////////////////
// IMPLEMENTATION
//////////////////////////*/

#if defined(VGL_IMPLEMENTATION) || defined(__INTELLISENSE__)

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define VG_MAX_PATH     (2048*2048)
#define VG_MAX_STATE    (256)

#define VG_TESS_DIST    (4.0f)
#define VG_TESS_DIST2   (VG_TESS_DIST*VG_TESS_DIST)
#define VG_TESS_FACTOR  (1.0f / VG_TESS_DIST)

#define VG_PATH_NONE    (0)
#define VG_PATH_MOVETO  (1)
#define VG_PATH_LINETO  (2)
#define VG_PATH_CURVETO (3)

typedef struct vgPath    vgPath;
typedef struct vgState   vgState;
typedef struct vgContext vgContext;

struct vgPath {
	union {
		struct { 
			int closed   : 1;
			int winding  : 1;
			int reserved : 30;
			int end;
		};
		vgPoint point;
	};
};

struct vgState {
	int      mode;
	int      winding;
	float    spaa;
	float    alpha;
	vgFont*  font;
	vgMatrix matrix;
	vgMatrix clip;
};

struct vgContext {
	struct {
		int x;
		int y;
	} size;
	struct {
		int edges;
		int tiles;
		int draws;
		int upload;
	} stats;
	vgState state;
};

vgContext vg;
int       vg_initialized;
int       vg_path_reset;
int       vg_path_index;
int       vg_path_count;
vgPoint   vg_path_start;
vgPoint   vg_path_point;
vgPath    vg_path_buffer[VG_MAX_PATH];
vgState   vg_state_buffer[VG_MAX_STATE];
int       vg_state_count;
void     *vg_default_font;

void vg_fill_prime();
void vg_fill_flush();

void vg_driver_init();
void vg_driver_prime();
void vg_driver_size(int *w, int *h);
void vg_driver_clear(unsigned color);
void vg_driver_flush();

void vg_init() 
{
	if (vg_initialized) return;
	vg_initialized = 1;
	memset(&vg, 0, sizeof(vg));
	vg_driver_init();
	vg.state.spaa = 0;
	vg_reset();
}

void vg_begin()
{
	int w, h;

	vg_init();

	vg_driver_size(&w, &h);
	vg.size.x = w;
	vg.size.y = h;

	vg.stats.edges  = 0;
	vg.stats.tiles  = 0;
	vg.stats.draws  = 0;
	vg.stats.upload = 0;

	vg_path_reset  = 1;
	vg_path_index  = 0;
	vg_path_count  = 0;
	vg_state_count = 0;

	vg_reset();
	vg_fill_prime();
	vg_driver_prime();
}

void vg_size(int *w, int *h)
{
	*w = vg.size.x;
	*h = vg.size.y;
}

void vg_path()
{
	vg_path_reset  = 1;
	vg_path_index  = 0;
	vg_path_count  = 0;
}

void vg_end()
{
	vg_flush();
}

void vg_clear(unsigned color)
{
	vg_driver_clear(color);
}

void vg_flush()
{
	vg_driver_flush();
	vg_fill_flush();
}

static void vg_push_point(float x, float y)
{
	assert(vg_path_count < VG_MAX_PATH - 1);
	vgPoint point = { x, y };
	if (vg_path_reset) {
		vg_path_reset = 0;
		vg_path_index = 0;
		vg_path_count = 0;
	}
	if (vg_path_index == vg_path_count) {
		vgPath *path = &vg_path_buffer[vg_path_count++];
		path->winding = vg.state.winding >= 0;
		vg_path_start = point;
	}
	vg_path_point = point;
	vg_path_buffer[vg_path_count++].point = (vgPoint) { x, y };
}

static void vg_push_path()
{
	if (vg_path_index == vg_path_count) return;
	vgPath *path = &vg_path_buffer[vg_path_index];
	path->end = vg_path_count;
	path->closed = vg_path_point.x == vg_path_start.x && vg_path_point.y == vg_path_start.y;
	vg_path_index = vg_path_count;
}

void vg_moveto(float x, float y)
{
	vg_push_path();
	vg_project(&x, &y);
	vg_push_point(x, y);
}

void vg_lineto(float x, float y)
{
	vg_project(&x, &y);
	vg_push_point(x, y);
}

static void vg_curvetor(
	float x1, float y1, 
	float x2, float y2,
	float x3, float y3,
	int level)
{
	const float tesstol = 0.125f;

	float x12, y12, x23, y23, x123, y123;
	float dx, dy, d2;

	if (level > 10) {
		vg_push_point(x3, y3);
		return;
	}

	dx = x3 - x1;
	dy = y3 - y1;
	d2 = ((x2 - x3) * dy - (y2 - y3) * dx);

	if ((fabsf(dx) < 0.5f && fabsf(dy) < 0.5f)) {
		vg_push_point(x3, y3);
		return;
	}

	if (d2*d2 < tesstol * (dx*dx + dy*dy)) {
		vg_push_point(x3, y3);
		return;
	}

	x12 = (x1 + x2) * 0.5f;
	y12 = (y1 + y2) * 0.5f;
	x23 = (x2 + x3) * 0.5f;
	y23 = (y2 + y3) * 0.5f;
	x123 = (x12 + x23) * 0.5f;
	y123 = (y12 + y23) * 0.5f;

	vg_curvetor(x1, y1, x12, y12, x123, y123, level + 1);
	vg_curvetor(x123, y123, x23, y23, x3, y3, level + 1);
}

void vg_curveto(float ax, float ay, float px, float py)
{
	float sx, sy;

	if (vg_path_reset) {
		vg_moveto(px, py);
		return;
	}

	vg_project(&ax, &ay);
	vg_project(&px, &py);

	sx = vg_path_point.x;
	sy = vg_path_point.y;
	 
	if ((sx < 0 && ax < 0 && px < 0) ||
		(sx > vg.size.x && ax > vg.size.x && px > vg.size.x) ||
		(sy < 0 && ax < 0 && px < 0) ||
		(sy > vg.size.y && ay > vg.size.x && px > vg.size.x)) {
		vg_push_point(ax, ay);
		vg_push_point(px, py);
		return;
	}

	vg_curvetor(sx, sy, ax, ay, px, py, 0);
}

static void vg_cubictor(
	float x1, float y1,
	float x2, float y2,
	float x3, float y3,
	float x4, float y4,
	int level)
{
	// bezier tesselation. thanks to nanovg.
	const float tesstol = 0.125f;

	float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
	float dx, dy, d2, d3;

	if (level > 10) {
		vg_push_point(x4, y4);
		return;
	}

	dx = x4 - x1;
	dy = y4 - y1;
	d2 = fabsf(((x2 - x4) * dy - (y2 - y4) * dx));
	d3 = fabsf(((x3 - x4) * dy - (y3 - y4) * dx));

	if ((fabsf(dx) < 0.5f && fabsf(dy) < 0.5f)) {
		vg_push_point(x4, y4);
		return;
	}

	if ((d2 + d3)*(d2 + d3) < tesstol * (dx*dx + dy*dy)) {
		vg_push_point(x4, y4);
		return;
	}

	x12   = (x1 + x2) * 0.5f;
	y12   = (y1 + y2) * 0.5f;
	x23   = (x2 + x3) * 0.5f;
	y23   = (y2 + y3) * 0.5f;
	x34   = (x3 + x4) * 0.5f;
	y34   = (y3 + y4) * 0.5f;
	x123  = (x12 + x23) * 0.5f;
	y123  = (y12 + y23) * 0.5f;
	x234  = (x23 + x34) * 0.5f;
	y234  = (y23 + y34) * 0.5f;
	x1234 = (x123 + x234) * 0.5f;
	y1234 = (y123 + y234) * 0.5f;

	vg_cubictor(x1, y1, x12, y12, x123, y123, x1234, y1234, level + 1);
	vg_cubictor(x1234, y1234, x234, y234, x34, y34, x4, y4, level + 1);
}

void vg_cubicto(float ax, float ay, float bx, float by, float px, float py)
{
	float sx, sy;
	
	if (vg_path_reset) {
		vg_moveto(px, py);
		return;
	}

	vg_project(&ax, &ay);
	vg_project(&bx, &by);
	vg_project(&px, &py);
	
	sx = vg_path_point.x;
	sy = vg_path_point.y;

	if ((sx < 0 && ax < 0 && bx < 0 && px < 0) ||
		(sx > vg.size.x && ax > vg.size.x && bx > vg.size.x && px > vg.size.x) ||
		(sy < 0 && ay < 0 && by < 0 && py < 0) ||
		(sy > vg.size.y && ay > vg.size.y && by > vg.size.y && py > vg.size.y)) {
		vg_push_point(ax, ay);
		vg_push_point(bx, by);
		vg_push_point(px, py);
		return;
	}

	vg_cubictor(sx, sy, ax, ay, bx, by, px, py, 0);
}

void vg_close()
{
	if (vg_path_point.x != vg_path_start.x ||
		vg_path_point.y != vg_path_start.y) {
		vg_push_point(vg_path_start.x, vg_path_start.y);
	}
}

void vg_line(float x0, float y0, float x1, float y1)
{
	vg_moveto(x0, y0);
	vg_lineto(x1, y1);
}

void vg_vline(float x, float y0, float y1)
{
	vg_moveto(x, y0);
	vg_lineto(x, y1);
}

void vg_hline(float y, float x0, float x1)
{
	vg_moveto(x0, y);
	vg_lineto(x1, y);
}

void vg_arc(float x, float y, float a0, float a1, float r)
{
	static int   cached;
	static float points[2048][2];
	const  int   cachesize = sizeof(points) / sizeof(points[0]);

	if (!cached) {
		float step = 3.14159265359f * 2.0f / cachesize;
		float angle = 0.0f;
		for (int index = 0; index < cachesize; index++) {
			angle += step;
			points[index][0] = cosf(angle);
			points[index][1] = sinf(angle);
		}
		cached = 1;
	}

	float delta, start, angle, step, *vector, sx, sy;
	int index, id, count, closed;

	sx = vg.state.matrix.xx + vg.state.matrix.xy;
	sy = vg.state.matrix.yx + vg.state.matrix.yy;

	count = 4 + (int)(fabsf(r) * 0.75f * sqrtf(sx * sx + sy * sy));
	if (count > 256) count = 256;

	delta = a1 - a0;
	delta = delta < -360.0f ? -360.0f : delta > 360.0f ? 360.0f : delta;
	closed = delta == 360.0f;
	step = 1.0f / (count - 1) * delta / 360.0f;
	start = angle = a0 / 360.0f;
	if (r < 0) step = -step;

	for (index = 0; index < count; index++) {
		id = ((int)(angle * cachesize) % cachesize + cachesize) % cachesize;
		vector = points[id];
		if (index == 0) {
			vg_moveto(x + vector[0] * r, y + vector[1] * r);
		} else {
			vg_lineto(x + vector[0] * r, y + vector[1] * r);
		}
		if (closed && index == count - 2) {
			angle = start;
		} else {
			angle += step;
		}
	}
}

void vg_ellipse(float x, float y, float rx, float ry)
{
	vgMatrix m;
	m = vg.state.matrix;
	vg_scale(rx, ry);
	vg_arc(x, y, 0, 360, 1.0f);
	vg.state.matrix = m;
}

void vg_circle(float x, float y, float r)
{
	vg_arc(x, y, 0, 360, r);
}

void vg_rect(float x, float y, float w, float h)
{
	vg_moveto(x, y);
	vg_lineto(x + w, y);
	vg_lineto(x + w, y + h);
	vg_lineto(x, y + h);
	vg_lineto(x, y);
}

void vg_rectr(float x, float y, float w, float h, float rx, float ry)
{
	float hw, hh;

	hw = w * 0.5f;
	hh = h * 0.5f;
	rx = (rx > fabsf(hw)) ? hw : hw > 0 ? rx : -rx;
	ry = (ry > fabsf(hh)) ? hh : hh > 0 ? ry : -ry;

	vg_moveto  (x + rx,     y                                  );
	vg_lineto  (x + w - rx, y                                  );
	vg_curveto (x + w,      y,          x + w,      y + ry     );
	vg_lineto  (x + w,      y + h - ry                         );
	vg_curveto (x + w,      y + h,      x + w - rx, y + h      );
	vg_lineto  (x + rx,     y + h                              );
	vg_curveto (x,          y + h,      x,          y + h - ry );
	vg_lineto  (x,          y + ry                             );
	vg_curveto (x,          y,          x + rx,     y          );
}

void vg_char(float x, float y, float size, int c)
{
	if (!vg.state.font) return;
	vg_font_draw_char((vgFont*)vg.state.font, x, y, size, c);
}

void vg_text(float x, float y, float size, const char *str)
{
	if (!vg.state.font) return;
	vg_font_draw_text((vgFont*)vg.state.font, x, y, size, str);
}

float vg_textw(float size, const char *str)
{
	if (!vg.state.font) return 0;
	return vg_font_measure_text((vgFont*)vg.state.font, size, str);
}

void vg_textf(float x, float y, float size, const char *format, ...)
{
	va_list args; int length; char sbuff[512], *pbuff, *mbuff = 0;
	va_start(args, format);
	length = vsnprintf(0, 0, format, args);
	va_end(args);
	if (length < sizeof(sbuff)) pbuff = sbuff;
	else pbuff = mbuff = malloc(length + 1);
	va_start(args, format);
	vsnprintf(pbuff, length + 1, format, args);
	va_end(args);
	vg_text(x, y, size, pbuff);
	if (mbuff) free(mbuff);
}

void vg_reset()
{
	vg.state.mode = VG_NONZERO;
	vg.state.winding = VG_POSITIVE;
	vg.state.alpha = 1.0f;
	vg_identity();
	vg_noclip();
}

void vg_push()
{
	vg_state_buffer[vg_state_count++] = vg.state;
}

void vg_pop()
{
	vg.state = vg_state_buffer[--vg_state_count];
}

void vg_mode(int mode)
{
	vg.state.mode = mode;
}

void vg_winding(int winding)
{
	vg.state.winding = winding;
}

void vg_spaa(float spaa)
{
	vg.state.spaa = spaa;
}

void vg_alpha(float alpha)
{
	if (alpha < 0) alpha = 0; 
	else if (alpha > 1) alpha = 1;
	vg.state.alpha *= alpha;
}

void vg_font(vgFont *font)
{
	vg.state.font = font;
}

void vg_matrix(float *matrix)
{
	vg.state.matrix = *(vgMatrix*)matrix;
}

void vg_identity()
{
	vg_matrix_identity(vg.state.matrix.v);
}

void vg_translate(float x, float y)
{
	vg_matrix_translate(vg.state.matrix.v, x, y);
}

void vg_rotate(float degs)
{
	vg_matrix_rotate(vg.state.matrix.v, degs * (VG_PI / 180.0f));
}

void vg_rotater(float rads)
{
	vg_matrix_rotate(vg.state.matrix.v, rads);
}

void vg_scale(float x, float y)
{
	vg_matrix_scale(vg.state.matrix.v, x, y);
}

void vg_project(float *x, float *y)
{
	vg_matrix_project(vg.state.matrix.v, x, y);
}

void vg_unproject(float *x, float *y)
{
	vg_matrix_unproject(vg.state.matrix.v, x, y);
}

void vg_projectn(float *x, float *y)
{
	vg_matrix_projectn(vg.state.matrix.v, x, y);
}

void vg_unprojectn(float *x, float *y)
{
	vg_matrix_unprojectn(vg.state.matrix.v, x, y);
}

void vg_clip(float x, float y, float w, float h)
{
	x += 0.5f; y += 0.5f; w -= 1.0f; h -= 1.0f;
	float iw = 1.0f / w, ih = 1.0f / h;
	vg_matrix_inverse(vg.state.clip.v, vg.state.matrix.v);
	vg.state.clip.v[0] = vg.state.clip.v[0] * iw;
	vg.state.clip.v[1] = vg.state.clip.v[1] * iw;
	vg.state.clip.v[2] = vg.state.clip.v[2] * iw - x * iw;
	vg.state.clip.v[3] = vg.state.clip.v[3] * ih;
	vg.state.clip.v[4] = vg.state.clip.v[4] * ih;
	vg.state.clip.v[5] = vg.state.clip.v[5] * ih - y * ih;
}

void vg_noclip()
{
	vg.state.clip.v[0] = 0.0f;
	vg.state.clip.v[1] = 0.0f;
	vg.state.clip.v[2] = 0.5f;
	vg.state.clip.v[3] = 0.0f;
	vg.state.clip.v[4] = 0.0f;
	vg.state.clip.v[5] = 0.5f;
}

/*//////////////////////////
// POINT
//////////////////////////*/

int vg_point_norm(vgPoint *v, float *l)
{
	float d, i;
	d = v->x*v->x + v->y*v->y;
	if (d > 0) {
		i = 1.0f / sqrtf(d);
		v->x *= i;
		v->y *= i;
		*l = d;
		return 1;
	} else {
		v->x = 0;
		v->y = 0;
		*l = 0;
		return 0;
	}
}

/*//////////////////////////
// RECT
//////////////////////////*/

typedef struct vgRect {
	int minx, miny;
	int maxx, maxy;
} vgRect;

static vgRect vg_rect_add(vgRect a, int x, int y)
{
	vgRect r;
	r.minx = a.minx < x ? a.minx : x;
	r.miny = a.miny < y ? a.miny : y;
	r.maxx = a.maxx > x ? a.maxx : x;
	r.maxy = a.maxy > y ? a.maxy : y;
	return r;
}

static vgRect vg_rect_inflate(vgRect a, int rx, int ry) 
{
	vgRect r;
	r.minx = a.minx - rx;
	r.miny = a.miny - ry;
	r.maxx = a.maxx + rx;
	r.maxy = a.maxy + ry;
	return r;
}

static vgRect vg_rect_clamp(vgRect a, vgRect b)
{
	vgRect r;
	r.minx = a.minx > b.minx ? a.minx : b.minx;
	r.miny = a.miny > b.miny ? a.miny : b.miny;
	r.maxx = a.maxx < b.maxx ? a.maxx : b.maxx;
	r.maxy = a.maxy < b.maxy ? a.maxy : b.maxy;
	return r;
}

static vgRect vg_rect_union(vgRect a, vgRect b)
{
	vgRect c;
	c.minx = a.minx < b.minx ? a.minx : b.minx;
	c.miny = a.miny < b.miny ? a.miny : b.miny;
	c.maxx = a.maxx > b.maxx ? a.maxx : b.maxx;
	c.maxy = a.maxy > b.maxy ? a.maxy : b.maxy;
	return c;
}

/*//////////////////////////
// FILL
//////////////////////////*/

// VGL works by cutting paths into tiles and evaluating trapezoidal coverage on the GPU.
// 
// Edges use 8bit fixed - point coordinates(x0, y0, x1, y1), totaling 32bits per edge and are uploaded to a texture.
// 
// Tiles are rendered with quads using GPU instancing, each tile contains an edge - list pointer, fill - info pointer along with the sign(inside / outside) state of it's bottom-left corner.
// 
// A sign buffer is used to track when paths cross the top / bottom of tiles.
// Before filling, the sign buffer is scanned from left to right, accumilating sign per tile.

#define VG_GRID_SIZE   (1024)

#define VG_MAX_DATA    (2048*2048)
#define VG_MAX_TILES   (2048*128)
#define VG_MAX_EDGES   (1 << 18)

#define VG_PIXEL_LOG2  (4) // subpixel precision (16x16 for 256AA)
#define VG_PIXEL_SIZE  (1 << VG_PIXEL_LOG2)
#define VG_PIXEL_MASK  (VG_PIXEL_SIZE - 1)

#define VG_TILE_LOG2   (7) // tile precision (128/16 for 8px per tile)
#define VG_TILE_SIZE   (1 << VG_TILE_LOG2)
#define VG_TILE_DIMS   (VG_TILE_SIZE / VG_PIXEL_SIZE)
#define VG_TILE_MASK   (VG_TILE_SIZE - 1)

#define VG_EDGE_LOG2   (8) // edge precision
#define VG_EDGE_SIZE   (1 << VG_EDGE_LOG2)
#define VG_EDGE_MASK   (VG_EDGE_SIZE - 1)
#define VG_EDGE_BORDER ((VG_EDGE_SIZE - VG_TILE_SIZE) / 2)

#define VG_FILL_FLAT    (0)
#define VG_FILL_LIN     (1)
#define VG_FILL_RAD     (2)
#define VG_FILL_RAD_HUE (3)
#define VG_FILL_RAD_SAT (4)
#define VG_FILL_BOX     (5)
#define VG_FILL_BOX_HUE (6)
#define VG_FILL_BOX_SAT (7)
#define VG_FILL_GRID    (8)

#pragma pack(push, 1)

typedef struct vgFill {
	union {
		struct {
			char mode;
			char type;
			char spaa;
			char rsv1;
		};
		unsigned args;
	};
	unsigned color0;
	unsigned color1;
	unsigned clip[6];
	unsigned matrix[6];
	unsigned extent[2];
	unsigned radius[2];
} vgFill;

typedef struct vgTile {
	union {
		struct {
			  signed short sign;
			unsigned short count;
		};
		unsigned args;
	};
	float    data;
	float    edges;
	unsigned coord;
} vgTile;

typedef union vgEdge {
	struct {
		unsigned char x0;
		unsigned char y0;
		unsigned char x1;
		unsigned char y1;
	};
	unsigned packed;
} vgEdge;

#pragma pack(pop)

unsigned    vg_data_buffer[VG_MAX_DATA];
int         vg_data_count;
		    
vgTile      vg_tile_buffer[VG_MAX_TILES];
int         vg_tile_count;

vgEdge      vg_edge_buffer[VG_MAX_EDGES];
int         vg_edge_links[VG_MAX_EDGES];
int         vg_edge_count;
		 
signed char vg_tile_sign[VG_GRID_SIZE * VG_GRID_SIZE];
int         vg_tile_edge[VG_GRID_SIZE * VG_GRID_SIZE];
		 
float       vg_grid_scalex;
float       vg_grid_scaley;
int         vg_grid_sizex;
int         vg_grid_sizey;
vgRect      vg_grid_bounds;
		    
int         vg_fill_reset;
vgPoint     vg_fill_start;
vgPoint     vg_fill_point;
int         vg_fill_winding;

static void vg_push_fill(vgFill *fill, int ntiles, int nedges, unsigned** pdata, unsigned** pedges);
static void vg_push_tile(int x, int y, int sign, void* data, void* edges, int count);

static void vg_fill_prime()
{
	vg_data_count  = 0;
	vg_tile_count  = 0;
	vg_grid_scalex = vg.size.x / (float)VG_TILE_DIMS;
	vg_grid_scaley = vg.size.y / (float)VG_TILE_DIMS;
	vg_grid_sizex  = (int)ceilf(vg_grid_scalex) + 2;
	vg_grid_sizey  = (int)ceilf(vg_grid_scaley) + 2;
	memset(vg_tile_sign, 0, vg_grid_sizex * vg_grid_sizey * sizeof(vg_tile_sign[0]));
	memset(vg_tile_edge, 0, vg_grid_sizex * vg_grid_sizey * sizeof(vg_tile_edge[0]));
}

static void vg_fill_flush()
{
	vg.stats.draws += 1;
	vg.stats.tiles += vg_tile_count;
	vg.stats.upload += sizeof(vgTile) * vg_tile_count + sizeof(vgEdge) * vg_edge_count;

	vg_tile_count = 0;
	vg_data_count = 0;
}

static void vg_fill_begin()
{
	vg_push_path();
	vg_path_reset = 1;
	vg_fill_reset = 1;
	vg_fill_winding = vg.state.winding;

	vg_edge_count = 1;
	vg_grid_bounds.minx = vg_grid_sizex;
	vg_grid_bounds.miny = vg_grid_sizey;
	vg_grid_bounds.maxx = 0;
	vg_grid_bounds.maxy = 0;
}

static void vg_fill_set(vgFill *fill, int mode, int type, unsigned c0, unsigned c1, float e0, float e1, float r0, float r1, vgMatrix *m)
{
	vgMatrix minv, mclip;
	int spaa, alpha;
	spaa = (int)(vg.state.spaa * 255);
	spaa = spaa < 0 ? 0 : spaa > 255 ? 255 : spaa;
	alpha = (int)(vg.state.alpha * 255);
	alpha = alpha < 0 ? 0 : alpha > 255 ? 255 : alpha;
	mclip = vg.state.clip;
	vg_matrix_inverse(minv.v, m->v);
	fill->mode = mode;
	fill->type = type;
	fill->spaa = spaa;
	fill->color0 = VG_ALPHA(c0, alpha);
	fill->color1 = VG_ALPHA(c1, alpha);
	fill->clip[0] = *((unsigned*)&mclip.xx);
	fill->clip[1] = *((unsigned*)&mclip.xy);
	fill->clip[2] = *((unsigned*)&mclip.xt);
	fill->clip[3] = *((unsigned*)&mclip.yx);
	fill->clip[4] = *((unsigned*)&mclip.yy);
	fill->clip[5] = *((unsigned*)&mclip.yt);
	fill->matrix[0] = *((unsigned*)&minv.xx);
	fill->matrix[1] = *((unsigned*)&minv.xy);
	fill->matrix[2] = *((unsigned*)&minv.xt);
	fill->matrix[3] = *((unsigned*)&minv.yx);
	fill->matrix[4] = *((unsigned*)&minv.yy);
	fill->matrix[5] = *((unsigned*)&minv.yt);
	fill->extent[0] = *((unsigned*)&e0);
	fill->extent[1] = *((unsigned*)&e1);
	fill->radius[0] = *((unsigned*)&r0);
	fill->radius[1] = *((unsigned*)&r1);
}

static void vg_push_fill(vgFill *fill, int ntiles, int nedges, unsigned** pdata, unsigned** pedges)
{
	int ifill, isize;
	unsigned *data;

	int size = sizeof(vgFill);

	ifill = sizeof(vgFill) / 4;
	isize = ifill + nedges * sizeof(vgEdge) / 4;

	assert(ifill * 4 == sizeof(vgFill));
	assert(ntiles <= VG_MAX_TILES);
	assert(isize  <= VG_MAX_DATA);

	if (vg_tile_count + ntiles > VG_MAX_TILES ||
		vg_data_count + isize  > VG_MAX_DATA)
		vg_flush();

	data = &vg_data_buffer[vg_data_count];
	*(vgFill*)data = *fill;
	*pdata = data;
	*pedges = data + ifill;
	vg_data_count += ifill;
}

static void vg_push_tile(int x, int y, int sign, void *data, void *edges, int count)
{
	vgTile *tile;

	assert(vg_tile_count + 1 <= VG_MAX_TILES);

	tile = &vg_tile_buffer[vg_tile_count++];
	tile->sign  = sign;
	tile->count = count;
	tile->coord = (x | (y << 16));
	tile->data  = (float)((unsigned*)data  - vg_data_buffer);
	tile->edges = (float)((unsigned*)edges - vg_data_buffer);

	vg_data_count += count * sizeof(vgEdge) / 4;
}

static void vg_push_bounds(float x, float y)
{
	int ix, iy; vgRect bb;
	ix = (int)(x / VG_TILE_DIMS);
	iy = (int)(y / VG_TILE_DIMS);
	bb = vg_grid_bounds;
	vg_grid_bounds.minx = bb.minx < ix ? bb.minx : ix;
	vg_grid_bounds.miny = bb.miny < iy ? bb.miny : iy;
	vg_grid_bounds.maxx = bb.maxx > ix ? bb.maxx : ix;
	vg_grid_bounds.maxy = bb.maxy > iy ? bb.maxy : iy;
}

static void vg_push_edge(int ix, int iy, int ax, int ay, int bx, int by)
{
	int index, previd, edgeid;
	vgEdge edge;

	if (vg_edge_count >= VG_MAX_EDGES  ||
		(ax == bx && ay == by)         ||
		ix < 0 || ix >= vg_grid_sizex  ||
		iy < 0 || iy >= vg_grid_sizey)
		return;

	vg.stats.edges++;

	index  = ix + iy * vg_grid_sizex;
	previd = vg_tile_edge[index];
	edgeid = vg_edge_count;

	if (vg_fill_winding > 0) {
		edge.x0 = ax - (ix << VG_TILE_LOG2) + VG_EDGE_BORDER;
		edge.y0 = ay - (iy << VG_TILE_LOG2) + VG_EDGE_BORDER;
		edge.x1 = bx - (ix << VG_TILE_LOG2) + VG_EDGE_BORDER;
		edge.y1 = by - (iy << VG_TILE_LOG2) + VG_EDGE_BORDER;
	} else {								
		edge.x0 = bx - (ix << VG_TILE_LOG2) + VG_EDGE_BORDER;
		edge.y0 = by - (iy << VG_TILE_LOG2) + VG_EDGE_BORDER;
		edge.x1 = ax - (ix << VG_TILE_LOG2) + VG_EDGE_BORDER;
		edge.y1 = ay - (iy << VG_TILE_LOG2) + VG_EDGE_BORDER;
	}

	vg_edge_buffer[edgeid] = edge;
	vg_edge_links[edgeid] = previd;
	vg_tile_edge[index] = edgeid;

	vg_edge_count++;
}

static void vg_push_sign(int ix, int iy, int sign)
{
	if (iy >= vg_grid_sizey || iy < 0 ||
		ix >= vg_grid_sizex) 
		return;
	
	if (ix < 0) 
		ix = 0;

	vg_tile_sign[ix + iy * vg_grid_sizex] -= sign * vg_fill_winding;
}

static void vg_push_sign_span(int iy0, int iy1)
{
	int dy, sv, sw;
	char *sp, *se;

	iy0 = iy0 < 0 ? 0 : iy0 >= vg_grid_sizey ? vg_grid_sizey - 1 : iy0;
	iy1 = iy1 < 0 ? 0 : iy1 >= vg_grid_sizey ? vg_grid_sizey - 1 : iy1;

	dy = iy1 - iy0;
	sw = vg_grid_sizex;

	if (dy > 0) {
		sp = &vg_tile_sign[iy0 * sw];
		se = sp + dy * sw;
		sv = -vg_fill_winding;
	} else
	if (dy < 0) {
		sp = &vg_tile_sign[iy1 * sw];
		se = sp - dy * sw;
		sv = +vg_fill_winding;
	} else {
		return;
	}

	while (sp != se) {
		*sp += sv;
		sp += sw;
	}
}

static int vg_fill_closed()
{
	return
		vg_fill_point.x == vg_fill_start.x &&
		vg_fill_point.y == vg_fill_start.y;
}

static void vg_fill_close()
{
	static void vg_fill_lineto(float x, float y);
	if (!vg_fill_reset && !vg_fill_closed())
		vg_fill_lineto(vg_fill_start.x - VG_TILE_DIMS, vg_fill_start.y);
	vg_fill_reset = 1;
}

static void vg_fill_moveto_base(float x, float y)
{
	vg_fill_reset = 0;
	vg_fill_start.x = x;
	vg_fill_start.y = y;
	vg_fill_point.x = x;
	vg_fill_point.y = y;
	vg_push_bounds(x, y);
}

static void vg_fill_moveto(float x, float y)
{
	vg_fill_moveto_base(x + VG_TILE_DIMS, y);
}

static void vg_fill_lineto_base(float x, float y)
{
	int dx, dy, lx, ly, tx, ty;
	int tx0, ty0, tx1, ty1;
	int ix0, iy0, ix1, iy1;
	int x0, y0, x1, y1;
	int sx, sy, fx, fy;
	int ex, ey, er;
	int nx, ny, ni;

	if (vg_fill_reset) {
		vg_fill_moveto_base(x, y);
		return;
	}

	// TODO: clip line?

	x0 = (int)(vg_fill_point.x * VG_PIXEL_SIZE);
	y0 = (int)(vg_fill_point.y * VG_PIXEL_SIZE);
	x1 = (int)(x * VG_PIXEL_SIZE);
	y1 = (int)(y * VG_PIXEL_SIZE);

	if (x0 == x1 && y0 == y1)
		return;

	ix0 = x0 >> VG_TILE_LOG2;
	iy0 = y0 >> VG_TILE_LOG2;
	ix1 = x1 >> VG_TILE_LOG2;
	iy1 = y1 >> VG_TILE_LOG2;

	if ((iy0 < 0 && iy1 < 0) ||
		(ix0 > vg_grid_sizex && ix1 > vg_grid_sizex) ||
		(iy0 > vg_grid_sizey && iy1 > vg_grid_sizey)) {
		goto pass;
	}

	if (x0 < 0 && x1 < 0) {
		vg_push_sign_span(iy0, iy1);
		goto pass;
	}

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);

	if (dx >= (64 << VG_TILE_LOG2) ||
		dy >= (64 << VG_TILE_LOG2)) {
		vg_fill_lineto_base(
			(vg_fill_point.x + x) * 0.5f, 
			(vg_fill_point.y + y) * 0.5f);
		vg_fill_lineto_base(x, y);
		return;
	}

	nx = abs(ix1 - ix0);
	ny = abs(iy1 - iy0);
	ni = nx + ny;

	sx = x1 >= x0 ? 1 : -1;
	sy = y1 >= y0 ? 1 : -1;
	lx = dy > 0 ? (dx << VG_EDGE_LOG2 << VG_TILE_LOG2) / dy * sx : 0;
	ly = dx > 0 ? (dy << VG_EDGE_LOG2 << VG_TILE_LOG2) / dx * sy : 0;
	fx = ((sx > 0 ? VG_TILE_MASK - x0 : x0) & VG_TILE_MASK);
	fy = ((sy > 0 ? VG_TILE_MASK - y0 : y0) & VG_TILE_MASK);
	tx = (lx * (fy << (VG_EDGE_LOG2 - VG_TILE_LOG2))) >> VG_EDGE_LOG2;
	ty = (ly * (fx << (VG_EDGE_LOG2 - VG_TILE_LOG2))) >> VG_EDGE_LOG2;

	tx0 = tx1 = x0;
	ty0 = ty1 = y0;
	ix1 = ix0;
	iy1 = iy0;

	ex = -(dy << VG_TILE_LOG2);
	ey =  (dx << VG_TILE_LOG2);
	er =  (dx * (fy + 1)) - (dy * (fx + 1));

	// TODO: preallocate edges? (ni + nx * 2)

	while (ni-- >= 0) {
		tx0 = tx1;
		ty0 = ty1;
		ix0 = ix1;
		iy0 = iy1;

		if (ni == -1) {
			tx1  = x1;
			ty1  = y1;
		} else
		if (er > 0) {
			tx1 = ((ix0 + (sx > 0)) << VG_TILE_LOG2);
			ty1 = y0 + (ty >> VG_EDGE_LOG2);

			er  += ex;
			ty  += ly;
            ix1 += sx;

			if (sx > 0) {
				vg_push_edge(ix1, iy1, tx1 - 32, (iy1 << VG_TILE_LOG2), tx1 - 32, ty1);
			} else {
				vg_push_edge(ix0, iy0, tx1 - 32, ty1, tx1 - 32, (iy0 << VG_TILE_LOG2));
			}
        } else {
			tx1 = x0 + (tx >> VG_EDGE_LOG2);
			ty1 = ((iy0 + (sy > 0)) << VG_TILE_LOG2);

			er  += ey;
			tx  += lx;
            iy1 += sy;

			if (sy > 0) {
				vg_push_sign(ix0, iy0, +1);
			} else {
				vg_push_sign(ix1, iy1, -1);
			}
		}

		vg_push_edge(ix0, iy0, tx0, ty0, tx1, ty1);
	}

pass:
	vg_fill_point.x = x;
	vg_fill_point.y = y;
	vg_push_bounds(x, y);
}

static void vg_fill_lineto(float x, float y)
{
	vg_fill_lineto_base(x + VG_TILE_DIMS, y);
}

static void vg_fill_draw(vgFill *fill)
{
	vgRect rect; vgEdge edge;
	unsigned *data, *edges, *edgep;
	int index, sign, link, x, y;
	int sizex, sizey, count;

	rect = vg_grid_bounds;
	if (rect.minx > rect.maxx)
		return;

	rect.minx -= 1;
	rect.maxx += 1;
	rect.maxy += 1;
	rect = vg_rect_clamp(rect, (vgRect) { 0, 0, vg_grid_sizex - 1, vg_grid_sizey - 1 });

	sizex = rect.maxx - rect.minx - 1;
	sizey = rect.maxy - rect.miny;

	if (sizex <= 0 || sizey <= 0)
		return;

	vg_push_fill(fill, sizex * sizey, vg_edge_count - 1, &data, &edges);

	for (y = 0; y < sizey; y++) {
		sign = 0;
		index = rect.minx + (rect.miny + y) * vg_grid_sizex;
		for (x = 0; x <= sizex; x++, index++) {
			if (x > 0) {
				count = 0;
				edgep = edges;
				link = vg_tile_edge[index];
				while (link) {
					edge = vg_edge_buffer[link];
					link = vg_edge_links[link];
					*(edges++) = edge.packed;
					count++;
				}
				if (sign != 0 || count > 0) {
					vg_push_tile(
						rect.minx + x - 1,
						rect.miny + y, 
						sign, data, edgep, count);
				}
			}
			sign += vg_tile_sign[index];
			vg_tile_sign[index] = 0;
			vg_tile_edge[index] = 0;
		}
	}
}

static void vg_fill_base(vgFill *fill)
{
	vgPoint point;
	vgPath path;
	int index;

	vg_fill_begin();

	for (index = 0; index < vg_path_count;) {
		path = vg_path_buffer[index++];
		point = vg_path_buffer[index++].point;
		vg_fill_winding = path.winding ? 1 : -1;
		vg_fill_moveto(point.x, point.y);
		while (index < path.end) {
			point = vg_path_buffer[index++].point;
			vg_fill_lineto(point.x, point.y);
		}
	}

	vg_fill_close();
	vg_fill_draw(fill);
}

void vg_fill(unsigned color)
{
	vgFill fill;
	vg_fill_set(&fill, vg.state.mode, VG_FILL_FLAT, color, color, 0, 0, 0, 0, &vg.state.matrix);
	vg_fill_base(&fill);
}

void vg_fillr(unsigned c0, unsigned c1, float x, float y, float r0, float r1)
{
	vgMatrix matrix;
	vgFill fill; 
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x, y);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_RAD, c0, c1, 0, 0, r0, r1, &matrix);
	vg_fill_base(&fill);
}

void vg_fillrh(float x, float y, float r0, float r1, float sat, float val)
{
	vgFill fill;
	vgMatrix matrix;
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x, y);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_RAD_HUE, 0xFFFFFFFF, 0xFFFFFFFF, sat, val, r0, r1, &matrix);
	vg_fill_base(&fill);
}

void vg_fillrs(float x, float y, float r0, float r1, float hue)
{
	vgFill fill;
	vgMatrix matrix;
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x, y);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_RAD_SAT, 0xFFFFFFFF, 0xFFFFFFFF, hue, 0, r0, r1, &matrix);
	vg_fill_base(&fill);
}

void vg_fillb(unsigned c0, unsigned c1, float x, float y, float w, float h, float r0, float r1)
{
	vgFill fill;
	vgMatrix matrix;
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x + w / 2, y + h / 2);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_BOX, c0, c1, w / 2, h / 2, r0, r1, &matrix);
	vg_fill_base(&fill);
}

void vg_fillg(unsigned c0, unsigned c1, float x0, float y0, float x1, float y1)
{
	vgFill fill;
	vgMatrix matrix;
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x0, y0);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_LIN, c0, c1, x1 - x0, y1 - y0, 0, 0, &matrix);
	vg_fill_base(&fill);
}

void vg_fillbh(float x, float y, float w, float h, float sat, float val)
{
	vgFill fill;
	vgMatrix matrix;
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x, y);
	vg_matrix_scale(matrix.v, w, h);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_BOX_HUE, 0xFFFFFFFF, 0xFFFFFFFF, sat, val, 0, 0, &matrix);
	vg_fill_base(&fill);
}

void vg_fillbs(float x, float y, float w, float h, float hue)
{
	vgFill fill;
	vgMatrix matrix;
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x, y);
	vg_matrix_scale(matrix.v, w, h);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_BOX_SAT, 0xFFFFFFFF, 0xFFFFFFFF, hue, 0, 0, 0, &matrix);
	vg_fill_base(&fill);
}

void vg_fillgr(unsigned c0, unsigned c1, float x, float y, float w, float h, float r)
{
	vgFill fill;
	vgMatrix matrix;
	matrix = vg.state.matrix;
	vg_matrix_translate(matrix.v, x, y);
	vg_fill_set(&fill, vg.state.mode, VG_FILL_GRID, c0, c1, w, h, r, 0, &matrix);
	vg_fill_base(&fill);
}

/*//////////////////////////
// STROKE
//////////////////////////*/

vgPoint vg_stroke_norm[VG_MAX_PATH];

void vg_stroke(unsigned color, float width)
{
	vgPoint p0, p1, n0, n1;
	vgMatrix mt, mi;
	vgPath path;
	vgFill fill;
	float l, r;
	int i, j;

	vg_fill_begin();

	r = width / 2.0f;
	mt = vg.state.matrix;
	vg_matrix_inverse(mi.v, mt.v);

	for (i = 0; i < vg_path_count;) {
		path = vg_path_buffer[i++];
		p0 = vg_path_buffer[i].point;
		for (j = i + 1; j < path.end; j++) {
			p1 = vg_path_buffer[j].point;
			n0.x = p1.y - p0.y;
			n0.y = p0.x - p1.x;
			n1.x = n0.x * mi.xx + n0.y * mi.xy;
			n1.y = n0.x * mi.yx + n0.y * mi.yy;
			vg_point_norm(&n1, &l);
			n0.x = (n1.x * mt.xx + n1.y * mt.xy) * r;
			n0.y = (n1.x * mt.yx + n1.y * mt.yy) * r;
			vg_stroke_norm[j - 1] = n0;
			p0 = p1;
		}
		i = path.end;
	}

	for (i = 0; i < vg_path_count;) {
		vg_path_reset = 1;
		path = vg_path_buffer[i++];
		p0 = vg_path_buffer[i].point;
		n0 = vg_stroke_norm[i];
		vg_fill_winding = path.winding ? 1 : -1;
		for (j = i + 1; j < path.end; j++) {
			p1 = vg_path_buffer[j].point;
			n1 = vg_stroke_norm[j];
			vg_fill_lineto(p0.x + n0.x, p0.y + n0.y);
			vg_fill_lineto(p1.x + n0.x, p1.y + n0.y);
			p0 = p1;
			n0 = n1;
		}
		if (path.closed) vg_fill_close();
		for (j = path.closed ? path.end - 2 : path.end - 1; j >= i; j--) {
			p1 = vg_path_buffer[j].point;
			n1 = vg_stroke_norm[j];
			vg_fill_lineto(p0.x - n1.x, p0.y - n1.y);
			vg_fill_lineto(p1.x - n1.x, p1.y - n1.y);
			p0 = p1;
		}
		vg_fill_close();
		i = path.end;
	}

	vg_fill_set(&fill, VG_NONZERO, VG_FILL_FLAT, color, color, 0, 0, 0, 0, &mt);
	vg_fill_draw(&fill);
}

/*//////////////////////////
// DRIVER
//////////////////////////*/

#ifndef VGL_INIT
#define VGL_INIT()
#endif

#ifndef VGL_LOG
#define VGL_LOG(msg)
#endif

#define VGL_SHADER_(...) #__VA_ARGS__
#define VGL_SHADER(...)  VGL_SHADER_(__VA_ARGS__)

/*//////////////////////////
// DRIVER: OPENGL
//////////////////////////*/

#if VGL_DRIVER == VGL_OPENGL

#ifndef VGL_TRACE
#define VGL_TRACE()
#endif

#define VGL_VERSION "#version 330\n"
#undef min
#undef max

const GLchar* vgl_shader_lib = 
VGL_VERSION 
VGL_SHADER(
	precision highp float;
	precision highp int;

	uniform usampler2D udata;
	uniform ivec2 uscreensize;
	uniform ivec2 udatasize;

	int du8(const uint v) {
		return int(v);
	}

	int du16(const uvec2 v) {
		return int(v.r + (v.g << 8));
	}

	int du24(const uvec3 v) {
		return int(v.r + (v.g << 8) + (v.b << 16));
	}

	uint du32(const uvec4 v) {
		return v.r + (v.g << 8) + (v.b << 16) + (v.a << 24);
	}

	int di8(const uint v) {
		int r = int(v); return r > 127 ? r - 256 : r;
	}

	int di16(const uvec2 v) {
		int r = int(du16(v)); return r > 32767 ? r - 65536 : r;
	}

	int di24(const uvec3 v) {
		int r = int(du24(v)); return r > 8388607 ? r - 16777216 : r;
	}

	int di32(const uvec4 v) {
		return int(du32(v));
	}

	float df8(const uint v) {
		return float(v) / 255.0;
	}

	float df32(const uvec4 v) {
		return uintBitsToFloat(v.r + (v.g << 8) + (v.b << 16) + (v.a << 24));
	}

	vec4 dv4(const uvec4 v) {
		return vec4(v) / 255.0;
	}

	uvec4 get_value(const int index) {
		return texelFetch(udata, ivec2(index % udatasize.x, index / udatasize.x), 0);
	}

	vec3 hsv2rgb(vec3 c) {
		vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
		vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
		return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
	}

	vec3 rgb2hsv(vec3 c) {
		vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
		vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
		vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
		float d = q.x - min(q.w, q.y);
		float e = 1.0e-10;
		return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
	}
);

const GLchar* vgl_shader_vs =
VGL_SHADER(
	in vec4  iargs;
	in float idata;
	in float iedges;
	in vec4  icoord;

	flat out int    vmode;
	flat out int    vfill;
	flat out float  vspaa;
	flat out int    vsign;
	flat out int    vcount;
	flat out int    vindex;
	flat out ivec2  vcoord;
	flat out vec4   vcolor0;
	flat out vec4   vcolor1;
	flat out vec2   vextent;
	flat out vec2   vradius;
	flat out vec2   vscale;

	out vec2 vpixel;
	out vec2 vscreen;
	out vec2 vclip;
	out vec2 vgrad;

	const vec2 QUAD[6] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
	};

	void main() {
		int data; uvec4 args;
		data = int(idata);
		args = get_value(data);

		vmode   = di8(args.r);
		vfill   = di8(args.g);
		vspaa   = df8(args.b);
		vcolor0 = dv4(get_value(data + 1));
		vcolor1 = dv4(get_value(data + 2));
		vsign   = di16(uvec2(iargs.rg*255));
		vcount  = du16(uvec2(iargs.ba*255));
		vindex  = int(iedges);
		vcoord  = ivec2(du16(uvec2(icoord.rg*255)), du16(uvec2(icoord.ba*255)));
		vpixel  = QUAD[gl_VertexID] * VG_TILE_DIMS;
		vscreen = vec2(vcoord * VG_TILE_DIMS + vpixel);

		mat2x3 mclip;
		mclip[0].x = df32(get_value(data + 3));
		mclip[0].y = df32(get_value(data + 4));
		mclip[0].z = df32(get_value(data + 5));
		mclip[1].x = df32(get_value(data + 6));
		mclip[1].y = df32(get_value(data + 7));
		mclip[1].z = df32(get_value(data + 8));
		vclip = (vec3(vscreen, 1.0) * mclip).xy;

		if (vfill != VG_FILL_FLAT) {
			mat2x3 mgrad;
			mgrad[0].x = df32(get_value(data + 9));
			mgrad[0].y = df32(get_value(data + 10));
			mgrad[0].z = df32(get_value(data + 11));
			mgrad[1].x = df32(get_value(data + 12));
			mgrad[1].y = df32(get_value(data + 13));
			mgrad[1].z = df32(get_value(data + 14));
			vgrad = (vec3(vscreen, 1.0) * mgrad).xy;
			vscale = abs(mgrad[0].xy) + abs(mgrad[1].xy);
			vextent.x = df32(get_value(data + 15));
			vextent.y = df32(get_value(data + 16));
			vradius.x = df32(get_value(data + 17));
			vradius.y = df32(get_value(data + 18));
		} else {
			vgrad = vec2(0.0);
			vscale = vec2(1.0);
		}

		gl_Position = vec4((vscreen / uscreensize * 2.0 - 1.0) * vec2(1.0, -1.0), 0.0, 1.0);
	}
);

const GLchar* vgl_shader_fs =
VGL_SHADER(
	flat in int    vmode;
	flat in int    vfill;
	flat in float  vspaa;
	flat in int    vsign;
	flat in int    vcount;
	flat in int    vindex;
	flat in ivec2  vcoord;
	flat in vec4   vcolor0;
	flat in vec4   vcolor1;
	flat in vec2   vextent;
	flat in vec2   vradius;
	flat in vec2   vscale;

	in vec2 vpixel;
	in vec2 vscreen;
	in vec2 vclip;
	in vec2 vgrad;

	vec2 pixel;

	layout(location = 0, index = 0) out vec4 fcolor;
	layout(location = 0, index = 1) out vec4 fmask;

	float eval_area(vec2 a, vec2 b, in vec2 l, in vec2 window) {
		float ta, tb, ty, th;
		float area = 0.0;

		/* right */
		if (sign(a.x - window.y) != sign(b.x - window.y)) {
			if (a.x < b.x) {
				b.y = b.y - (b.x - window.y) * l.y;
				b.x = window.y;
			} else {
				a.y = a.y - (a.x - window.y) * l.y;
				a.x = window.y;
			}
		} else if (a.x > window.y) {
			return 0.0;
		}

		/* left intersection */
		if (sign(a.x - window.x) != sign(b.x - window.x)) {
			// split edge into a rectangle and a trapezoid
			// append rectangle area here and update
			// coordinates to form the remaining trapezoid
			if (a.x < b.x) {
				ty = a.y - (a.x - window.x) * l.y;
				th = ty - a.y;
				a.y = ty;
				a.x = window.x;
			} else {
				ty = b.y - (b.x - window.x) * l.y;
				th = b.y - ty;
				b.y = ty;
				b.x = window.x;
			}
			/* signed area of rectangle (unit x) */
			area -= th;
		}

		/* signed area of trapezoid */
		th = clamp(b.y - a.y, -1.0, 1.0);
		ta = clamp(window.y - a.x, 0.0, (window.y - window.x)) / (window.y - window.x);
		tb = clamp(window.y - b.x, 0.0, (window.y - window.x)) / (window.y - window.x);
		area -= (ta + tb) * 0.5 * th;

		return area;
	}

	vec3 eval_cover() {
		vec2 wr, wg, wb;
		vec2 a, b, d, l;
		int idx, end;
		vec4 edge;
		vec3 area;

		idx =  vindex;
		end  = vindex + vcount;
		area = vec3(vsign);

		if (vspaa > 0.0) {
			wr = vec2(      0.0, 1.0 / 3.0);
			wg = vec2(1.0 / 3.0, 2.0 / 3.0);
			wb = vec2(2.0 / 3.0,       1.0);
		}

		while (idx < end) {
			edge  = dv4(get_value(idx++));
			edge *= float(VG_EDGE_MASK);
			edge -= float(VG_EDGE_BORDER);
			edge /= float(VG_PIXEL_SIZE);
			edge -= pixel.xyxy;

			a = edge.xy;
			b = edge.zw;
			d = b - a;
			l = vec2(d.x / d.y, d.y / d.x);

			/* top  */
			if (sign(a.y) != sign(b.y)) {
				if (d.y > 0) {
					a.x = a.x - a.y * l.x;
					a.y = 0.0f;
				} else {
					b.x = b.x - b.y * l.x;
					b.y = 0.0f;
				}
			} else if (a.y < 0) {
				continue;
			}

			/* bottom  */
			if (sign(a.y - 1) != sign(b.y - 1)) {
				if (d.y > 0) {
					b.x = b.x - (b.y - 1) * l.x;
					b.y = 1.0f;
				} else {
					a.x = a.x - (a.y - 1) * l.x;
					a.y = 1.0f;
				}
			} else if (a.y > 1) {
				continue;
			}

			if (vspaa > 0.0) {
				area.r += eval_area(a, b, l, wr);
				area.g += eval_area(a, b, l, wg);
				area.b += eval_area(a, b, l, wb);
			} else {
				area += eval_area(a, b, l, vec2(0.0, 1.0));
			}
		}

		if (vspaa > 0.0 && vspaa < 1.0) {
			area = mix(vec3(dot(area, vec3(1.0 / 3.0))), area, vspaa);
		}

		return area;
	}

	vec3 eval_alpha() {
		vec3 c, a;
		c = eval_cover();
		switch (vmode) {
		case VG_NEGATIVE:
			a = clamp(-c, 0.0, 1.0);
			break;
		case VG_POSITIVE:
			a = clamp(c, 0.0, 1.0);
			break;
		case VG_NONZERO:
			a = abs(clamp(c, -1.0, 1.0));
			break;
		case VG_EVENODD:
			a = abs(mod(c + 1.0, 2.0) - 1.0);
			break;
		case VG_INTERSECTION:
			a = clamp(abs(c) - 1.0, 0.0, 1.0);
			break;
		default:
			a = clamp(c, 0.0, 1.0);
			break;
		}
		return a;
	}

	float eval_dither(float seed) {
		vec3 p = fract(vec3(vscreen.xyx) * vec3(443.8975, 397.2973, 491.1871));
		p += dot(p, p.yzx + 19.19 + seed);
		return (fract((p.x + p.y) * p.z) - 0.5) * (1.0 / 128.0);
	}

	vec4 eval_color() {
		float d, a, r, w, b; vec2 v;
		switch (vfill) {
		case VG_FILL_LIN:
			d = sqrt(dot(vgrad, vextent));
			a = clamp(d / length(vextent), 0.0, 1.0);
			return mix(vcolor0, vcolor1, a);
		case VG_FILL_RAD:
			d = length(vgrad) - vradius.x;
			a = clamp(d / (vradius.y - vradius.x), 0.0, 1.0);
			return mix(vcolor0, vcolor1, a);
		case VG_FILL_RAD_HUE:
			d = length(vgrad) - vradius.x;
			a = clamp(d / (vradius.y - vradius.x), 0.0, 1.0);
			v = normalize(vgrad);
			r = acos(v.x) * sign(v.y) / VG_PI2 + 0.5;
			return vec4(hsv2rgb(vec3(r, vextent.x * a, vextent.y * (1.0 - a) + a)), 1.0) * vcolor0;
		case VG_FILL_RAD_SAT:
			d = length(vgrad) - vradius.x;
			a = clamp(d / (vradius.y - vradius.x), 0.0, 1.0);
			r = length(vgrad / (vradius.y - vradius.x) / 2.0 + 0.5);
			return vec4(hsv2rgb(vec3(vextent.x, r, a)), 1.0) * vcolor0;
		case VG_FILL_BOX:
			r = abs(vradius.y - vradius.x);
			v = abs(vgrad) - (vextent - r);
			d = length(max(v, 0.0)) + min(max(v.x, v.y), 0.0) - vradius.x - r;
			a = clamp(d / (vradius.y - vradius.x), 0.0, 1.0);
			return mix(vcolor0, vcolor1, a);
		case VG_FILL_BOX_HUE:
			v = clamp(vgrad, 0.0, 1.0);
			return vec4(hsv2rgb(vec3(v.x, vextent.x, vextent.y)), 1.0) * vcolor0;
		case VG_FILL_BOX_SAT:
			v = clamp(vgrad, 0.0, 1.0);
			return vec4(hsv2rgb(vec3(vextent.x, v.x, v.y)), 1.0) * vcolor0;
		case VG_FILL_GRID:
			v = abs(fract(vgrad / vextent) - 0.5) - (0.5 - vradius.x / vextent);
			w = dot(vscale / vextent, vec2(0.5));
			d = max(v.x, v.y);
			a = smoothstep(w, -w, d);
			return mix(vcolor0, vcolor1, a);
		default:
			a = 0.0;
			return vcolor0;
		}
	}

	float eval_clip() {
		vec2  r = abs(vclip - 0.5) - vec2(0.5);
		float d = length(max(r, 0.0)) + min(max(r.x, r.y), 0.0);
		float w = fwidth(d);
		return smoothstep(w, -w, d);
	}

	void main() {
		vec4 color, alpha;
		pixel  = floor(vpixel);
		color  = eval_color();
		alpha  = vec4(eval_alpha(), 1.0) * color.a * eval_clip();
		fcolor = color * alpha;
		fmask  = alpha;
	}
);

GLuint vgl_shader;
GLuint vgl_shader_uscreensize;
GLuint vgl_shader_udatasize;
GLuint vgl_shader_iargs;
GLuint vgl_shader_idata;
GLuint vgl_shader_iedges;
GLuint vgl_shader_icoord;

GLuint vgl_buffer_vao;
GLuint vgl_buffer_data;
GLuint vgl_buffer_draw;
GLuint vgl_buffer_size;

void vg_driver_init()
{
	static char log[1024];
	const GLchar *source[2];
	GLuint shader;
	GLint result;

	VGL_INIT();

	glGenTextures(1, &vgl_buffer_data);
	glBindTexture(GL_TEXTURE_2D, vgl_buffer_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, vgl_buffer_size, vgl_buffer_size, 0, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE, vg_data_buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	VGL_TRACE();

	vgl_shader = glCreateProgram();

	shader = glCreateShader(GL_VERTEX_SHADER);
	source[0] = vgl_shader_lib; 
	source[1] = vgl_shader_vs;
	glShaderSource(shader, 2, source, 0);
	glCompileShader(shader);
	glAttachShader(vgl_shader, shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		glGetShaderInfoLog(shader, sizeof(log), 0, log);
		VGL_LOG(log);
	}

	shader = glCreateShader(GL_FRAGMENT_SHADER);
	source[0] = vgl_shader_lib;
	source[1] = vgl_shader_fs;
	glShaderSource(shader, 2, source, 0);
	glCompileShader(shader);
	glAttachShader(vgl_shader, shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		glGetShaderInfoLog(shader, sizeof(log), 0, log);
		VGL_LOG(log);
	}

	glLinkProgram(vgl_shader);
	glGetProgramiv(vgl_shader, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		glGetProgramInfoLog(vgl_shader, sizeof(log), 0, log);
		VGL_LOG(log);
	}

	vgl_shader_uscreensize = glGetUniformLocation(vgl_shader, "uscreensize");
	vgl_shader_udatasize   = glGetUniformLocation(vgl_shader, "udatasize");	
	vgl_shader_iargs       = glGetAttribLocation(vgl_shader, "iargs");
	vgl_shader_idata       = glGetAttribLocation(vgl_shader, "idata");
	vgl_shader_iedges      = glGetAttribLocation(vgl_shader, "iedges");
	vgl_shader_icoord      = glGetAttribLocation(vgl_shader, "icoord");

	vgl_buffer_size = (int)ceilf(sqrtf(VG_MAX_DATA));

	glGenVertexArrays(1, &vgl_buffer_vao);
	glBindVertexArray(vgl_buffer_vao);
	VGL_TRACE();

	glGenBuffers(1, &vgl_buffer_draw);
	glBindBuffer(GL_ARRAY_BUFFER, vgl_buffer_draw);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vg_tile_buffer), NULL, GL_DYNAMIC_DRAW);
	VGL_TRACE();

	glEnableVertexAttribArray(vgl_shader_iargs);
	glVertexAttribPointer(vgl_shader_iargs, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vgTile), &((vgTile*)0)->args);
	glVertexAttribDivisor(vgl_shader_iargs, 1);
	VGL_TRACE();

	glEnableVertexAttribArray(vgl_shader_idata);
	glVertexAttribPointer(vgl_shader_idata, 1, GL_FLOAT, GL_FALSE, sizeof(vgTile), &((vgTile*)0)->data);
	glVertexAttribDivisor(vgl_shader_idata, 1);
	VGL_TRACE();

	glEnableVertexAttribArray(vgl_shader_iedges);
	glVertexAttribPointer(vgl_shader_iedges, 1, GL_FLOAT, GL_FALSE, sizeof(vgTile), &((vgTile*)0)->edges);
	glVertexAttribDivisor(vgl_shader_iedges, 1);
	VGL_TRACE();

	glEnableVertexAttribArray(vgl_shader_icoord);
	glVertexAttribPointer(vgl_shader_icoord, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vgTile), &((vgTile*)0)->coord);
	glVertexAttribDivisor(vgl_shader_icoord, 1);
	VGL_TRACE();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void vg_driver_prime()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_SCISSOR_TEST);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	VGL_TRACE();

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC1_COLOR);
	VGL_TRACE();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, vgl_buffer_data);
	glBindBuffer(GL_ARRAY_BUFFER, vgl_buffer_draw);
	glBindVertexArray(vgl_buffer_vao);
	VGL_TRACE();

	glUseProgram(vgl_shader);
	glUniform2i(vgl_shader_uscreensize, vg.size.x, vg.size.y);
	glUniform2i(vgl_shader_udatasize, vgl_buffer_size, vgl_buffer_size);
	VGL_TRACE();
}

void vg_driver_flush()
{
	if (vg_tile_count == 0) 
		return;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, vgl_buffer_size, (vg_data_count + vgl_buffer_size - 1) / vgl_buffer_size, 0, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE, vg_data_buffer);
	// TODO: find out what's wrong with this
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vgl_buffer_size, (vg_data_count + vgl_buffer_size - 1) / vgl_buffer_size, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE, vg_data_buffer);
	VGL_TRACE();

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vgTile) * vg_tile_count, vg_tile_buffer);
	VGL_TRACE();

	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, vg_tile_count);
	VGL_TRACE();
}

void vg_driver_clear(unsigned color)
{
	float r, g, b, a;
	r = ((color >> 0)  & 0xFF) / 255.0f;
	g = ((color >> 8)  & 0xFF) / 255.0f;
	b = ((color >> 16) & 0xFF) / 255.0f;
	a = ((color >> 24) & 0xFF) / 255.0f;
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void vg_driver_size(int *w, int *h)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	*w = viewport[2];
	*h = viewport[3];
}

#endif

/*//////////////////////////
// DRIVER: VULKAN
//////////////////////////*/

#if VGL_DRIVER == VGL_VULKAN
// NOT IMPLEMENTED
#endif

/*//////////////////////////
// DRIVER: DIRECTX
//////////////////////////*/

#if VGL_DRIVER == VGL_DIRECTX
// NOT IMPLEMENTED
#endif

/*//////////////////////////
// MATRIX
//////////////////////////*/

void vg_matrix_identity(float *m) 
{
	*(vgMatrix*)m = (vgMatrix) { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
}

void vg_matrix_translate(float *m, float x, float y)
{
	m[2] += x * m[0] + y * m[1];
	m[5] += x * m[3] + y * m[4];
}

void vg_matrix_rotate(float *m, float a)
{
	float cs = cosf(a);
	float sn = sinf(a);
	float xx = m[0];
	float xy = m[1];
	float yx = m[3];
	float yy = m[4];
	m[0] = xx *  cs + xy * sn;
	m[1] = xx * -sn + xy * cs;
	m[3] = yx *  cs + yy * sn;
	m[4] = yx * -sn + yy * cs;
}

void vg_matrix_scale(float *m, float x, float y)
{
	m[0] *= x;
	m[1] *= y;
	m[3] *= x;
	m[4] *= y;
}

void vg_matrix_multiply(float *m, float *a)
{
	float xx = m[0];
	float xy = m[1];
	float xt = m[2];
	float yx = m[3];
	float yy = m[4];
	float yt = m[5];
	
	m[0] = xx * a[0] + xy * a[1];
	m[1] = xx * a[3] + xy * a[4];
	
	m[3] = yx * a[0] + yy * a[1];
	m[4] = yx * a[3] + yy * a[4];	
	
	m[2] = xt + a[2];
	m[5] = yt + a[5];
}

int vg_matrix_inverse(float *m, float *a)
{
	float i, d;
	d = a[0] * a[4] - a[1] * a[3];
	if (d > -1e-6f && d < 1e-6f) {
		vg_matrix_identity(m);
		return 0;
	}
	i = 1.0f / d;
	m[0] =  a[4] * i;
	m[1] = -a[1] * i;
	m[2] = (a[1] * a[5] - a[4] * a[2]) * i;
	m[3] = -a[3] * i;
	m[4] =  a[0] * i;
	m[5] = (a[3] * a[2] - a[0] * a[5]) * i;
	return 1;
}

void vg_matrix_lerp(float *m, float *a, float t)
{
	m[0] = m[0] * (1.0f - t) + a[0] * t;
	m[1] = m[1] * (1.0f - t) + a[1] * t;
	m[2] = m[2] * (1.0f - t) + a[2] * t;
	m[3] = m[3] * (1.0f - t) + a[3] * t;
	m[4] = m[4] * (1.0f - t) + a[4] * t;
	m[5] = m[5] * (1.0f - t) + a[5] * t;
}

void vg_matrix_project(float *m, float *x, float *y)
{
	float sx = *x;
	float sy = *y;
	*x = sx * m[0] + sy * m[1] + m[2];
	*y = sx * m[3] + sy * m[4] + m[5];
}

void vg_matrix_unproject(float *m, float *x, float *y)
{
	vgMatrix inv;
	vg_matrix_inverse(inv.v, m);
	vg_matrix_project(inv.v, x, y);
}

void vg_matrix_projectn(float *m, float *x, float *y)
{
	float sx = *x;
	float sy = *y;
	*x = sx * m[0] + sy * m[1];
	*y = sx * m[3] + sy * m[4];
}

void vg_matrix_unprojectn(float *m, float *x, float *y)
{
	vgMatrix inv;
	vg_matrix_inverse(inv.v, m);
	vg_matrix_projectn(inv.v, x, y);
}

void vg_matrix_pan(float *m, float x, float y, float speed)
{
	x *= speed; y *= speed;
	if (x == 0.0f && y == 0.0f) return;
	vg_matrix_unprojectn(m, &x, &y);
	vg_matrix_translate(m, x, y);
}

void vg_matrix_zoom(float *m, float x, float y, float zoom)
{
	if (zoom == 0.0f) return;
	float factor = powf(1.1f, zoom);
	vg_matrix_unproject(m, &x, &y);
	vg_matrix_translate(m, x, y);
	vg_matrix_scale(m, factor, factor);
	vg_matrix_translate(m, -x, -y);
}

/*//////////////////////////
// TTF FONT
//////////////////////////*/

typedef struct vgttEntry vgttEntry;
typedef struct vgttGlyph vgttGlyph;

struct vgttEntry {
	unsigned tag;
	unsigned checksum;
	unsigned offset;
	unsigned length;
};

struct vgttGlyph {
	int key;
	int index;
	int offset;
	int ncont;
	int xmin;
	int ymin;
	int xmax;
	int ymax;
	float width;
	float lsb;
	vgttGlyph *next;
};

struct vgFont {
	void *data;
	unsigned size;
	unsigned version;
	unsigned num_tables;
	unsigned search_range;
	unsigned entry_selector;
	unsigned range_shift;
	vgttEntry head;
	vgttEntry maxp;
	vgttEntry loca;
	vgttEntry glyf;
	vgttEntry cmap;
	vgttEntry hhea;
	vgttEntry os_2;
	vgttEntry hmtx;
	vgttEntry gpos;
	vgttEntry kern;
	vgttEntry cff;
	vgttGlyph *glyphs[256];
};

#ifdef VG_BIG_ENDIAN
#define TTF_SWAP_U16(V) (V)
#define TTF_SWAP_U32(V) (V)
#else
#define TTF_SWAP_U16(V) (ttf_font_swap_u16(V))
#define TTF_SWAP_U32(V) (ttf_font_swap_u32(V))
static unsigned short ttf_font_swap_u16(unsigned short v) { return ((v >> 8) & 0xFF) | (((v) & 0xFF) << 8); }
static unsigned int   ttf_font_swap_u32(unsigned int   v) { return (((v) >> 24) & 0xFF) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | (((v) << 24) & 0xFF000000); }
#endif

#define TTF_INDEX(TTF, BASE, OFFSET)       ((char*)(TTF)->data + (BASE) + (OFFSET))
#define TTF_CHECK(TTF, BASE, OFFSET, TYPE) ((BASE)+(OFFSET)+sizeof(TYPE) <= (TTF)->size)

#define TTF_VAL(TTF, BASE, OFFSET, TYPE)   (TTF_CHECK(TTF, BASE, OFFSET, TYPE) ? *(TYPE*)TTF_INDEX(TTF, BASE, OFFSET) : (TYPE)0)
#define TTF_U8(TTF, BASE, OFFSET)          (TTF_VAL(TTF, BASE, OFFSET, unsigned char))
#define TTF_U16(TTF, BASE, OFFSET)         (TTF_SWAP_U16(TTF_VAL(TTF, BASE, OFFSET, unsigned short)))
#define TTF_U32(TTF, BASE, OFFSET)         (TTF_SWAP_U32(TTF_VAL(TTF, BASE, OFFSET, unsigned int)))
#define TTF_I8(TTF, BASE, OFFSET)          ((signed char)TTF_U8(TTF, BASE, OFFSET))
#define TTF_I16(TTF, BASE, OFFSET)         ((signed short)TTF_U16(TTF, BASE, OFFSET))
#define TTF_I32(TTF, BASE, OFFSET)         ((signed int)TTF_U32(TTF, BASE, OFFSET))
#define TTF_F32(TTF, BASE, OFFSET)         ((TTF_U16(TTF, BASE, OFFSET) / 4.0f) + TTF_U16(TTF, BASE, (OFFSET)+2))

#define TTF_TAG(A,B,C,D) (((D)<<0)|((C)<<8)|((B)<<16)|((A)<<24))

void vg_font_init(vgFont *ttf, void *data, int size)
{
	vgttEntry entry;
	unsigned base, i;

	memset(ttf, 0, sizeof(vgFont));
	ttf->data = (char*)data;
	ttf->size = size;

	base = 0;
	ttf->version        = TTF_U32(ttf, base, 0);
	ttf->num_tables     = TTF_U16(ttf, base, 4);
	ttf->search_range   = TTF_U16(ttf, base, 6);
	ttf->entry_selector = TTF_U16(ttf, base, 8);
	ttf->range_shift    = TTF_U16(ttf, base, 10);

	base = 12;
	for (i = 0; i < ttf->num_tables; i++) {
		entry.tag      = TTF_U32(ttf, base, 0);
		entry.checksum = TTF_U32(ttf, base, 4);
		entry.offset   = TTF_U32(ttf, base, 8);
		entry.length   = TTF_U32(ttf, base, 12);

		switch (entry.tag) {
		case TTF_TAG('h','e','a','d'): ttf->head = entry; break;
		case TTF_TAG('m','a','x','p'): ttf->maxp = entry; break;
		case TTF_TAG('l','o','c','a'): ttf->loca = entry; break;
		case TTF_TAG('g','l','y','f'): ttf->glyf = entry; break;
		case TTF_TAG('c','m','a','p'): ttf->cmap = entry; break;
		case TTF_TAG('h','h','e','a'): ttf->hhea = entry; break;
		case TTF_TAG('o','s','/','2'): ttf->os_2 = entry; break;
		case TTF_TAG('h','m','t','x'): ttf->hmtx = entry; break;
		case TTF_TAG('G','P','O','S'): ttf->gpos = entry; break;
		case TTF_TAG('k','e','r','n'): ttf->gpos = entry; break;
		case TTF_TAG('C','F','F',' '): ttf->cff  = entry; break;
		}

		base += 16;
	}
}

vgFont* vg_font_load(const char *filename)
{
	int size; void *data;
	vgFont *font;
	FILE *file; 

	file = fopen(filename, "r");
	if (!file) return 0;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	font = malloc(sizeof(vgFont) + size);
	data = (void*)&font[1];

	fread(data, 1, size, file);
	fclose(file);

	vg_font_init(font, data, size);
	return font;
}

vgFont* vg_font_loadp(void *data, int size)
{
	vgFont *font;
	font = malloc(sizeof(vgFont));
	vg_font_init(font, data, size);
	return font;
}

vgFont* vg_font_default()
{	
	// TODO: embed small default font?
	return 0;
}

static int vg_font_glyph_index(vgFont *ttf, unsigned c)
{
	int version, ntables, platformid, encodingid;
	int oec, osc, odt, oro, ogi, ro, sc, ec, dt;
	int segcount, range, selector, shift;
	int base, format, length, offset;
	int lang, index, i;

	if (c < 0) return 0;

	base = ttf->cmap.offset;
	version = TTF_U16(ttf, base, 0);
	ntables = TTF_U16(ttf, base, 2);

	base += 4;
	platformid = TTF_U16(ttf, base, 0);
	encodingid = TTF_U16(ttf, base, 2);
	offset = TTF_U32(ttf, base, 4);

	base = ttf->cmap.offset + offset;
	format = TTF_U16(ttf, base, 0);
	length = TTF_U16(ttf, base, 2);

	index = 0;

	if (format == 4) {
		lang     = TTF_U16(ttf, base, 4);
 		segcount = TTF_U16(ttf, base, 6) / 2;
		range    = TTF_U16(ttf, base, 8);
		selector = TTF_U16(ttf, base, 10);
		shift    = TTF_U16(ttf, base, 12);

		oec = base + 14;
		osc = oec + segcount * 2 + 2;
		odt = osc + segcount * 2;
		oro = odt + segcount * 2;
		ogi = oro + segcount * 2;

		for (i = 0; i < segcount; i++) {
			sc = TTF_U16(ttf, osc, i * 2);
			ec = TTF_U16(ttf, oec, i * 2);
			dt = TTF_I16(ttf, odt, i * 2);
			if (c <= ec) {
				if (c >= sc) {
					ro = TTF_U16(ttf, oro, i * 2);
					if (ro) {
						index = TTF_U16(ttf, oro, (i + ro / 2 + (c - sc)) * 2);
						if (index) index += dt;
					} else {
						index = (c + dt) % 65536;
					}
				} else {
					return 0;
				}
				break;
			}
		}
	} else 
	if (format == 0) {
		if (c > 255) return 0;
		lang = TTF_U8(ttf, base, 4);
		index = TTF_U8(ttf, base, 6 + c);
	}

	return index;
}

static int vg_font_glyph_offset(vgFont *ttf, unsigned index)
{
	int offset, wide;
	wide = TTF_U16(ttf, ttf->head.offset, 50);
	if (wide)
		 offset = TTF_U32(ttf, ttf->loca.offset, index * 4);
	else offset = TTF_U16(ttf, ttf->loca.offset, index * 2) * 2;
	return ttf->glyf.offset + offset;
}

static vgttGlyph* vg_font_glyph(vgFont *ttf, unsigned c)
{
	vgttGlyph *glyph;
	int hash;

	hash = c & 0xFF;
	glyph = ttf->glyphs[hash];
	while (glyph) {
		if (glyph->key == c)
			return glyph;
		glyph = glyph->next;
	}

	// TODO: batch alloc
	glyph = calloc(1, sizeof(vgttGlyph));
	glyph->key = c;

	glyph->index = vg_font_glyph_index(ttf, c);
	if (glyph->index == 0) goto done;

	glyph->offset = vg_font_glyph_offset(ttf, glyph->index);
	if (glyph->offset == 0) goto done;

	glyph->ncont = TTF_I16(ttf, glyph->offset, 0);
	glyph->xmin  = TTF_I16(ttf, glyph->offset, 2);
	glyph->ymin  = TTF_I16(ttf, glyph->offset, 4);
	glyph->xmax  = TTF_I16(ttf, glyph->offset, 6);
	glyph->ymax  = TTF_I16(ttf, glyph->offset, 8);

	int nmetrics = TTF_U16(ttf, ttf->hhea.offset, 34);
	if (glyph->index < nmetrics) {
		glyph->width = TTF_I16(ttf, ttf->hmtx.offset, 4 * glyph->index) / 2000.0f;
		glyph->lsb   = TTF_I16(ttf, ttf->hmtx.offset, 4 * glyph->index + 2) / 2000.0f;
	} else {
		glyph->width = TTF_I16(ttf, ttf->hmtx.offset, 4 * (nmetrics - 1)) / 2000.0f;
		glyph->lsb   = TTF_I16(ttf, ttf->hmtx.offset, 4 * nmetrics + 2 * (glyph->index - nmetrics)) / 2000.0f;
	}

done:
	glyph->next = ttf->glyphs[hash];
	ttf->glyphs[hash] = glyph;
	return glyph;
}

static int vg_font_glyph_coverage(vgFont *ttf, int ocoverage, unsigned glyph)
{
	int format = TTF_U16(ttf, ocoverage, 0);
	switch (format) {
	case 1: {
		int nglyph = TTF_U16(ttf, ocoverage, 2);
		int l = 0, r = nglyph - 1, m;
		int straw, needle = glyph;
		while (l <= r) {
			m = (l + r) >> 1;
			straw = TTF_U16(ttf, ocoverage, 4 + 2 * m);
			if      (needle < straw) r = m - 1;
			else if (needle > straw) l = m + 1;
			else     return m;
		}
		break; }
	case 2: {
		int nrange = TTF_U16(ttf, ocoverage, 2);
		int orange = ocoverage + 4;
		int l = 0, r = nrange - 1, m;
		int orecord, strawa, strawb, needle = glyph;
		while (l <= r) {
			m = (l + r) >> 1;
			orecord = orange + 6 * m;
			strawa = TTF_U16(ttf, orecord, 0);
			strawb = TTF_U16(ttf, orecord, 2);
			if      (needle < strawa) r = m - 1;
			else if (needle > strawb) l = m + 1;
			else    return TTF_U16(ttf, orecord, 4) + glyph - strawa;
		}
		break; }
	default: 
		return -1;
	}
	return -1;
}

static float vg_font_glyph_kern_gpos(vgFont *ttf, int g1, int g2)
{
	if (!ttf->gpos.tag) return 0;

	int odata = ttf->gpos.offset;
	if (TTF_U16(ttf, odata, 0) != 1) return 0; // major version 1
	if (TTF_U16(ttf, odata, 2) != 0) return 0; // minor version 0

	int olist = TTF_U16(ttf, odata, 8) + odata;
	int nlist = TTF_U16(ttf, olist, 0);

	for (int i = 0; i < nlist; i++) {
		int olookup = TTF_U16(ttf, olist, 2 + 2 * i) + olist;
		int tlookup = TTF_U16(ttf, olookup, 0);
		int nlookup = TTF_U16(ttf, olookup, 4);
		int ooffset = olookup + 6;
		if (tlookup != 2) continue; // pair adjustment positioning subtable

		for (int j = 0; j < nlookup; j++) {
			int otable = TTF_U16(ttf, ooffset, 2 * j) + olookup;
			int format = TTF_U16(ttf, otable, 0);
			int ocoverage = TTF_U16(ttf, otable, 2) + otable;
			int icoverage = vg_font_glyph_coverage(ttf, ocoverage, g1);
			if (icoverage == -1) continue;

			switch (format) {
			case 1: {
				// TODO:
				return 0; }
			case 2: {
				// TODO:
				return 0; }
			default:
				return 0; // unsupported
			}
		}
	}

	return 0;
}

static float vg_font_glyph_kern_info(vgFont *ttf, int g1, int g2)
{
	unsigned needle, straw;
	int l, r, m;

	if (!ttf->kern.tag) return 0;
	if (TTF_U16(ttf, ttf->kern.offset, 2) < 1) return 0;
	if (TTF_U16(ttf, ttf->kern.offset, 8) != 1) return 0;
	
	l = 0;
	r = TTF_U16(ttf, ttf->kern.offset, 10) - 1;
	needle = g1 << 16 | g2;

	while (l <= r) {
		m = (l + r) >> 1;
		straw = TTF_U32(ttf, ttf->kern.offset, 18 + (m * 6));
		if      (needle < straw) r = m - 1;
		else if (needle > straw) l = m + 1;
		else return TTF_I16(ttf, ttf->kern.offset, 22 + (m * 6)) / 2000.0f;
	}

	return 0;
}

static float vg_font_glyph_kern(vgFont *ttf, int g1, int g2)
{
	// TODO: cache?
	if      (ttf->gpos.tag) return vg_font_glyph_kern_gpos(ttf, g1, g2);
	else if (ttf->kern.tag) return vg_font_glyph_kern_info(ttf, g1, g2);
	else                    return 0;
}

static void vg_font_draw_glyph(vgFont *ttf, float x, float y, float size, int oglyph);

static void vg_font_draw_glyph_contour(vgFont *ttf, float x, float y, float size, int oglyph)
{
	int ocont, ncont, npnts, oinst, ninst, oflag, ocoordx, ocoordy, oncurve;
	int flag, ix, iy, iw, nx, ny, dx, dy, i, c, r;
	int c0, c1, move, end;
	vgPoint p0, p1, pc, ps;

	ncont = TTF_I16(ttf, oglyph, 0);
	if (ncont <= 0) return;

	ocont = oglyph + 10;
	npnts = TTF_U16(ttf, ocont, (ncont - 1) * 2) + 1;
	ninst = TTF_U16(ttf, ocont, ncont * 2);
	oinst = ocont + ncont * 2 + 2;
	oflag = oinst + ninst;
	ix = iw = 0;

	// find coord offsets
	for (i = 0; i < npnts; iw++) {
		flag = TTF_U8(ttf, oflag, iw);
			
		if (flag & 0x08 /* REPEAT */) {
			iw++;
			r = TTF_U8(ttf, oflag, iw) + 1;
		} else {
			r = 1;
		}
			
		while (r--) {
			if (flag & 0x02 /* X_SHORT_VECTOR */) {
				ix += 1;
			} else 
			if (!(flag & 0x10 /* X_IS_SAME */)) {
				ix += 2;
			}
			i++;
		}
	}

	ocoordx = oflag + iw;
	ocoordy = ocoordx + ix;

	p0.x = p0.y = ps.x = 0;
	p1.x = p1.y = ps.y = 0;
	ix = iy = iw = 0;
	nx = ny = 0;
	i = 0;

	// emit contours
	for (c = i = 0; c < ncont; c++) {
		c0 = c1 = 0;
		end = TTF_U16(ttf, ocont, c * 2);
		move = 1;

		for (; i <= end; iw++) {
			flag = TTF_U8(ttf, oflag, iw);
			oncurve = (flag & 0x01);

			if (flag & 0x08 /* REPEAT */) {
				iw++;
				r = TTF_U8(ttf, oflag, iw) + 1;
			} else {
				r = 1;
			}

			while (r--) {
				if (flag & 0x02 /* X_SHORT_VECTOR */) {
					dx = TTF_U8(ttf, ocoordx, ix);
					if (!(flag & 0x10 /* X_IS_POSITIVE */))
							dx = -dx;
					ix += 1;
				} else 
				if (flag & 0x10 /* X_IS_SAME */) {
					dx = 0;
				} else {
					dx = TTF_I16(ttf, ocoordx, ix);
					ix += 2;
				}

				if (flag & 0x04 /* Y_SHORT_VECTOR */) {
					dy = TTF_U8(ttf, ocoordy, iy);
					if (!(flag & 0x20 /* Y_IS_POSITIVE */))
						dy = -dy;
					iy += 1;
				} else 
				if (flag & 0x20 /* Y_IS_SAME */) {
					dy = 0;
				} else {
					dy = TTF_I16(ttf, ocoordy, iy);
					iy += 2;
				}

				nx += dx;
				ny += dy;

				c0 = c1;
				p0 = p1;
				p1.x = nx / 2000.0f;
				p1.y = 1.0f - ny / 2000.0f;
				p1.x = p1.x * size + x;
				p1.y = p1.y * size + y;
				c1 = oncurve == 0;

				if (move) {
					move = 0;
					ps = p1;
					vg_moveto(p1.x, p1.y);
				} else {
					if (c1) {
						if (c0) {
							pc.x = (p0.x + p1.x) * 0.5f;
							pc.y = (p0.y + p1.y) * 0.5f;
							vg_curveto(p0.x, p0.y, pc.x, pc.y);
						}
					} else {
						if (c0) {
							vg_curveto(p0.x, p0.y, p1.x, p1.y);
						} else {
							vg_lineto(p1.x, p1.y);
						}
					}
				}
				i++;
			}
		}

		if (c1) {
			vg_curveto(p1.x, p1.y, ps.x, ps.y);
		} else {
			vg_lineto(ps.x, ps.y);
		}
	}
}

static void vg_font_draw_glyph_compound(vgFont *ttf, float x, float y, float size, int oglyph) {
	int ncont, ocomp, more, flags, next;

	ncont = TTF_I16(ttf, oglyph, 0);
	if (ncont >= 0) return;

	ocomp = oglyph + 10;
	flags = TTF_U16(ttf, ocomp, 0);
	next  = TTF_U16(ttf, ocomp, 2);
	more  = 1;

	while (more) {
		// TODO: transform
		vg_font_draw_glyph(ttf, x, y, size, vg_font_glyph_offset(ttf, next));
		// TODO: more
		more = 0;
	}
}

static void vg_font_draw_glyph(vgFont *ttf, float x, float y, float size, int oglyph) {
	// TODO: cache?
	int ncont = TTF_I16(ttf, oglyph, 0);
	if (ncont < 0) vg_font_draw_glyph_compound(ttf, x, y, size, oglyph);
	else           vg_font_draw_glyph_contour(ttf, x, y, size, oglyph);
}

void vg_font_draw_char(vgFont *ttf, float x, float y, float size, int c)
{
	vgttGlyph *glyph;

	glyph = vg_font_glyph(ttf, c);
	if (glyph == 0) return;

	vg_font_draw_glyph(ttf, x, y, size, glyph->offset);
}

float vg_font_measure_text(vgFont *ttf, float size, const char *str)
{
	vgttGlyph *glyph, *prev;
	float x, w; 
	int i;

	x = w = 0;
	prev = 0;
	
	for (i = 0; str[i]; i++) {
		if (w < x) w = x;

		if (str[i] == '\n') {
			x = 0;
			continue;
		}

		glyph = vg_font_glyph(ttf, str[i]);
		if (glyph == 0) {
			prev = 0;
			continue;
		}

		if (str[i] == ' ') {
			x += glyph->width * size;
			prev = glyph;
			continue;
		}

		if (prev) {
			x += vg_font_glyph_kern(ttf, prev->index, glyph->index);
		}

		prev = glyph;
		x += glyph->width * size;
	}

	if (w < x) w = x;
	return w;
}

void vg_font_draw_text(vgFont *ttf, float x, float y, float size, const char *str)
{
	// TODO: vertical alignment / advance
	// TODO: font fallbacks
	// TODO: unicode

	vgttGlyph *glyph, *prev;
	float px, py;
	int i;

	vg_path();

	px = x;
	py = y;
	prev = 0;

	for (i = 0; str[i]; i++) {
		if (str[i] == '\n') {
			px = x;
			py += size * 0.65f;
			prev = 0;
			continue;
		}

		glyph = vg_font_glyph(ttf, str[i]);
		if (glyph == 0) {
			prev = 0;
			continue;
		}

		if (str[i] == ' ') {
			px += glyph->width * size;
			prev = glyph;
			continue;
		}

		if (prev) {
			px += vg_font_glyph_kern(ttf, prev->index, glyph->index);
		}

		vg_font_draw_glyph(ttf, px, py, size, glyph->offset);

		prev = glyph;
		px += glyph->width * size;
	}
}

/*//////////////////////////
// COLOR
//////////////////////////*/

vgColor vg_color_hsv(float h, float s, float v)
{
	float r, g, b, f, p, q, t; int i;
	if (h < 0) h = -h;
	r = 0.0f, g = 0.0f, b = 0.0f;
	i = (int)(h * 6);
	f = h * 6 - i;
	p = v * (1 - s);
	q = v * (1 - f * s);
	t = v * (1 - (1 - f) * s);
	switch (i % 6) {
	case 0: r = v, g = t, b = p; break;
	case 1: r = q, g = v, b = p; break;
	case 2: r = p, g = v, b = t; break;
	case 3: r = p, g = q, b = v; break;
	case 4: r = t, g = p, b = v; break;
	case 5: r = v, g = p, b = q; break;
	}
	return VG_RGBF(r, g, b);
}

vgColor vg_color_blend(vgColor src, vgColor dst)
{
	vgColor a = (src >> 24) + 1;
	vgColor drb = dst & 0xFF00FF;
	vgColor dg = dst & 0xFF00;
	return ((((((src & 0xFF00FF) - drb) * a) >> 8) + drb) & 0xFF00FF) | ((((((src & 0xFF00) - dg) * a) >> 8) + dg) & 0xFF00) | 0xFF000000;
}

vgColor vg_color_lerp(vgColor src, vgColor dst, vgColor a)
{
	return ((((VG_R(src) - VG_R(dst)) * a) >> 8) + VG_R(dst)) << 0  |
	       ((((VG_G(src) - VG_G(dst)) * a) >> 8) + VG_G(dst)) << 8  |
	       ((((VG_B(src) - VG_B(dst)) * a) >> 8) + VG_B(dst)) << 16 |
	       ((((VG_A(src) - VG_A(dst)) * a) >> 8) + VG_A(dst)) << 24;
}

vgColor vg_color_lerpf(vgColor src, vgColor dst, float a)
{
	return vg_color_lerp(src, dst, (vgColor)(a * 255));
}

/*//////////////////////////
// COMMANDS
//////////////////////////*/

void vg_eval(vgCommand *cmd) {
	while (1) {
		switch (cmd->type) {
		case VG_CMD_MOVETO:
			vg_moveto(cmd->moveto.coords[0], cmd->moveto.coords[1]);
			cmd = (vgCommand*)((char*)cmd + sizeof(cmd->moveto));
			break;
		case VG_CMD_LINETO:
			vg_lineto(cmd->lineto.coords[0], cmd->lineto.coords[1]);
			cmd = (vgCommand*)((char*)cmd + sizeof(cmd->lineto));
			break;
		case VG_CMD_CURVETO:
			vg_curveto(cmd->curveto.coords[0], cmd->curveto.coords[1], cmd->curveto.coords[2], cmd->curveto.coords[3]);
			cmd = (vgCommand*)((char*)cmd + sizeof(cmd->curveto));
			break;
		case VG_CMD_CUBICTO:
			vg_cubicto(cmd->cubicto.coords[0], cmd->cubicto.coords[1], cmd->cubicto.coords[2], cmd->cubicto.coords[3], cmd->cubicto.coords[4], cmd->cubicto.coords[5]);
			cmd = (vgCommand*)((char*)cmd + sizeof(cmd->cubicto));
			break;
		case VG_CMD_ALPHA:
			vg_alpha(cmd->alpha.value);
			cmd = (vgCommand*)((char*)cmd + sizeof(cmd->alpha));
			break;
		case VG_CMD_FILL:
			vg_fill(cmd->fill.color); 
			cmd = (vgCommand*)((char*)cmd + sizeof(cmd->fill));
			break;
		case VG_CMD_STROKE: 
			vg_stroke(cmd->stroke.color, cmd->stroke.width);
			cmd = (vgCommand*)((char*)cmd + sizeof(cmd->stroke));
			break;
		default: return;
		}
	}
}

#endif
#endif