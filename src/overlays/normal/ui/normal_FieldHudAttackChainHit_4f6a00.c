#include "types.h"
/* normal 0x004F6A00 -- re-lays the 0x28 sub-object at 256x240, arms the 0x3E4
 * flag with a zero scroll offset, and if the 0x14 sub-object hands back a
 * sprite, writes its position from that offset (72 and 128 units per unit of
 * scroll, negated) and its 0x3C x 0x4E size.  The 0x3E8 float is RELOADED for
 * the second product because the intervening `sh` through the sprite pointer
 * is a store mwcc will not move a load past. */

typedef struct Spr {
    s16 f000;
    s16 f002;
    u8  pad004[0x1C - 4];
    s16 f01C;
    s16 f01E;
} Spr;

typedef struct Obj {
    u8  pad000[0x14];
    u8  f014[0x28 - 0x14];
    u8  f028[0x3E4 - 0x28];
    s16 f3E4;
    u8  pad3E6[0x3E8 - 0x3E6];
    f32 f3E8;
} Obj;

extern void func_383350(void *p, s32 w, s32 h);
extern Spr *func_28F2B0(void *p, s32 id, s32 a);

extern void normal_FieldHudAttackChainHit_4f6a00(Obj *p);

void normal_FieldHudAttackChainHit_4f6a00(Obj *p)
{
    Spr *s;

    func_383350(&p->f028, 0x100, 0xF0);
    p->f3E4 = 1;
    p->f3E8 = 0.0f;
    s = func_28F2B0(&p->f014, 2, 0);
    if (s != NULL) {
        s->f000 = (s16)-(72.0f * p->f3E8);
        s->f002 = (s16)-(128.0f * p->f3E8);
        s->f01C = 0x3C;
        s->f01E = 0x4E;
    }
}
