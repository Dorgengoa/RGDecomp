/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuGridCursorMoveCb_520a90 1
#include "port/game_protos.h"
#line 1
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

extern s16 normal_D_005260B0[];
extern s16 D_004807A8;            /* gp - 0x49C8, declared SHORT to stay in small data */

extern u8 normal_D_00528060[];

extern void *D_00484920;          /* gp - 0x850 */
extern Cfg  *D_00484934;          /* gp - 0x83C */
extern f32   D_0047D3F0;          /* main pool, 0.4f */

/*rgp*/

/*rgp*/
/*rgp*/
extern void  memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/


s32 normal_ThinkMenuGridCursorMoveCb_520a90(Box *p)
{
    s16   ty[5];
    s16   tx[9] __attribute__((aligned(16)));
    s32   st[4] __attribute__((aligned(16)));
    s16  *s;
    s16  *d;
    s32   i;
    void *r;

    s = (s16 *)normal_D_005260B0;
    d = tx;
    for (i = 9; i > 0; i--) {
        *d++ = *s++;
    }
    s = &D_004807A8;
    d = ty;
    for (i = 5; i > 0; i--) {
        *d++ = *s++;
    }
    UiSelFrameSetRect_28db40(normal_D_00528060, 0x753B, tx[p->f10], ty[p->f12],
                0x2A, 0x30, 0x46, 0x4B);
    r = InvFindByCategoryIndex_3c86e0(((Ent *)GetGameData_1fede0())->f18, 0, D_00484934->f11,
                    p->f10, p->f12, 0);
    memset(st, 0, 0x10);
    st[0] = ((s32)UiGetWidgetSprite_28fe10(D_00484920, 0x7546, 0));
    st[1] = ((s32)UiGetWidgetSprite_28fe10(D_00484920, 0x7545, 0));
    st[2] = ((s32)UiGetWidgetText_28f620(D_00484920, 0x7545, 0));
    st[3] = ((s32)UiGetWidgetSprite_28fe10(D_00484920, 0x7547, 0));
    MenuItemInfoPopupShow_2a33e0(D_00484934, r, 0x7540, 0x753D, st, 0x4D, 0x160, -1,
                D_0047D3F0);
    return 1;
}
