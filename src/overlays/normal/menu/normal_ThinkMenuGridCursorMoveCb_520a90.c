#include "types.h"
/* normal 0x00520A90 -- copy the two s16 offset tables to the stack, look the
 * pair up by the box's two indices, then build the four-slot argument block
 * (memset then filled) for the 0x7540 dialogue call.
 *
 * Two readings that the register allocator settles: the `daddu $16,$2` AFTER
 * the func_3C86E0 call takes THAT call's return value (not func_1FEDE0's --
 * func_1FEDE0's result is dereferenced INLINE for ->f18), and both table
 * copies are POINTER-walking down-counting loops, not indexed `for`s.  The
 * three loop locals must be declared src, dst, COUNT -- that order alone is
 * worth 11 bad words (5 of the 6 permutations score 6-17). */

typedef struct Box {
    u8  pad00[0x10];
    s16 f10; s16 f12;
} Box;

typedef struct Ent { u8 pad00[0x18]; void *f18; } Ent;
typedef struct Cfg { u8 pad00[0x11]; s8 f11; } Cfg;

extern const s16 D_005260B0[];
extern s16 D_004807A8;            /* gp - 0x49C8, declared SHORT to stay in small data */

extern const u8 D_00528060[];

extern void *D_00484920;          /* gp - 0x850 */
extern Cfg  *D_00484934;          /* gp - 0x83C */
extern f32   D_0047D3F0;          /* main pool, 0.4f */

extern void  func_28DB40(const u8 *w, s32 id, s32 x, s32 y,
                         s32 a, s32 b, s32 c, s32 d);
extern Ent  *func_1FEDE0(void);
extern void *func_3C86E0(void *p, s32 a, s32 b, s32 x, s32 y, s32 c);
extern void  func_131B60(void *p, s32 v, s32 n);
extern s32   func_28FE10(void *w, s32 id, s32 a);
extern s32   func_28F620(void *w, s32 id, s32 a);
extern void  func_2A33E0(Cfg *cfg, void *e, s32 a, s32 b, s32 *st,
                         s32 c, s32 d, s32 f, f32 t);

s32 normal_ThinkMenuGridCursorMoveCb_520a90(Box *p)
{
    s16   ty[5];
    s16   tx[9];
    s32   st[4];
    s16  *s;
    s16  *d;
    s32   i;
    void *r;

    s = (s16 *)D_005260B0;
    d = tx;
    for (i = 9; i > 0; i--) {
        *d++ = *s++;
    }
    s = &D_004807A8;
    d = ty;
    for (i = 5; i > 0; i--) {
        *d++ = *s++;
    }
    func_28DB40(D_00528060, 0x753B, tx[p->f10], ty[p->f12],
                0x2A, 0x30, 0x46, 0x4B);
    r = func_3C86E0(func_1FEDE0()->f18, 0, D_00484934->f11,
                    p->f10, p->f12, 0);
    func_131B60(st, 0, 0x10);
    st[0] = func_28FE10(D_00484920, 0x7546, 0);
    st[1] = func_28FE10(D_00484920, 0x7545, 0);
    st[2] = func_28F620(D_00484920, 0x7545, 0);
    st[3] = func_28FE10(D_00484920, 0x7547, 0);
    func_2A33E0(D_00484934, r, 0x7540, 0x753D, st, 0x4D, 0x160, -1,
                D_0047D3F0);
    return 1;
}
