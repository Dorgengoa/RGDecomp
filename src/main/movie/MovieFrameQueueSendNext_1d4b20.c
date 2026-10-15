#include "types.h"

typedef struct Struct001d4b20 {
    s32 unk0;
    u8 pad4[0x40 - 0x4];
    s32 unk40;
} Struct001d4b20;

extern void sceDmaSend_10a040(s32 a, s32 b);
extern void sceDmaSync_10a2e0(s32 a, s32 b, s32 c);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern void VoBufDecCount_1d48a0(void *a);
extern Struct001d4b20 *VoBufGetTag_1d4940(void *a);
extern s32 sceDmaGetChan(s32 a);

extern s32 D_004817A0;
extern volatile u8 D_004817D8;
extern u8 D_004B3330[0x20];

void MovieFrameQueueSendNext_1d4b20(void)
{
    s32 temp_17;
    Struct001d4b20 *temp_2;

    temp_2 = VoBufGetTag_1d4940(D_004B3330);
    if (temp_2 == NULL) {
        D_004817A0 += 1;
        return;
    }
    DrawCtxVif1HandlerStop_15dc40();
    temp_17 = sceDmaGetChan(2);
    if (temp_2->unk0 == 2) {
        sceDmaSend_10a040(temp_17, temp_2->unk40);
        sceDmaSync_10a2e0(temp_17, 0, 0);
        temp_2->unk0 = 3;
        D_004817D8 = 1;
        if (D_004817D8 != 0) {
            VoBufDecCount_1d48a0(D_004B3330);
            D_004817D8 = 0;
        }
    }
}
