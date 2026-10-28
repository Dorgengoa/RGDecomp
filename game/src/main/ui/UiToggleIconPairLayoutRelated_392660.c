/* rgp:protos */
#define RGP_SELF_UiToggleIconPairLayoutRelated_392660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    f32 f10;
    f32 f14;
    s16 f18;
    s16 f1A;
    u8 pad[4];
} Elem;

typedef struct {
    u8 pad[0x20];
    Elem *list;
} Obj;

void UiToggleIconPairLayoutRelated_392660(s32 pd0, Obj *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    Elem *e;

    if (arg1 != NULL) {
        e = arg1->list;
        if (e != NULL) {
            if (arg4 != 0) {
                e += arg5;
            }
            if (arg4 == 0) {
                e->f0 = 0;
                e->f2 = -4;
                e->f4 = 0x2A;
                e->fC = 0x2A;
                e->f6 = 0x16;
                e->fE = 0x16;
                e->f10 = e->f14 = e->f18 = e->f1A = 0;
                if (arg2 != 0) {
                    e->f8 = 0x88;
                    e->fA = 8;
                } else {
                    e->f8 = 0xB2;
                    e->fA = 8;
                }
                e++;
            }
            if (arg4 == 0) {
                e->f0 = 0x32;
                e->f2 = -4;
            }
            e->f4 = 0x2A;
            e->fC = 0x2A;
            e->f6 = 0x16;
            e->fE = 0x16;
            e->f10 = e->f14 = e->f18 = e->f1A = 0;
            if (arg3 != 0) {
                e->f8 = 0x88;
                e->fA = 0x1E;
            } else {
                e->f8 = 0xB2;
                e->fA = 0x1E;
            }
        }
    }
}
