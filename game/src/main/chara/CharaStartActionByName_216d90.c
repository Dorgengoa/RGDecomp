/* rgp:protos */
#define RGP_SELF_CharaStartActionByName_216d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ch {
    u8 pad0[0x428];
    s32 m428;
    u8 pad42c[0x568 - 0x42c];
    s64 m568;
    u8 pad570[0xa0c - 0x570];
    s32 mA0C;
    f32 mA10;
    s32 mA14;
    s32 mA18;
    s32 mA1C;
    s32 mA20;
    s32 mA24;
    u8 mA28;
    u8 padA29[0xaac - 0xa29];
    u8 mAAC[0xb44 - 0xaac];
    s16 mB44;
    s16 mB46;
} Ch;

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

s32 CharaStartActionByName_216d90(Ch *c, s32 arg1, s64 arg2, f32 f)
{
    s32 id;
    s32 d;
    s32 t;

    if (CharaCanStartAction_210300((void *)c) == 0) {
        return 0;
    }
    id = ((s32)ActCfgTableFindActionByName_223d20(c->m428, ActCfgTableResolveActionAlias_223730(c->m428, c->mB44, c->mB46, c->mAAC, arg1)));
    if (id == 0) {
        return 0;
    }
    if (((short)CharaTableGetActionKind_225d30(id)) == 0x13 && ((unsigned char)CharaIsActionActive_215040(c)) != 0 &&
        ((short)CharaTableGetActionKind_225d30(c->mA14)) == 0x13 && id == c->mA14) {
        return 0;
    }
    d = CharaTableGetStepArray_225470(id);
    if (d == 0) {
        return 0;
    }
    if (CharaHasMotion_212510(c, CharaTableDataGetMotionName_2269e0(d)) == 0) {
        return 0;
    }
    CharaBeginActionStateResetMaybe_216f10(c);
    t = CharaTableGetName_225480(id);
    c->mA10 = 1.0f;
    c->mA0C = 0;
    c->mA20 = 0;
    c->mA24 = 0;
    c->mA28 = 0;
    c->mA1C = 0;
    c->mA14 = 0;
    c->mA18 = 0;
    c->mA0C = t;
    c->mA10 = f;
    c->mA14 = id;
    c->mA18 = d;
    c->mA1C = 0;
    c->m568 &= ~arg2;
    return 1;
}
