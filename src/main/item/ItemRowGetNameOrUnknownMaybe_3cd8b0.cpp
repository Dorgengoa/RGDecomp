#include "types.h"

struct Item;

struct Slot {
    Item *item;
    bool b0 : 1;
    bool b1 : 1;

    bool Flag() const { return b0; }
};

extern "C" s32 ItemDefGetDisplayName_40e470(Item *item, char *buf, bool flag);
extern "C" char *strcpy(char *dst, const char *src);
extern "C" const char D_004663D0[];

extern "C" s32 ItemRowGetNameOrUnknownMaybe_3cd8b0(Slot *self, char *buf)
{
    if (buf == NULL) {
        return 0;
    }
    if (self->b1) {
        ItemDefGetDisplayName_40e470(self->item, buf, self->Flag());
    } else {
        strcpy(buf, D_004663D0);
    }
    return 1;
}
