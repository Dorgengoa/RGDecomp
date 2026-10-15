#include "types.h"

class V1f9bb0 {
public:
    u8 pad0[0x1B0];
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void f(f32);
};


extern "C" s32 ObjRecGetValue_1c3d30(s32 arg0, s32 arg1, s32 arg2);
extern "C" s32 ObjRecIsActiveMaybe_1c4830(s32 arg0, s32 arg1);
extern "C" V1f9bb0 *ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern "C" f32 GameSceneGetTimeStep_1ceba0(s32 arg0);
extern "C" s32 GetCurrentScene_1f5be0(void);

extern "C" void CameraCharaStep_1f9bb0(void)
{
    s32 temp_2;
    f32 temp_f20;
    s32 var_17;
    V1f9bb0 *temp_2_2;

    temp_2 = GetCurrentScene_1f5be0();
    temp_f20 = GameSceneGetTimeStep_1ceba0(temp_2);
    var_17 = 0;
    do {
        if (ObjRecIsActiveMaybe_1c4830(temp_2, var_17) != 0) {
            temp_2_2 = ObjRecGetLiveObject_1c4a90(temp_2, var_17);
            if ((temp_2_2 != NULL) && (ObjRecGetValue_1c3d30(temp_2, 1, var_17) == 5)) {
                temp_2_2->f(temp_f20);
            }
        }
        var_17 += 1;
    } while (var_17 < 0xE0);
}
