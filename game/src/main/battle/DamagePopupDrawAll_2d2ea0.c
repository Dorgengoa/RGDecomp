/* rgp:protos */
#define RGP_SELF_DamagePopupDrawAll_2d2ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
} Sub;

typedef struct {
    u8 pad0[4];
    Sub *unk4;
    f32 unk8;
    s8 unkC;
} Arg;

typedef struct {
    u8 pad0[0x38];
    s32 unk38;
} Elem;

extern void Sprintf_1343b8(char *, char *, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *, s32, u32);
extern char D_004615D8[];

void DamagePopupDrawAll_2d2ea0(Arg *arg0)
{
    char buf[0x18] __attribute__((aligned(16)));
    s32 h;
    s32 n;
    s32 pass;
    s16 *res;
    s32 obj;
    s32 i;
    Elem *e;
    s32 t;

    if (arg0->unk4 == NULL) {
        return;
    }
    h = GetDrawCtx_15de80();
    n = arg0->unk4->unk14;
    if (n == 0) {
        return;
    }
    pass = 0;
    do {
        memset(buf, 0, 0x18);
        Sprintf_1343b8(buf, D_004615D8, pass + 1);
        res = ((s16 *)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), buf, 0x32B));
        if (res != NULL) {
            DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), *res, 1.0f);
        }
        obj = ((s32)DrawListBeginPrim_141b00(h));
        GsPktSetAlphaBlend_13e500(obj, 1);
        GsPktSetBlendMode_13e4f0(obj, 1);
        GsPktEnableAlphaTest_13e4d0(obj, 1);
        GsPktSetAlphaTestFunc_13e4c0(obj, 5, 0);
        GsPktSetZWriteMask_13e430(obj, 1);
        if (arg0->unkC & 1) {
            GsPktSetTexFilter_13e3d0(obj, 1);
        } else {
            GsPktSetTexFilter_13e3d0(obj, 0);
        }
        GsPktSetTextured_13e400(obj, 1);
        GsPktEnableZTest_13e460(obj, 0);
        GsPktSetOriginMode_13e2f0(obj, 1);
        for (i = 0; i < n; i++) {
            e = ((Elem *)PoolGetUsedElem_36acb0(arg0->unk4, i));
            if (e == NULL) {
                continue;
            }
            t = e->unk38;
            if (t == 3) {
                goto caseA;
            }
            if (t == 4) {
                goto caseA;
            }
            if (t == 5) {
                goto caseA;
            }
            if (t != 6) {
                goto caseB;
            }
caseA:
                if (pass == 0) {
                    DamagePopupDraw_2d3240(e, obj, res, (u8)arg0->unkC, arg0->unk8);
                }
            continue;
caseB:
                if (pass == 1) {
                    DamagePopupDraw_2d3240(e, obj, res, (arg0->unkC | 2) & 0xFF, arg0->unk8);
                }
        }
        DrawListEndPrim_141a20(h);
        pass++;
    } while (pass < 2);
}
