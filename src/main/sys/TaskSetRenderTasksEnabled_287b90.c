#include "types.h"

/* The sibling of TaskSetUpdateTasksPaused_287dd0 -- the same registration LIST, one call per
   phase-name string, with the flag passed straight through instead of being
   rebuilt.  The 32nd call is CONDITIONAL: retail falls through into it when
   the masked byte is zero, so the fall-through is the source's `if` body
   (memory/levers.d/main-pass32-spellings.md section 1). */

extern s32  TaskSetEnabled_27c2a0(s32, void *);
extern void *GetGameData_1fede0(void);

typedef struct {
    u8  pad[0x24C];
    u8  flags;
} Sub;

typedef struct {
    u8  pad[0x20];
    Sub *sub;
} Ctx;

extern u8 D_00460638[];
extern u8 D_00460640[];
extern u8 D_00460650[];
extern u8 D_00460660[];
extern u8 D_00460670[];
extern u8 D_00460690[];
extern u8 D_004606A0[];
extern u8 D_004606B0[];
extern u8 D_004606C0[];
extern u8 D_004606D0[];
extern u8 D_004606F0[];
extern u8 D_00460720[];
extern u8 D_00460760[];
extern u8 D_00460780[];
extern u8 D_004607A8[];
extern u8 D_004607B8[];
extern u8 D_004607E8[];
extern u8 D_004607F8[];
extern u8 D_00460810[];
extern u8 D_00460820[];
extern u8 D_00460840[];
extern u8 D_00460890[];
extern u8 D_004608A0[];
extern u8 D_004608B0[];
extern u8 D_004608D0[];
extern u8 D_00460908[];
extern u8 D_00460920[];
extern u8 D_00460930[];
extern u8 D_00460950[];
extern u8 D_00460A78[];
extern u8 D_00460C48[];
extern u8 D_00460E68[];

void TaskSetRenderTasksEnabled_287b90(s32 mode)
{
    TaskSetEnabled_27c2a0(mode, D_00460638);
    TaskSetEnabled_27c2a0(mode, D_00460640);
    TaskSetEnabled_27c2a0(mode, D_00460650);
    TaskSetEnabled_27c2a0(mode, D_004607E8);
    TaskSetEnabled_27c2a0(mode, D_004606C0);
    TaskSetEnabled_27c2a0(mode, D_004606D0);
    TaskSetEnabled_27c2a0(mode, D_004606F0);
    TaskSetEnabled_27c2a0(mode, D_004607B8);
    TaskSetEnabled_27c2a0(mode, D_00460A78);
    TaskSetEnabled_27c2a0(mode, D_00460690);
    TaskSetEnabled_27c2a0(mode, D_00460660);
    TaskSetEnabled_27c2a0(mode, D_00460670);
    TaskSetEnabled_27c2a0(mode, D_004607A8);
    TaskSetEnabled_27c2a0(mode, D_00460E68);
    TaskSetEnabled_27c2a0(mode, D_00460720);
    TaskSetEnabled_27c2a0(mode, D_00460840);
    TaskSetEnabled_27c2a0(mode, D_004606A0);
    TaskSetEnabled_27c2a0(mode, D_004606B0);
    TaskSetEnabled_27c2a0(mode, D_00460810);
    TaskSetEnabled_27c2a0(mode, D_00460908);
    TaskSetEnabled_27c2a0(mode, D_00460820);
    TaskSetEnabled_27c2a0(mode, D_00460950);
    TaskSetEnabled_27c2a0(mode, D_00460920);
    TaskSetEnabled_27c2a0(mode, D_00460890);
    TaskSetEnabled_27c2a0(mode, D_004608A0);
    TaskSetEnabled_27c2a0(mode, D_004608B0);
    TaskSetEnabled_27c2a0(mode, D_004608D0);
    TaskSetEnabled_27c2a0(mode, D_004607F8);
    TaskSetEnabled_27c2a0(mode, D_00460930);
    TaskSetEnabled_27c2a0(mode, D_00460C48);
    TaskSetEnabled_27c2a0(mode, D_00460780);

    if ((((Ctx *)GetGameData_1fede0())->sub->flags & 1) == 0) {
        TaskSetEnabled_27c2a0(mode, D_00460760);
    }
}
