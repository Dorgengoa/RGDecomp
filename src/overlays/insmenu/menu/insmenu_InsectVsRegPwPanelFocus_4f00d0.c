#include "types.h"

/* insmenu 0x004F00D0 -- the insmenu_FUN_004F0A00 shape with three flag bits
 * instead of two and a five-case dispatch.  Every recipe below was measured on
 * 004F0A00; only what differs is re-argued here.
 *
 * The counter starts at 1 and the two tested bits are bit 1 (dsll32 30 /
 * dsrl32 31) and bit 2 (dsll32 29 / dsrl32 31), so the struct needs three
 * one-bit fields and this function reads the upper two.
 *
 * THE STORE IS INSIDE THE GUARD HERE, and that is the opposite of 004F0A00 --
 * the two references say so directly.  004F0A00 computes the table load BEFORE
 * `beqz $16` and sinks the `sw` into that branch's delay slot; this one puts
 * `daddu $4, $0, $0` in the guard's slot and sinks the `sw` into the FIRST
 * CASE COMPARE's slot instead, with the switch then testing the loaded value
 * `$3` rather than reloading through $16.  Same two source spellings, and each
 * produces the other's code.
 *
 * case 0x25E shares its body (k = 3) with case 0x25D, so mwcc cannot duplicate
 * the constant into a likely delay slot -- that slot already holds the sunk
 * store -- and the arm is emitted as its own block physically LAST, falling
 * into the join.  The three blocks above it are the unreachable originals left
 * by the delay-slot duplication, exactly as in 004F0A00.
 */

typedef struct {
    s16 field00;
    s16 field02;
    u8 pad04[2];
    s16 field06;
    u8 pad08[2];
    s16 field0A;
    u8 pad0C[6];
    s16 field12;
} Panel;

typedef struct {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
} Item;

typedef struct {
    u8 pad00[0x24];
    void *field24;
} Handle;

/* Overlay data, outside the gp window 0x47D170..0x48D170 -- must be `const`. */
extern const u8 D_004FA1A0[];
extern const u8 D_004FA180[];
extern const s32 D_004F99B0[];

extern void func_28EA90(const void *a, s32 b, s32 c);
extern Panel *func_28EC60(const void *a);
extern Handle *func_1FEDE0(void);
extern Item *func_430B10(void *a);
extern u8 insmenu_InsectVsTakeCancelFlag_4ea0d0(void);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void insmenu_InsectVsRegPwPanelBright_4f03f0(void);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsRegPwCursorFadeIn_4f03a0(void);

void insmenu_InsectVsRegPwPanelFocus_4f00d0(void)
{
    Panel *p;
    Item *h;
    s32 n;
    s32 k;

    func_28EA90(D_004FA1A0, 0x7535, 0);
    p = func_28EC60(D_004FA1A0);
    p->field06 = 0x39;
    p->field0A = 3;
    h = func_430B10(func_1FEDE0()->field24);
    n = 1;
    if (h != 0) {
        if (h->bit1) {
            n++;
        }
        if (h->bit2) {
            n++;
        }
        p->field0A = n;
    }
    if (insmenu_InsectVsTakeCancelFlag_4ea0d0() == 0) {
        k = 0;
        if (h != 0) {
            h->field00 = D_004F99B0[n];
            switch (h->field00) {
            case 0x25A:
                k = 0;
                break;
            case 0x25B:
                k = 1;
                break;
            case 0x25C:
                k = 2;
                break;
            case 0x25D:
                k = 3;
                break;
            case 0x25E:
                k = 3;
                break;
            }
        }
        p->field12 = k;
        func_290F60(D_004FA180, 0x51, p->field00, p->field02 + p->field12 * 57);
        func_290F60(D_004FA180, 0x4D, 0, p->field12 * 57);
        func_2907A0(D_004FA180, 0x4D, 1.0f);
    }
    insmenu_InsectVsRegPwPanelBright_4f03f0();
    insmenu_InsectVsListSetRowColors_4ea110(0x4E, 4, n);
    insmenu_InsectVsRegPwCursorFadeIn_4f03a0();
}
