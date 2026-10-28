/* rgp:protos */
#define RGP_SELF_MapCfgMapPartsEnd_18b9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3_0018B9A0;

typedef struct {
    u8 pad0[0x130];
    s32 unk130;
} Obj0018B9A0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_00481240;
extern f32 D_00481244;
extern f32 D_00481248;
extern s32 D_00481250;
extern s32 D_0048125C;
extern f32 D_00481270;
extern f32 D_00481274;
extern f32 D_00481278;
extern u8 D_00481280[8];
extern u8 D_00481290[8];
extern u8 D_004812A0[8];
extern u8 D_004812B0[8];
extern s32 D_004812C0;
extern s32 D_004812C4;
extern u8 D_0049CE80[0x80];
extern u8 D_0049CF00[0x80];
extern s8 D_0049CF80[0x80];
extern s8 D_0049D000[0x80];
extern u8 D_0049D080[0xC];
extern f32 D_0049D08C[4];
extern f32 D_0049D090[4];

s32 MapCfgMapPartsEnd_18b9a0(void)
{
    V3_0018B9A0 v __attribute__((aligned(16)));
    Obj0018B9A0 *o;
    s32 h;

    v.x = D_00481270 + D_00481240;
    v.y = D_00481274 + D_00481244;
    v.z = D_00481278 + D_00481248;
    o = ((Obj0018B9A0 *)ObjListInstantiateByName_1890b0(D_00481250, D_0049CF00, &v, D_00481280, D_00481290, D_0048125C));
    if (o == NULL) {
        return 0;
    }
    ModelObjSetName_195150(o, D_0049CE80);
    if (!(D_0049D08C[0] <= 0.0f) || !(D_0049D090[0] <= 0.0f)) {
        FarClipRecCopy_18bbd0(((s32)NodeGetFarClip_18bc20(o)), D_0049D080);
    }
    NodeSetEnabled_18bbc0(o, D_004812C4);
    if (D_004812C0 != 0) {
        h = NodeObjNewShade_18bb70(o, D_0048125C);
        if (h != 0) {
            CopyQwordPair_18bb20(h, D_004812A0, D_004812B0);
        }
    }
    if (D_0049D000[0] != 0) {
        NodeObjSetPartsId_18bb10(o, ((s32)MemStackStrDup_14cff0(D_0049D000, D_0048125C)));
    }
    if (D_0049CF80[0] != 0) {
        o->unk130 = MapPartsGroupAdd_189c00(D_00481250, D_0049CF80, o, D_0048125C);
    }
    return 1;
}
