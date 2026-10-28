/* rgp:protos */
#define RGP_SELF_ResGroupCmdElemSet_42ae50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 m0;
    s16 m2;
    void *m4;
    u16 m8;
    s8 mA;
    s32 mC;
} X;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
extern s16 D_00484008;

s32 ResGroupCmdElemSet_42ae50(s64 *arg0, s32 arg1)
{
    s64 *p;
    X *x;
    s32 h;
    s32 n;
    void *m;
    s8 *s;

    p = arg0;
    x = ((X *)ResGroupListCurElem_42a570());
    if (x == NULL) {
        return 1;
    }
    h = ResGroupParseGetArena_42a600();
    x->m0 = VariantGetInt_15f780((s32)p++);
    x->m2 = VariantGetInt_15f780((s32)p++);
    x->m4 = 0;
    if (*(s32 *)p == 1) {
        n = VariantGetInt_15f780((s32)p++);
        if (n > 0) {
            m = ArenaNewChecked_42c9a0(n, h, 4, 4);
            x->m4 = m;
            if (m != NULL) {
                memset(m, 0, n);
            }
        }
    } else {
        s = ((s8 *)SlotGetInt_15f720((s32)p++));
        if (s != NULL) {
            if (*s == 0) {
                x->m4 = 0;
            } else {
                x->m4 = ArenaStrDup_3701d0(h, s, -1, 4, 0);
            }
        }
    }
    x->mA = VariantGetInt_15f780((s32)p++);
    x->mC = VariantGetInt_15f780((s32)p++);
    x->m8 = 0;
    if (arg1 >= 6) {
        x->m8 |= (u16)((u16)VariantGetInt_15f780((s32)p++) << 7);
    }
    if (arg1 >= 7) {
        x->m8 |= (u16)VariantGetInt_15f780((s32)p++);
    }
    D_00484008++;
    return 1;
}
