#include "types.h"

typedef struct Self {
    u8   pad000[0x424];
    s16  m424;
    u8   pad426[0x2];
    void *m428;
    u8   pad42C[0xA2C - 0x42C];
    s16  mA2C;
} Self;

extern const char D_0045C798[];
extern const char D_0045C7A8[];
extern void ActCfgTableRunEvntByName_21f680(void *h, s32 n, const char *s);

void CharaInvokeInitBt1_212ad0(Self *self)
{
    void *h;

    h = self->m428;
    if (h == NULL) {
        return;
    }
    switch (self->mA2C) {
    case 1:
        ActCfgTableRunEvntByName_21f680(h, self->m424, D_0045C798);
        break;
    default:
        ActCfgTableRunEvntByName_21f680(h, self->m424, D_0045C7A8);
        break;
    }
}
