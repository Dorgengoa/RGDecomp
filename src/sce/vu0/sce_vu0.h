/* SPDX-License-Identifier: CC0-1.0 */
/* libvu0 functions the game calls (src/sce/vu0/libvu0.c, docs/BINDINGS.md).
 * Sony's types: a 16-byte-aligned float[4] vector and float[4][4] matrix
 * (row i = 16 bytes at offset 16*i). */
#ifndef RG_SCE_VU0_H
#define RG_SCE_VU0_H

#include "port/vu0.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef float sceVu0FVECTOR[4] __attribute__((aligned(16)));
typedef float sceVu0FMATRIX[4][4] __attribute__((aligned(16)));

void sceVu0AddVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2);
void sceVu0SubVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2);
void sceVu0ScaleVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, float t);
void sceVu0ScaleVectorXYZ(sceVu0FVECTOR v0, sceVu0FVECTOR v1, float t);
void sceVu0DivVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, float t);
void sceVu0InterVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2, float t);
void *sceVu0CopyVector(sceVu0FVECTOR v0, sceVu0FVECTOR v1);
float sceVu0InnerProduct(sceVu0FVECTOR v0, sceVu0FVECTOR v1);
void sceVu0OuterProduct(sceVu0FVECTOR v0, sceVu0FVECTOR v1, sceVu0FVECTOR v2);
void sceVu0CopyMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1);
void sceVu0MulMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FMATRIX m2);
void sceVu0TransposeMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1);
void sceVu0InversMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1);
void sceVu0RotMatrixX(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float rx);
void sceVu0RotMatrixY(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float ry);
void sceVu0RotMatrixZ(sceVu0FMATRIX m0, sceVu0FMATRIX m1, float rz);
void sceVu0RotMatrix(sceVu0FMATRIX m0, sceVu0FMATRIX m1, sceVu0FVECTOR rot);

#ifdef __cplusplus
}
#endif
#endif
