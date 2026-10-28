/* rgp:protos */
#define RGP_SELF_SceneCamerasInit_1f6c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S001f6c10 {
    u8 pad0[0x4344];
    s32 unk4344;
} S001f6c10;

extern u8 D_004B5660[0x2F0];
extern u8 D_004B5950[0x2F0];
extern u8 D_004B5C40[0x2F0];
extern u8 D_004B5F30[0x2F0];
extern u8 D_004B6220[0x2F0];
extern u8 D_004B6510[0x2F0];
extern s8 D_00481A18;
extern s8 D_00481A1C;
extern s32 D_00481A20;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void SceneCamerasInit_1f6c10(void)
{
    S001f6c10 *self;

    self = ((S001f6c10 *)GetCurrentScene_1f5be0());
    ObjRecTableBindSlot_1c3c10(self, 0, &D_004B5660, 0);
    ObjRecTableBindSlot_1c3c10(self, 1, &D_004B5950, 0);
    ObjRecTableBindSlot_1c3c10(self, 2, &D_004B5C40, 0);
    ObjRecTableBindSlot_1c3c10(self, 3, &D_004B5F30, 0);
    ObjRecTableBindSlot_1c3c10(self, 4, &D_004B6220, 0);
    ObjRecTableBindSlot_1c3c10(self, 5, &D_004B6510, 0);
    self->unk4344 = 1;
    CameraObjInit_309ab0(&D_004B5660);
    CameraObjInit_309ab0(&D_004B5950);
    CameraSetDefaultParams_309260(&D_004B5950);
    CameraObjInit_309ab0(&D_004B5C40);
    CameraObjInit_309ab0(&D_004B5F30);
    CameraObjInit_309ab0(&D_004B6220);
    CameraObjInit_309ab0(&D_004B6510);
    D_00481A18 = 0;
    D_00481A1C = 0;
    D_00481A20 = 0;
    CameraModeSetTop_309440(&D_004B5950, 0);
    CameraModeSetTop_309440(&D_004B6220, 0);
}
