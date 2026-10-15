#include "types.h"
#pragma opt_loop_invariants off

typedef struct SNode00242890 SNode00242890;
struct SNode00242890 {
    SNode00242890 *unk0;
    u8 pad4[0xC - 4];
    s32 unkC;
    u8 pad10[0x1C - 0x10];
    s32 unk1C;
    u8 pad20[0x48 - 0x20];
    f32 unk48;
    s32 unk4C;
};

typedef struct {
    s32 unk0;
    SNode00242890 *unk4;
    s32 unk8;
} Ctx00242890;

typedef struct {
    s32 unk0;
    Ctx00242890 *unk4;
} Obj00242890;

void ParamTableSetAlpha_1cfb10(s32, s32, f32);                   /* extern */
s32 ScriptGetCodeAddr_249050(s32);                                 /* extern */
f32 TaggedGetFloat_2490d0(s32);                              /* extern */
s32 ScriptGetInt_2490f0(s32);                              /* extern */
s32 EventCastFindKeyByName_24bb50(Ctx00242890 *, s32);               /* extern */
extern Obj00242890 *gEventContext;

static inline SNode00242890 *next00242890(Ctx00242890 *c, s32 *key)
{
    SNode00242890 *n;
    SNode00242890 *nx;
    SNode00242890 *d;

    n = c->unk4;
    if (n == NULL) {
        return NULL;
    }
    *key = n->unkC;
    d = (SNode00242890 *)((u8 *)n + 0x10);
    nx = n->unk0;
    c->unk4 = nx;
    if (nx == NULL) {
        c->unk8 = 1;
    }
    return d;
}

s32 EvCmdCastSetAlpha_242890(s64 *arg0, s32 arg1) {
    f32 temp_f20;
    s32 temp_21;
    SNode00242890 *var_20;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_19;
    s32 var_4;
    Ctx00242890 *temp_18;
    SNode00242890 *temp_3;
    SNode00242890 *temp_3_2;

    temp_21 = gEventContext->unk0;
    temp_18 = (Ctx00242890 *)((u8 *) gEventContext->unk4 + 0x60);
    temp_2 = EventCastFindKeyByName_24bb50(temp_18, ScriptGetCodeAddr_249050((s32)arg0++));
    if ((!(temp_18->unk4 == NULL))) {
        var_4 = -1;
    } else {
        var_4 = 0;
        temp_18->unk4 = (SNode00242890 *) temp_18->unk0;
        temp_18->unk8 = 0;
    }
    if (var_4 != 0) {
        var_20 = NULL;
    } else {
        while ((var_20 = next00242890(temp_18, &var_19)) != NULL) {
            if (temp_2 == var_19) {
                break;
            }
        }
        temp_18->unk4 = NULL;
        temp_18->unk8 = 0;
    }
    temp_f20 = TaggedGetFloat_2490d0((s32)arg0++);
    if (arg1 == 2) {
        ParamTableSetAlpha_1cfb10(temp_21, var_20->unk1C, temp_f20);
    } else if (arg1 == 3) {
        temp_2_2 = ScriptGetInt_2490f0((s32)arg0);
        if (temp_2_2 == 0) {
            ParamTableSetAlpha_1cfb10(temp_21, var_20->unk1C, temp_f20);
        } else {
            var_20->unk48 = temp_f20;
            var_20->unk4C = temp_2_2;
        }
    }
    return 1;
}
