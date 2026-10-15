#include "types.h"

extern void *GetActionMgr_1fdb50(void);
extern void *ActionMgrGetGlobalTable_234850(void *);
extern void *CharaEffEntryGetName_230250(void *);
extern s32 StrEqualNonNull_1ca6c0(char *, char *);

/* Look a name up in the +0x40 table of 0x18-byte entries.  A leading '#'
   (0x23) redirects the search to another container, recursively -- unless the
   halfword at +0x12 is already 0x7FFF, whose `beql` delay slot carries the
   duplicated `lw $19,0x40($17)` of its real target. */

void *ActCfgTableFindEfctByName_222a50(void *p0, char *name)
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
                return ActCfgTableFindEfctByName_222a50(t, name);
            }
            return 0;
        }
    }
    e = *(u8 **)((u8 *)p0 + 0x40);
    if (e == 0) {
        return 0;
    }
    i = 0;
    while (i < *(s16 *)((u8 *)p0 + 0x6C)) {
        if (StrEqualNonNull_1ca6c0(name, CharaEffEntryGetName_230250(e)) != 0) {
            return e;
        }
        i++;
        e += 0x7C;
    }
    return 0;
}
