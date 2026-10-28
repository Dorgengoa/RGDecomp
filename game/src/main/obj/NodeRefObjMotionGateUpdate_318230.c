/* rgp:protos */
#define RGP_SELF_NodeRefObjMotionGateUpdate_318230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00318230 {
    u8 pad0[0xB6];
    s16 unkB6;
    u8 padB8[0xC8 - 0xB8];
    f32 unkC8;
    u8 padCC[0x680 - 0xCC];
    s16 unk680;
    s16 unk682;
    u8 pad684[0x890 - 0x684];
    s8 unk890;
    u8 pad891[0x8B0 - 0x891];
    f32 unk8B0;
    f32 unk8B4;
} S00318230;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NodeRefObjMotionGateUpdate_318230(S00318230 *a, s32 arg1, f32 f)
{
    s32 obj;
    f32 t;
    u8 *q;

    if (a->unkB6 != 0) {
        return 0;
    }
    if (!((a->unkC8 - f) < 0.0f)) {
        return 0;
    }
    a->unkB6 = 1;
    if (a->unk890 != 0x23) {
        goto have;
    }
    a->unkB6 = 0;
    goto done;
have:
        q = (u8 *)a + 0x180;
        if (q != NULL && a->unk680 > 0) {
            obj = ((s32)ObjRecGetLiveObject_1c4a90(GetCurrentScene_1f5be0(), a->unk682));
            if (obj != 0 && ((unsigned char)StrEqualNonNull_1ca6c0(&a->unk890, ModelObjGetMotionName_1add90(obj))) != 0) {
                t = ModelObjGetMotionPhase_1add70(obj);
                if (a->unk8B0 <= t && t < a->unk8B4) {
                    a->unkB6 = 0;
                }
            }
        }
done:
    if (a->unkB6 == 0) {
        goto call;
    }
    return 0;
call:
    return NodeRefObjUpdate_318af0(a, arg1, f);
}
