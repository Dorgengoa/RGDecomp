/* rgp:protos */
#line 1
/* ★★★★★★★★ SESSION 45 (n45v): BYTE-IDENTICAL, 228/228 words, MERGED.
 * Five levers, in the order they were found.  Each is a general NORMAL screen.
 *
 * 1. THE b-CHAIN RVALUE IS A 64-BIT READ-BACK, NOT A ZERO.  Retail 0x005044F0
 *    materialises the propagated zero with `dsll32 $2,$0,16` / `dsra32
 *    $2,$2,16` and stores THAT with `sh` into b->f0C, b->f06, b->f04; a plain
 *    `0` rvalue gives `sh $0`, and the m2c `= a->f0E` gives a real `lh`.
 *    ★ THE ORACLE is the MERGED unit normal_BtlChgMenuItemGridLayout_5000b0, whose blank path is
 *    spelled `pb[i].f1E = 0; pb[i].f1C = 0; pb[i].f08 = pb[i].f1C;` -- mwcc
 *    CONSTANT-PROPAGATES a stored zero read back through the SAME pointer with
 *    NO intervening aliasing store (source register is $0) but KEEPS the
 *    s16<->s64 CONVERSION.  So: `z64 = a->f04;` directly under `a->f04 = 0;`,
 *    then `b->f04 = b->f06 = b->f0C = z64;`.
 *    ⚠ A DIFFERENT pointer does not forward: `d->f08` as the rvalue is a real
 *    `ld` (measured).  Reading `a->f0E` across the intervening `b->f0E = 0;`
 *    is a real `lh` for the same reason.
 *    ⚠ Every LITERAL spelling folds and is inert: `(s16)(s64)0`, an `s64 z64`
 *    assigned `0`, `(s64)a->f0E`, `(s16)(a->f0E + 0LL)`.  The value has to come
 *    from MEMORY.
 *
 * 2. `b = 0;` BELOW `func_290460(h, 0x55)`.  Retail fills the jal delay slot
 *    with the ARGUMENT (`addiu $5,$0,0x55`) and the following `beqz` delay slot
 *    with `daddu $18,$0,$0`.  With `b = 0;` above the call, mwcc spends the jal
 *    delay on it and NOPs the branch -- and opscan counts that nop as an `sll`,
 *    which is why s44 read the residue as `sll: 15 -> 16`.
 *
 * 3. `n = i + 0x10;` AS THE FIRST STATEMENT OF THE LOOP, used ONLY in the `idx`
 *    expression.  Ours and retail both materialise `i + 0x10` three times; only
 *    the FIRST placement differed (retail 0x005044F8 in the loop-head block, we
 *    had it inside the `k == 1` arm).
 *    ⚠⚠ A NEW `s32 j` is +3 words in ALL TWENTY decl x position cells.  REUSING
 *    a local that is dead at the loop top is free: `n` and `t` are both exact
 *    and byte-identical, at "top" or "after a->f0E = 0".
 *    ⚠ Passing the temp to the two func_290BD0 calls as well is +2: retail
 *    REMATERIALISES `addiu $8,$17,0x10` there because $4 is call-clobbered.
 *
 * s44's ~70 arms of INERT / OVERSHOOT / SHORTER spellings are all still valid
 * and are not repeated here; the one recorded verdict they contained that this
 * session did NOT need was "find a wider rvalue TYPE" -- the type is right, it
 * is the SOURCE OF THE VALUE (memory vs literal) that carries the conversion.
 */
#include "types.h"
/* normal 0x00504410 -- the eight-slot party rack builder, the narrow sibling of
 * normal_FUN_005047A0.  Both rows start 0x200 bytes into their widget, `k`
 * selects which half of the roster the eight slots come from (0 = the first
 * column at y -0x32, 1 = the second at y 0x64), and each live member's 0x2E
 * sprite index is split into an 8x8 cell (`% 8` and `/ 8`, scaled by 32).
 * Members whose slot-56 count is under their slot-26 limit take func_290BD0
 * with +1, the rest with -1; an empty slot writes -1 into the row's f00.
 *
 * THREE VIRTUAL calls, so the unit is .cpp -- a struct of function pointers
 * gives `jalr $v0`.  The slots are (0xE8-8)/4 = 56 on Node and (0x70-8)/4 = 26
 * on Ent, the same two classes normal_FUN_004FE750 already carries.
 * `sq`/`lq` at 0xC0 and 0xB0 are mwcc SPILLS of the two column bases, not
 * source objects.
 * `$30` is left undefined when `k` is neither 0 nor 1 -- the chain has no
 * `else`, so it must be written as an if / else-if with no default. */

typedef struct Mdl { u8 pad00[0x2E]; s16 f2E; } Mdl;

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x1C - 0x10];
    u16 f1C;
    u8  pad1E[2];
} Box;

typedef struct Rec {
    s16 f00;
    u8  pad02[6];
    s64 f08;
    u8  pad10[0x1C - 0x10];
    s16 f1C;
    s16 f1E;
} Rec;

