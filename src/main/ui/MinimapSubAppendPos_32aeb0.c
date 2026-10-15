#include "types.h"

typedef struct { f32 x, y, z, w; } V_0032aeb0;
typedef struct { u8 *f0; s32 f4; s16 f8; } T_0032aeb0;

extern void EntryPosRecInit_32afd0(void *, V_0032aeb0 *);

void MinimapSubAppendPos_32aeb0(T_0032aeb0 *p, V_0032aeb0 *src)
{
    V_0032aeb0 v;

    v = *src;
    EntryPosRecInit_32afd0((void *)(p->f0 + p->f8 * 16), &v);
    p->f8 = p->f8 + 1;
}
