/* rgp:protos */
#define RGP_SELF_CharaNormalTableClone_225830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x34];
} Elem;

typedef struct {
    s64 unk0;
    s64 unk8;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    Elem *unk28;
    s16 unk2C;
    s16 unk2E;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaNormalTableClone_225830(Obj *self, s32 arg1, Obj *src, s32 arg3, s32 arg4)
{
    s32 n;
    s32 i;
    Elem *p;

    self->unk10 = 0;
    self->unk26 = 0;
    self->unk0 = 0;
    self->unk8 = 0;
    self->unk14 = 0;
    self->unk20 = 0;
    self->unk18 = 0;
    self->unk22 = 0;
    self->unk1C = 0;
    self->unk24 = 0;
    self->unk2E = -1;
    self->unk28 = 0;
    self->unk2C = 0;
    if (arg3 == 0 || arg1 == 0 || src == NULL || src->unk2E < 0) {
        return 0;
    }
    if (ActDataClone_225d40((void *)self, (int)arg1, (void *)src, (int)arg3, (int)arg4) == 0) {
        return 0;
    }
    self->unk2E = src->unk2E;
    if (src->unk28 != NULL) {
        n = src->unk2C;
        if (n <= 0) {
            goto done;
        }
        p = (Elem *)((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0(n * 0x34 + 0x10, arg3)), CharaTableDataCtor_2270e0, 0, 0x34, n));
        self->unk28 = p;
        if (p == NULL) {
            return 0;
        }
        self->unk2C = src->unk2C;
        for (i = 0; i < self->unk2C; i++) {
            CharaTableDataCopy_2269f0(&self->unk28[i], &src->unk28[i], arg3, arg4);
        }
    }
done:
    return 1;
}
