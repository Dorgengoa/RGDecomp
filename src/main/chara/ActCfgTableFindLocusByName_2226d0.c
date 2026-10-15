#include "types.h"

extern void *GetActionMgr_1fdb50(void);
extern void *ActionMgrGetGlobalTable_234850(void *);
extern void *ActInfoLocusGetName_22f880(void *);
extern s32 StrEqualNonNull_1ca6c0(char *, char *);

/* Look a name up in the +0x54 table of 0x18-byte entries.  A leading '#'
   (0x23) redirects the search to another container, recursively -- unless the
   halfword at +0x12 is already 0x7FFF, whose `beql` delay slot carries the
   duplicated `lw $19,0x54($17)` of its real target. */

void *ActCfgTableFindLocusByName_2226d0(void *p0, char *name)
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
                return ActCfgTableFindLocusByName_2226d0(t, name);
            }
            return 0;
        }
    }
    e = *(u8 **)((u8 *)p0 + 0x54);
    if (e == 0) {
        return 0;
    }
    i = 0;
    while (i < *(s16 *)((u8 *)p0 + 0x76)) {
        if (StrEqualNonNull_1ca6c0(name, ActInfoLocusGetName_22f880(e)) != 0) {
            return e;
        }
        i++;
        e += 0x18;
    }
    return 0;
}
