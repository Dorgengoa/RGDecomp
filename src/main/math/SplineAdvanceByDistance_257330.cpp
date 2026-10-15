/* PARKED s17b: not attempted -- m2c hits 3 unknown FPU instructions
   (mula.s/madda.s/madd.s, the documented 3-multiply-term accumulator chain)
   plus an `arg0->unk-C` negative-offset artifact suggesting the surrounding
   struct-index arithmetic isn't fully understood yet. Needs a manual asm
   read of asm/matchings/main/SplineAdvanceByDistance_257330.s before a first C draft. */
/* s49m: MATCH */
#include "types.h"

typedef struct Key {
    s32 t0;
    s32 dt;
    f32 a[3];
    f32 b[3];
    f32 c[3];
    f32 d[3];
} Key;

typedef struct Obj {
    Key keys[16];
    s32 m380;
    s32 m384;
    f32 m388;
    f32 m38C[3];
    f32 m398;
} Obj;

extern f32 D_0047D24C;
extern "C" f32 VecDistance_13d3d0(f32 *, f32 *);

extern "C" s32 SplineAdvanceByDistance_257330(Obj *o)
{
    f32 cur[4];
    f32 nxt[4];
    s32 i;
    f32 t;
    f32 t2;
    f32 t3;
    f32 dist;
    bool done;
    s32 k;

    if (o->m380 < 2) {
        return 1;
    }
    if (o->m398 <= 0.0f) {
        return 1;
    }
    do {
        o->m388 += D_0047D24C;
        k = *(volatile s32 *)&o->m384;
        if (!(o->m388 < (f32)(o->keys[k].t0 + o->keys[k].dt))) {
            o->m384 = k + 1;
            if (o->m384 >= o->m380) {
                for (i = 0; i < 3; i++) {
                    o->m38C[i] = o->keys[o->m380 - 1].d[i];
                }
                o->m384 = o->m380 - 1;
                o->m388 = 100.0f + (f32)(o->keys[o->m384].t0 + o->keys[o->m384].dt);
                return 1;
            }
        }
        t = (o->m388 - (f32)o->keys[o->m384].t0) / (f32)o->keys[o->m384].dt;
        t2 = t * t;
        t3 = t2 * t;
        for (i = 0; i < 3; i++) {
            cur[i] = o->m38C[i];
            nxt[i] = o->keys[o->m384].a[i] * t3 + o->keys[o->m384].b[i] * t2 + o->keys[o->m384].c[i] * t + o->keys[o->m384].d[i];
        }
        cur[3] = 1.0f;
        nxt[3] = 1.0f;
        dist = VecDistance_13d3d0(cur, nxt);
        done = dist >= o->m398;
    } while (!done);
    o->m38C[0] = nxt[0];
    o->m38C[1] = nxt[1];
    o->m38C[2] = nxt[2];
    return 0;
}
