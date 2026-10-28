/* rgp:protos */
#define RGP_SELF_InsectUiMemberIconSetTypeMaybe_393760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[8];
    s16 unk8;
    s16 unkA;
    u8 padC[4];
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    u8 pad1C[4];
} E_393760;

void InsectUiMemberIconSetTypeMaybe_393760(s32 pad0, void *arg1, s32 arg2, s32 arg3) {
    E_393760 *e;

    if (arg1 == NULL) {
        return;
    }
    e = *(E_393760 **)((u8 *)arg1 + 0x20);
    if (e == NULL) {
        return;
    }
    e = &e[arg2];
    switch (arg3) {
    case 0:
        e->unk8 = 0x90;
        e->unkA = 0x62;
        break;
    case 1:
        e->unk8 = 0xC0;
        e->unkA = 0x62;
        break;
    case 2:
        e->unk8 = 0xA8;
        e->unkA = 0x62;
        break;
    case 3:
        e->unk8 = 0xD8;
        e->unkA = 0x62;
        break;
    }
    e->unk1A = 0;
    e->unk18 = 0;
    e->unk10 = e->unk14 = e->unk18;
}
