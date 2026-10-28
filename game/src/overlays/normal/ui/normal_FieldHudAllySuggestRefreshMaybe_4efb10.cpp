/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x004EFB10 -- retargets the 0x71.. widget row of screen `o` when its
 * 0x398 page id still matches `k`.  The active entity's slot-303 count is
 * clamped to 3, used to pick a layout id out of normal_D_005262D6, and the resulting
 * record's 0x08 handle is written into every widget whose per-slot 0x39A state
 * is 2.
 *
 * C++ virtuals: 0x4C4 -> slot 303, 0x70 -> slot 26.
 * `daddiu $18,$0,0x71` plus the `andi 0xFFFF` wrap is a `u16` widget id.
 * ⚠ THE WHOLE RESIDUE WAS THE WIDGET ID, and it took THREE stacked levers:
 *   1. `u16 id` (not s32) -- a REGISTER-RESIDENT u8/u16 destination is what
 *      selects `daddiu $18,$0,0x71`; s32/u32/s64 all give `addiu`
 *      (levers.d/mwcc-daddiu-unsigned-narrow).
 *   2. `id++`, NOT `id = (u16)(id + 1)` -- with a u16 destination the cast is
 *      a SECOND narrowing and mwcc emits TWO `andi 0xFFFF` (one word long).
 *      `id = id + 1` gives the same object as the cast; `id++`/`++id`/`id += 1`
 *      are one object and the right length.
 *   3. func_290460's SECOND PARAMETER declared `u16` -- with an `s32` param the
 *      u16->int promotion masks AGAIN at the call (`andi $5,$18,0xFFFF` in the
 *      loop-back delay slot) where retail passes a bare `daddu $5,$18,$0`.
 *      `s16` goes one word long, `u32` is identical to `s32`
 *      (levers.d/pk-callee-param-width).
 *   Arms 1 and 2 alone read as 2 bad words that look like a SCHEDULING swap of
 *   two delay slots -- it is not scheduling, it is the mask.
 */
struct Rec;
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Rec * find(s16 k) { return VCM(Rec *, (void *, s16), 0x70, k); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s303() { return VCM0(s32, 0x4C4); }
};

typedef struct Scr  { u8 pad000[0x398]; s16 f398; s16 f39A[6]; s16 f3A6; } Scr;
typedef struct Slot { u8 pad00[4]; s32 f04; } Slot;
typedef struct Wid  { u8 pad00[0x28]; Slot *f28; } Wid;
typedef struct Rec  { u8 pad00[8]; s32 f08; } Rec;
typedef struct Own  { u8 pad00[0x14]; void *f14; } Own;
typedef struct Box  { u8 pad00[8]; Ent *f08; } Box;
typedef struct Src  { u8 pad00[0x44]; Box *f44; } Src;

extern "C" s16 normal_D_005262D6[];

extern "C" {
extern Own  *GetGameData_1fede0(void);
extern Src  *GetWorldDataMgr_1fedf0(void);
extern Ent  *CharaMgrPoolFindById_3a8c60(void *a, s16 k);
extern Wid  *UiFindWidget_290460(Scr *p, u16 id);
}

extern "C" void normal_FieldHudAllySuggestRefreshMaybe_4efb10(Scr *o, s32 k)
{
    Own  *a;
    Src  *b;
    Ent  *t;
    Rec  *m;
    Wid  *h;
    Slot *w;
    s32   n;
    u16   id;
    s32   i;

    if (o->f39A[4] == 0) {
        return;
    }
    if (o->f398 != k) {
        return;
    }
    a = GetGameData_1fede0();
    b = GetWorldDataMgr_1fedf0();
    t = CharaMgrPoolFindById_3a8c60(a->f14, o->f398);
    if (t == 0) {
        return;
    }
    n = t->s303();
    if (n <= 0) {
        return;
    }
    if (n > 3) {
        n = 3;
    }
    m = b->f44->f08->find(normal_D_005262D6[n]);
    if (m == 0) {
        return;
    }
    id = 0x71;
    for (i = 0; i < o->f3A6; i++) {
        h = UiFindWidget_290460(o, id);
        if (h != 0) {
            w = h->f28;
            if (w != 0) {
                if (o->f39A[i] == 2) {
                    w->f04 = m->f08;
                }
            }
        }
        id++;
    }
}
