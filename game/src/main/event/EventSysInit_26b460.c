/* rgp:protos */
#define RGP_SELF_EventSysInit_26b460 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0x1D8 vs retail 0x1E8. */
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);
extern void strcpy(void *, void *);
extern u32 strlen(void *);
extern u8 D_0045F1C0[];
extern u8 D_0045F1E0[];
extern s32 D_00482040;
extern s32 D_00482044;
extern s32 D_00482048;
extern s32 D_0048204C;
extern s32 D_00482050;
extern s32 D_00482054;
extern s32 D_00482058;
extern s32 D_0048205C;
extern s32 D_00482060;
extern s32 D_00482064;
extern s32 D_00482068;
extern s32 D_0048206C;
extern u8 D_004BDDB0[];
extern u8 D_004BDFB0[];
extern u8 D_004BDFF0[];
extern u8 D_004BE030[];
extern u8 D_004BE070[];
extern u8 D_004BE0B0[];
extern u8 D_004BE110[];

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    volatile s32 d;
} E26;

void EventSysInit_26b460(void)
{
    s32 var_16;
    s32 var_16_2;
    s32 var_7;
    E26 *temp_5;

    MemStackInit_14d810(D_004BE0B0, D_00482054, 0x801);
    if (strlen(D_0045F1C0) < 0x10U) {
        strcpy(D_004BE0B0, D_0045F1C0);
    }
    MemStackReset_14d830(D_004BE0B0);
    MemStackInit_14d810(D_004BE110, D_00482058, 0x141);
    if (strlen(D_0045F1E0) < 0x10U) {
        strcpy(D_004BE110, D_0045F1E0);
    }
    MemStackReset_14d830(D_004BE110);
    D_00482044 = -1;
    memset(D_004BDFB0, 0, 0x40);
    memset(D_004BDFF0, 0, 0x40);
    D_00482048 = -1;
    memset(D_004BE030, 0, 0x40);
    D_0048204C = 0;
    memset(D_004BE070, 0, 0x40);
    D_00482050 = 0;
    var_7 = 0;
    do {
        temp_5 = (E26 *)(D_004BDDB0 + (var_7 * 0x10));
        var_7 += 1;
        temp_5->a = -1;
        temp_5->b = -1;
        temp_5->c = 1;
        temp_5->d = 0;
        temp_5->d = 0;
        temp_5->d = 0;
        temp_5->d = 0;
        temp_5->d = 0;
    } while (var_7 < 0x20);
    EventCameraInit_254be0(D_00482060, D_0048205C, 0x20);
    var_16 = 0;
    do {
        EvSubMachineInit_251ff0(D_00482068 + (var_16 * 0x5F0), D_00482064, 0x80);
        var_16 += 1;
    } while (var_16 < 0x20);
    var_16_2 = 0;
    do {
        MenuWinInit_26c450(D_0048206C + (var_16_2 * 0xE0));
        var_16_2 += 1;
    } while (var_16_2 < 8);
    EventStateResetMaybe_26b780();
    D_00482040 = 0;
}
