/* rgp:protos */
#define RGP_SELF_ActCfgTableFindAbltByName_222870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Look a name up in the +0x4C table of 0x18-byte entries.  A leading '#'
   (0x23) redirects the search to another container, recursively -- unless the
   halfword at +0x12 is already 0x7FFF, whose `beql` delay slot carries the
   duplicated `lw $19,0x4C($17)` of its real target. */

void *ActCfgTableFindAbltByName_222870(void *p0, char *name)
{
    u8 *e;
    void *t;
    s32 i;

    if (name == 0) {
        return 0;
    }
    if (*(s16 *)((u8 *)p0 + 0x12) != 0x7FFF) {
        if (*(s8 *)name == 0x23) {
            t = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
            if (t != 0) {
                return ActCfgTableFindAbltByName_222870(t, name);
            }
            return 0;
        }
    }
    e = *(u8 **)((u8 *)p0 + 0x4C);
    if (e == 0) {
        return 0;
    }
    i = 0;
    while (i < *(s16 *)((u8 *)p0 + 0x72)) {
        if (((unsigned char)StrEqualNonNull_1ca6c0(name, ActInfoAbltGetName_22ec50(e))) != 0) {
            return e;
        }
        i++;
        e += 0xC;
    }
    return 0;
}
