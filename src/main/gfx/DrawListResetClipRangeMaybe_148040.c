#include "types.h"
typedef unsigned __int128 u128;

typedef struct Ctx00148040 {
    u8 pad0[0x28];
    u8 *unk28;
    s32 unk2C;
} Ctx00148040;

extern void DmaPktAddCallTag_141b80(void *arg0, void *arg1);
extern Ctx00148040 *DrawListGetCurBuf_142790(void);
extern void MemStackAllocQw_14d950(void *arg0, s32 arg1);

void DrawListResetClipRangeMaybe_148040(void *arg0)
{
    Ctx00148040 *temp_2;
    u8 *temp_18;
    u8 *temp_19;
    u8 *temp_16;

    temp_2 = DrawListGetCurBuf_142790();
    if (temp_2 != NULL) {
        temp_16 = temp_2->unk28 + (temp_2->unk2C * 0x10);
        if (temp_16 != NULL) {
            *(u128 *) (temp_16 + 0x0) = 0;
            *(s32 *) (temp_16 + 0x0) = 0x60000002;
            *(s32 *) (temp_16 + 0x8) = 0x01000101;
            *(s32 *) (temp_16 + 0xC) = 0x6C020062;
            temp_19 = temp_16 + 0x10;
            temp_18 = temp_16 + 0x20;
            MemStackAllocQw_14d950(temp_2, 3);
            *(s32 *) (temp_19 + 0x0) = 0x4B800000;
            *(s32 *) (temp_19 + 0x4) = 0x4B800000;
            *(s32 *) (temp_19 + 0x8) = 0x4B800000;
            *(s32 *) (temp_19 + 0xC) = 0x4B800000;
            *(s32 *) (temp_18 + 0x0) = 0xCB800000;
            *(s32 *) (temp_18 + 0x4) = 0xCB800000;
            *(s32 *) (temp_18 + 0x8) = 0xCB800000;
            *(s32 *) (temp_18 + 0xC) = 0xCB800000;
            DmaPktAddCallTag_141b80(arg0, temp_16);
            *(s32 *) ((u8 *) arg0 + 0x3CCC) = 1;
        }
    }
}
