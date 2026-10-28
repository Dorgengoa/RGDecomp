/* rgp:protos */
#define RGP_SELF_DebugItemIconGridDrawInfo_29a680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(char *arg0, const char *arg1, ...);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_004613B8[];
extern char D_004613C0[];

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 pad8[0x8];
    s32 unk10;
} T29a680_arg0;

void DebugItemIconGridDrawInfo_29a680(T29a680_arg0 *arg0)
{
    char spA0[0x80] __attribute__((aligned(16)));
    char sp20[0x80] __attribute__((aligned(16)));
    char *p;
    u8 *r;
    s32 t;

    if (arg0->unk10 == 0) {
        return;
    }
    if (((s32)GetGameData_1fede0()) == 0) {
        return;
    }
    r = DebugItemIconGridFindItem_29aa10(arg0->unk0 + arg0->unk4, arg0->unk2 + arg0->unk6);
    FontCtxSetup9x15_2085d0(0x338, 2);
    if (r == NULL) {
        return;
    }
    sp20[0] = 0;
    spA0[0] = 0;
    Sprintf_1343b8(spA0, D_004613B8, *(s16 *)(r + 0x0), *(s32 *)(r + 0xC));
    FontDrawTextAtCell_208490(0x12, 0x12C, 0, 0, spA0, 128.0f);
    t = *(s32 *)(r + 0x30);
    if (t == 0) {
        return;
    }
    Sprintf_1343b8(spA0, D_004613C0, t);
    for (p = spA0; *p != 0; p++) {
        if (*p == 0x5C && p[1] == 0x6E) {
            *p = 0;
            Sprintf_1343b8(sp20, D_004613C0, p + 2);
            break;
        }
    }
    FontDrawTextAtCell_208490(0x12, 0x142, 0, 0, spA0, 128.0f);
    FontDrawTextAtCell_208490(0x12, 0x158, 0, 0, sp20, 128.0f);
}
