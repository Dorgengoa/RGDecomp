/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x00004EBBD0 -- member of the 28-unit C++ virtual-dispatch family whose
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
    VC_VPTR_MEMBER; void init() { VCM0(void, 0x8); }      /* vtable +0x08 -- the first declared virtual */
    
};

/* Alias for the raw vptr write.  `volatile` is what keeps the first store. */
struct IObjRaw {
    s32 f00;
    s32 f04;
    const void *volatile vptr;
    f32 f0C;
    s32 f10;
    f32 f14;
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

extern "C" u8 D_0047D018[];
extern "C" u8 D_0047D008[];
extern "C" IRoot *insect_InsectSeqGetThunk_5108d0(void);
extern "C" void *MemStackNew_14e230(s32 size, void *pool);
extern "C" void insect_InsectSeqCmdQueuePush_4ea5d0(IMgr *m, IObj *o);
extern "C" f32 VariantGetFloat_15f740(Arg *a);
extern "C" char *SlotGetInt_15f720(Arg *a);
extern "C" s32 strcmp(const char *a, const char *b);
extern "C" char insect_D_00524700[];

extern "C" s32 insect_InsectSeqParseMove_4ebbd0(Arg *a, s32 n)
{
    IRoot *p;
    void *pool;
    char *s;
    s32 i;
    IMgr *t;
    IObj *m;
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
            m = (IObj *)MemStackNew_14e230(0x18, pool);
            if (m != 0) {
                ((IObjRaw *)m)->vptr = D_0047D018;
                ((IObjRaw *)m)->vptr = D_0047D008;
            }
            if (m != 0) {
                m->init();
                ((IObjRaw *)m)->f0C = VariantGetFloat_15f740(a++);
                if (n >= 2) {
                    s = SlotGetInt_15f720(a++);
                    for (i = 0; i < 2; i++) {
                        if (strcmp(&insect_D_00524700[i * 16], s) == 0) {
                            ((IObjRaw *)m)->f10 = i;
                            break;
                        }
                    }
                    if (n >= 3) {
                        ((IObjRaw *)m)->f14 = VariantGetFloat_15f740(a);
                    }
                }
                insect_InsectSeqCmdQueuePush_4ea5d0(t, m);
            }
            rv = 1;
        }
    }
    return rv;
}
