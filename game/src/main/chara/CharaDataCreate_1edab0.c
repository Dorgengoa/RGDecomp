/* rgp:protos */
#define RGP_SELF_CharaDataCreate_1edab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Slot {
    u8 pad0[0x28];
    s32 x28;
    u8 pad2C[8];
    s32 x34;
    u8 pad38[0x20];
} Slot;

typedef struct Self {
    u8 pad0[0xE80];
    Slot slots[3];
    s16 ids[3];
    s16 padF8E;
    u8 padF90[4];
    s32 heap;
} Self;

typedef struct Req {
    s32 id;
    s32 type;
    u8 pad8[0x1C];
    s32 size;
} Req;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaDataCreate_1edab0(Self *self, Req *req) {
    Slot *slot;
    void *obj;
    s32 buf;
    s32 id;
    s32 i;

    if (req == 0) {
        return 0;
    }
    if (CharaDataFindById_1ed990(self, req->id) != 0) {
        return 0;
    }
    slot = 0;
    i = 0;
    switch (req->type) {
    case 0:
        if ((obj = CharaDataFindFreeRec_1ed940(self)) == 0) {
            return 0;
        }
        id = req->id;
        if (id == 0x3E9) {
            self->ids[0] = id;
            slot = &self->slots[0];
        } else {
            for (i = 1; i < 3; i++) {
                if (self->ids[i] == -1) {
                    self->ids[i] = id;
                    slot = &self->slots[i];
                    break;
                }
            }
        }
        if (slot == 0) {
            return 0;
        }
        CharaDataRecInitMemStack_1ee5b0(obj, slot->x28, slot->x34);
        if (CharaDataRecAllocSubRecs_1ee3c0(obj, req) == 0) {
            MemStackReset_14d830(slot);
            self->ids[i] = -1;
            return 0;
        }
        break;
    case 2:
        if ((obj = CharaDataFindFreeRec_1ed940(self)) == 0) {
            return 0;
        }
        self->ids[0] = req->id;
        slot = &self->slots[0];
        CharaDataRecInitMemStack_1ee5b0(obj, self->slots[0].x28, self->slots[0].x34);
        if (CharaDataRecAllocSubRecs_1ee3c0(obj, req) == 0) {
            MemStackReset_14d830(slot);
            self->ids[0] = -1;
            return 0;
        }
        break;
    case 3:
        if ((obj = CharaDataFindFreeRec_1ed940(self)) == 0) {
            return 0;
        }
        self->ids[1] = req->id;
        slot = &self->slots[1];
        CharaDataRecInitMemStack_1ee5b0(obj, self->slots[1].x28, self->slots[1].x34);
        if (CharaDataRecAllocSubRecs_1ee3c0(obj, req) == 0) {
            MemStackReset_14d830(slot);
            self->ids[1] = -1;
            return 0;
        }
        break;
    case 4:
        if ((obj = CharaDataFindFreeRec_1ed940(self)) == 0) {
            return 0;
        }
        self->ids[2] = req->id;
        slot = &self->slots[2];
        CharaDataRecInitMemStack_1ee5b0(obj, self->slots[2].x28, self->slots[2].x34);
        if (CharaDataRecAllocSubRecs_1ee3c0(obj, req) == 0) {
            MemStackReset_14d830(slot);
            self->ids[2] = -1;
            return 0;
        }
        break;
    case 1:
        if (self->heap == 0) {
            return 0;
        }
        buf = MemStackHeapAllocFront_14dd10(self->heap, req->size);
        if (buf == 0) {
            return 0;
        }
        if ((obj = CharaDataFindFreeRec_1ed940(self)) == 0) {
            return 0;
        }
        CharaDataRecInitMemStack_1ee5b0(obj, buf, req->size);
        if (CharaDataRecAllocSubRecs_1ee3c0(obj, req) == 0) {
            MemStackReset_14d830(0);
            MemStackHeapFree_14dcb0(self->heap, buf);
            return 0;
        }
        break;
    }
    return 1;
}
