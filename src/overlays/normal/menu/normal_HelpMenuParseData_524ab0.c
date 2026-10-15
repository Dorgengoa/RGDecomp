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

extern Ctx  *func_1FEDE0(void);
extern s16   func_15F780(Slot *p);
extern char *func_15F720(Slot *p);
extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_134A98(void *a, const char *t);
extern s32   func_3CCD70(s32 c, s32 k);

s32 normal_HelpMenuParseData_524ab0(void *args)
{
    Ctx  *h;
    Rec  *r;
    Slot *p;
    char *s;

    p = args;
    h = func_1FEDE0();
    if (D_004849E8 != 0) {
        r = &D_004849E8[D_004849EC];
        r->f00 = func_15F780(p++);
        r->f02 = func_15F780(p++);
        r->f04 = func_15F780(p++);
        func_131B60(r->f06, 0, 0x40);
        func_131B60(r->f46, 0, 0x20);
        func_131B60(r->f66, 0, 0x10);
        s = func_15F720(p++);
        if (s != 0) {
            func_134A98(r->f06, s);
        }
        s = func_15F720(p++);
        if (s != 0) {
            func_134A98(r->f46, s);
        }
        s = func_15F720(p);
        if (s != 0) {
            func_134A98(r->f66, s);
        }
        D_004849EC = D_004849EC + 1;
        if (r->f00 == 4) {
            if (func_3CCD70(h->f10, 0x186) == 0) {
                D_004849EC = D_004849EC - 1;
                goto done;
            }
        }
        if (r->f00 == 0x16) {
            if (func_3CCD70(h->f10, 0x187) == 0) {
                D_004849EC = D_004849EC - 1;
            }
        }
    }
done:
    return 1;
}
