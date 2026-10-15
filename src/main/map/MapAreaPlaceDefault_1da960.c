#include "types.h"
typedef struct { f32 w[4]; } SD4_0047E370;
extern SD4_0047E370 D_0047E370 __attribute__((section(".sdata")));

extern void MapAreaPlace_1da680(void *, void *, f32);

void MapAreaPlaceDefault_1da960(void *self)
{
    f32 sp10[4];

    *(SD4_0047E370 *)sp10 = D_0047E370;
    MapAreaPlace_1da680(self, sp10, 0.0f);
}
