#include "types.h"

typedef struct Ctx {
    u8 pad0[0x18];
    s32 unk18;
} Ctx;

typedef struct Ent {
    u8 pad0[4];
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} Ent;

typedef struct Tab {
    s16 a;
    s16 b;
    s16 c;
} Tab;

extern Ctx *GetGameData_1fede0(void);
extern Ent *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern u8 *CharaGetIconRecMaybe_3ae3e0(s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetMemberChara_3c2420(s32, s32);
extern Tab D_00450D80[];

s32 MenuItemUseTargetMemberLabelSpritesMaybe_2a2b70(s32 *arg0, s32 arg1)
{
    s32 i2;
    s16 k;
    s32 key;
    Ent *p;
    s32 n;
    s32 i;
    Ctx *ctx;
    Tab *e;
    s32 j;
    s32 id;

    key = arg1;
    ctx = GetGameData_1fede0();
    n = PartyCountMembers_3c2010(ctx->unk18, 1, 1);
    key &= 0xFFFF;
    for (i = 0; i < 3;) {
        p = UiGetWidgetSprite_28fe10(*arg0, (key + i) & 0xFFFF, 0);
        if (p == NULL) {
            return 0;
        }
        p->unkC = 0;
        i++;
        p->unk4 = 0;
    }
    for (i2 = 0; i2 < n; i2++) {
        p = UiGetWidgetSprite_28fe10(*arg0, (key + i2) & 0xFFFF, 0);
        if (p == NULL) {
            return 0;
        }
        id = PartyGetMemberChara_3c2420(ctx->unk18, i2);
        if (id == 0) {
            return 0;
        }
        k = *(s16 *)(CharaGetIconRecMaybe_3ae3e0(id) + 0x2C);
        p->unkA = 0;
        p->unk8 = 0;
        for (j = 0; j < 10; j++) {
            if (k == D_00450D80[j].a) {
                p->unk8 = D_00450D80[j].b;
                p->unkA = D_00450D80[j].c;
                break;
            }
        }
        p->unkC = 0x4C;
        p->unk4 = 0x4C;
        p->unkE = 0x12;
        p->unk6 = 0x12;
    }
    return 1;
}
