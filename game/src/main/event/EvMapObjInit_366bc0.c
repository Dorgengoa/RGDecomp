/* rgp:protos */
#define RGP_SELF_EvMapObjInit_366bc0 1
#include "port/game_protos.h"
#line 1
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

s32 EvMapObjInit_366bc0(Obj *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 n;
    u8 *p;
    s32 i;
    u8 *p2;
    s32 i2;

    EvMapObjResetMaybe_366f20((void *)arg0);
    if (arg2 == 0 || arg3 == 0) {
        return 0;
    }
    {
        if (EvObjInit_2f9cf0(arg0, arg1, arg2, arg3, arg4, arg5) == 0) {
            return 0;
        }
        if ((arg0->p224 = ((s32)MemStackStrDup_14cff0(EvMapObjGetModelName_366ba0(arg2), arg3))) == 0) {
            return 0;
        }
        if ((arg0->p228 = ((s32)MemStackStrDup_14cff0(EvMapObjGetName_366b90(arg2), arg3))) == 0) {
            return 0;
        }
        n = ((short)EvMapObjDataGetNameRefCount_366af0(arg2));
        if ((arg0->arr4 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 4 + 0x10, arg3), EvMapNameRefCtor_367600, 0, 4, n)) == 0) {
            return 0;
        }
        arg0->n4 = ((short)EvMapObjDataGetNameRefCount_366af0(arg2));
        for (i = 0, p = arg0->arr4; i < arg0->n4; i++, p += 4) {
            if (EvMapNameRefCopy_367530(p, ((u8 *)EvMapObjDataGetNameRefs_366b00(arg2)) + i * 4, arg3) == 0) {
                return 0;
            }
        }
        n = ((short)EvMapObjDataGetNodeCount_366ac0(arg2));
        if ((arg0->arr150 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x150 + 0x10, arg3), EvMapObjNodeCtor_3674c0, 0, 0x150, n)) == 0) {
            return 0;
        }
        arg0->n150 = ((short)EvMapObjDataGetNodeCount_366ac0(arg2));
        for (i2 = 0, p2 = arg0->arr150; i2 < arg0->n150; i2++, p2 += 0x150) {
            if (EvMapObjNodeCopy_3673f0(p2, ((u8 *)EvMapObjDataGetNodes_366ad0(arg2)) + i2 * 0x150, arg3) == 0) {
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
