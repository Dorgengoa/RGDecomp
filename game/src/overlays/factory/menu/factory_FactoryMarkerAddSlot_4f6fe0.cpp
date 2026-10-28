/* rgp:protos */
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F6FE0 -- 288 bytes / 72 words, 3 branches,
 * 4 calls + 1 virtual.  Allocate the first free trail record, fill it from a
 * source vector, arm its widget and seed the number-table entry.
 *
 * .cpp for the ONE call, exactly as factory_FactoryShutdown_504850.cpp records: the
 * plain-C struct-of-function-pointers spelling reproduced every other word but
 * emitted `8C820000 / 8C420070 / 0040F809` (target in $v0) where retail has
 * `8C990000 / 8F390070 / 0320F809` (target in $t9).  Only a real `virtual`
 * uses $t9.  `this` is the object itself and the vptr is at offset 0, so the
 * class is polymorphic with no base; slot 0x70 is index (0x70-8)/4 = 26, so
 * twenty-six placeholders precede it.  The plain-C draft is kept as
 * build/wf-parked/factory/factory_FactoryMarkerAddSlot_4f6fe0.c.plainC.
 *
 * * `factory_FactoryMarkerFindFree_4f6280` (byte-identical, same lane) is the allocator; its
 *   result is re-extended with `dsll32/dsra32 ..,16` HERE, so the prototype in
 *   THIS unit returns `s32` and the value is cast `(s16)` explicitly
 *   ([[normal-s16-cast-sign-extension]]).  `$4` is never reloaded for that
 *   call -- a0 still holds the parameter.
 * * The seven record stores are in SOURCE order 0x00,0x04,0x08,0x0C,0x10,
 *   0x0E,0x0F -- the byte fields come LAST ([[normal-row-store-order]]).
 * * `factory_D_0050B960[i]` is a NAMED local assigned BEFORE `func_1FEDE0` -- that is
 *   what forces the fourth callee-saved register ($19) and the 0x50 frame;
 *   computing it at its use inside the `if` costs the save/restore pair and
 *   re-materialises the `%hi`/`%lo`.
 * * `factory_D_0050BB20[i]` must ALSO be a named local: written as two subscripted
 *   stores mwcc folds `+8` into the address and emits TWO `lui`/`addiu`/`addu`
 *   triples plus a second `sll ..,6` -- three wasted words.
 * * `sll $16, $17, 6` is CSE'd across the `func_1FEDE0` call and serves BOTH
 *   tables, so both are 0x40-stride arrays indexed by `i`.
 * * `daddu $7, $6, $0` is mwcc noticing both trailing `func_291110` arguments
 *   are 1, the shape the byte-identical `factory_FactoryBlueprintAskClear_4fae70` records.
 */

struct Cell {
    f32 f00;
    f32 f04;
    f32 f08;
    s16 f0C;
    u8  f0E;
    u8  f0F;
    s32 f10;
};                                              /* 0x14 */

struct Ctx {
    u8    pad00[0x78];
    Cell *f78;
};

struct Src {
    f32 f00;
    f32 f04;
    f32 f08;
    s16 f0C;
};

struct Num {
    s16 f00;
    u8  pad02[0x6];
    s64 f08;
    u8  pad10[0x30];
};                                              /* 0x40 */

struct Slot {
    u8 pad00[0x40];
};

struct Res {
    u8  pad00[0x2C];
    s16 f2C;
};

struct ObjV {
    VC_VPTR_MEMBER;    
        
        
        
        
      void s16() { VCM0(void, 0x48); }  
        
        
      
    Res * f70(s32 k) { return VCM(Res *, (void *, s32), 0x70, k); }
};

struct H2 {
    u8    pad00[0x8];
    ObjV *f08;
};

struct H1 {
    u8  pad00[0x40];
    H2 *f40;
};

struct H0 {
    u8  pad00[0x8];
    H1 *f08;
};

extern "C" Slot factory_D_0050B960[];
extern "C" Num  factory_D_0050BB20[];
extern "C" void *D_004807F0;                    /* _gp - 0x4980 */

extern "C" s32   factory_FactoryMarkerFindFree_4f6280(Ctx *o);
extern "C" void  UiSetWidgetsVisibleById_291110(void *w, u16 id, s32 a, s32 b);
extern "C" H0   *GetGameData_1fede0(void);
extern "C" void  UiSetItemIconUv_288e50(void *p, s32 a, s32 b, s32 c);

extern "C" s32 factory_FactoryMarkerAddSlot_4f6fe0(Ctx *o, Src *s);

s32 factory_FactoryMarkerAddSlot_4f6fe0(Ctx *o, Src *s)
{
    Cell *e;
    H0   *h;
    ObjV *ob;
    Res  *r;
    Num  *t;
    s32   i;
    Slot *sl;

    if (s == NULL) {
        return -1;
    }
    i = (s16)((short)factory_FactoryMarkerFindFree_4f6280(o));
    if (i < 0) {
        return -1;
    }
    e = &o->f78[i];
    e->f00 = s->f00;
    e->f04 = s->f04;
    e->f08 = s->f08;
    e->f0C = 0;
    e->f10 = 0;
    e->f0E = 1;
    e->f0F = 0;
    UiSetWidgetsVisibleById_291110(D_004807F0, i + 0x98, 1, 1);
    sl = &factory_D_0050B960[i];
    h = GetGameData_1fede0();
    if (h != NULL) {
        ob = h->f08->f40->f08;
        r = ob->f70(s->f0C);
        UiSetItemIconUv_288e50(sl, r->f2C, 0x28, 0x2D);
    }
    t = &factory_D_0050BB20[i];
    t->f08 = 0;
    t->f00 = 0x16;
    return i;
}
