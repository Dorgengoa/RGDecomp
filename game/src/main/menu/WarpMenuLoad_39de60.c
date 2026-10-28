/* rgp:protos */
#define RGP_SELF_WarpMenuLoad_39de60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xC];
} Item;

typedef struct {
    Item items[2];
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    u8 pad26[2];
    f32 unk28;
    u8 pad2C[0x4];
    s8 unk30;
    u8 pad31[0x1];
    s16 unk32;
    s16 unk34;
} T39de60_arg0;

extern void Sprintf_1343b8(void *, void *, s32);
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
extern char *strcpy(s32, void *);
extern u32 strlen(void *);
extern u8 D_004643F8[];
extern u8 D_00464410[];
extern u8 D_00464430[];

s32 WarpMenuLoad_39de60(T39de60_arg0 *arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4)
{
    u8 buf[2][0x20] __attribute__((aligned(16)));
    u32 n;
    s32 i;
    s32 h;
    s32 t;

    if (arg3 == 0) {
        return 0;
    }
    if (arg0->unk24 != 0) {
        return 0;
    }
    WarpMenuReset_39e020((void *)arg0);
    GetGameData_1fede0();
    n = AlignUp16_1cacd0(0x58) >> 4;
    t = MemStackHeapAllocBack_14dcf0(arg3, 0xA00);
    arg0->unk20 = t;
    if (t == 0) {
        return 0;
    }
    arg0->unk1C = arg3;
    MemStackClear_14dff0(arg0->unk20);
    MemStackInit_14d810(arg0->unk20, PtrAddAligned16_1cac90(arg0->unk20, n << 4), 0xA00 - n);
    h = arg0->unk20;
    if (strlen(D_004643F8) < 0x10) {
        strcpy(h, D_004643F8);
    }
    MemStackReset_14d830(arg0->unk20);
    MemStackAlign64_14d8e0(arg0->unk20);
    if (arg1 == 10) {
        arg1 = 7;
    }
    if (arg2 == 10) {
        arg2 = 7;
    }
    Sprintf_1343b8(buf[0], D_00464410, arg1);
    Sprintf_1343b8(buf[1], D_00464430, arg2);
    for (i = 0; i < 2; i++) {
        LoadHandleRequestFile_1ccbb0(&arg0->items[i], buf[i]);
    }
    arg0->unk24 = 1;
    arg0->unk28 = 1.0f;
    arg0->unk30 = arg4;
    arg0->unk32 = arg1;
    arg0->unk34 = arg2;
    return 1;
}
