#include "types.h"
/* normal 0x004F4600 -- the full RESET, a superset of 0x004F4790's 16-slot
 * loop: same two parallel record arrays (stride 60 through
 * normal_FieldHudEnemyRowInitMaybe_4f9d20, stride 28 through normal_FieldHudSlotRecClearRelated_4f9ce0) plus a
 * func_2907A0 fade per slot, then a 5x3 entity clear, then the tail. */

typedef struct RecA { u8 pad000[0x3C]; } RecA;   /* stride 60 */
typedef struct RecB { u8 pad000[0x1C]; } RecB;   /* stride 28 */

typedef struct Ent {
    u8  pad00[0x14];
    s32 f14;
    s32 f18;
    s16 f1C;
    u8  pad1E[0x2];
    s32 f20;
    s32 f24;
    s32 f28;
} Ent;

typedef struct Obj {
    u8    pad000[0x378];
    s16   f378;
    u8    pad37A[0x430 - 0x37A];
    u8    f430;
    u8    pad431[0x434 - 0x431];
    RecA *f434;
    s32   f438[16];
    s16   f478;
    s16   f47A;
    s16   f47C[16];
    u8    pad49C[0x4A8 - 0x49C];
    s16   f4A8;
    u8    pad4AA[0x4AC - 0x4AA];
    s32   f4AC[16];
    RecB *f4EC;
    s32   f4F0;
    s32   f4F4;
} Obj;

extern void normal_FieldHudEnemyRowInitMaybe_4f9d20(RecA *p, s32 idx);
extern void normal_FieldHudSlotRecClearRelated_4f9ce0(RecB *p);
extern void func_2907A0(Obj *a, u16 id, f32 t);
extern Ent *func_290460(Obj *a, u16 id);

void normal_FieldHudResetFull_4f4600(Obj *p)
{
    s32  i;
    u16  id;
    s32  j;
    Ent *e;

    p->f4A8 = 0;
    for (i = 0; i < 16; i++) {
        if (p->f434 != NULL) {
            normal_FieldHudEnemyRowInitMaybe_4f9d20(&p->f434[i], i);
        }
        p->f4AC[i] = 0;
        if (p->f4EC != NULL) {
            normal_FieldHudSlotRecClearRelated_4f9ce0(&p->f4EC[i]);
        }
        p->f438[i] = 0;
        p->f47C[i] = 0;
        if (p->f378 != 0) {
            func_2907A0(p, i + 0x2E, 0.0f);
        }
    }
    id = 0x4A;
    if (p->f378 != 0) {
        for (j = 0; j < 5; j++) {
            e = func_290460(p, id);
            e->f14 = 0;
            e->f18 = 0;
            e->f1C = 0;
            e->f20 = 0;
            e->f24 = 0;
            e->f28 = 0;
            e = func_290460(p, id - 5);
            e->f14 = 0;
            e->f18 = 0;
            e->f1C = 0;
            e->f20 = 0;
            e->f24 = 0;
            e->f28 = 0;
            e = func_290460(p, id - 10);
            e->f14 = 0;
            e->f18 = 0;
            e->f1C = 0;
            e->f20 = 0;
            e->f24 = 0;
            e->f28 = 0;
            id++;
        }
    }
    p->f478 = 0;
    p->f430 = 0;
    p->f47A = 0;
    p->f378 = 0;
    p->f4F0 = -1;
    p->f4F4 = 0;
}
