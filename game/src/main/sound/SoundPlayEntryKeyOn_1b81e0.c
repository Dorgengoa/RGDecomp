/* rgp:protos */
#define RGP_SELF_SoundPlayEntryKeyOn_1b81e0 1
#define RGP_SELF_getbank 1
#define RGP_SELF_getent 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    u8 pad0[0x38];
} Ent;

typedef struct {
    u8 pad0[4];
    s32 unk4;
    u8 pad8[0x10];
    Ent ent[5];
    u8 pad[0x1E0 - 0x18 - 0x118];
} Bank;

/*rgp*/
extern s32 D_004814D0;
extern Bank D_0049EB10[];
extern s32 D_004A1E40[];

static inline Bank *getbank(s32 b)
{
    if (b < 0 || b > 16) {
        return NULL;
    }
    return &D_0049EB10[b];
}

static inline Ent *getent(Bank *bk, s32 e)
{
    if (e < 0 || e >= 5) return NULL; return &bk->ent[e];
}

void SoundPlayEntryKeyOn_1b81e0(u32 arg0, s32 arg1, s32 arg2, s64 arg3, s32 arg4, s64 arg5, s64 arg6, s32 arg7)
{
    s32 e;
    s32 a1;
    s32 b;
    Bank *bk;
    s32 snd;
    s32 ok;
    s32 idx;
    Ent *en;

    a1 = arg1;
    if (arg0 == (u32)-1) {
        return;
    }
    b = (arg0 >> 24) & 0xFF;
    e = (arg0 >> 16) & 0xFF;
    snd = arg2;
    bk = getbank(b);
    if (bk == NULL) {
        ok = 0;
    } else {
        en = getent(bk, (arg0 >> 16) & 0xFF);
        if (en == NULL) {
            ok = 0;
        } else {
            snd = bk->unk4;
            idx = e;
            ok = 1;
        }
    }
    if (ok == 0) {
        return;
    }
    if (arg4 < 0) {
        arg4 = 0x7F;
    }
    if (arg3 < 0) {
        arg3 = 0x7F;
    }
    if (snd >= 0 && (u32)snd < 0x10) {
        arg4 = (s32)(arg4 * D_004A1E40[snd]) / 127;
    }
    if (arg7 == -1 || arg7 < 0) {
        D_004814D0 = (D_004814D0 + 1) % 25;
        arg7 = D_004814D0 + 0x66;
    }
    SoundSendCmd_1b6cc0(0x20, 0xA, snd, arg7, idx, a1, 0, arg2, (s32)(arg3), (s32)(arg5), arg4, (s32)(arg6));
}
