#include "types.h"

/* title.bin overlay, 0x004EE9C0 -- initialise two halfword fields, then six
 * calls, three of which take fields of the same object. */

typedef struct Obj_title_FUN_004ee9c0 {
    u8 pad000[0xA];
    s16 field00A;      /* +0xA */
    u8 pad00C[0x2];
    s16 field00E;      /* +0xE */
    u8 pad010[0x2];
    s16 field012;      /* +0x12 */
    u8 pad014[0x2];
    s16 field016;      /* +0x16 */
} Obj_title_FUN_004ee9c0;

extern void func_37B490(s32 a);
extern void title_TitleLoadSlotCursorBob_4edcf0(void *o, void *b, s32 c);
extern void title_TitleLoadHighlightOption_4ede30(s16 a);
extern void func_3777A0(void *o, s32 b, s32 c);
extern void title_TitleLoadSlotListRefreshMaybe_4edeb0(s16 a);
extern void title_TitleSetNoAnalogPause_4f13b0(s32 a);

s32 title_TitleLoadSlotListEnterCb_4ee9c0(Obj_title_FUN_004ee9c0 *o, void *b)
{
    o->field00E = 0x31;
    o->field00A = 2;
    func_37B490(0x43);
    title_TitleLoadSlotCursorBob_4edcf0(o, b, 1);
    title_TitleLoadHighlightOption_4ede30(o->field012);
    func_3777A0(o, 0x45, 0);
    title_TitleLoadSlotListRefreshMaybe_4edeb0(o->field016);
    title_TitleSetNoAnalogPause_4f13b0(1);
    return 1;
}
