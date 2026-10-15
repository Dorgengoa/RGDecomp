#include "types.h"

typedef struct Obj2C {
    u8 pad2C[0x2C];
    s16 unk2C;
} Obj2C;

typedef struct Entry6 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Entry6;

u8 *GetGameData_1fede0(void);
void UiSetSpriteSizeUvSize_28f670(s32, s32, s32, s32, s32, s32, s32);
u8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
Obj2C *CharaGetIconRecMaybe_3ae3e0(s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyGetMemberChara_3c2420(s32, s32);
extern Entry6 D_00450D30[];

s32 MenuItemUseTargetMemberFaceSprites_2a2450(s32 *arg0, u16 arg1) {
    u16 base;
    u8 *obj;
    s32 i;
    s32 n;
    s32 j;
    u8 *p;
    s32 h;
    s16 id;
    s32 k;
    Entry6 *e;

    base = arg1;
    obj = GetGameData_1fede0();
    i = 0;
    do {
        UiSetSpriteSizeUvSize_28f670(*arg0, (base + i) & 0xFFFF, 0, 0, 0, 0, 0);
        i += 1;
    } while (i < 3);
    n = PartyCountMembers_3c2010(*(s32 *)(obj + 0x18), 1, 1);
    for (j = 0; j < n; j++) {
        p = UiGetWidgetSprite_28fe10(*arg0, (base + j) & 0xFFFF, 0);
        if (p == NULL) {
            return 0;
        }
        h = PartyGetMemberChara_3c2420(*(s32 *)(obj + 0x18), j);
        if (h == 0) {
            return 0;
        }
        id = CharaGetIconRecMaybe_3ae3e0(h)->unk2C;
        *(s16 *)(p + 8) = 0;
        *(s16 *)(p + 0xA) = 0;
        for (k = 0; k < 0xA; k++) {
            e = &D_00450D30[k];
            if (id == e->unk0) {
                *(s16 *)(p + 8) = e->unk2;
                *(s16 *)(p + 0xA) = e->unk4;
                *(s16 *)(p + 0xC) = 0x36;
                *(s16 *)(p + 4) = 0x36;
                *(s16 *)(p + 0xE) = 0x42;
                *(s16 *)(p + 6) = 0x42;
                break;
            }
        }
    }
    return 1;
}
