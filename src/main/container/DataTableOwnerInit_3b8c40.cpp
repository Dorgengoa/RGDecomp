#include "types.h"

/* jalr $25 (jalr-is-cpp-virtual lever): this=var_2 directly (K=0), slot
   0xC -> N=(0xC-8)/4=1. D_004658B8 needs an INCOMPLETE array declaration
   to force %hi/%lo addressing -- a scalar or a <=8-byte array both fall
   under mwcc's small-data threshold and go %gp_rel (im-gp-array-sdata-
   threshold lever). */

class VE {
public:
    virtual s32 v0();
    virtual s32 v1(s32, s32, s32, s32);
};

extern "C" void *MemStackNew_14e130(s32);
extern "C" VE *DataTableCtor_3ba020(void *);
extern "C" s32 D_004658B8[];

extern "C" s32 DataTableOwnerInit_3b8c40(void *arg0, s32 arg1)
{
    VE *var_2;

    if (arg1 == 0) {
        return 0;
    }
    *(s32 *)((u8 *)arg0 + 0) = arg1;
    var_2 = (VE *) MemStackNew_14e130(0xA4);
    if (var_2 != NULL) {
        var_2 = DataTableCtor_3ba020(var_2);
    }
    *(VE **)((u8 *)arg0 + 0xC) = var_2;
    if (var_2 == NULL) {
        return 0;
    }
    return var_2->v1(*(s32 *)((u8 *)arg0 + 0), 0, D_004658B8[0] != 0, 0) & 0xFF;
}
