#include "types.h"

extern u8 D_004E6B80[];
extern u8 D_00451F90[];
extern void *D_00482868;
extern void *D_00482870;

extern void *ScriptArgGetStr_301a00(u8 *p);
extern void *EventStrDup_301aa0(void *a);
extern void *EventScratchAlloc_301b00(s32 size);
extern void EvScriptTemplatesReset_301c20(void);
extern void *LookupNameValueNoCase_1cab50(void *a, u8 *b, s32 c);
extern void EvMapObjInitByName_366e50(u8 *tbl, void *a, void *b, void *c, s32 d, s32 e,
                         void *f, void *g, void *h, void *i, void *j, void *k,
                         void *l);

s32 EvScriptCmdMapObjInit_2ffaa0(u8 *p, s32 argc)
{
    EvScriptTemplatesReset_301c20();
    if (argc != 4 && argc != 5) {
        return 0;
    }
    D_00482868 = EventScratchAlloc_301b00(0x80);
    D_00482870 = EventScratchAlloc_301b00(0x2A00);
    if (D_00482868 == 0 || D_00482870 == 0) {
        return 1;
    }
    switch (argc) {
    case 4:
        EvMapObjInitByName_366e50(D_004E6B80, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0, 0, -1, 0,
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 8)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     LookupNameValueNoCase_1cab50(ScriptArgGetStr_301a00(p + 0x18), D_00451F90, 0),
                     D_00482868, 0, D_00482870, 0);
        break;
    case 5:
        EvMapObjInitByName_366e50(D_004E6B80, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0,
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)), -1, 0,
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 8)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     LookupNameValueNoCase_1cab50(ScriptArgGetStr_301a00(p + 0x18), D_00451F90, 0),
                     D_00482868, 0, D_00482870, 0);
        break;
    }
    return 1;
}
