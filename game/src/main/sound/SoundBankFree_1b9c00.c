/* rgp:protos */
#define RGP_SELF_GetChan 1
#define RGP_SELF_GetSlot 1
#define RGP_SELF_SoundBankFree_1b9c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
    s32 w28;
    s32 w2C;
    s32 w30;
    s32 w34;
} Slot;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s8 bC;
    s8 bD;
    u8 padE[2];
    s32 w10;
    s32 w14;
    Slot slot[5];
    s32 w130;
    s32 w134;
    u8 pad138[0x14];
    s32 w14C;
    s32 w150;
    s32 w154;
    s32 w158;
    s32 w15C;
    u8 pad160[0x80];
} Chan;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Chan D_0049EB10[0x11];

static inline Chan *GetChan(s32 i)
{
    if (i < 0 || i > 0x10) {
        return NULL;
    }
    return &D_0049EB10[i];
}

static inline Slot *GetSlot(Chan *c, s32 i)
{
    Slot *s;
    if (i < 0 || !(i < 5)) {
        s = NULL;
    } else {
        s = &c->slot[i];
    }
    return s;
}

void SoundBankFree_1b9c00(s32 arg0)
{
    Chan *c;
    Slot *s;
    s32 i;

    c = GetChan(arg0);
    if (c == NULL) {
        return;
    }
    if (c->w8 >= 0) {
        SoundSendCmd_1b6cc0(0xF, 1, c->w8);
        SoundSendCmd_1b6cc0(1, 1, c->w8);
        SoundSendCmd_1b6cc0(2, 1, c->w8);
    }
    if (c->w4 >= 0) {
        SoundSendCmd_1b6cc0(1, 1, c->w4);
        SoundSendCmd_1b6cc0(2, 1, c->w4);
    }
    if (c->w4 >= 0) {
        SoundSendCmd_1b6cc0(0x1A, 1, c->w4);
        SoundSendCmd_1b6cc0(0x19, 1, c->w4);
    }
    if (c->w8 >= 0) {
        SoundSendCmd_1b6cc0(0x1A, 1, c->w8);
        SoundSendCmd_1b6cc0(0x18, 1, c->w8);
    }
    if (c->w14C >= 0) {
        SoundSendCmd_1b6cc0(0x16, 1, c->w14C);
    }
    for (i = 0; i < 5; i++) {
        s = GetSlot(c, i);
        if (s == NULL) {
            break;
        }
        if (s->w0 == 0) {
            continue;
        }
        SoundBankPartRelease_1ba620(arg0, s, 0);
        s->w0 = 0;
        s->w4 = 0;
        s->w8 = 0;
        s->wC = 0;
        s->w10 = -1;
        s->w30 = 0;
        s->w20 = 0;
        s->w18 = 0;
        s->w1C = 0;
        s->w24 = 0;
        s->w34 = 0;
        s->w14 = 0;
        s->w28 = 0;
        s->w2C = 0;
    }
    c = GetChan(arg0);
    if (c != NULL) {
        c->w0 = 0;
        c->w10 = 0x7F;
        c->w14 = 0;
        c->w4 = -1;
        c->w8 = -1;
        c->bC = 0;
        c->bD = 0;
        c->w14C = -1;
        c->w150 = -1;
        c->w154 = 0;
        c->w158 = 0;
        c->w15C = -1;
        SoundBankClearIds_1b9ed0(c);
        c->w134 = 0;
        c->w130 = 0;
        for (i = 0; i < 5; i++) {
            SoundBankPartInit_1b9e90(&c->slot[i]);
        }
    }
}
