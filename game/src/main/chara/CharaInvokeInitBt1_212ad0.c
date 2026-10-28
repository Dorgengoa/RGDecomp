/* rgp:protos */
#define RGP_SELF_CharaInvokeInitBt1_212ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Self {
    u8   pad000[0x424];
    s16  m424;
    u8   pad426[0x2];
    void *m428;
    u8   pad42C[0xA2C - 0x42C];
    s16  mA2C;
} Self;

extern char D_0045C798[];
extern char D_0045C7A8[];
/*rgp*/

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
