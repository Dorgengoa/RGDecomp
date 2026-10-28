/* rgp:protos */
#define RGP_SELF_ModelObjExReset_1b0a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *, s32, s32);

typedef struct {
    u8 pad0[0x4f0];
    s32 unk4F0;
    u8 pad4F4[0x4];
    s32 unk4F8;
    s32 unk4FC;
    s32 unk500;
    s32 unk504;
    u32 unk508;
    s32 unk50C;
    s32 unk510;
    s32 unk514;
    s32 unk518;
    s32 unk51C;
    u32 unk520;
    u32 unk524;
    s32 unk528;
    u32 unk52C;
    u32 unk530;
    s32 unk534;
    u8 pad538[0x4];
    s32 unk53C;
    s8 unk540;
    u8 pad541[0x3];
    s32 unk544;
    u8 pad548[0xc];
    s32 unk554;
} T1b0a50_arg0;

void ModelObjExReset_1b0a50(void *arg0)
{
    ModelObjExEffectsStop_1b0880(arg0, 0, 1);
    ModelObjInit_1ae420(arg0);
    memset((u8 *)arg0 + 0x4F0, 0, 0x2C);
    ((T1b0a50_arg0 *) arg0)->unk4F0 = -1;
    ((T1b0a50_arg0 *) arg0)->unk4FC = -1;
    ((T1b0a50_arg0 *) arg0)->unk500 = -1;
    ((T1b0a50_arg0 *) arg0)->unk4F8 = 1;
    ((T1b0a50_arg0 *) arg0)->unk504 = 1;
    ((T1b0a50_arg0 *) arg0)->unk508 = 0x3F800000;
    ((T1b0a50_arg0 *) arg0)->unk50C = 0;
    ((T1b0a50_arg0 *) arg0)->unk510 = -1;
    ((T1b0a50_arg0 *) arg0)->unk514 = 0;
    ((T1b0a50_arg0 *) arg0)->unk518 = 0;
    ((T1b0a50_arg0 *) arg0)->unk51C = 0;
    ((T1b0a50_arg0 *) arg0)->unk520 = 0x43200000;
    ((T1b0a50_arg0 *) arg0)->unk524 = 0x44960000;
    ((T1b0a50_arg0 *) arg0)->unk528 = 0;
    ((T1b0a50_arg0 *) arg0)->unk52C = 0x3F800000;
    ((T1b0a50_arg0 *) arg0)->unk530 = 0x3F800000;
    ((T1b0a50_arg0 *) arg0)->unk534 = 0;
    MotionEventListClear_1b4aa0((u8 *)arg0 + 0x568);
    ((T1b0a50_arg0 *) arg0)->unk53C = 0;
    ((T1b0a50_arg0 *) arg0)->unk540 = 0;
    ((T1b0a50_arg0 *) arg0)->unk544 = 0;
    ((T1b0a50_arg0 *) arg0)->unk554 = 0;
}
