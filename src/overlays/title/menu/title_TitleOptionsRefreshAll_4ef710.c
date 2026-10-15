#include "types.h"

/* title.bin overlay, 0x004EF710 -- ten calls that publish the option block's
 * fields, each with its own pair of widget ids.  Three of them mask a single
 * bit out of the same +0x1A halfword.
 *
 * The first call reads +0xC off the RETURN REGISTER and the other nine off
 * $16; that is one source expression with the copy scheduled between them.
 */

typedef struct Opt_title_FUN_004ef710 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
    u8 pad014[0x6];
    s16 field01A;      /* +0x1A */
    u8 pad01C[0x4];
    s16 field020;      /* +0x20 */
    s16 field022;      /* +0x22 */
    u8 pad024[0x2];
    s16 field026;      /* +0x26 */
    s16 field028;      /* +0x28 */
    s16 field02A;      /* +0x2A */
    s16 field02C;      /* +0x2C */
} Opt_title_FUN_004ef710;

typedef struct Sys_title_FUN_004ef710 {
    u8 pad000[0xC];
    Opt_title_FUN_004ef710 *field00C;   /* +0xC */
} Sys_title_FUN_004ef710;

extern Sys_title_FUN_004ef710 *func_1FEDE0(void);
extern void title_TitleOptionsShowValue_4ef860(s32 a, s32 b, s32 c, s32 d, s32 e);

s32 title_TitleOptionsRefreshAll_4ef710(void)
{
    Sys_title_FUN_004ef710 *s;

    s = func_1FEDE0();
    title_TitleOptionsShowValue_4ef860(s->field00C->field01A & 1, 1, 0, 0x4C, 0x4D);
    title_TitleOptionsShowValue_4ef860(s->field00C->field022, 1, 0, 0x4E, 0x4F);
    title_TitleOptionsShowValue_4ef860(s->field00C->field012, 0, 1, 0x50, 0x51);
    title_TitleOptionsShowValue_4ef860(s->field00C->field026, 1, 0, 0x52, 0x53);
    title_TitleOptionsShowValue_4ef860(s->field00C->field02A, 1, 0, 0x54, 0x55);
    title_TitleOptionsShowValue_4ef860(s->field00C->field028, 1, 0, 0x56, 0x57);
    title_TitleOptionsShowValue_4ef860(s->field00C->field01A & 2, 0, 2, 0x58, 0x59);
    title_TitleOptionsShowValue_4ef860(s->field00C->field01A & 4, 0, 4, 0x5A, 0x5B);
    title_TitleOptionsShowValue_4ef860(s->field00C->field02C, 1, 0, 0x5C, 0x5D);
    title_TitleOptionsShowValue_4ef860(s->field00C->field020, 1, 0, 0x5E, 0x5F);
    return 1;
}
