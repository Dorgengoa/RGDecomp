/* rgp:protos */
#define RGP_SELF_ActInfoClsnClone_2309b0 1
#define RGP_SELF_copyElem 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Elem {
    f32 x;
    f32 y;
    s32 p;
    u8 c;
} Elem;

static inline u8 copyElem(Elem *d, Elem *s, s32 a2, s32 a3)
{
    d->x = 0;
    d->y = 0;
    d->p = 0;
    d->c = 0;
    if (a2 == 0 || a3 == 0 || s == NULL || s->p == 0) {
        return 0;
    }
    d->x = s->x;
    d->y = s->y;
    d->c = s->c;
    d->p = ((s32)StrPoolIntern_302fd0(a3, s->p, a2));
    if (d->p == 0) {
        return 0;
    }
    return 1;
}

s32 ActInfoClsnClone_2309b0(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 temp_2;
    s32 temp_3;
    s32 temp_2_2;
    s32 temp_2_3;
    s16 temp_2_4;
    s32 temp_2_5;
    s32 temp_4;
    s32 temp_5;
    s32 var_20;
    s32 var_21;
    s16 var_2;
    u8 *temp_20;
    u8 *temp_3_2;

    *(s32 *)((u8 *)arg0 + 0x0) = 0;
    *(s32 *)((u8 *)arg0 + 0x4) = 0;
    *(s32 *)((u8 *)arg0 + 0x8) = 0;
    *(s16 *)((u8 *)arg0 + 0x10) = 0;
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *(s16 *)((u8 *)arg0 + 0x12) = 0;
    if ((arg2 == 0) || ((arg3 == 0) || ((arg1 == NULL) || (*(s32 *)((u8 *)arg1 + 0x0) == 0)))) return 0;
    if (*(s32 *)((u8 *)arg1 + 0x8) != 0) {
        temp_2 = *(s16 *)((u8 *)arg1 + 0x10);
        if (temp_2 > 0) {
            temp_2_2 = ((s32)MemStackNew_14e1b0(temp_2 * 0x10, arg2));
            *(s32 *)((u8 *)arg0 + 0x8) = temp_2_2;
            if (temp_2_2 == 0) {
                return 0;
            }
            *(s16 *)((u8 *)arg0 + 0x10) = *(s16 *)((u8 *)arg1 + 0x10);
        }
    }
    if (*(s32 *)((u8 *)arg1 + 0xC) != 0) {
        temp_3 = *(s16 *)((u8 *)arg1 + 0x12);
        if (temp_3 > 0) {
            temp_2_3 = ((s32)MemStackNew_14e1b0(temp_3 * 0x18, arg2));
            *(s32 *)((u8 *)arg0 + 0xC) = temp_2_3;
            if (temp_2_3 == 0) {
                return 0;
            }
            *(s16 *)((u8 *)arg0 + 0x12) = *(s16 *)((u8 *)arg1 + 0x12);
        }
    }
    for (var_21 = 0; var_21 < *(s16 *)((u8 *)arg0 + 0x10); var_21++) {
        temp_4 = var_21 * 0x10;
        if (!copyElem((Elem *)(*(u8 **)((u8 *)arg0 + 0x8) + temp_4), (Elem *)(*(u8 **)((u8 *)arg1 + 0x8) + temp_4), arg2, arg3)) {
            return 0;
        }
    }
    for (var_20 = 0; var_20 < *(s16 *)((u8 *)arg0 + 0x12); var_20++) {
        temp_5 = var_20 * 0x18;
        if (ActInfoClsnLinClone_230c60((s32)(*(u8 **)((u8 *)arg0 + 0xC) + temp_5),
                          (s32)(*(u8 **)((u8 *)arg1 + 0xC) + temp_5), arg2, arg3) == 0) {
            return 0;
        }
    }
    temp_2_5 = ((s32)StrPoolIntern_302fd0(arg3, *(s32 *)((u8 *)arg1 + 0x0), arg2));
    *(s32 *)((u8 *)arg0 + 0x0) = temp_2_5;
    if (temp_2_5 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)arg0 + 0x4) = *(s32 *)((u8 *)arg1 + 0x4);
    return 1;
}
