#include "types.h"

/* D_00482880 must be RE-READ after the second allocation (mwcc cannot keep the
   stored value across the call), while D_00482888's stored value IS
   value-numbered - that asymmetry is in the listing, not in the source. */

extern u8 D_004E7000[];
extern void *D_00482880;
extern void *D_00482888;

extern void *ScriptArgGetStr_301a00(u8 *p);
extern void *EventStrDup_301aa0(void *a);
extern s32 ScriptArgGetAreaId_3019b0(u8 *p);
extern void *EventScratchAlloc_301b00(s32 size);
extern void EvScriptTemplatesReset_301c20(void);
extern void EvObjLiftInitByName_336410(u8 *tbl, void *a, void *b, void *c, s32 d, void *e,
                         void *f, void *g, void *h, void *i, void *j, void *k);

s32 EvScriptCmdObjLiftInit_2feb60(u8 *p, s32 argc)
{
    EvScriptTemplatesReset_301c20();
    if (argc != 5 && argc != 6) {
        return 0;
    }
    D_00482880 = EventScratchAlloc_301b00(0xD00);
    D_00482888 = EventScratchAlloc_301b00(0x2300);
    if (D_00482880 == 0 || D_00482888 == 0) {
        return 1;
    }
    switch (argc) {
    case 5:
        EvObjLiftInitByName_336410(D_004E7000, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0, 0,
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x18)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x20)),
                     D_00482880, 0, D_00482888, 0);
        break;
    case 6:
        EvObjLiftInitByName_336410(D_004E7000, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0,
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)),
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x18)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x20)),
                     D_00482880, 0, D_00482888, 0);
        break;
    }
    return 1;
}
