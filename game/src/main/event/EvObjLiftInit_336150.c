/* rgp:protos */
#define RGP_SELF_EvObjLiftInit_336150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0xA0];
    u8 sub[0x30];
    u32 flags;
    u8 padD4[0xC];
    u8 *arrA;
    u8 *arrB;
    s16 nA;
    s16 nB;
    s32 resA;
    s32 resB;
    s32 resC;
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

s32 EvObjLiftInit_336150(Obj *self, s32 arg1, void *data, s32 heap, s32 arg4, s32 arg5) {
    u8 *p;
    s32 i;
    s16 n;


    EvObjLiftReset_336500((void *)self);
    if (data == 0 || heap == 0) {
        return 0;
    }
    self->resA = EvObjLiftGetVolumeRec_336140(data);
    if (self->resA == 0) {
        return 0;
    }
    self->resB = EvObjLiftGetPathRec_336130(data);
    if (self->resB == 0) {
        return 0;
    }
    if (EvObjInit_2f9cf0(self, arg1, data, heap, arg4, arg5) == 0) {
        return 0;
    }
    if (self->flags & 0x100000) {
        TargetRefStashId_2e61b0(self->sub);
    }
    if (EvObjLiftGetTargetPairs_3360b0(data) != 0 && ((short)EvObjLiftGetTargetPairCount_3360a0(data)) > 0) {
        n = ((short)EvObjLiftGetTargetPairCount_3360a0(data));
        self->nA = n;
        self->arrA = ((u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x68 + 0x10, heap), TargetRefPairCtor_3370c0, 0, 0x68, n));
        if (self->arrA == 0) {
            return 0;
        }
        p = self->arrA;
        for (i = 0; i < self->nA; i++, p += 0x68) {
            if (TargetRefPairCopy_336ed0(p, ((s32)EvObjLiftGetTargetPairAt_3360c0(data, i)), heap, (self->flags & 0x100000) != 0) == 0) {
                return 0;
            }
        }
    }
    if (EvObjLiftGetTargetSets_336030(data) != 0 && ((short)EvObjLiftGetTargetSetCount_336020(data)) >= 2) {
        n = ((short)EvObjLiftGetTargetSetCount_336020(data));
        self->nB = n;
        self->arrB = ((u8 *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x118 + 0x10, heap), EvTargetSetCtor_336c10, 0, 0x118, n));
        if (self->arrB == 0) {
            return 0;
        }
        p = self->arrB;
        for (i = 0; i < self->nB; i++, p += 0x118) {
            if (EvTargetSetCopy_336780(p, ((s32)EvObjLiftGetTargetSet_336040(data, i)), heap, (self->flags & 0x100000) != 0) == 0) {
                return 0;
            }
        }
    }
    self->resC = ((s32)MemStackStrDup_14cff0(*(s32 *)((u8 *)data + 0xF4), heap));
    return 1;
}