typedef struct Hold { u8 pad00[0x20]; void *f20; } Hold;

struct Node {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 count() { return VCM0(s32, 0xE8); }                   /* slot 56 -> vtable +0xE8 */
};

struct Ent {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 limit() { return VCM0(s32, 0x70); }                   /* slot 26 -> vtable +0x70 */
    u8   pad04[0x10 - 4];
    Mdl *f10;
};

typedef struct Ctx { u8 pad00[0x7C]; Ent *f7C[1]; } Ctx;

extern "C" void *normal_UiPageGetLayout_289b60(Ctx *p);
extern "C" Rec  *UiGetWidgetSubItem_28f2b0(void *p, s32 id, s32 a);
extern "C" Hold *UiFindWidget_290460(void *p, s32 id);
extern "C" void UiSetSpriteFlags_290bd0(void *, s32, long long, s32, s32, s32);
extern "C" s32   ItemIsWeapon_3d46c0(Ent *e);
extern "C" s32   PartyFindItemHolder_3d4c20(Ent *e);
extern "C" Node *ItemFindOwnerChara_3d4d80(Ent *e, s32 a);

extern "C" s32 normal_BtlChgPageWeaponGridScrollRow_504410(Ctx *ctx, s32 id, s32 k, s32 col);

s32 normal_BtlChgPageWeaponGridScrollRow_504410(Ctx *ctx, s32 id, s32 k, s32 col)
{
    void *h;
    Rec  *d;
    Hold *w;
    Box  *a;
    Box  *b;
    Rec  *c;
    s32   i;
    Ent  *e;
    Node *nd;
    s32   idx;
    s32   n;
    s32   t;
    s64   z64;

    h = normal_UiPageGetLayout_289b60(ctx);
    w = UiFindWidget_290460(h, id);
    if (w == 0) {
        return 0;
    }
    c = UiGetWidgetSubItem_28f2b0(h, 0x27, 0);
    if (c == 0) {
        return 0;
    }
    if (w->f20 == 0) {
        return 0;
    }
    a = (Box *)((u8 *)w->f20 + 0x200);
    w = UiFindWidget_290460(h, 0x55);
    b = 0;
    if (w != 0) {
        b = (Box *)w->f20;
    }
    if (b != 0) {
        b = (Box *)((u8 *)b + 0x200);
    }
    d = (Rec *)((u8 *)c + 0x200);
    for (i = 0; i < 8; i++) {
        n = i + 0x10;
        a->f0E = 0;
        a->f0C = 0;
        a->f06 = 0;
        a->f04 = 0;
        z64 = a->f04;
        if (b != 0) {
            b->f0E = 0;
            b->f04 = b->f06 = b->f0C = z64;
        }
        d->f08 = d->f1C = d->f1E = 0;
        a->f00 = i * 0x2C + 2;
        if (b != 0) {
            b->f00 = (s16)(i * 0x2C + 2);
        }
        if ((s16)k == 0) {
            idx = i + col * 8;
            a->f02 = -0x32;
            if (b != 0) {
                b->f02 = -0x32;
            }
        } else if ((s16)k == 1) {
            idx = n + (col - 1) * 8;
            a->f02 = 0x64;
            if (b != 0) {
                b->f02 = 0x64;
            }
        }
        e = ctx->f7C[idx];
        if (e != 0) {
            if (ItemIsWeapon_3d46c0(e) != 0) {
                nd = ItemFindOwnerChara_3d4d80(e, 0);
                n = nd->count();
                if (n >= e->limit()) {
                    UiSetSpriteFlags_290bd0(h, id, (long long)(0x20), 1, i + 0x10, 0);
                } else {
                    UiSetSpriteFlags_290bd0(h, id, (long long)(0x20), -1, i + 0x10, 0);
                }
            }
            t = e->f10->f2E;
            a->f04 = 0x28;
            a->f06 = 0x2D;
            a->f0C = 0x20;
            a->f0E = 0x20;
            a->f08 = (s16)((t % 8) * 32);
            a->f0A = (s16)((t / 8) * 32);
            a->f1C = a->f1C | 2;
            if (PartyFindItemHolder_3d4c20(e) != 0 && b != 0) {
                t = e->f10->f2E;
                b->f04 = 0x28;
                b->f06 = 0x2D;
                b->f0C = 0x20;
                b->f0E = 0x20;
                b->f08 = (s16)((t % 8) * 32);
                b->f0A = (s16)((t / 8) * 32);
                b->f1C = b->f1C | 2;
            }
        } else {
            a->f00 = -1;
            if (b != 0) {
                b->f00 = -1;
            }
        }
        a++;
        if (b != 0) {
            b++;
        }
        d++;
    }
    a->f00 = -1;
    if (b != 0) {
        b->f00 = -1;
    }
    d->f00 = -1;
    return 1;
}
