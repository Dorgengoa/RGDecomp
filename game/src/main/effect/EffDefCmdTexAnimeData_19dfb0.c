/* rgp:protos */
#define RGP_SELF_EffDefCmdTexAnimeData_19dfb0 1
#define RGP_SELF_getp 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S8F(p, o) (*(s8 *)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004707F0[];
extern u8 D_004709E0[];
extern u8 D_00470E30[];
typedef struct {
    u8 pad0[0x20];
    s32 m20;
    u8 pad24[0x54 - 0x24];
    void *m54;
} Own;
static inline void *getp(Own *obj)
{
    void *t = obj->m54;
    if (t != NULL) {
        return t;
    }
    t = MemStackNew_14e230(0x28, obj->m20);
    if (t != NULL) {
            *(void **)t = D_00470E30;
            S32(t, 4) = -1;
            *(void **)t = D_004709E0;
            S32(t, 8) = 0x3F800000;
            S32(t, 0xC) = 0x3F800000;
            S32(t, 0x10) = 1;
            S32(t, 0x14) = 1;
            *(void **)t = D_004707F0;
            S32(t, 0x18) = 0;
            S8F(t, 0x1C) = 0;
            S8F(t, 0x1D) = 0;
            S32(t, 0x20) = 0;
    }
    obj->m54 = t;
    return t;
}

s32 EffDefCmdTexAnimeData_19dfb0(s32 arg0, s32 arg1, void **arg2)
{
    void *p;
    f32 f;
    s32 a;
    s32 c;

    p = getp((Own *)*arg2);
    if (p == NULL) {
        return 0;
    }
    f = VariantGetFloat_15f740(arg0);
    EffTexUvParamSetCellSize_198a50(p, f, VariantGetFloat_15f740(arg0 + 8));
    a = 1;
    c = 0;
    if (arg1 >= 2) {
        a = VariantGetInt_15f780(arg0 + 0x10);
    }
    if (arg1 >= 3) {
        c = VariantGetInt_15f780(arg0 + 0x18);
    }
    S8F(p, 0x1C) = (a != 0);
    S8F(p, 0x1D) = (c != 0);
    return 1;
}
