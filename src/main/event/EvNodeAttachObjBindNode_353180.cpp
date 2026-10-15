#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#undef NULL
#define NULL 0
extern "C" {

typedef struct Item00353180 {
    u8 pad0[0x6C];
    s32 unk6C;
} Item00353180;

typedef struct Obj00353180 Obj00353180;
typedef struct VT00353180 {
    u8 pad0[0x14];
    s32 (*unk14)(Obj00353180 *);
} VT00353180;
struct Obj00353180 {
    u8 pad0[0xD0];
    s32 unkD0;
    u8 padD4[0x8];
    VT00353180 *unkDC;
    u8 padE0[0x10];
    s32 unkF0;
    u8 padF4[0x30];
    Item00353180 *unk124;
    s32 unk128;
};

extern s32 ModelGetFrame_1511f0(s32, s32);
extern s32 ModelFindFrameIndexByName_151220(s32, s32);
extern Item00353180 *NodeObjFindChildByName_195040(s32, s32);
extern s32 GetEventObjMgr_2d1960(...);
extern s32 EventRecGetKey_2e5730(void *);
extern void TargetRefResolve_2e5ed0(void *, s32);
extern s32 TargetRefGetMapObj_2e7050(void *);
extern s32 EventObjMgrFindVolumeRecByName_2e9bc0(s32, s32);
extern void EvObjResolveTarget_2f9a60(...);
extern s32 EvNodeAttachObjGetNodeName_353310(void *);
extern s32 EvNodeAttachObjGetModelName_353320(void *);

class VC_0 {
public:
    u8 pad[0xDC];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual s32 f();
};
s32 EvNodeAttachObjBindNode_353180(Obj00353180 *arg0) {
    s32 temp_17;
    s32 temp_17_2;
    s32 temp_2;
    s32 var_2;
    s32 t;
    Item00353180 *temp_2_2;

    EvObjResolveTarget_2f9a60();
    temp_17 = GetEventObjMgr_2d1960();
    arg0->unkF0 = EventObjMgrFindVolumeRecByName_2e9bc0(temp_17, EventRecGetKey_2e5730((u8 *)arg0 + 0xE0));
    TargetRefResolve_2e5ed0((u8 *)arg0 + 0xF4, 0);
    arg0->unk124 = NULL;
    arg0->unk128 = 0;
    temp_2 = TargetRefGetMapObj_2e7050((u8 *)arg0 + 0xF4);
    if (temp_2 != 0) {
        temp_2_2 = NodeObjFindChildByName_195040(temp_2, EvNodeAttachObjGetModelName_353320(arg0));
        arg0->unk124 = temp_2_2;
        if (temp_2_2 != NULL) {
            t = EvNodeAttachObjGetNodeName_353310(arg0);
            temp_17_2 = arg0->unk124->unk6C;
            arg0->unk128 = ModelGetFrame_1511f0(temp_17_2, ModelFindFrameIndexByName_151220(temp_17_2, t));
        }
    }
    if (!(((VC_0 *)(arg0))->f() & 0xFF)) {
        var_2 = arg0->unkD0 & 0xFDFFFFFF;
    } else {
        var_2 = arg0->unkD0 | 0x02000000;
    }
    arg0->unkD0 = var_2;
    return 1;
}

}
