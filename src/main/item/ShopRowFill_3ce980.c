#include "types.h"

struct Obj0;
struct Obj0 {
    s32 m0;
    void *m4;
    s16 m8;
    s16 mA;
};

struct Obj1;
struct Obj1 {
    u8 pad000[0x2];
    s16 m2;
};

struct Obj2;
struct Obj2 {
    u8 pad000[0x18];
    s32 m18;
};

extern s32 InvAddItemCoreMaybe_3c6540(s32, s16, s32, s32, s32, s32, s32);
extern void ShopRowClear_3cea30(void);
extern struct Obj2 *D_00483910;

s32 ShopRowFill_3ce980(struct Obj0 *arg0, struct Obj1 *arg1, s16 arg2, s16 arg3) {
    s32 temp_2;

    if (arg1 == NULL) {
        return 0;
    }
    ShopRowClear_3cea30();
    if (D_00483910 == NULL) {
        return 0;
    }
    temp_2 = InvAddItemCoreMaybe_3c6540(D_00483910->m18, arg1->m2, 8, 1, -1, 0, 0);
    arg0->m0 = temp_2;
    if (temp_2 == 0) {
        return 0;
    }
    arg0->m4 = arg1;
    arg0->m8 = arg2;
    arg0->mA = arg3;
    return 1;
}
