/* rgp:protos */
#define RGP_SELF_WorldDataMgrZoneEntryAttach_3f1fc0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK s16d: 1 round trip, same length as retail (115 words) but 58 bad
   -- register/CSE residue, not structural. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s8 *strcpy(s32, s8 *);
extern u32 strlen(s8 *);
extern s32 D_004644A8 __attribute__((section(".data")));
extern s8 D_00466D38[];

typedef struct {
    void *unk0;
    u8 pad4[0xc];
    s16 unk10;
} T3f1fc0_arg1;

s32 WorldDataMgrZoneEntryAttach_3f1fc0(void *arg0, T3f1fc0_arg1 *arg1, s32 arg2)
{
    s16 idx;
    s32 t2;
    s32 t2_2;
    void *p0;
    s8 *nm;
    s32 t4;

    if (arg1 == NULL) {
        return 0;
    }
    idx = arg1->unk10;
    if (idx < 0 || idx >= D_004644A8) {
        return 0;
    }
    t2 = ((s32)MemStackArrayGet_3f23f0(arg0, idx));
    if (t2 == 0) {
        return 0;
    }
    if (arg2 == 1 || arg2 < 0) {
        MemStackReset_14d830(t2);
    }
    if (arg2 == 1 || arg2 < 0) {
        t2_2 = ((s32)MemStackArrayGet_3f2390(arg0, arg1->unk10));
        if (t2_2 != 0) {
            MemStackReset_14d830(t2_2);
            p0 = arg1->unk0;
            if (p0 != NULL) {
                nm = *(s8 **)((u8 *)p0 + 0x4);
                if (strlen(nm) < 0x10U) {
                    strcpy(t2_2, nm);
                }
            } else {
                if (strlen(D_00466D38) < 0x10U) {
                    strcpy(t2_2, D_00466D38);
                }
            }
        }
    }
    t4 = *(s32 *)((u8 *)arg0 + 0x6C);
    if (t4 != 0 && (arg2 == 1 || arg2 < 0)) {
        WorldSubsysZoneEntryAttach_41c510(t4, arg1);
    }
    t4 = *(s32 *)((u8 *)arg0 + 0x80);
    if (t4 != 0 && (arg2 == 2 || arg2 < 0)) {
        WorldSubsysZoneEntryAttach_41e3d0(t4, arg1);
    }
    t4 = *(s32 *)((u8 *)arg0 + 0x78);
    if (t4 != 0 && (arg2 == 3 || arg2 < 0)) {
        WorldSubsysZoneEntryAttach_427020(t4, arg1);
    }
    return 1;
}
