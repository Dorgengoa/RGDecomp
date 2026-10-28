/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x004F4A30 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x24 =
 * virtual #7.  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
    
    void s07() { VCM0(void, 0x24); }               /* slot 0x24 */
};

struct EL {
    u8  pad000[0x4DC];
    s32 f4DC;
    u8  pad4E0[0x790 - 0x4E0];
};

struct O {
    u8    pad000[0xC0];
    void *f0C0;
    u8    pad0C4[0x17B0 - 0xC4];
    EL    arr[4];
    u8    pad35F0[0x5D8C - 0x35F0];
    f32   f5D8C;
};

struct Vec {
    s32 f00;
    f32 f04;
    s32 f08;
    s32 f0C;
};

extern "C" f32 D_0047D1FC;
extern "C" s32 insect_InsectBattleTestFlag_50da40(O *o, s32 k);
extern "C" void DrawListAddTexLoad_1418c0(void *h, s32 id, f32 t);
extern "C" void ModelSetRot_151080(EL *e, Vec *v);

/* ix18e LEVER: the count must be COPIED into a local declared AFTER the
 * pointer and assigned BEFORE it -- that is what puts the pointer in the
 * HIGHER temp ($v1) and the counter in $v0, as retail has.  Four other
 * spellings (swapped parameters, initialiser-declaration, the reversed
 * declaration order with the reversed assignment order, and swapping the
 * `n--` / `q++` order) are ONE object b697ef0a; only this one moves. */
static inline void clr(void *p, u32 n)
{
    u8 *q;
    u32 c;

    c = n;
    q = (u8 *)p;
    if (q != 0) {
        do {
            *q = 0;
            c--;
            q++;
        } while (c != 0);
    }
}

extern "C" void insect_InsectBattleDrawMarkerModels_4f4a30(O *o)
{
    s32 k;
    s32 i;
    s32 j;
    EL *e;
    f32 t;
    Vec v __attribute__((aligned(16)));

    if (insect_InsectBattleTestFlag_50da40(o, 0x28) != 0 || insect_InsectBattleTestFlag_50da40(o, 0x27) != 0) {
        k = 0;
        if (insect_InsectBattleTestFlag_50da40(o, 0x28) != 0) {
            k = 1;
        }
        e = &o->arr[k];
        DrawListAddTexLoad_1418c0(o->f0C0, o->arr[k].f4DC, 1.0f);
        t = D_0047D1FC * o->f5D8C / 180.0f;
        clr(&v, 0x10);
        v.f00 = 0;
        v.f04 = t;
        v.f08 = 0;
        ModelSetRot_151080(e, &v);
        ((VE *)e)->s07();
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x26) != 0) {
        for (i = 0; i < 2; i++) {
            j = i + 2;
            e = &o->arr[j];
            DrawListAddTexLoad_1418c0(o->f0C0, o->arr[j].f4DC, 1.0f);
            ((VE *)e)->s07();
        }
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x29) != 0) {
        e = &o->arr[2];
        DrawListAddTexLoad_1418c0(o->f0C0, o->arr[2].f4DC, 1.0f);
        ((VE *)e)->s07();
    }
}
