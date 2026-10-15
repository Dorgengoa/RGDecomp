#include "types.h"

typedef struct {
    u8 pad0[0x224];
    s32 p224;
    s32 p228;
    u8 pad22C[0x2F0 - 0x22C];
    u8 *arr4;
    u8 *arr150;
    u8 pad2F8[2];
    s16 n4;
    s16 n150;
    s16 h2FE;
    u8 pad300[0x324 - 0x300];
    f32 f324;
    f32 f328;
    s16 h32C;
    s16 h32E;
} Obj;

extern void *ConstructNewArray_100710(void *, void *, s32, s32, s32);
extern s32 MemStackStrDup_14cff0(s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern s32 EvObjInit_2f9cf0(Obj *, s32, s32, s32, s32, s32);
extern s32 EvMapObjDataGetNodeCount_366ac0(s32);
extern u8 *EvMapObjDataGetNodes_366ad0(s32);
extern s32 EvMapObjDataGetNameRefCount_366af0(s32);
extern u8 *EvMapObjDataGetNameRefs_366b00(s32);
extern s16 EvMapObjGetH32ERelated_366b30(s32);
extern s16 EvMapObjGetBreakSe_366b40(s32);
extern f32 EvMapObjGetScatterSpeedMaybe_366b50(s32);
extern f32 EvMapObjGetRadiusMaybe_366b60(s32);
extern s16 EvMapObjGetId_366b70(s32);
extern s32 EvMapObjGetName_366b90(s32);
extern s32 EvMapObjGetModelName_366ba0(s32);
extern void EvMapObjResetMaybe_366f20();
extern s32 EvMapObjNodeCopy_3673f0(u8 *, u8 *, s32);
extern s32 EvMapNameRefCopy_367530(u8 *, u8 *, s32);
extern void EvMapNameRefCtor_367600(void);
extern void EvMapObjNodeCtor_3674c0(void);

s32 EvMapObjInit_366bc0(Obj *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 n;
    u8 *p;
    s32 i;
    u8 *p2;
    s32 i2;

    EvMapObjResetMaybe_366f20();
    if (arg2 == 0 || arg3 == 0) {
        return 0;
    }
    {
        if (EvObjInit_2f9cf0(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
            return 0;
        }
        if ((arg0->p224 = MemStackStrDup_14cff0(EvMapObjGetModelName_366ba0(arg2), arg3)) == 0) {
            return 0;
        }
        if ((arg0->p228 = MemStackStrDup_14cff0(EvMapObjGetName_366b90(arg2), arg3)) == 0) {
            return 0;
        }
        n = EvMapObjDataGetNameRefCount_366af0(arg2);
        if ((arg0->arr4 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 4 + 0x10, arg3), EvMapNameRefCtor_367600, 0, 4, n)) == 0) {
            return 0;
        }
        arg0->n4 = EvMapObjDataGetNameRefCount_366af0(arg2);
        for (i = 0, p = arg0->arr4; i < arg0->n4; i++, p += 4) {
            if (EvMapNameRefCopy_367530(p, EvMapObjDataGetNameRefs_366b00(arg2) + i * 4, arg3) == 0) {
                return 0;
            }
        }
        n = EvMapObjDataGetNodeCount_366ac0(arg2);
        if ((arg0->arr150 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x150 + 0x10, arg3), EvMapObjNodeCtor_3674c0, 0, 0x150, n)) == 0) {
            return 0;
        }
        arg0->n150 = EvMapObjDataGetNodeCount_366ac0(arg2);
        for (i2 = 0, p2 = arg0->arr150; i2 < arg0->n150; i2++, p2 += 0x150) {
            if (EvMapObjNodeCopy_3673f0(p2, EvMapObjDataGetNodes_366ad0(arg2) + i2 * 0x150, arg3) == 0) {
                return 0;
            }
        }
        arg0->h2FE = EvMapObjGetId_366b70(arg2);
        arg0->f324 = EvMapObjGetRadiusMaybe_366b60(arg2);
        arg0->f328 = EvMapObjGetScatterSpeedMaybe_366b50(arg2);
        arg0->h32C = EvMapObjGetBreakSe_366b40(arg2);
        arg0->h32E = EvMapObjGetH32ERelated_366b30(arg2);
        return 1;
    }
    return 0;
}
