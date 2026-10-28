/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x00004EAE90 -- member of the 15-unit C++ virtual-dispatch family whose
 * exemplar is insect_InsectSeqParseSnailThrow_4ea8a0.  Every member is instruction-identical
 * apart from the derived-vtable address and the allocation size.
 *
 * ⚠ THIS UNIT IS C++.  `lw $25,0x8($16) / lw $25,0x8($25) / jalr $25` is a
 * virtual member call on virtual #0 (slot 8 + 4*0), and no C spelling of an
 * indirect call reaches `jalr $25`.  [[jalr-is-cpp-virtual]]
 *
 * The two `sw` to +0x08 are the base-then-derived vptr writes of an INLINED
 * constructor chain, written as raw stores through an alias struct with a
 * `volatile` member: mwcc dead-stores the first in every non-volatile
 * spelling, and a real C++ constructor would emit OUR vtable into this
 * object's .rodata, which is a link blocker.
 *
 * ★ THE INTEGER-ADD LEVER (measured, ix18b): the pool argument must be
 * spelled `(void *)((s32)t + 4)`, an INTEGER add, not `&t->pool`.  Written as
 * a member address-of, mwcc ranks the SIZE CONSTANT ahead of the address and
 * the two delay slots swap (`bnel` + `addiu $4,$0,size` instead of retail's
 * `bnel` + `addiu $5,$17,4`); written before the guard it SINKS into the slot
 * and the branch degrades to a plain `bne`.  See the report for the 15 inert
 * spellings this was isolated against.
 */

class IObj {
public:
    s32 f00;
    s32 f04;
    VC_VPTR_MEMBER; void init() { VCM0(void, 0x8); }      /* vtable +0x08 -- the first declared virtual */
    
};

/* Alias for the raw vptr write.  `volatile` is what keeps the first store. */
struct IObjRaw {
    s32 f00;
    s32 f04;
    const void *volatile vptr;
};

struct IMgr {
    s32 f00;
    s32 pool;                 /* +0x04 -- its ADDRESS is the allocator's arg */
};

struct IRoot {
    u8 pad00[0x2C];
    IMgr mgr;                 /* +0x2C */
};

extern "C" u8 D_0047D018[];
extern "C" u8 D_0047CEE8[];
extern "C" IRoot *insect_InsectSeqGetThunk_5108d0(void);
extern "C" void *MemStackNew_14e230(s32 size, void *pool);
extern "C" void insect_InsectSeqCmdQueuePush_4ea5d0(IMgr *m, IObj *o);

extern "C" s32 insect_InsectSeqParseReclimed_4eae90(void)
{
    IRoot *p;
    IMgr *t;
    IObj *m;
    void *pool;
    s32 rv;

    p = insect_InsectSeqGetThunk_5108d0();
    if (p == 0) {
        rv = 0;
    } else {
        t = &p->mgr;
        if (t == 0) {
            rv = 0;
        } else {
            pool = (void *)((s32)t + 4);
            m = (IObj *)MemStackNew_14e230(0xC, pool);
            if (m != 0) {
                ((IObjRaw *)m)->vptr = D_0047D018;
                ((IObjRaw *)m)->vptr = D_0047CEE8;
            }
            if (m != 0) {
                m->init();
                insect_InsectSeqCmdQueuePush_4ea5d0(t, m);
            }
            rv = 1;
        }
    }
    return rv;
}
