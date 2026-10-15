#include "types.h"

typedef struct Obj0029a2a0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s16 m18;
    u8 m1A;
    u8 m1B;
} Obj0029a2a0;

typedef struct Obj0029a2d0 {
    s16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    s32 m08;
    u8 pad00C[0x4];
    s32 m10;
} Obj0029a2d0;

extern void RegisterGlobalObject_100dc0(void *, void *, void *);
extern void IosBaseInitCtor_102bd0(void *);
extern void WIosBaseInitCtor_103110(void *);
extern void DebugItemIconGridInit_29a2d0(Obj0029a2d0 *);
extern s32 D_0047E5B0;
extern s32 D_0047EBAC;
extern s32 D_00480268;
extern s32 D_0048026C;
extern s32 D_00482D50;
extern s32 D_00482D5C;
extern s32 D_00482D60;
extern s32 D_00482D6C;
extern s32 D_004823C0;
extern s32 D_00482400;
extern s32 D_00482404;
extern s32 D_00482408;
extern Obj0029a2a0 D_004DB220;
extern Obj0029a2d0 D_004DB240;
extern void IosBaseInitDtor_102ee0(void);
extern void WIosBaseInitDtor_103420(void);
extern void DebugItemListDtor_29ace0(void);

extern s32 D_004E8960[0x100],D_004E8964[0x100],D_004E8968[0x100],D_004E8D90[0x100];
void StaticInitLoadingScreen_46d360(void){
 IosBaseInitCtor_102bd0(&D_00482D5C);
 RegisterGlobalObject_100dc0(&D_00482D5C, &IosBaseInitDtor_102ee0, &D_00482D50);
 WIosBaseInitCtor_103110(&D_00482D6C);
 RegisterGlobalObject_100dc0(&D_00482D6C, &WIosBaseInitDtor_103420, &D_00482D60);
 D_004E8960[0]=-1;D_004E8964[0]=0;D_004E8968[0]=0;D_004E8D90[0]=0;
}
