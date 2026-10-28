/* rgp:protos */
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EC7E0 -- TWO functions in one 0x138-byte unit.
 *
 * 0x004EC7E0 is a four-word VIRTUAL TAIL CALL:
 *     lw $25,0x0($4) / lw $25,0x10($25) / jr $25 / nop
 * `$25` is unreachable from C ([[jalr-is-cpp-virtual]]), so the whole unit is
 * .cpp.  Slot 0x10 is index (0x10 - 8) / 4 = 2, so two placeholder virtuals
 * then the real one, and the `jr` (not `jalr`) is the -O4 tail call of a void
 * member that forwards `this` unchanged.
 *
 * 0x004EC7F0 has NO glabel -- nothing in .text references it, only a table in
 * .data -- so it lands inside this symbol's size instead of getting its own.
 * It is scored as part of the same .text, hence the second definition here.
 *
 * Its guard is `beqz $8`, i.e. PARAMETER FIVE under the PS2 EABI ($4..$11);
 * parameters two through four are never read.
 *
 * The 64-bit third argument of func_13EC80 is four s32s widened one at a time
 * (`dsll32/dsra32 ..,0` -- the s32 -> s64 widening pair) and OR'd at 0/16/32/48,
 * so the source is `(s64)x0 | ((s64)x1<<16) | ((s64)y0<<32) | ((s64)y1<<48)`.
 *
 * ** THE ACCUMULATOR MUST BE A NAMED LOCAL.  Written as ONE four-term
 * expression the whole unit is exact except the last `or`, which comes out
 * `or $6,$2,$3` against retail's `or $6,$3,$2` -- mwcc canonicalises the final
 * commutative operand pair the other way round.  Splitting the first three
 * terms into `v` and passing `v | ((s64)y1 << 48)` fixes it, 1 bad -> 0.
 * MEASURED INERT on that one word: `v |= term;` four times (14 bad); the whole
 * expression reversed (22 bad); `((s64)y1<<48) | (three-term group)` (1 bad,
 * unchanged); `(x0|x1<<16) | (y0<<32|y1<<48)` (19 bad); a named local for the
 * y1 TERM instead of for the accumulator (1 bad, unchanged).
 *
 * ! mwcc emits ONE `.text` SECTION PER FUNCTION, so this two-function unit
 * produces two.  `scripts/bytecheck.py` takes `names.index(".text")` -- the
 * FIRST -- and pairs it with the wrong `.rel.text`, so `pk_obytecheck.score_obj`
 * raises `struct.error` on this object instead of scoring it.  Score it with
 * `python build/fy22I_mtscore.py factory factory_FactoryRelated_4ec7e0 build/obj-<tag>/factory_FactoryRelated_4ec7e0.o`,
 * which concatenates every .text and relocates each with its own .rel.text.
 */

struct Win {
    VC_VPTR_MEMBER;
    
    
};

typedef struct Rect {
    u8  pad00[0xAC];
    s32 fAC;
    s32 fB0;
    s32 fB4;
    s32 fB8;
} Rect;

extern "C" Rect *D_00484A4C;                    /* _gp - 0x724 */

extern "C" void  GsPktOpenPrim_13f730(void *o, s32 a);
extern "C" void  GsPktWriteAD_13ec80(void *o, s32 a, s64 v);
extern "C" void  GsPktClose_13f5b0(void *o);
extern "C" void *GetDrawCtx_15de80(void);
extern "C" s32   DrawEnvGetWidth_1451e0(void *h);
extern "C" s32   DrawEnvGetHeight_1451d0(void *h);

extern "C" void factory_FactoryRelated_4ec7e0(Win *p);

void __attribute__((naked)) factory_FactoryRelated_4ec7e0(Win *p)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *16(%eax)"); 

}

extern "C" s32 factory_sub_004EC7F0(void *o, s32 a, s32 b, s32 c, s32 mode);

s32 factory_sub_004EC7F0(void *o, s32 a, s32 b, s32 c, s32 mode)
{
    Rect *r;
    s32   x0;
    s32   y0;
    s32   x1;
    s32   y1;
    void *h;
    s32   w;
    s32   t;
    s64   v;

    if (mode != 0) {
        GsPktOpenPrim_13f730(o, 6);
        r = D_00484A4C;
        x0 = r->fAC + 0x11;
        y0 = r->fB0 + 0x39;
        x1 = x0 + (r->fB4 + 1);
        y1 = y0 + (r->fB8 + 1);
        v = (s64)x0 | ((s64)x1 << 16) | ((s64)y0 << 32);
        GsPktWriteAD_13ec80(o, 0x40, v | ((s64)y1 << 48));
        GsPktClose_13f5b0(o);
    } else {
        h = GetDrawCtx_15de80();
        w = DrawEnvGetWidth_1451e0(h);
        t = DrawEnvGetHeight_1451d0(h);
        GsPktOpenPrim_13f730(o, 6);
        GsPktWriteAD_13ec80(o, 0x40, (s64)0 | ((s64)(w - 1) << 16) | ((s64)0 << 32) |
                             ((s64)(t - 1) << 48));
        GsPktClose_13f5b0(o);
    }
    return 1;
}
