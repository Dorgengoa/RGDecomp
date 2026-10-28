/* rgp:protos */
#define RGP_SELF_StaticInitMainMenu_46beb0 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0047E5B0;
extern s32 D_0047EBAC;
extern s32 D_00480268;
extern s32 D_0048026C;
extern s32 D_00482310;
extern s32 D_0048231C;
extern s32 D_00482320;
extern s32 D_0048232C;
extern s32 D_004823C0;
extern s32 D_00482400;
extern s32 D_00482404;
extern s32 D_00482408;
extern Obj0029a2a0 D_004DB220;
extern Obj0029a2d0 D_004DB240;
/*rgp*/
/*rgp*/
/*rgp*/

void StaticInitMainMenu_46beb0(void) {
    IosBaseInitCtor_102bd0(&D_0048231C);
    RegisterGlobalObject_100dc0(&D_0048231C, &IosBaseInitDtor_102ee0, &D_00482310);
    WIosBaseInitCtor_103110(&D_0048232C);
    RegisterGlobalObject_100dc0(&D_0048232C, &WIosBaseInitDtor_103420, &D_00482320);
    RegisterGlobalObject_100dc0(&D_004DB220, &DebugItemListDtor_29ace0, &D_004823C0);
    DebugItemIconGridInit_29a2d0(&D_004DB240);
    D_00482400 = D_00480268;
    D_00482404 = D_0048026C;
    D_00482408 = D_0047E5B0;
    D_0047EBAC = D_0047E5B0;
}
