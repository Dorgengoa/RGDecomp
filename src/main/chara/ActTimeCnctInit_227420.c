#include "types.h"

typedef struct { f32 a, b, c; s32 d; f32 e; } T;

void ActTimeCnctInit_227420(T *t, s32 flag, f32 x, f32 y, f32 z, f32 w)
{
    t->a = -1.0f;
    t->b = -1.0f;
    t->c = -1.0f;
    t->d = 0;
    t->e = 1.0f;
    if (flag != 0) {
        t->a = z;
        t->b = x;
        t->c = y;
        t->d = 0;
        t->e = 1.0f;
        if (flag != 0) {
            t->d = flag;
            if (0.0f < w) {
                if (w <= 1.0f) {
                    t->e = w;
                }
            }
        }
    }
}
/* MEASURED: the second `if (flag)` is NESTED inside the first (a sibling
   `if` is 4 words long).  Naming 1.0f in a local is INERT (same object).
   The struct-member spelling is required: `*(f32 *)((u8 *)p + K)` repeated
   makes mwcc materialise each address in its own register (7 words long). */
