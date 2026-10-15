#include "types.h"

typedef struct Ent {
    s16 x;
    s16 y;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Ent;

typedef struct Obj {
    u8 pad[0x28];
    Ent *ents;
} Obj;

static inline void setpos(Ent *d, Ent *s, u32 i, s32 k)
{
    d[i].x = s[i].x + k * 8;
    d[i].y = s[i].y;
}
void InsectUiRosterRowSetTextMaybe_393020(s32 pd0, Obj *arg1, Obj *arg2, Obj *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg_sp0)
{
    Ent *e1;
    Ent *e2;
    Ent *e3;
    s32 k;

    if (arg1 == NULL || arg2 == NULL || arg3 == NULL) {
        return;
    }
    e1 = arg1->ents;
    e2 = arg2->ents;
    e3 = arg3->ents;
    if (e1 == NULL || e2 == NULL) {
        return;
    }
    if (arg4 >= 0 && arg4 < 10) {
        e1[arg4].unk4 = arg5;
        e2[arg4].unk4 = arg6;
        if (arg6 != 0) {
            e3[arg4].unk4 = arg7;
            k = 0x15;
            if (arg_sp0 != 0) {
                k = 0x1D;
            }
            setpos(e3, e2, arg4, k);
        }
    }
}
