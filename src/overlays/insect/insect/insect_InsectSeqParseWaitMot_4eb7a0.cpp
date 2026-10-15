#include "types.h"
/* insect 0x00004EB7A0 -- member of the 28-unit C++ virtual-dispatch family whose
 * exemplar is insect_InsectSeqParseSnailThrow_4ea8a0: fetch the manager singleton, allocate an
 * object out of its pool, run the inlined constructor's two vptr stores, call
 * virtual #0, parse the script arguments, register the object.
 *
 * THIS UNIT IS C++.  `lw $25,0x8($16) / lw $25,0x8($25) / jalr $25` is a
 * virtual member call on virtual #0 (slot 8 + 4*0); no C spelling of an
 * indirect call reaches `jalr $25`.  [[jalr-is-cpp-virtual]]
 *
 * The two `sw` to +0x08 are the base-then-derived vptr writes of an INLINED
 * constructor chain, written as raw stores through an alias struct with a
 * `volatile` member (mwcc dead-stores the first otherwise, and a real C++
 * constructor would emit OUR vtable into this object's .rodata).
 *
 * The pool argument MUST be the integer add `(void *)((s32)t + 4)`, not
 * `&t->pool`: written as a member address-of, mwcc ranks the size constant
 * ahead of the address and the two delay slots swap; written before the guard
 * it sinks into the slot and the `bnel` degrades to a plain `bne`.
 */

class IObj {
public:
    s32 f00;
    s32 f04;
    virtual void init();      /* vtable +0x08 -- the first declared virtual */
    virtual void slot0C();
};

/* Alias for the raw vptr write.  `volatile` is what keeps the first store. */
struct IObjRaw {
    s32 f00;
    s32 f04;
    const void *volatile vptr;
    f32 f0C;
};

struct IMgr {
    s32 f00;
    s32 pool;                 /* +0x04 -- its ADDRESS is the allocator's arg */
};

struct IRoot {
    u8 pad00[0x2C];
    IMgr mgr;                 /* +0x2C */
};

/* One script argument slot: the walking cursor advances by 8. */
struct Arg {
    s32 w0;
    s32 w1;
};

extern const u8 D_0047D018[];
extern const u8 D_0047CFA8[];
extern "C" IRoot *insect_InsectSeqGetThunk_5108d0(void);
extern "C" void *func_14E230(s32 size, void *pool);
extern "C" void insect_InsectSeqCmdQueuePush_4ea5d0(IMgr *m, IObj *o);
extern "C" f32 func_15F740(Arg *a);

extern "C" s32 insect_InsectSeqParseWaitMot_4eb7a0(Arg *a, s32 n)
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
            m = (IObj *)func_14E230(0x10, pool);
            if (m != 0) {
                ((IObjRaw *)m)->vptr = D_0047D018;
                ((IObjRaw *)m)->vptr = D_0047CFA8;
            }
            if (m != 0) {
                m->init();
                if (n > 0) {
                    ((IObjRaw *)m)->f0C = func_15F740(a);
                }
                insect_InsectSeqCmdQueuePush_4ea5d0(t, m);
            }
            rv = 1;
        }
    }
    return rv;
}
