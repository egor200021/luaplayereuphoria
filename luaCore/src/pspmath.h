/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2007 Steve Galatis
 * Copyright (c) 2007 Christophe Avoinme
 *
 * General purpose math library using vfpu optimized instructions.
 * Most of the routines here run at least 5 to 20 times faster than the equivalent
 * routines in libm
 *
 */
 
 /*
 * LuaPlayer Euphoria
 * ------------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE for details.
 *
 * Copyright (c) 2005 Frank Buss <fb@frank-buss.de> (aka Shine)
 * Copyright (c) 2009 Danny Glover <danny86@live.ie> (aka Zack) 
 *
 * Official Forum : http://www.retroemu.com/forum/forumdisplay.php?f=148
 * For help using LuaPlayer, code help, tutorials etc please visit the official site : http://www.retroemu.com/forum/forumdisplay.php?f=148
 *
 * Credits:
 * 
 * (from Shine/Zack) 
 *
 *   many thanks to the authors of the PSPSDK from http://forums.ps2dev.org
 *   and to the hints and discussions from #pspdev on freenode.net
 *
 * (from Zack Only)
 *
 * Thanks to Brunni for the Swizzle/UnSwizzle code (taken from oslib). 
 * Thanks to Arshia001 for AALIB. It is the sound engine used in LuaPlayer Euphoria. 
 * Thanks to HardHat for being a supportive friend and advisor.
 * Thanks to Benhur for IntraFont.
 * Thanks to Jono for the moveToVram code.
 * Thanks to Raphael for the Vram manager code.
 * Thanks to Osgeld, Dan369 & Cmbeke for testing LuaPlayer Euphoria for me and coming up with some neat ideas for it.
 * Thanks to the entire LuaPlayer Euphoria userbase, for using it and for supporting it's development. You guys rock!
 *
 *
 */

#ifndef _pspmath_h_
#define _pspmath_h_

#include <psptypes.h>

/** @defgroup VFPUMATH VFPU Math Library
 *
 */

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct quat {
	float x, y, z, w;
} __attribute__((aligned(16))) ScePspQuatMatrix;

/** @addtogroup VFPUMATH */
/*@{*/

/**
  * Print a formatted block of 16 vfpu registers
  *
  * @param blockid - register block id (0 to 7)
  *
**/
void printVFPURegisters(int blockid);

/**
  * Set vfpu random generator seed
  *
  * @param x - seed value
  *
**/
void vfpu_srand(unsigned int x);

/**
  * Return random float value
  *
  * @param min - minimum value to return
  * @param max - maximum value to return
  *
**/
float vfpu_randf(float min, float max);

/**
  * Return random color value in 8888 format
  * This always sets the alpha channel value to 0xFF
  *
  * @param min - minimum value for each color channel (0..255)
  * @param max - maximum value for each color channel (0..255)
  *
**/
unsigned int vfpu_rand_8888(int min, int max);

/**
  * Generate an identity matrix
  *
  * @param m - pointer to matrix to set
  *
**/
void vfpu_identity_matrix(ScePspFMatrix4 *m);

/**
  * Generate a translation matrix
  *
  * @param m - pointer to matrix
  * @param x - translation on x axis
  * @param y - translation on y axis
  * @param z - translation on z axis
  *
**/
void vfpu_translate_matrix(ScePspFMatrix4 *m, float x, float y, float z);

/**
  * Generate a perspective projection matrix
  *
  * @param m      - pointer to matrix
  * @param fovy   - vertical field of view
  * @param aspect - aspect ratio of viewport
  * @param near   - near clipping plane
  * @param far    - far clipping plane
  *
**/
void vfpu_perspective_matrix(ScePspFMatrix4 *m, float fovy, float aspect, float near, float far);

/**
  * Generate an orthogonal  projection matrix
  *
  * @param m      - pointer to matrix
  * @param left   - coordinate for left edge of viewport
  * @param right  - coordinate for right edge of viewport
  * @param bottom - coordinate for bottom edge of viewport
  * @param top    - coordinate for top edge of viewport
  * @param near   - near clipping plane
  * @param far    - far clipping plane
  *
**/
void vfpu_ortho_matrix(ScePspFMatrix4 *m, float left, float right, float bottom, float top, float near, float far);

//Returns an integer no greater than or no less than the given value
float vfpu_floor(float x);

