#include "types.h"

/* TWO defects, and the missing-argument screen found the second one:
   (1) `jalr $25` = C++ virtual, vptr +0xC0, slot 0xA4 = virtual #39
       ([[levers.d/jalr-is-cpp-virtual]]);
   (2) ObjRecGetLiveObject_1c3bc0 takes TWO arguments -- retail loads the 0x4344 field into
       `$a1`, leaving `$a0` holding arg0. Declared with one, it is 4 bad. */

class VE1C4FC0 {
public:
    u8 pad000[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void v39(void *v);
};
extern "C" {
void VecNormalize_13bd90(void *, void *);
void VecScale_13be00(void *, void *, f32);
void TimeOfDaySunDir_18d2d0(void *, void *);
VE1C4FC0 *ObjRecGetLiveObject_1c3bc0(void *, s32);
void *ObjRecGetLiveObject_1c5250(void *, s32);
}

extern "C" void SceneGetSunPos_1c4fc0(void *arg0, void *arg1)
{
    f32 sp30[4];
    VE1C4FC0 *temp_2;
    void *temp_2_2;

    *(__int128 *)sp30 = 0;
    temp_2 = ObjRecGetLiveObject_1c3bc0(arg0, *(s32 *)((u8 *)arg0 + 0x4344));
    if (temp_2 != NULL) {
        temp_2->v39(sp30);
    }
    temp_2_2 = ObjRecGetLiveObject_1c5250(arg0, *(s32 *)((u8 *)arg0 + 0x434C));
    if (temp_2_2 != NULL) {
        TimeOfDaySunDir_18d2d0(temp_2_2, arg1);
        VecNormalize_13bd90(arg1, arg1);
        VecScale_13be00(arg1, arg1, (f32)0x1388);
        *(f32 *)((u8 *)arg1 + 0) = *(f32 *)((u8 *)arg1 + 0) + sp30[0];
        *(f32 *)((u8 *)arg1 + 4) = *(f32 *)((u8 *)arg1 + 4) + *(f32 *)((u8 *)temp_2_2 + 0x204);
        *(f32 *)((u8 *)arg1 + 8) = *(f32 *)((u8 *)arg1 + 8) + sp30[2];
    }
}
