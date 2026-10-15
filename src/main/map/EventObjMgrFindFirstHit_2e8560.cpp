#include "types.h"
extern "C" {

class C {
public:
    u8 pad[0xDC];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual s32 f(s32, s32, s32, s32, s32);
};

s32 GetGameModePhase_1f59b0(void);
s32 GetGameMode_1f59c0(void);
s32 TaskIsEnabled_27c2c0(void *);
u8 *DListGetHead_42ea60(u8 *);
u8 *DListGetNext_42eb30(u8 *);
extern u8 D_004619D8[];

void *EventObjMgrFindFirstHit_2e8560(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 t;
    s32 i;
    u8 *p;

    for (i = 0; i < 0x10; i++) {
        if (i == 9) {
            switch (GetGameMode_1f59c0()) {
            case 0x11:
                if (GetGameModePhase_1f59b0() < 400 || TaskIsEnabled_27c2c0(D_004619D8) == 0) {
                    continue;
                }
            case 6:
                break;
            default:
                continue;
            }
        }

        p = DListGetHead_42ea60((u8 *)(arg0 + (i * 0x10) + 0x50));
        while (p != NULL) {
            if (((C *)(p + 0x10))->f(arg1, arg2, arg3, arg4, arg5) != 0) {
                return p + 0x10;
            }
            p = DListGetNext_42eb30(p);
        }
    }
    return NULL;
}

}
