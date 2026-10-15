#include "types.h"

typedef struct Ent_FUN_00290150 {
    u8 pad000[0x2];
    u16 f02;
    u8 pad004[0x80];
    s32 f84;
} Ent_FUN_00290150;

typedef struct Node_FUN_00290150 {
    Ent_FUN_00290150 *f00;
    u8 pad004[0x4];
    struct Node_FUN_00290150 *f08;
} Node_FUN_00290150;

typedef struct Obj_FUN_00290150 {
    Node_FUN_00290150 *f00;
} Obj_FUN_00290150;

extern s32 UiFindWidget_290460(Obj_FUN_00290150 *o, u16 k);
extern void UiWidgetAppendChild_290100(Obj_FUN_00290150 *o, s32 r, Ent_FUN_00290150 *e);

s32 UiLinkWidgetTree_290150(Obj_FUN_00290150 *o)
{
    Node_FUN_00290150 *n;
    Ent_FUN_00290150 *e;

    n = o->f00;
    if (n == 0) {
        return 0;
    }
    while (n != 0) {
        e = n->f00;
        if (n == 0) {
            break;
        }
        e->f84 = UiFindWidget_290460(o, e->f02);
        UiWidgetAppendChild_290100(o, e->f84, e);
        n = n->f08;
    }
    return 1;
}
