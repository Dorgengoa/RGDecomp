/* rgp:protos */
#define RGP_SELF_StaticInitCameraObjs_46a5e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O46a5e0 {
    u8 pad00[0xC0];
    void *m0C0;
    u8 padC4[0x180];
    f32 m244;
    f32 m248;
    f32 m24C;
    u8 pad250[0xA0];
} O46a5e0;

extern s32 D_004819F8;
extern s32 D_00481A04;
extern s32 D_00481A08;
extern s32 D_00481A14;
extern f32 D_0047D350;
extern u8 D_004700E0[];
extern u8 D_00471220[];
extern O46a5e0 D_004B5660[6];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StaticInitCameraObjs_46a5e0(void)
{
    IosBaseInitCtor_102bd0(&D_00481A04);
    RegisterGlobalObject_100dc0(&D_00481A04, (void *)IosBaseInitDtor_102ee0, &D_004819F8);
    WIosBaseInitCtor_103110(&D_00481A14);
    RegisterGlobalObject_100dc0(&D_00481A14, (void *)WIosBaseInitDtor_103420, &D_00481A08);
    CameraObjCtor_177430(&D_004B5660[0]);
    D_004B5660[0].m0C0 = D_004700E0;
    D_004B5660[0].m244 = D_0047D350;
    D_004B5660[0].m24C = D_0047D350;
    D_004B5660[0].m248 = 3.0f;
    CameraObjSetDefaults_161d50(&D_004B5660[0]);
    D_004B5660[0].m0C0 = D_00471220;
    CameraObjInit_309ab0(&D_004B5660[0]);
    CameraObjCtor_177430(&D_004B5660[1]);
    D_004B5660[1].m0C0 = D_004700E0;
    D_004B5660[1].m244 = D_0047D350;
    D_004B5660[1].m24C = D_0047D350;
    D_004B5660[1].m248 = 3.0f;
    CameraObjSetDefaults_161d50(&D_004B5660[1]);
    D_004B5660[1].m0C0 = D_00471220;
    CameraObjInit_309ab0(&D_004B5660[1]);
    CameraObjCtor_177430(&D_004B5660[2]);
    D_004B5660[2].m0C0 = D_004700E0;
    D_004B5660[2].m244 = D_0047D350;
    D_004B5660[2].m24C = D_0047D350;
    D_004B5660[2].m248 = 3.0f;
    CameraObjSetDefaults_161d50(&D_004B5660[2]);
    D_004B5660[2].m0C0 = D_00471220;
    CameraObjInit_309ab0(&D_004B5660[2]);
    CameraObjCtor_177430(&D_004B5660[3]);
    D_004B5660[3].m0C0 = D_004700E0;
    D_004B5660[3].m244 = D_0047D350;
    D_004B5660[3].m24C = D_0047D350;
    D_004B5660[3].m248 = 3.0f;
    CameraObjSetDefaults_161d50(&D_004B5660[3]);
    D_004B5660[3].m0C0 = D_00471220;
    CameraObjInit_309ab0(&D_004B5660[3]);
    CameraObjCtor_177430(&D_004B5660[4]);
    D_004B5660[4].m0C0 = D_004700E0;
    D_004B5660[4].m244 = D_0047D350;
    D_004B5660[4].m24C = D_0047D350;
    D_004B5660[4].m248 = 3.0f;
    CameraObjSetDefaults_161d50(&D_004B5660[4]);
    D_004B5660[4].m0C0 = D_00471220;
    CameraObjInit_309ab0(&D_004B5660[4]);
    CameraObjCtor_177430(&D_004B5660[5]);
    D_004B5660[5].m0C0 = D_004700E0;
    D_004B5660[5].m244 = D_0047D350;
    D_004B5660[5].m24C = D_0047D350;
    D_004B5660[5].m248 = 3.0f;
    CameraObjSetDefaults_161d50(&D_004B5660[5]);
    D_004B5660[5].m0C0 = D_00471220;
    CameraObjInit_309ab0(&D_004B5660[5]);
}
