#include "types.h"
#include "vec.h"


extern void *ObjRecGetLiveObject_1c3bc0(void *, s32);
extern void *GetCurrentScene_1f5be0(void);
extern void CameraModePush_3093e0(void *, s32);

void CameraPushTwoTarget_309c30(void *arg0) {
    union {f32 f[4];u32 u[4];u128 q;} sp;
    f32 x,y,z; s32 id,a,b;
    void *temp_2;
    void *temp_2_2;
    void *temp_5;

    temp_2 = GetCurrentScene_1f5be0();
    temp_2_2 = ObjRecGetLiveObject_1c3bc0(temp_2, *(s32 *)((u8 *)temp_2 + 0x4344));
    if (temp_2_2 != NULL) {
        CameraModePush_3093e0(temp_2_2, 4);
        if (*(u8 *)((u8 *)arg0 + 0xA) & 1) {
            temp_5 = *(void **)((u8 *)arg0 + 0x10);
            if (temp_5 != NULL) {
                x = *(f32 *)((u8 *)temp_5 + 0x38);
                y = *(f32 *)((u8 *)temp_5 + 0x3C);
                z = *(f32 *)((u8 *)temp_5 + 0x40);
                id = *(s16 *)((u8 *)arg0 + 0);
                sp.u[3] = 0x3F800000;

                *(s32 *)((u8 *)temp_2_2 + 0x278) = id;
                sp.f[0] = x; sp.f[1] = y; sp.f[2] = z;
                *(u8 *)((u8 *)temp_2_2 + 0x280) = 1;
                *(u128 *)((u8 *)temp_2_2 + 0x290) = sp.q;
                return;
            }
        }
        b = *(s16 *)((u8 *)arg0 + 2);
        a = *(s16 *)((u8 *)arg0 + 0);
        *(s32 *)((u8 *)temp_2_2 + 0x278) = a;
        *(s32 *)((u8 *)temp_2_2 + 0x27C) = b;
        *(u8 *)((u8 *)temp_2_2 + 0x280) = 0;
    }
}
