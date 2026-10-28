/* rgp:protos */
#define RGP_SELF_WorldDataMgrReset_3f1c60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item003f1c60 {
    u8 pad0[0x28];
    u8 *unk28;
    s32 unk2C;
    u8 pad30[4];
    s32 unk34;
} Item003f1c60;

typedef struct S003f1c60 {
    u8 pad0[0x6C];
    s32 unk6C;
    u8 pad70[8];
    s32 unk78;
    u8 pad7C[4];
    s32 unk80;
} S003f1c60;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *dst, s32 val, s32 n);
extern void strcpy(void *dst, char *src);
extern u32 strlen(char *arg0);
extern s32 D_004644A8[];
extern char D_00466D38[16];

void WorldDataMgrReset_3f1c60(S003f1c60 *arg0)
{
    Item003f1c60 *it;
    s32 n;
    s32 i;

    WorldDataMgrFreeHandleEntryRes_3f2190(arg0);
    if (arg0->unk6C != 0) WorldSubsysZoneEntryReleaseAll_41c390(arg0->unk6C);
    if (arg0->unk80 != 0) WorldSubsysZoneEntryReleaseAll_41e1c0(arg0->unk80);
    if (arg0->unk78 != 0) WorldSubsysZoneEntryReleaseAll_426ea0(arg0->unk78);
    n = D_004644A8[0];
    for (i = 0; i < n; i++) {
        it = ((Item003f1c60 *)MemStackArrayGet_3f2390(arg0, i));
        if (it != 0) {
            MemStackReset_14d830(it);
            if (strlen(D_00466D38) < 0x10U) {
                strcpy(it, D_00466D38);
            }
            memset(it->unk28 + it->unk2C * 0x10, 0, (it->unk34 - it->unk2C) * 0x10);
        }
        it = ((Item003f1c60 *)MemStackArrayGet_3f23f0(arg0, i));
        if (it != 0) {
            MemStackReset_14d830(it);
        }
    }
}
