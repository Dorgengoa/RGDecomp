#include "types.h"

/* Event-command handler.  Two argc arms of one call; the "default" of the
   second dispatch falls into the shared tail, so it is a `switch` with the
   case order reversed in the listing (8 tested first, 7 written first).
   Argument evaluation is strictly left to right - that is what fixes the
   position of every literal 0. */

extern u8 D_004E7110[];
extern void *D_00482890;

extern void *ScriptArgGetStr_301a00(u8 *p);
extern void *EventStrDup_301aa0(void *a);
extern s32 ScriptArgGetAreaId_3019b0(u8 *p);
extern void *EventScratchAlloc_301b00(s32 size);
extern void EvScriptTemplatesReset_301c20(void);
extern void *GetEventObjMgr_2d1960(void);
extern void *EventObjMgrFindVolumeRecByName_2e9bc0(void *a, void *b);
extern void EvM05ChangeSetVolumeRecs_352050(u8 *tbl, void *a, void *b);
extern void EvM05ChangeInitByName_3521f0(u8 *tbl, void *a, void *b, void *c, s32 d, void *e,
                         void *f, void *g, void *h, void *i);

s32 EvScriptCmdM05ChangeInit_2fdd20(u8 *p, s32 argc)
{
    void *m0;
    void *m1;

    if (argc != 7 && argc != 8) {
        return 0;
    }
    EvScriptTemplatesReset_301c20();
    D_00482890 = EventScratchAlloc_301b00(0x2800);
    if (D_00482890 == 0) {
        return 1;
    }
    switch (argc) {
    case 7:
        EvM05ChangeInitByName_3521f0(D_004E7110, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0, 0,
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x30)),
                     D_00482890, 0);
        break;
    case 8:
        EvM05ChangeInitByName_3521f0(D_004E7110, EventStrDup_301aa0(ScriptArgGetStr_301a00(p)), 0,
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x38)),
                     ScriptArgGetAreaId_3019b0(p + 8),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x10)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x28)),
                     EventStrDup_301aa0(ScriptArgGetStr_301a00(p + 0x30)),
                     D_00482890, 0);
        break;
    }
    m0 = EventObjMgrFindVolumeRecByName_2e9bc0(GetEventObjMgr_2d1960(), ScriptArgGetStr_301a00(p + 0x18));
    m1 = EventObjMgrFindVolumeRecByName_2e9bc0(GetEventObjMgr_2d1960(), ScriptArgGetStr_301a00(p + 0x20));
    EvM05ChangeSetVolumeRecs_352050(D_004E7110, m0, m1);
    return 1;
}
