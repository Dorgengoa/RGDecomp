#include "types.h"

/* factory.bin overlay, 0x00504500 -- zero a five-word record and return it.
 *
 * ★ The store order is 0x0, 0x8, 0x4, 0x10, 0xC -- two HIGH-then-LOW pairs
 * after a lone word, and 0x00504570 clears its own pair the same way round.
 * Stores through one pointer are emitted in source order, so that IS the
 * source order; it reads as a lone member followed by two inlined two-word
 * sub-object clears. Written ascending it is 4 of 7 words wrong. */

typedef struct R5 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} R5;

R5 *factory_ModelObjShadowFrameMapCtor_504500(R5 *o)
{
    o->f0 = 0;
    o->f8 = 0;
    o->f4 = 0;
    o->f10 = 0;
    o->fC = 0;
    return o;
}
