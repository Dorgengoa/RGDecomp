#include "types.h"

/* insmenu 0x004F4F00 (200 bytes) -- commit the picked entry: if either lookup
 * accepts it the panel bounces, otherwise the scene is handed over.
 *
 * ★ `addiu $4, $0, 0x6` in the first `bnel`'s delay slot is the shared arm's
 * first instruction duplicated -- the two lookups are an `||`, not two `if`s.
 * ★ `sh $0, -0xE30($28)` rides the guard's delay slot because the zero is
 * stored BEFORE the test in the source. */

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0x16];
    s16 field16;
};

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x16];
    s16 field16;
    u8  pad18[2];
    s16 field1A;
};

typedef struct Scene Scene;

extern const u8 D_004FA1A0[];
extern s16 D_00484340;          /* gp - 0xE30 */
extern s16 D_0048435C;          /* gp - 0xE14 */

extern Widget *func_28EA40(const void *a, s32 id);
extern Scene *insmenu_InsectVsGetSaveCtx_4f3850(void);
extern s32 func_373540(Scene *s, s32 n);
extern s32 func_373480(Scene *s, s32 n);
extern void func_376B20(s32 a);
extern void func_207FE0(void);
extern void func_37B9C0(s32 a);
extern void func_28EA90(const void *a, s32 id, s32 c);

s32 insmenu_InsectVsTeamListConfirm_4f4f00(Panel *p)
{
    Widget *w;

    w = func_28EA40(D_004FA1A0, 0x88BB);
    D_00484340 = 0;
    if (w != 0) {
        D_00484340 = w->field1A + w->field16;
    }
    D_0048435C = p->field16;
    if (func_373540(insmenu_InsectVsGetSaveCtx_4f3850(), D_00484340) != 0 ||
        func_373480(insmenu_InsectVsGetSaveCtx_4f3850(), D_00484340) != 0) {
        func_376B20(6);
        return 0;
    }
    func_207FE0();
    func_376B20(5);
    func_37B9C0(D_00484340);
    func_28EA90(D_004FA1A0, 0x88BF, 1);
    return 1;
}
