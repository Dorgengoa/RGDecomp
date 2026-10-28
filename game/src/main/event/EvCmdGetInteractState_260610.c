/* rgp:protos */
#define RGP_SELF_EvCmdGetInteractState_260610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x38];
    f32 x;
    f32 y;
    f32 z;
} Pos00260610;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 rest : 5;
    u8 padB[5];
    Pos00260610 *pos;
} Src00260610;

typedef struct {
    u8 pad0[0xCE];
    s16 unkCE;
} Found00260610;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdGetInteractState_260610(s64 *out, s32 n) {
    Src00260610 *src;
    Found00260610 *found;

    src = ((Src00260610 *)GetInteractState_27a650());
    ScriptSetRefInt_26a1e0((s32)out++, src->unk0);
    ScriptSetRefInt_26a1e0((s32)out++, src->unk2);
    ScriptSetRefInt_26a1e0((s32)out++, src->unk4);
    ScriptSetRefInt_26a1e0((s32)out++, src->unk6);
    ScriptSetRefInt_26a1e0((s32)out++, src->unk8);
    found = ((Found00260610 *)NpcObjFindById_2fb420(((s32)GetNpcObjTable_312860()), src->unk2));
    if (found != NULL) {
        ScriptSetRefInt_26a1e0((s32)out++, found->unkCE);
    } else {
        ScriptSetRefInt_26a1e0((s32)out++, 0);
    }
    if (n >= 7) {
        if (src->b1) {
            ScriptSetRefInt_26a1e0((s32)out++, 1);
        } else {
            ScriptSetRefInt_26a1e0((s32)out++, 0);
        }
        if (src->pos != NULL) {
            ScriptSetRefFloat_26a1c0((s32)out++, src->pos->x);
            ScriptSetRefFloat_26a1c0((s32)out++, src->pos->y);
            ScriptSetRefFloat_26a1c0((s32)out++, src->pos->z);
        } else {
            ScriptSetRefFloat_26a1c0((s32)out++, 0.0f);
            ScriptSetRefFloat_26a1c0((s32)out++, 0.0f);
            ScriptSetRefFloat_26a1c0((s32)out++, 0.0f);
        }
        if (src->b2) {
            ScriptSetRefInt_26a1e0((s32)out++, 1);
        } else {
            ScriptSetRefInt_26a1e0((s32)out++, 0);
        }
        if (src->b0) {
            ScriptSetRefInt_26a1e0((s32)out++, 1);
        } else {
            ScriptSetRefInt_26a1e0((s32)out++, 0);
        }
    }
    return 1;
}
