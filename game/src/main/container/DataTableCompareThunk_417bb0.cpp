/* rgp:protos */
#line 1
#include "types.h"

/* DataTableCompareThunk_417bb0 -- ONE 60-byte symbol spanning TWO entry points.
 *   0x00417BB0   4 words: tail-call of virtual #32 (vptr 0, slot 0x88)
 *   0x00417BC0  11 words: DataTableResetCounts_368f50(this), then zero m8C / m90
 * There is no symbol at the second entry: the lcf name covers both, and the
 * two `.word 0x00417BC0` in main_data are the VTABLE slots that reach it.
 * Both functions must come out of ONE translation unit, in this order --
 * mwcc gives each its own `.text`, and the lcf line `<name>.o (.text)`
 * takes them both, in file order.
 * The tail call needs C++: plain C emits `jr $2`, the virtual call `jr $25`.
 * One of 75 byte-identical members of this clone group.
 */

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" void DataTableResetCounts_368f50(void *);

extern "C" void __attribute__((naked)) DataTableCompareThunk_417bb0(VE *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *136(%eax)"); 

}

extern "C" void func_00417BB0_e1(VE *o)
{
    DataTableResetCounts_368f50(o);
    *(s32 *)((u8 *)o + 0x8C) = 0;
    *(s32 *)((u8 *)o + 0x90) = 0;
}
