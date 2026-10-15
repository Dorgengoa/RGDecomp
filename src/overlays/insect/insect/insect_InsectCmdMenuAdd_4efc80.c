#include "types.h"
/* insect 0x004EFC80 -- 192 bytes, 48 instructions.  Allocates a node, fills it
 * from the indexed word of the owner's table and appends it to the owner's
 * singly-linked list.
 *
 * The list walk's back edge is an unconditional `b` with the advance in its
 * delay slot and the test at the TOP, so it is `for (;;) { t = p->f04;
 * if (t == 0) break; p = t; }` and not a `while` (the ixa04 back-edge tell);
 * mwcc then tail-duplicates the post-loop store into the exit `bnel`'s slot.
 * The index parameter is s32, not s8: an s8 would cost a `dsll32`/`dsra32`
 * re-extension in front of the `sll $2, $18, 2`.
 *
 * The exit test is `sltu $2, $0, $3` + `xori $2, $2, 1` + `bnel $2, $0` -- a
 * MATERIALISED boolean, two words more than the `beqzl $3` every equality
 * spelling gives.  It is a NEGATED POINTER RELATIONAL: `!(t > (Node *)0)`.
 * `t == 0`, `!(t != 0)`, `(t != 0) == 0`, `!t`, `z = (t != 0); if (!z)` and
 * `z = (t == 0); if (z)` are ALL one inert object (80e378c4), two words short.
 */

typedef struct Node {
    s32          f00;               /* +0x00 */
    struct Node *f04;               /* +0x04 */
    s8           f08;               /* +0x08 */
    u8           pad09[0xC - 0x9];
    s32          f0C;               /* +0x0C */
} Node;

typedef struct Own {
    void *f00;                      /* +0x00 */
    Node *f04;                      /* +0x04 */
    s32   f08[1];                   /* +0x08 */
} Own;

extern s32   func_14DB10(void *h, s32 a, s32 b, s32 c);
extern void *func_14E230(s32 n, void *h);
extern void  func_14DAD0(void *h);
extern void  insect_InsectCmdMenuEntryInit_4efd90(Node *n);

void insect_InsectCmdMenuAdd_4efc80(Own *o, s32 i)
{
    s32   e;
    Node *n;
    Node *p;
    Node *t;

    if (o->f00 != 0) {
        e = func_14DB10(o->f00, 2, 0, 0x40);
        if (e != 0) {
            n = (Node *)func_14E230(0x10, o->f00);
            insect_InsectCmdMenuEntryInit_4efd90(n);
            n->f00 = o->f08[i];
            n->f0C = e;
            n->f08 = i;
            p = o->f04;
            if (p != 0) {
                for (;;) {
                    t = p->f04;
                    if (!(t > (Node *)0)) {
                        break;
                    }
                    p = t;
                }
                p->f04 = n;
            } else {
                o->f04 = n;
            }
            func_14DAD0(o->f00);
        }
    }
}
