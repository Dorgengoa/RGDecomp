/* rgp:protos */
#define RGP_SELF_FileSlotSeek_180ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct Ent {
    u8 used;
    u8 type;
    u8 pad2[2];
    s32 m4;
    u32 m8;
    u8 padC[4];
    u32 m10;
    u8 pad14[0x58];
    u32 pos;
    u32 blk;
    u8 pad74[8];
} Ent;

extern s32 sceLseek_11bd30(s32, u32, s32);
extern void SignalSema(s32);
extern void WaitSema(s32);
extern s32 D_0047E028;
extern s32 D_004811C4;
extern Ent D_0049B100[12];
extern u8 D_0049B178[];

s32 FileSlotSeek_180ed0(s32 arg0, u32 arg1, s32 arg2)
{
    Ent *e;
    u32 blk;
    u32 n;
    u32 off;
    u32 lim;
    s32 r;

    if (arg0 < 0 || arg0 >= 12) {
        e = NULL;
    } else {
        e = &D_0049B100[arg0];
        if (e->used == 0) {
            e = NULL;
        } else if (D_0049B178[arg0 * 0x7C] != 0) {
            e = NULL;
        }
    }
    if (e == NULL) {
        return -1;
    }
    blk = e->blk;
    off = arg1;
    if (blk > 1) {
        n = arg1 / blk;
        if (arg1 % blk != 0) {
            n++;
        }
        off = n * blk;
    }
    switch (e->type) {
    case 0:
        if (D_0047E028 >= 0) {
            WaitSema(D_0047E028);
        }
        D_004811C4++;
        r = sceLseek_11bd30(e->m4, arg1, arg2);
        if (D_0047E028 >= 0) {
            SignalSema(D_0047E028);
        }
        D_004811C4--;
        if (r >= 0) {
            e->pos = r;
        }
        break;
    case 2:
    case 4:
    case 1:
        lim = e->m10 * blk;
        if (e->type == 2) {
            lim = e->m8;
        }
        switch (arg2) {
        case 0:
            e->pos = off;
            break;
        case 1:
            e->pos += off;
            break;
        case 2:
            e->pos = lim + off;
            break;
        }
        if (lim < e->pos) {
            e->pos = lim;
        }
        r = e->pos;
        break;
    default:
        r = -1;
        break;
    }
    return r;
}
