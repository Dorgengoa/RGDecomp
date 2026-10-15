#include "types.h"
/* normal 0x004F8DD0 -- resets the 0x79 group: clears the four flag bytes,
 * seeds 0x3D0 with 30, invalidates the five 118-byte records hanging off
 * 0x3C8 (their 0x70 s16 goes -1; the -1 stays live in $7 and is reused as
 * func_290010's fourth argument), then re-places and re-whitens the group. */

typedef struct Rec {
    u8  pad000[0x70];
    s16 f070;
    u8  pad072[0x76 - 0x72];
} Rec;                              /* stride 118 */

typedef struct Obj {
    u8   pad000[0x3C8];
    Rec *f3C8;
    u8   f3CC;
    u8   f3CD;
    u8   f3CE;
    u8   f3CF;
    u8   f3D0;
} Obj;

extern void func_290010(Obj *p, u16 id, s32 c, s32 d);
extern void func_290F60(Obj *p, u16 id, s32 c, s32 d);
extern void func_2905B0(Obj *p, u16 id, f32 x, f32 y, f32 z, f32 w);

extern void normal_FieldHudLogReset_4f8dd0(Obj *p);

void normal_FieldHudLogReset_4f8dd0(Obj *p)
{
    u16 id;
    s32 j;
    s32 i;

    p->f3CD = 0;
    p->f3CE = 0;
    p->f3CC = 0;
    p->f3CF = 0;
    p->f3D0 = 30;
    for (i = 0; i < 5; i++) {
        p->f3C8[i].f070 = -1;
    }
    func_290010(p, 0x79, 0, -1);
    func_290F60(p, 0x79, 0x28, 0x40);
    id = 0x7A;
    for (j = 0; j < 5; j++) {
        func_2905B0(p, id, 1.0f, 1.0f, 1.0f, 1.0f);
        id++;
    }
}
