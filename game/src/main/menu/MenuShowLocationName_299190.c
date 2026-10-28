/* rgp:protos */
#define RGP_SELF_MenuShowLocationName_299190 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN MenuShowLocationName_299190 -- window-title formatter, same window and same
   D_004DB1B0 dialogue object as the settled seeds MenuMainResLoad_299080 /
   MainMenuInit_297510.  MATCHED ON THE FIRST BUILD.

   Readings:
     * `bnel $2,$3` PAST the arm -> if/else-if chain with the case AS
       WRITTEN, so the guard is the positive `if (PartyGetLocationGroupIdMaybe_3cb150(...) == 0xA)`.
     * `blez $18` PAST the inner arm -> `if (n > 0)`.
     * D_004DB1B0 / D_004DB2D0 / D_00461370 are all loaded %hi/%lo, so none of
       them is in small data: they are plain `extern u8 x[]` objects passed by
       address.  D_004823DC is `lw %gp_rel`, i.e. a POINTER variable in small
       data, so it is `extern void *`.

   THREE MEASURED-INERT ARMS (one round trip, build/mn07v/MenuShowLocationName_299190):
   naming the MsgTableLookup_28aa30 result in a local, spelling the inner guard as
   `if (n <= 0) {} else {...}`, and widening MsgTableLookup_28aa30's second parameter
   from s16 to s32 all produce the IDENTICAL object a3dd14bc.  The `lh`
   0x4CA0 load pins the s16 at the STRUCT, not at the prototype.  */

typedef struct Sub99190 { u8 pad0000[0x4CA0]; s16 m4CA0; } Sub99190;
typedef struct Sys99190 { u8 pad00[0x18]; Sub99190 *m18; } Sys99190;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(void *, const char *, void *, s32);

extern u8 D_004DB1B0[];
extern u8 D_004DB2D0[];
extern char D_00461370[];
extern void *D_004823DC;

s32 MenuShowLocationName_299190(void *w)
{
    Sys99190 *p;
    s32 n;

    UiSetWidgetVisible_290010(D_004DB1B0, w, 1, -1);
    p = ((Sys99190 *)GetGameData_1fede0());
    UiSetTextString_28f510(D_004DB1B0, w, MsgTableLookup_28aa30(D_004823DC, p->m18->m4CA0), 0);
    if (PartyGetLocationGroupIdMaybe_3cb150(p->m18) == 0xA) {
        n = PartyGetFloorNum_3cb000(p->m18);
        if (n > 0) {
            Sprintf_1343b8(D_004DB2D0, D_00461370,
                         MsgTableLookup_28aa30(D_004823DC, p->m18->m4CA0), n);
            UiSetTextString_28f510(D_004DB1B0, w, D_004DB2D0, 0);
        }
    }
    return 1;
}
