/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCalcWinStats_4f0820 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F0820 -- 688 bytes, 172 instructions.
 *
 * Fills the seven-halfword block at o->f5D7C from a per-difficulty record and
 * copies it out to the caller's buffer.  The u32<->f32 helper sequences
 * (`bltz`/`srl 1`/`or`/`cvt.s.w`/`add.s` and the 0x4F000000 compare with the
 * 0x80000000 fixup) say the operands are UNSIGNED int, so the percentages are
 * computed through `u32` locals, and the results are stored back through a u16
 * truncation (`andi 0xFFFF`).
 * The `add.s $f2, $f0, $f1` with 0.5f in `fs` is the operand order of
 * `0.5f + ...`, which is a live source lever (unlike mul.s, whose order is
 * canonicalised).
 */

typedef struct Rec3 { u8 pad[0x4C8]; u16 f4C8; u16 f4CA; } Rec3;
typedef struct Rec4 { u8 pad[0x3E0]; u16 f3E0; u16 f3E2; } Rec4;
typedef struct Rec5 { u8 pad[0x2EE]; u16 f2EE; u16 f2F0; } Rec5;

typedef struct Save { u8 pad[0x24]; s32 f24; } Save;

typedef struct Obj {
    u8  pad0000[0x5D7C];
    s16 f5D7C;                      /* +0x5D7C */
    s16 f5D7E;                      /* +0x5D7E */
    u16 f5D80;                      /* +0x5D80 */
    u16 f5D82;                      /* +0x5D82 */
    s16 f5D84;                      /* +0x5D84 */
    s16 f5D86;                      /* +0x5D86 */
    u16 f5D88;                      /* +0x5D88 */
    u8  pad5D8A[0x5DA8 - 0x5D8A];
    s32 f5DA8;                      /* +0x5DA8 */
} Obj;

extern void  memset(void *d, s32 c, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleCalcWinStats_4f0820(s16 *dst, Obj *o)
{
    Save *s;
    Rec3 *r3;
    Rec4 *r4;
    Rec5 *r5;
    u32 tot;
    f32 pb;
    f32 pa;
    s16 *src;
    s32 n;

    memset(&o->f5D7C, 0, 0xE);
    s = ((Save *)GetGameData_1fede0());
    switch (o->f5DA8) {
    case 3:
        r3 = ((Rec3 *)RecordGetPayloadIfKind1E_430b70(s->f24));
        o->f5D80 = r3->f4C8;
        o->f5D82 = r3->f4CA;
        break;
    case 4:
        r4 = ((Rec4 *)RecordGetPayloadIfKind28_430b50(s->f24));
        o->f5D80 = r4->f3E0;
        o->f5D82 = r4->f3E2;
        break;
    case 5:
        r5 = ((Rec5 *)RecordGetPayloadIfKind32_430b30(s->f24));
        o->f5D80 = r5->f2EE;
        o->f5D82 = r5->f2F0;
        break;
    }
    o->f5D88 = o->f5D80 + o->f5D82;
    o->f5D84 = o->f5D88 - o->f5D80;
    o->f5D86 = o->f5D88 - o->f5D82;
    tot = o->f5D88;
    if (tot != 0) {
        pb = 0.5f + 100.0f * (f32)(u32)o->f5D82 / (f32)tot;
        pa = 0.5f + 100.0f * (f32)(u32)o->f5D80 / (f32)tot;
        o->f5D7C = (u16)pa;
        o->f5D7E = (u16)pb;
    }
    src = &o->f5D7C;
    n = 7;
    do {
        *dst = *src;
        src++;
        dst++;
        n--;
    } while (n > 0);
}
