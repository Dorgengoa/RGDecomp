#ifndef VEC_H
#define VEC_H

#include "types.h"

/* A 16-byte aligned row. The alignment is load-bearing, not decoration: it is
   what lets mwcc move one with a single lq/sq. Without it the compiler falls
   back to a byte-wise copy and nothing involving a matrix will match.

   ★ And the rows have to be assigned ONE AT A TIME. Assigning a whole 64-byte
   Mtx4 makes mwcc emit a four-iteration block-copy LOOP; retail is always four
   explicit lq/sq pairs. See src/anim/ModelFrameSetMatrix_14a190.c, where that distinction is
   the entire difference between 39% and 100%. */
/* mwcc has a real 128-bit integer on the R5900. It is the only type that moves
   a qword in ONE instruction -- and `= 0` on it is the `sq zero` that four
   separate zero stores never coalesce into. See VEC4_ZERO below. */
typedef unsigned __int128 u128;

typedef struct Vec4 {
    f32 x, y, z, w;
#ifdef __cplusplus
    /* In C++ the alignment is not enough on its own: mwcc's IMPLICIT copy
       assignment is MEMBERWISE, so `a = b` emits four lwc1/swc1 pairs where the
       same source in C emits one lq/sq. Routing it through u128 brings the
       qword move back. Measured on CameraLatchGoals_177310: 60% vs 100%. */
    Vec4 &operator=(const Vec4 &o) {
        *(u128 *)this = *(const u128 *)&o;
        return *this;
    }
#endif
} __attribute__((aligned(16))) Vec4;

/* Zeroing a Vec4 field by field is FOUR `sw zero`s and mwcc never coalesces
   them; retail's single `sq zero` is a 128-bit store of an integer zero. */
#define VEC4_ZERO(v) (*(u128 *)&(v) = 0)

typedef struct Mtx4 {
    Vec4 r[4];
} Mtx4;

#endif
