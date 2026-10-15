#include "types.h"

/* factory.bin overlay, 0x005029B0 -- 188 bytes / 47 words, 1 branch, 1 call.
 * Take the step delta for an orientation, scale the caller's cell coordinates
 * by the pitch at 0x2B4 and write the resulting doubled position plus the
 * advanced orientation into the caller's record.
 *
 * * The FIFTH integer argument arrives in `$8` and is handed straight to
 *   `factory_FactoryGridDirToStep_502a70` -- the same five-parameter prototype the caller
 *   `factory_FactoryBeltResetAll_500f50` already declares.
 * * `d` is the only stack local, at 0x58($29).
 * * `mult` then `mult1` is the EE's two integer pipes, one multiply each; it
 *   is one source multiply per axis, not a shared one.
 * * The tail is the recorded PLAIN-u16 `((h & ~3) | v) & 3` lever with a
 *   NON-ZERO v (`(d.f & 3) + 2`), the same spelling as `factory_FactoryBeltResetAll_500f50`;
 *   `addiu $4, $0, -0x4` is the promoted `int` complement.
 */

typedef struct Pos {
    s16 x;
    s16 y;
    u16 f;
} Pos;                                          /* 6 */

typedef struct Obj {
    u8  pad000[0x2B4];
    s32 f2B4;
} Obj;

extern void factory_FactoryGridDirToStep_502a70(Obj *o, Pos *d, s32 f);

s32 factory_FactoryPortToFineCell_5029b0(Obj *o, Pos *p, s32 x, s32 y, s32 f)
{
    Pos d;

    if (p == 0) {
        return 0;
    }
    factory_FactoryGridDirToStep_502a70(o, &d, f);
    p->x = d.x * 2 + (x * o->f2B4 + 1);
    p->y = d.y * 2 + (y * o->f2B4 + 1);
    p->f = (u16)(((p->f & ~3) | ((d.f & 3) + 2)) & 3);
    return 1;
}
