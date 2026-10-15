#include "types.h"

extern "C" s32 ItemInInvCategory9_3d48e0(void *arg0);
extern "C" s32 ItemInInvCategory0_3d4960(void *arg0);

class Obj3ACF20 {
public:
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
};

extern "C" s32 CharaSetEquipId242_3acf20(Obj3ACF20 *arg0, void *arg1)
{
    if (arg1 == NULL) {
        return 0;
    }
    if ((ItemInInvCategory0_3d4960(arg1) == 0) && (ItemInInvCategory9_3d48e0(arg1) == 0)) {
        return 0;
    }
    *(s16 *)((u8 *)arg0 + 0x242) = *(s16 *)((u8 *)arg1 + 0x4);
    arg0->slot38();
    return 1;
}