//Returns an integer no greater than or no less than the given value
float vfpu_ceil(float x);

//Return the absolute, or non-negative value, of a given value
float vfpu_abs(float x);

//Calculates the square root
float vfpu_sqrtf(float x);

float vfpu_fmaxf(float x, float y);
float vfpu_fminf(float x, float y);
float vfpu_logf(float x);
float vfpu_Log10(float x);

/**
  * Calculate sine
  *
  * @param x - input in radians
  *
**/
float vfpu_sinf(float x);

/**
  * Calculate cosine
  *
  * @param x - input in radians
  *
**/
float vfpu_cosf(float x);

/**
  * Calculate tangent
  *
  * @param x - input in radians
  *
**/
float vfpu_tanf(float x);

/**
  * Calculate inverse sine (arcsin)
  *
  * @param x - input
  *
**/
float vfpu_asinf(float x);

/**
  * Calculate inverse cosine (arccos)
  *
  * @param x - input
  *
**/
float vfpu_acosf(float x);

/**
  * Calculate inverse tangent (arctan)
  *
  * @param x - input
  *
**/
float vfpu_atanf(float x);

/**
  * Calculate inverse tangent, with proper quadrant fixup
  *
  * @param x - input
  *
**/
float vfpu_atan2f(float x, float y);

/**
  * Calculate hyperbolic sine
  *
  * @param x - input
  *
**/
float vfpu_sinhf(float x);

/**
  * Calculate hyperbolic cosine
  *
  * @param x - input
  *
**/
float vfpu_coshf(float x);

/**
  * Calculate hyperbolic tangent
  *
  * @param x - input
  *
**/
float vfpu_tanhf(float x);

/**
  * Calculate sine and cosine
  *
  * @param r - input in radians
  * @param s - pointer to float for sin
  * @param c - pointer to float for cos
**/
void vfpu_sincos(float r, float *s, float *c);

/**
  * Calculate exponent of x
  *
  * @param x - input
  *
**/
float vfpu_expf(float x);

/**
  * Calculate logarithm of x
  *
  * @param x - input
  *
**/
float vfpu_logf(float x);

/**
  * Calculate x raised to the power of y
  *
  * @param x - number to raise power of
  * @param y - power to raise x by
  *
**/
float vfpu_powf(float x, float y);

/**
  * Calculate floating point remainder of x/y
  *
  * @param x - input
  * @param y - input
  *
**/
float vfpu_fmodf(float x, float y);

/**
  * Perform a smooth acceleration/deceleration curve based on the input time value
  * returns 0 to 1
  *
  * @param t - input (0 to 1 float)
  *
**/
float vfpu_ease_in_out(float t);


/**
  * Normalize a 3d vector, returning a unit vector of length = 1
  *
  * @param v - pointer to vector to normalize
  *
**/
void vfpu_normalize_vector(ScePspFVector4 *v);

/**
  * Zero a 3d vector
  *
  * @param v - pointer to vector
  *
**/
void vfpu_zero_vector(ScePspFVector4 *v);

/**
  * Scale a 3d vector
  *
  * @param vout  - pointer to result vector
  * @param vin   - pointer to vector to scale
  * @param scale - float value to scale vector by
  *
**/
void vfpu_scale_vector(ScePspFVector4 *vout, ScePspFVector4 *vin, float scale);

/**
  * Add 2 3d vectors
  *
  * @param vout - pointer to result vector
  * @param va   - pointer to first vector to add
  * @param vb   - pointer to second vector to add
**/
void vfpu_add_vector(ScePspFVector4 *vout, ScePspFVector4 *va, ScePspFVector4 *vb);


/**
  * Generate rotation matrix for environment map.
  *
  * @param envmat - pointer to array of 2 vectors to store envmap matrix
  * @param r      - angle to rotate in radians
**/
void vfpu_envmap_matrix(ScePspFVector4 *envmat, float r);

/**
  * Transform 3d vector by 4x4 matrix
  *
  * @param m    - pointer to transformation matrix
  * @param vin  - pointer to vector to transform
  * @param vout - pointer to result vector
**/
void vfpu_transform_vector(ScePspFMatrix4 *m, ScePspFVector4 *vin, ScePspFVector4 *vout);

