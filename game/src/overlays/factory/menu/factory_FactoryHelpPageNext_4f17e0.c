/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpPageNext_4f17e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F17E0 -- 608 B.  BYTE-IDENTICAL, session 23 (fz23c).
 *
 * The whole unit turned on ONE address spelling ([[insect-cse-two-spellings]]).
 * Retail computes the guard's element as `(f74 + 2) + f6C*4` and the later
 * `o->f74[o->f6C*2]` as a SEPARATE `addu $3,$6,$7` off the same two registers.
 * Writing the guard as `&o->f74[o->f6C*2] + 1` makes mwcc form `f74 + f6C*4`
 * ONCE, read the guard at displacement 2 and CSE the second site onto it -- one
 * word short, and it also forces an early `move s1,a0` because the shift then
 * clobbers $4.  The INTEGER-ADD cast is what mwcc will not fold into a
 * displacement, and the index must still be spelled as the ARRAY SUBSCRIPT so
 * the `sll` stays shared and the index (not the base) is evaluated first:
 *     qq = &((s16 *)((s32)o->f74 + 2))[o->f6C * 2];
 * MEASURED, same unit, same round: `qq = o->f74 + 1;` + `qq[o->f6C*2]` folds all
 * the way back (0x258, two short); `qq = (s16 *)((s32)o->f74 + 2);` + `qq[...]`
 * gets both `addu`s but evaluates the BASE first, so the shift takes $4 and the
 * `move s1,a0` returns (0x264, one long).
 */

typedef struct Scr {
    u8   pad00[0x6C];
    s32  f6C;
    s8   f70;
    s8   f71;
    u8   pad72[0x2];
    s16 *f74;
    s32  f78;
    s32  f7C;
    s32  f80;
    u8   pad84[0x4];
    void *f88;
} Scr;

extern void *D_00484A70;                        /* _gp - 0x700 */
extern u8    factory_D_0050CB20[];

/*rgp*/
extern void  Sprintf_1343b8(u8 *dst, u8 *fmt, void *s);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryHelpPageNext_4f17e0(Scr *o)
{
    u8   buf[0x20] __attribute__((aligned(16)));
    u8  *p;
    u8  *q;
    u8  *r;
    s32  h;
    s32  id;
    s32  k;
    s32  m;
    s16 *qq;
    u32  n;

    qq = &((s16 *)((s32)o->f74 + 2))[o->f6C * 2];
    if (*qq > 1 && o->f78 < *qq - 1) {
        if (o->f7C == -1) {
            if (o->f78 > 0) {
                m = o->f78 - 1;
                id = o->f74[o->f6C * 2] + 0x2710;
                k = m + id;
                h = GetDrawCtxNameTable_15de40();
                NameTableRemoveByName_158c40(h, ((u8 *)Strchr_1347c0(MsgTableLookup_28aa30(D_00484A70, k - 1), 0xA)) + 1, 0x32E);
                if (((o->f78 - 1) % 2) == 0) {
                    UiSetWidgetVisible_290010(o->f88, 0x84, 0, -1);
                } else {
                    UiSetWidgetVisible_290010(o->f88, 0x85, 0, -1);
                }
            }
            o->f78 = o->f78 + 1;
            k = o->f78 + (o->f74[o->f6C * 2] + 0x2710);
            h = ((s32)GetLoaderMgr_1f59d0());
            o->f7C = -1;
            o->f80 = 0;
            q = MsgTableLookup_28aa30(D_00484A70, k);
            p = ((u8 *)Strchr_1347c0(q, 0xA));
            *p = 0;
            r = buf;
            n = 0x20;
            if (r != 0) {
                do {
                    *r = 0;
                    n--;
                    r++;
                } while (n != 0);
            }
            Sprintf_1343b8(buf, factory_D_0050CB20, q);
            *p = 0xA;
            o->f7C = LoaderRequestFile_1cd870(h, buf, 0);
            if (o->f7C != -1) {
                o->f71 = 0;
                LoaderQueueAppendSeparator_1cd670(h);
                if ((o->f78 % 2) == 0) {
                    UiFadeWidgetAlpha_290690(o->f88, 0x85, 0.0f, -0.125f, -1.0f);
                } else {
                    UiFadeWidgetAlpha_290690(o->f88, 0x84, 0.0f, -0.125f, -1.0f);
                }
                o->f70 = 3;
            }
        }
    } else {
        factory_FactoryHelpPageClose_4f16b0(o);
    }
}
