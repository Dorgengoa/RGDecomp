#include "types.h"
/* insect 0x0050A1E0 -- 33 instructions.  A byte counter stepped toward a target
 * by a signed per-frame delta, snapping (and clearing the delta) on arrival.
 *
 * Both member addresses are MATERIALISED (`addiu $8,$4,0x5EAC`,
 * `addiu $6,$4,0x5EEF`) because `lbu $4,0x5EEF($4)` kills the object pointer in
 * each arm, so both are pointer locals; $6 is recomputed per arm.
 *
 * The sum is computed TWICE with different widths: `dsll32/dsra32 ..,24` for
 * the compare and `andi $7,0xFF` for the byte store. */

typedef struct Obj {
    u8 pad0000[0x5EAC];
    s8 m5EAC;                       /* +0x5EAC */
    u8 pad5EAD[0x5EEF - 0x5EAD];
    u8 m5EEF;                       /* +0x5EEF */
    u8 m5EF0;                       /* +0x5EF0 */
} Obj;

void insect_InsectBattleFadeStep_50a1e0(Obj *o)
{
    s8 *f;
    u8 *c;
    s32 v;
    s32 sv;

    f = &o->m5EAC;
    v = *f;
    if (v != 0) {
        sv = (s8)v;
        if (sv < 0) {
            c = &o->m5EEF;
            if (*c + sv <= o->m5EF0) {
                *c = o->m5EF0;
                *f = 0;
            } else {
                *c += v;
            }
        } else {
            c = &o->m5EEF;
            if (*c + sv >= o->m5EF0) {
                *c = o->m5EF0;
                *f = 0;
            } else {
                *c += v;
            }
        }
    }
}