/**
  * Convert input sphere coordinates to cartesian coordinates
  *
  * @param az  - azimuth angle (0 to PI*2)
  * @param ze  - zenith angle (0 to PI)
  * @param rad - sphere radius
  * @param x   - pointer to float for x coordinate
  * @param y   - pointer to float for y coordinate
  * @param z   - pointer to float for z coordinate
  *
**/
void vfpu_sphere_to_cartesian(float az, float ze, float rad, float *x, float *y, float *z);

/**
  * Generate an identity quaternion
  *
  * @param q - pointer to quaternion
  *
  * this will set the quaternion's components to 0,0,0,1
  *
**/
void vfpu_quaternion_identity(ScePspQuatMatrix *q);

/**
  * Copy a quaternion
  *
  * @param dst - pointer to quaternion to copy to
  * @param src - pointer to quaternion to copy from
  *
**/
void vfpu_quaternion_copy(ScePspQuatMatrix *dst, ScePspQuatMatrix *src);

/**
  * Normalize a quaternion
  *
  * @param res - pointer to quaternion to normalize
  *
**/
void vfpu_quaternion_normalize(ScePspQuatMatrix *res);

/**
  * Multiply 2 quaternions
  *
  * @param qout - pointer to result quaternion
  * @param a    - pointer to first quaternion to multiply
  * @param b    - pointer to second quaternion to multiply
  *
**/
void vfpu_quaternion_multiply(ScePspQuatMatrix *qout, ScePspQuatMatrix *a, ScePspQuatMatrix *b);

/**
  * Make a quaternion from euler angles
  *
  * @param qout - pointer to output quaternion
  * @param rx   - rotation on x axis, in degrees
  * @param ry   - rotation on y axis, in degrees
  * @param rz   - rotation on z axis, in degrees
**/
void vfpu_quaternion_from_euler(ScePspQuatMatrix *qout, float rx, float ry, float rz);

/**
  * Calculate exponent of a quaternion
  *
  * @param qout - pointer to output quaternion
  * @param qin  - pointer to input quaternion
  *
**/
void vfpu_quaternion_exp(ScePspQuatMatrix *qout, ScePspQuatMatrix *qin);

/**
  * Calculate logarithm of a quaternion
  *
  * @param qout - pointer to output quaternion
  * @param qin  - pointer to input quaternion
  *
**/
void vfpu_quaternion_ln(ScePspQuatMatrix *qout, ScePspQuatMatrix *qin);

/**
  * Return a sample from a linear interpolation of 2 quaternions
  *
  * @param qout - pointer to output quaternion
  * @param a    - pointer to starting quaternion
  * @param b    - pointer to ending quaternion
  * @param t    - time value to sample, from 0 to 1
  *
**/
void vfpu_quaternion_sample_linear(ScePspQuatMatrix *qout, ScePspQuatMatrix *a, ScePspQuatMatrix *b, float t);

/**
  * Return a sample from a hermite spline interpolation
  *
  * @param qout - pointer to output quaternion
  * @param a    - pointer to start quaternion
  * @param b    - pointer to end quaternion
  * @param at   - pointer to tangent point for quaternion a
  * @param bt   - pointer to tangent point for quaternion b
  * @param t    - time value to sample, from 0 to 1
  *
**/
void vfpu_quaternion_sample_hermite(ScePspQuatMatrix *qout, ScePspQuatMatrix *a, ScePspQuatMatrix *b, ScePspQuatMatrix *at, ScePspQuatMatrix *bt, float t);

/**
  * Return a tangent point for hermite spline interpolation
  *
  * @param qout - pointer to output quaternion
  * @param p1   - pointer to p-1 on spline curve for tangent
  * @param p2   - pointer to p+1 on spline curve for tangent
  * @param bias - value to scale difference between endpoints.
  *               for example, 0.5 results in a catmull-rom spline tangent
  *
**/

void vfpu_quaternion_hermite_tangent(ScePspQuatMatrix *qout, ScePspQuatMatrix *p1, ScePspQuatMatrix *p2, float bias);

/**
  * Convert quaternion to rotation matrix
  *
  * @param q - pointer to input quaternion
  * @param m - pointer to output matrix
  *
**/
void vfpu_quaternion_to_matrix(ScePspQuatMatrix *q, ScePspFMatrix4 *m);

float vfpu_Deg(float x);
float vfpu_Rad(float x);

#if defined(__cplusplus)
}
#endif

#endif
