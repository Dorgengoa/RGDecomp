/* rg_slots.c: machine-wide limit on concurrent rg-game processes (USER 2026-10-17: at
 * most 2 at a time, so test runs don't starve the desktop).
 *
 * Runs before main: takes one of RG_SLOT_COUNT named mutexes ("Local\rg-game-slot-N"),
 * waiting until one is free. Mutexes, not a semaphore, so a crashed or killed run frees
 * its slot (WAIT_ABANDONED counts as acquired). The process also drops to
 * BELOW_NORMAL priority so interactive work stays responsive.
 * Both apply only to headless runs (`--headless` on the command line; 2026-10-22, launch by
 * double-click): a windowed game runs at normal priority without taking a slot.
 * Overrides, either way: RG_SLOTS_PRIORITY=normal|low picks the priority, RG_SLOTS=1|0
 * forces the slot wait on or off. */
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RG_SLOT_COUNT 2

static HANDLE g_slots[RG_SLOT_COUNT];

/* Before main, so argv is not parsed yet: look for a whole `--headless` token. */
static int rg_slots_headless(void)
{
    const wchar_t *c = GetCommandLineW();
    const size_t n = wcslen(L"--headless");
    for (const wchar_t *p = c; (p = wcsstr(p, L"--headless")) != NULL; p += n) {
        wchar_t before = p == c ? L' ' : p[-1], after = p[n];
        if ((before == L' ' || before == L'\t' || before == L'"') &&
            (after == 0 || after == L' ' || after == L'\t' || after == L'"'))
            return 1;
    }
    return 0;
}

__attribute__((constructor)) static void rg_slots_acquire(void)
{
    const int headless = rg_slots_headless();
    const char *prio = getenv("RG_SLOTS_PRIORITY");
    const char *slots = getenv("RG_SLOTS");
    int low = prio && *prio ? strcmp(prio, "normal") != 0 : headless;
    int wait = slots && *slots ? strcmp(slots, "0") != 0 : headless;
    if (low)
        SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
    if (!wait)
        return;

    for (int i = 0; i < RG_SLOT_COUNT; i++) {
        wchar_t name[64];
        swprintf(name, 64, L"Local\\rg-game-slot-%d", i);
        g_slots[i] = CreateMutexW(NULL, FALSE, name);
        if (!g_slots[i])
            return; /* cannot enforce; run anyway */
    }
    DWORD r = WaitForMultipleObjects(RG_SLOT_COUNT, g_slots, FALSE, 0);
    if (r == WAIT_TIMEOUT) {
        fprintf(stderr, "rg-game: %d runs already active, waiting for a free slot...\n",
                RG_SLOT_COUNT);
        fflush(stderr);
        r = WaitForMultipleObjects(RG_SLOT_COUNT, g_slots, FALSE, INFINITE);
    }
    (void)r; /* slot held until the process exits */
}
#endif
