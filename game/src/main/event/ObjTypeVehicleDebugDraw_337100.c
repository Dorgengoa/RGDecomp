/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleDebugDraw_337100 1
#include "port/game_protos.h"
#line 1
#include "types.h"


typedef struct {
    u8 pad0[0xD0];
    s32 unkD0;
    u8 pad0xD4[0x118 - 0xD4];
    s32 unk118;
} Obj00337100;

/*rgp*/
/*rgp*/
extern f32 D_0047F600;
extern f32 D_0047F604;
extern f32 D_0047F608;
extern f32 D_0047F60C;

void ObjTypeVehicleDebugDraw_337100(Obj00337100 *arg0, s32 arg1)
{
    u8 sp40[0x40] __attribute__((aligned(16)));
    f32 sp[4] __attribute__((aligned(16)));

    if ((arg0->unkD0 & 0x02000000) && (arg0->unk118 != 0)) {
        XformGetMatrix_2e7750((u8 *)arg0 + 0x10, sp40);
        sp[0] = D_0047F600;
        sp[1] = D_0047F604;
        sp[2] = D_0047F608;
        sp[3] = D_0047F60C;
        EventVolumeRecDebugDraw_2e49b0(arg0->unk118, arg1, sp40, (s32)&sp[0]);
    }
}
