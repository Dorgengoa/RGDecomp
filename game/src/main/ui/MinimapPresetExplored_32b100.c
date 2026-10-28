/* rgp:protos */
#define RGP_SELF_MinimapPresetExplored_32b100 1
#define RGP_SELF_SetV 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z; } V3;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);
extern char D_00462418[];
extern char D_00462458[];
extern char D_00462468[];
extern char D_00462470[];
extern char D_00462480[];
extern char D_00462488[];
extern char D_00462490[];
extern char D_00462498[];
extern char D_004624A8[];
extern char D_004624C0[];
extern char D_004624D8[];
extern char D_004624E0[];
extern char D_004624F0[];
extern char D_00462500[];

static inline void SetV(V3 *v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

void MinimapPresetExplored_32b100(char *name) {
    V3 a __attribute__((aligned(16)));
    V3 b __attribute__((aligned(16)));
    s32 *p;
    s32 q;
    s32 n;
    s32 r;

    p = GetGameData_1fede0();
    q = ((s32)GetMinimapMgr_201a70());
    if (q == 0 || p == 0 || name == 0) {
        return;
    }
    n = ((short)StateGetChapter_3cd5b0(p[4]));
    if (strcmp(name, D_00462470) == 0) {
        if ((r = MinimapMgrFindSlotByName_322340(q, name)) != 0) {
            MinimapSetAllExplored_32b6d0(1, r);
        }
    }
    if (strcmp(name, D_00462480) == 0 && n >= 6) {
        SetV(&a, 4000.0f, -280.0f, -7200.0f);
        SetV(&b, 9600.0f, 3920.0f, -4900);
        MinimapSetRectExploredByName_32b590(name, D_00462418, &a, &b, 1);
    }
    if (strcmp(name, D_00462458) == 0) {
        if (n < 6) {
            SetV(&a, 1400.0f, -2200, 13400);
            SetV(&b, 4700, 2200, 19000);
            MinimapSetRectExploredByName_32b590(name, D_00462488, &a, &b, 1);
        }
        if (n >= 6) {
            SetV(&a, -3800, 400.0f, -12740);
            SetV(&b, 1200.0f, 3400, -10760);
            MinimapSetRectExploredByName_32b590(name, D_00462468, &a, &b, 1);
        }
    }
    if (strcmp(name, D_00462490) == 0) {
        SetV(&a, -4100, -1400.0f, 11200.0f);
        SetV(&b, 2200, 2600, 13400);
        MinimapSetRectExploredByName_32b590(name, D_00462498, &a, &b, 1);
    }
    if (strcmp(name, D_004624A8) == 0) {
        SetV(&a, -2240.0f, -1000.0f, -64800);
        SetV(&b, 4000.0f, 2820, -62400);
        MinimapSetRectExploredByName_32b590(name, D_004624C0, &a, &b, 1);
    }
    if (strcmp(name, D_004624D8) == 0) {
        SetV(&a, -2200, 3640, -4000.0f);
        SetV(&b, 2890, 5020, -1040.0f);
        MinimapSetRectExploredByName_32b590(name, D_004624E0, &a, &b, 1);
    }
    if (strcmp(name, D_004624F0) == 0) {
        SetV(&a, -4100, -1700, 3300);
        SetV(&b, 2410, 2600, 5600.0f);
        MinimapSetRectExploredByName_32b590(name, D_00462500, &a, &b, 1);
    }
}
