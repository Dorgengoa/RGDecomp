/* rgp:protos */
#line 1
#include "types.h"

class VE38A790 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v65(f32 a0) { VCM(void, (void *, f32), 0x10C, a0); }
};

extern "C" f32 GameSceneGetTimeStep_1ceba0(s32);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" void InsectCageMenuGetCurCageItem_391030(void);
extern "C" void *D_00483340;

extern "C" void MenuObjsAnimStepMaybe_38a790(void)
{
    f32 speed;
    VE38A790 *p;
    s32 i;

    speed = 0.5f * GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    i = 0;
    do {
        p = *(VE38A790 **)((u8 *)&D_00483340 + i * 4);
        if (p != NULL) {
            InsectCageMenuGetCurCageItem_391030();
            p->v65(speed);
        }
        i += 1;
    } while (i < 3);
}
