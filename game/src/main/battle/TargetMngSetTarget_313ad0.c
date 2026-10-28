/* rgp:protos */
#define RGP_SELF_TargetMngSetTarget_313ad0 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0x10C vs retail 0x110, close. */
#include "types.h"

#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
typedef struct B44 { s32 w[11]; } B44;
typedef struct Blk313 { s16 a; s16 b; B44 c; } Blk313;
typedef struct T313 { u8 pad[8]; s16 x; s16 y; } T313;
/*rgp*/
extern s32 D_00482A4C;

void TargetMngSetTarget_313ad0(void *arg0)
{
    void *temp_19;
    s32 *var_5;
    s32 temp_17;
    s32 temp_18;
    s16 var_3;
    void *temp_16;
    s32 *var_4;
    void *temp_2;

    if ((arg0 != NULL) && (((short)TargetRefGetKind_2e7130((void *)arg0)) == 4)) {
        temp_18 = GetCurrentScene_1f5be0();
        D_00482A4C = ((short)TargetRefGetId_2e7120(arg0));
        temp_16 = TargetRefGetObjSlot_2e70e0(arg0);
        temp_2 = GetTargetMng_313dd0();
        if (temp_2 != NULL) {
            ((Blk313 *)((u8 *)temp_2 + 0xC0))->a = ((Blk313 *)arg0)->a;
            ((Blk313 *)((u8 *)temp_2 + 0xC0))->b = ((Blk313 *)arg0)->b;
            ((Blk313 *)((u8 *)temp_2 + 0xC0))->c = ((Blk313 *)arg0)->c;
            TargetMngLock_31f4c0(temp_2);
            temp_19 = (u8 *)temp_2 + 0x10;
            if (temp_19 != NULL) {
                temp_17 = GameSceneSoundSlot5GetHandle_1d0790(temp_18);
                SoundPlayScaledVolume_1b9520(temp_17, 4, SoundNextPlayHandle_1b81c0(), 1.0f);
                TargetSlotShow_3209a0(temp_19, D_00482A4C, ((T313 *)temp_16)->x, ((T313 *)temp_16)->y);
            }
        }
    }
}
