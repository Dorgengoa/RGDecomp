#include "types.h"
/* insect 0x00510D20 -- 116 bytes, 29 instructions.  Allocate the pool's
 * element array: n elements of 0x10 bytes plus a 0x10-byte header.
 *
 * ix34s08: the residue was a three-word ROTATION at 0x510D48 --
 *   retail  sw $a1,0($s1) / lw $a1,4($s1) / sll $v0,$s0,4   (STORE, ARG2, ARG1)
 *   ours    sll $v0,$a1,4 / sw $s0,0($s1) / lw $a1,4($s1)   (ARG1, STORE, ARG2)
 * `n` has two webs (the incoming $a1 and the callee-saved $s0 it needs to
 * survive the call), and whichever use is emitted FIRST consumes $a1.  The
 * u32->s32 CONVERSION NODE decides which use that is: with `s32 f0` the node
 * sits on the store, so the shift owns the parameter's own web and is hoisted
 * above it.  Declaring the member `u32` and writing the cast at the SHIFT
 * instead moves the node onto the size operand -- the store becomes the first
 * consumer of $a1 and the shift reads $s0, which is retail exactly.
 * NEITHER EDIT PAYS ALONE: `u32 f0` by itself is 9 bad, `(s32)n` by itself is
 * 3 bad with callee[s0>a1:1].  41 arms, 15 distinct objects. */

typedef struct Pool {
    u32   f0;                       /* +0x00 */
    void *f4;                       /* +0x04 */
    void *f8;                       /* +0x08 */
    s32   fC;                       /* +0x0C */
} Pool;

extern void *func_14E1B0(s32 size, void *heap);
extern void *func_100710(void *p, void *f, s32 c, s32 d, s32 e);

s32 insect_InsectHelpAllocEntries_510d20(Pool *p, u32 n)
{
    if (p->f4 == 0) {
        return 0;
    }
    p->f0 = n;
    p->f8 = func_100710(func_14E1B0(((s32)n * 0x10) + 0x10, p->f4), 0, 0, 0x10, n);
    p->fC = 0;
    return 1;
}
