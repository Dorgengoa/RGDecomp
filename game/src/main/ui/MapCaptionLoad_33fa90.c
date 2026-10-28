/* rgp:protos */
#define RGP_SELF_MapCaptionLoad_33fa90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub {
    u8 pad0[4];
    s32 x4;
    u8 *x8;
    s16 xC;
} Sub;

typedef struct Obj {
    u8 pad0[0xC];
    Sub *xC;
    s32 x10;
    s32 x14;
    s32 x18;
    u8 pad1c[4];
    s32 x20;
    u8 x24;
} Obj;

s32 Sprintf_1343b8();
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(s32, char *);
u32 strlen(char *);
extern u8 D_00452EC0[0x400];
extern u8 D_00452F40[0x400];
extern char D_004626E8[0x10];
extern char D_004626F8[0x10];
extern char D_00462708[0x10];
extern char D_00462710[0x10];
extern u8 *D_00482CB0;

s32 MapCaptionLoad_33fa90(Obj *arg0, s32 arg1, s32 arg2, u8 arg3) {
    char spA0[64] __attribute__((aligned(16)));
    char sp60[64] __attribute__((aligned(16)));
    u8 *p;
    u8 *q;
    s32 i;
    u32 n;
    s32 size;
    s32 h;
    s32 cnt;

    if (arg2 == 0) {
        return 0;
    }
    if (arg0->x18 != 0) {
        return 0;
    }
    MapCaptionInit_33fd90((void *)arg0);
    p = ((u8 *)ResGroupListFindValueById_42c4d0(((s32)GetMenuResGroup_206a40()), 0x2E));
    D_00482CB0 = p;
    *(s32 *)(p + 0x20) = 0;
    *(u8 **)(p + 0xB4) = D_00452EC0;
    q = p + 0x128;
    for (i = 0; i <= 0x20; i++) {
        *(u8 **)(q + 0x20) = D_00452F40 + i * 0x40;
        q += 0x94;
    }
    if (arg1 >= 0x1BBC && arg1 < 0x1C21) {
        GetGameData_1fede0();
        n = AlignUp16_1cacd0(0x58) >> 4;
        arg0->x14 = MemStackHeapAllocBack_14dcf0(arg2, 0x2BC0);
        if (arg0->x14 == 0) {
            return 0;
        }
        arg0->x10 = arg2;
        MemStackClear_14dff0(arg0->x14);
        MemStackInit_14d810(arg0->x14, PtrAddAligned16_1cac90(arg0->x14, n << 4), 0x2BC0 - n);
        h = arg0->x14;
        if (strlen(D_004626E8) < 0x10) {
            strcpy(h, D_004626E8);
        }
        MemStackReset_14d830(arg0->x14);
        MemStackAlign64_14d8e0(arg0->x14);
        arg0->xC = ((Sub *)MemStackNew_14e230(0x10, arg0->x14));
        arg0->xC->xC = 0xAF;
        cnt = arg1 - 0x1BBC;
        arg0->xC->x8 = (u8 *)D_004626F8;
        arg0->xC->x4 = MsgGetTextByIndex_279040(0x2D);
        if (cnt > 0) {
            Sprintf_1343b8(spA0, D_00462708, cnt);
            arg0->xC->x4 = ((s32)MemStackStrDup_14cff0(spA0, arg0->x14));
        }
    } else {
        arg0->xC = ((Sub *)GroupGetRecordById_4113e0(*(s32 *)(*(u8 **)(((u8 *)GetGameData_1fede0()) + 8) + 0x34), arg1));
        if (arg0->xC == NULL) {
            return 0;
        }
        arg0->xC->xC = 0xAF;
        n = AlignUp16_1cacd0(0x58) >> 4;
        size = (arg0->xC->xC << 10) >> 4;
        arg0->x14 = MemStackHeapAllocBack_14dcf0(arg2, size);
        if (arg0->x14 == 0) {
            return 0;
        }
        arg0->x10 = arg2;
        MemStackClear_14dff0(arg0->x14);
        MemStackInit_14d810(arg0->x14, PtrAddAligned16_1cac90(arg0->x14, n << 4), size - n);
        h = arg0->x14;
        if (strlen(D_004626E8) < 0x10) {
            strcpy(h, D_004626E8);
        }
        MemStackReset_14d830(arg0->x14);
        MemStackAlign64_14d8e0(arg0->x14);
    }
    if (arg0->xC == NULL) {
        return 0;
    }
    Sprintf_1343b8(sp60, D_00462710);
    LoadHandleRequestFile_1ccbb0(arg0, sp60);
    arg0->x18 = 1;
    arg0->x20 = 0;
    arg0->x24 = arg3;
    return 1;
}
