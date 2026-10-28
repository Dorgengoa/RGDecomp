/* rgp:protos */
#line 1
/* ContainerViewGetAtFwd_404e50 -- byte-identical clone of EffTexUvRandParamApply_19a540 (24 B), symbol renamed,
   nothing else changed.  Group verified by sha1 over the
   retail bytes; see build/zz/s23_bhash.json. */
#include "types.h"

/* Head of an 8-member byte-identical group (24 B each):
   ContainerViewGetAtFwd_404e50 / ContainerViewGetAtFwd_3f61d0 / ContainerViewGetAtFwd_3fbcf0 / ContainerViewGetAtFwd_3fcb80 /
   ContainerViewGetAtFwd_401e00 / ContainerViewGetAtFwd_404e30 / ContainerViewGetAtFwd_404e50 / ContainerViewGetAtFwd_404e70.

   ONE symbol, TWO entry points -- 4 words of virtual tail-call thunk then a
   2-word `return 0` with no symbol of its own.  mwcc gives each function its
   own `.text`; the two sizes SUM to retail's 0x18.  See
   [[mwcc-section-per-function]].  The tail call needs C++: plain C emits
   `jr $2`, a virtual `jr $25`.  Slot 0x10 == 4 * (2 + 2), so index 2. */

class V19A540 {
public:
    VC_VPTR_MEMBER;
    
    
};

extern "C" void __attribute__((naked)) ContainerViewGetAtFwd_404e50(V19A540 *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" s32 func_00404E50_e1(void)
{
    return 0;
}
