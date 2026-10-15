#include "types.h"

/* DataTableCompareThunk_417650 -- ONE 60-byte symbol spanning TWO entry points.
 *   0x00417650   4 words: tail-call of virtual #32 (vptr 0, slot 0x88)
 *   0x00417660  11 words: DataTableResetCounts_368f50(this), then zero m8C / m90
 * There is no symbol at the second entry: the lcf name covers both, and the
 * two `.word 0x00417660` in main_data are the VTABLE slots that reach it.
 * Both functions must come out of ONE translation unit, in this order --
 * mwcc gives each its own `.text`, and the lcf line `<name>.o (.text)`
 * takes them both, in file order.
 * The tail call needs C++: plain C emits `jr $2`, the virtual call `jr $25`.
 * One of 75 byte-identical members of this clone group.
 */

class VE {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
};

extern "C" void DataTableResetCounts_368f50(void *);

extern "C" void DataTableCompareThunk_417650(VE *o)
{
    o->v32();
}

extern "C" void func_00417650_e1(VE *o)
{
    DataTableResetCounts_368f50(o);
    *(s32 *)((u8 *)o + 0x8C) = 0;
    *(s32 *)((u8 *)o + 0x90) = 0;
}
