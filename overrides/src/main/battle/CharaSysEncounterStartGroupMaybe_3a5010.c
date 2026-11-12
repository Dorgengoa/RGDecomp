/* rg-override: replaces game/src/main/battle/CharaSysEncounterStartGroupMaybe_3a5010.c sha256 10ff2f0cc1e94f7afcf77dc8b67d2d64bd3054f6f85baa555ad020c567526db1
 * why: holds rg_force_encounter_id(), the parser of the test hook $RG_FORCE_ENCOUNTER=GROUP
 * (encount_group_param id; > 0 = force, 0 = only $RG_FORCE_ENCOUNTER_LOG, -1 = off) used by the
 * CharaSysEncounterPickFormationMaybe_3a5090 override (docs/TEST-FIXTURES.md "Forced battles").
 * The body is the generated one: lane cactugus removed the earlier substitution here, which
 * looked the forced id up as an AREA TABLE id (GroupGetRecordById reads encount_param tables,
 * not groups), so a group id never matched (Cactugus 2506 "not found") or hit a table of the same
 * number (2501-2509 are both tables and groups on Juraika). */
/* rgp:protos */
#define RGP_SELF_CharaSysEncounterStartGroupMaybe_3a5010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include <stdio.h>
extern char *getenv(const char *);

typedef struct {
    u8 pad0[0x70];
    s32 unk70;
} Obj003A5010;

/*rgp*/
/*rgp*/
extern Obj003A5010 *D_004837C4;

s32 rg_force_encounter_id(void)
{
    static int force = -2;
    if (force == -2) {
        const char *e = getenv("RG_FORCE_ENCOUNTER");
        force = -1;
        if (e && *e >= '0' && *e <= '9')
            for (force = 0; *e >= '0' && *e <= '9'; e++) force = force * 10 + (*e - '0');
        else if (getenv("RG_FORCE_ENCOUNTER_LOG"))
            force = 0;   /* log only */
    }
    return force;
}

s32 CharaSysEncounterStartGroupMaybe_3a5010(s32 arg0, s64 arg1, s64 arg2, s32 arg3, s32 arg4) {
    s32 temp_2;

    temp_2 = GroupGetRecordById_402240(D_004837C4->unk70, (s64)(s16)arg1, (s64)(s16)arg2);
    if (temp_2 != 0) {
        return CharaSysEncounterPickFormationMaybe_3a5090(arg0, temp_2, (int)(arg1), arg3, arg4);
    }
    return 0;
}
