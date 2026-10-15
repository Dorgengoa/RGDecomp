#include "types.h"
/* insect 0x00515CD0 -- 196 bytes, 49 instructions, 4 calls, 1 conditional
 * branch, br/ins 0.020.  From x_band.py's branch-light band.
 *
 * A field-by-field copy between two objects of the SAME type.  The two-byte
 * out-buffer at $29+0x3C is read back as `lb 0x3C` / `lb 0x3D`, i.e. an
 * `s8 [2]`, and each half goes to its own destination member.
 *
 * The three sub-object addresses handed to insect_InsectPieceGetPos_5150d0 and
 * insect_InsectPieceGetYaw_5150a0 are each a bare `addiu $r, $17, K`, so they are member
 * addresses (`&d->f78`) and not a hoisted base -- the rematerialise side of
 * insect-array-member-blocks-cse.
 */

typedef struct Obj {
    u8  pad00[0x5C];
    s32 f5C;                        /* +0x5C */
    s32 f60;                        /* +0x60 */
    s32 f64;                        /* +0x64 */
    s32 f68;                        /* +0x68 */
    s16 f6C;                        /* +0x6C */
    s8  f6E;                        /* +0x6E */
    s8  f6F;                        /* +0x6F */
    s8  f70;                        /* +0x70 */
    s8  f71;                        /* +0x71 */
    u8  pad72[0x78 - 0x72];
    s32 f78;                        /* +0x78 */
    u8  pad7C[0x84 - 0x7C];
    s32 f84;                        /* +0x84 */
    u8  pad88[0x90 - 0x88];
    s32 f90;                        /* +0x90 */
    u8  pad94[0xC0 - 0x94];
    s32 fC0;                        /* +0xC0 */
    s32 fC4;                        /* +0xC4 */
    s32 fC8;                        /* +0xC8 */
    u8  padCC[0xDC - 0xCC];
    s16 fDC;                        /* +0xDC */
    u8  padDE[0xE0 - 0xDE];
    s32 fE0;                        /* +0xE0 */
} Obj;

extern void insect_InsectPieceCopyStats_512fe0(void);
extern void insect_InsectPieceGetYaw_5150a0(Obj *s, s32 *a, s32 *b, s32 *c);
extern void insect_InsectPieceGetPos_5150d0(Obj *s, s32 *a, s32 *b, s32 *c);
extern void insect_InsectPieceGetMoveKind_5151a0(s8 *t, Obj *s);

void insect_InsectPieceCopy_515cd0(Obj *d, Obj *s)
{
    s8 t[2];

    if (s != 0) {
        insect_InsectPieceCopyStats_512fe0();
        d->f68 = s->f68;
        d->f5C = s->f5C;
        d->f60 = s->f60;
        d->f64 = s->f64;
        d->f70 = s->f70;
        d->f71 = s->f71;
        insect_InsectPieceGetMoveKind_5151a0(t, s);
        d->f6E = t[0];
        d->f6F = t[1];
        d->f6C = s->f6C;
        insect_InsectPieceGetPos_5150d0(s, &d->f78, &d->f84, &d->f90);
        insect_InsectPieceGetYaw_5150a0(s, &d->fC0, &d->fC4, &d->fC8);
        d->fDC = s->fDC;
        d->fE0 = s->fE0;
    }
}
