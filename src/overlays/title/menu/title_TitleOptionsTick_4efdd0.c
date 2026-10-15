#include "types.h"

/* title.bin overlay, 0x004EFDD0 -- open a dialog, then dispatch on two
 * different results.  The first test is on a SIGN-EXTENDED halfword
 * (`dsll32`/`dsra32`), so it reads a s16-returning accessor; the other two are
 * on the 32-bit result kept in $17.
 *
 * The `bnel` delay slot carries the NEXT guard's constant, not a return value,
 * so this is an ordinary else-if chain.  Two arms share a body and retail
 * emits it twice.
 */

typedef struct Obj_title_FUN_004efdd0 {
    u8 pad000[0x10];
    s16 field010;      /* +0x10 */
    s16 field012;      /* +0x12 */
} Obj_title_FUN_004efdd0;

extern void *D_00484250;
extern void *D_00484258;
extern const u8 D_004B2570;

extern void func_28EA90(void *a, s32 b, s32 c);
extern void func_28EA40(void *a, s32 b);
extern s32 func_28E170(void *a, void *b, s32 c, s32 d);
extern Obj_title_FUN_004efdd0 *func_28EC60(void *a);
extern s16 title_TitleGetCardChangeState_4ed370(void);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void title_TitleOptionsToggle_4ef3f0(s16 a, s16 b);

s32 title_TitleOptionsTick_4efdd0(s32 a, s32 b)
{
    s32 r;
    Obj_title_FUN_004efdd0 *o;

    if (b != 0) {
        func_28EA90(D_00484258, 0x7536, 0);
        func_28EA40(D_00484258, 0x7536);
    }
    r = func_28E170(D_00484258, (void *)&D_004B2570, 4, 0);
    o = func_28EC60(D_00484258);
    if (title_TitleGetCardChangeState_4ed370() == 2) {
        func_28EDE0(D_00484250, 0xD, 0);
    } else if (r == 2) {
        func_28EDE0(D_00484250, 0xD, 0);
    } else if (r == 1) {
        title_TitleOptionsToggle_4ef3f0(o->field010, o->field012);
    }
    return 1;
}
