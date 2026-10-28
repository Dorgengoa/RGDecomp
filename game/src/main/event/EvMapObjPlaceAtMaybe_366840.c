/* rgp:protos */
#define RGP_SELF_EvMapObjPlaceAtMaybe_366840 1
#define RGP_SELF_clear16 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 unk0;
    f32 unk4;
    s32 unk8;
    s32 unkC;
} Arg00366840;

typedef struct {
    u8 pad0[0x32];
    s16 unk32;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
} Obj00366840;

typedef struct {
    u8 pad0[0xD0];
    s32 unkD0;
    u8 padD4[0x2F0 - 0xD4];
    s32 unk2F0;
    u8 pad2F4[6];
    s16 unk2FA;
    u8 pad2FC[0x334 - 0x2FC];
    u8 unk334;
} Own00366840;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline void clear16(void *dst)
{
    u8 *p = (u8 *)dst;
    u32 n = 16;
    if (p != NULL) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}

s32 EvMapObjPlaceAtMaybe_366840(Own00366840 *arg0, Obj00366840 *arg1, s32 arg2, f32 arg3)
{
    Arg00366840 a __attribute__((aligned(16)));
    s32 p;
    s32 i;
    Obj00366840 *o;

    if (!(arg0->unkD0 & 0x02000000)) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    arg1->unk32 = 1;
    arg1->unk3C &= ~1;
    arg1->unk34 = 0;
    arg1->unk38 = 0;
    NodeSetTranslation_1866b0(arg1, arg2);
    clear16(&a);
    a.unk4 = arg3;
    a.unk0 = 0;
    a.unk8 = 0;
    NodeSetRotation_186620(arg1, &a);
    p = arg0->unk2F0;
    for (i = 0; i < arg0->unk2FA; i++, p += 4) {
        o = ((Obj00366840 *)NodeObjFindChildByName_195040(arg1, EvMapNameRefGet_367520(p)));
        if (o != NULL) {
            o->unk32 = 1;
        }
    }
    arg0->unk334 = 1;
    return 1;
}
