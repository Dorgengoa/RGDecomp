/* rgp:protos */
#define RGP_SELF_AmixerCfgParse_1700d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Reader0015f140 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x2C - 0x18];
    s32 unk2C;
    s32 unk30;
    u8 padTail[0xED0 - 0x34];
} Reader0015f140;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0044A400[];
extern s32 D_00481188;
extern s32 D_0048118C;
extern s32 D_00481190;
extern s32 D_00481194;
extern s32 D_00481198;
extern s32 D_0048119C;
extern s32 D_004811A0;
extern s32 D_004811A4;

void AmixerCfgParse_1700d0(s32 arg0, u8 *arg1, s32 arg2, s32 arg3)
{
    Reader0015f140 sp30 __attribute__((aligned(16)));

    if (arg0 == 0 || arg3 == 0 || arg2 == 0) {
        return;
    }
    D_00481188 = arg0;
    D_0048118C = arg3;
    D_00481190 = 0;
    D_00481194 = 0;
    D_00481198 = 0;
    D_0048119C = 0;
    D_004811A4 = 0;
    D_004811A0 = 0;
    TextReaderCtor_15f140(&sp30);
    BuildKeywordHashTable_15f270(&sp30, D_0044A400);
    TextReaderOpen_15f1b0(&sp30, arg1, arg2);
    TextReaderParseAll_15f3f0(&sp30);
}
