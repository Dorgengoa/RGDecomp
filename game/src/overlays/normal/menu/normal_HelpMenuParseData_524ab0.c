/* rgp:protos */
#define RGP_SELF_normal_HelpMenuParseData_524ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00524AB0 -- the command-list handler that APPENDS one 0x76-byte
 * record to D_004849E8[D_004849EC].  The argument is a walk pointer over
 * 8-byte script slots: three func_15F780 (s16) then three func_15F720
 * (string), each followed by `p += 8` -- the LAST increment is dead and mwcc
 * drops it, which is why the final `jal func_15F720` has a `nop` delay slot.
 *
 * The two tail guards each re-read `r->f00`, so it is not a named local, and
 * the 0x186 guard's zero side `return`s (b .L00524C24) rather than falling
 * into the 0x16 test.
 */

typedef struct Ctx { u8 pad00[0x10]; s32 f10; } Ctx;
typedef struct Slot { u8 b[8]; } Slot;
typedef struct Rec {
    s16 f00;
    s16 f02;
    s16 f04;
    u8  f06[0x40];
    u8  f46[0x20];
    u8  f66[0x10];
} Rec;

extern Rec *D_004849E8;           /* gp - 0x788 */
extern s32  D_004849EC;           /* gp - 0x784 */

/*rgp*/
/*rgp*/
/*rgp*/
extern void  memset(void *p, s32 v, s32 n);
extern void  strcpy(void *a, const char *t);
/*rgp*/

s32 normal_HelpMenuParseData_524ab0(void *args)
{
    Ctx  *h;
    Rec  *r;
    Slot *p;
    char *s;

    p = args;
    h = ((Ctx *)GetGameData_1fede0());
    if (D_004849E8 != 0) {
        r = &D_004849E8[D_004849EC];
        r->f00 = VariantGetInt_15f780(p++);
        r->f02 = VariantGetInt_15f780(p++);
        r->f04 = VariantGetInt_15f780(p++);
        memset(r->f06, 0, 0x40);
        memset(r->f46, 0, 0x20);
        memset(r->f66, 0, 0x10);
        s = ((char *)SlotGetInt_15f720(p++));
        if (s != 0) {
            strcpy(r->f06, s);
        }
        s = ((char *)SlotGetInt_15f720(p++));
        if (s != 0) {
            strcpy(r->f46, s);
        }
        s = ((char *)SlotGetInt_15f720(p));
        if (s != 0) {
            strcpy(r->f66, s);
        }
        D_004849EC = D_004849EC + 1;
        if (r->f00 == 4) {
            if (StateFlagTest_3ccd70(h->f10, 0x186) == 0) {
                D_004849EC = D_004849EC - 1;
                goto done;
            }
        }
        if (r->f00 == 0x16) {
            if (StateFlagTest_3ccd70(h->f10, 0x187) == 0) {
                D_004849EC = D_004849EC - 1;
            }
        }
    }
done:
    return 1;
}
