#include "types.h"
extern s8* D_0047FBF0[3] __attribute__((section(".sdata")));
extern u8* InsectCageMenuGetCursorObj_390f70(void);extern s32 MenuObjCountActive_390ec0(void);extern void PlayMenuSe_289ef0(s32);extern void UiSetWidgetsVisibleById_291110(void*,s32,s32,s32);extern void InsectCageMenuSelectEntry_390d40(s32,s32);
static inline u32 hasA(u8*p){return *(s32*)(p+0x9C4)!=0;}
static inline u32 hasB(u8*p){return *(s32*)(p+0x9C8)!=0;}
s32 InsectCageMenuTopCommandState_38fe00(s8 *arg0, s8 *arg1) {
    u8 *temp_2;
    s32 var_4;
    s32 temp_17;

    temp_2 = InsectCageMenuGetCursorObj_390f70();
    var_4 = 0;
    if (temp_2 != 0) {
        if (hasA(temp_2)) {
            var_4 = 1;
        } else {
            if (hasB(temp_2)) {
                var_4 = 2;
            }
        }
    }
    temp_17 = D_0047FBF0[var_4][*(s16 *)(arg0+0x12)];
    if ((MenuObjCountActive_390ec0() <= 0) && (temp_17 != 3)) {
        PlayMenuSe_289ef0(6);
        return 0;
    }
    UiSetWidgetsVisibleById_291110(arg1, 0x7562, 0, 1);
    UiSetWidgetsVisibleById_291110(arg1, 0x756C, 0, 1);
    PlayMenuSe_289ef0(5);
    switch (temp_17) {
    case 0:
        InsectCageMenuSelectEntry_390d40(0x7533, 0);
        break;
    case 1:
        InsectCageMenuSelectEntry_390d40(0x7534, 0);
        break;
    case 2:
        InsectCageMenuSelectEntry_390d40(0x753A, 1);
        break;
    case 3:
        InsectCageMenuSelectEntry_390d40(0x753E, 1);
        break;
    case 4:
        InsectCageMenuSelectEntry_390d40(0x753F, 0);
        break;
    case 5:
        InsectCageMenuSelectEntry_390d40(0x7540, 0);
        break;
    }
    return 1;
}
