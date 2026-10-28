/* SPDX-License-Identifier: CC0-1.0
 * Per-field host samples for $RG_FIELD_STATS (docs/PERF-3D.md "Transition stutter"):
 * process / calling-thread CPU time, page faults, private bytes and the CPU time of every
 * thread of the process, identified by its start address (tools/perf3d/stutter.py maps it
 * to a symbol with rg-game.map).  Diagnostics only: nothing here feeds back into a run. */
#include "fstats_sys.h"

#include <string.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <intrin.h>

typedef LONG(WINAPI *nqit_fn)(HANDLE, int, PVOID, ULONG, PULONG);

static struct {
    int inited;
    nqit_fn nqit;
    int n;
    HANDLE h[RG_FSTATS_MAX_THREADS];
    uint32_t tid[RG_FSTATS_MAX_THREADS];
    uint32_t start[RG_FSTATS_MAX_THREADS];
} T;

/* CPU time from cycle counts (QueryThreadCycleTime / QueryProcessCycleTime count TSC
 * reference cycles while the thread runs; GetThreadTimes only moves in 15.6 ms scheduler
 * ticks, too coarse for one field).  Cycles -> ms with the TSC rate measured against QPC
 * between samples (first call: a 20 ms calibration). */
static double g_cyc_per_ms;
static double cyc_rate(void)
{
    if (g_cyc_per_ms == 0.0) {
        LARGE_INTEGER f, a, b;
        QueryPerformanceFrequency(&f);
        QueryPerformanceCounter(&a);
        unsigned long long t0 = __rdtsc();
        Sleep(20);
        unsigned long long t1 = __rdtsc();
        QueryPerformanceCounter(&b);
        double ms = (double)(b.QuadPart - a.QuadPart) * 1000.0 / (double)f.QuadPart;
        g_cyc_per_ms = ms > 0.0 ? (double)(t1 - t0) / ms : 3e6;
    }
    return g_cyc_per_ms;
}


/* (re)open every thread of this process; threads already held are kept */
void rg_fstats_sys_refresh(void)
{
    if (!T.inited) {
        T.inited = 1;
        HMODULE nt = GetModuleHandleA("ntdll.dll");
        if (nt)
            T.nqit = (nqit_fn)(void (*)(void))GetProcAddress(nt, "NtQueryInformationThread");
    }
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snap == INVALID_HANDLE_VALUE)
        return;
    DWORD pid = GetCurrentProcessId();
    THREADENTRY32 te;
    te.dwSize = sizeof te;
    for (BOOL ok = Thread32First(snap, &te); ok; ok = Thread32Next(snap, &te)) {
        if (te.th32OwnerProcessID != pid)
            continue;
        int have = 0;
        for (int i = 0; i < T.n; i++)
            if (T.tid[i] == te.th32ThreadID) { have = 1; break; }
        if (have || T.n >= RG_FSTATS_MAX_THREADS)
            continue;
        HANDLE h = OpenThread(THREAD_QUERY_INFORMATION, FALSE, te.th32ThreadID);
        if (!h)
            continue;
        void *sa = NULL;
        if (T.nqit)
            T.nqit(h, 9 /* ThreadQuerySetWin32StartAddress */, &sa, sizeof sa, NULL);
        T.h[T.n] = h;
        T.tid[T.n] = te.th32ThreadID;
        T.start[T.n] = (uint32_t)(uintptr_t)sa;
        T.n++;
    }
    CloseHandle(snap);
}

void rg_fstats_sys_sample(rg_fstats_sys *s)
{
    memset(s, 0, sizeof *s);
    double r = cyc_rate();
    ULONG64 cyc = 0;
    if (QueryProcessCycleTime(GetCurrentProcess(), &cyc))
        s->proc_cpu_ms = (double)cyc / r;
    if (QueryThreadCycleTime(GetCurrentThread(), &cyc))
        s->main_cpu_ms = (double)cyc / r;
    s->main_tid = GetCurrentThreadId();
    s->image_base = (uint32_t)(uintptr_t)GetModuleHandleA(NULL);
    PROCESS_MEMORY_COUNTERS_EX pm;
    memset(&pm, 0, sizeof pm);
    pm.cb = sizeof pm;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pm, sizeof pm)) {
        s->page_faults = pm.PageFaultCount;
        s->private_kb = (uint64_t)pm.PrivateUsage / 1024u;
    }
    if (!T.inited)
        rg_fstats_sys_refresh();
    for (int i = 0; i < T.n; i++) {
        s->tid[i] = T.tid[i];
        s->start[i] = T.start[i];
        if (QueryThreadCycleTime(T.h[i], &cyc))
            s->thr_cpu_ms[i] = (double)cyc / r;
    }
    s->nthr = T.n;
}

#else /* POSIX: process and calling-thread CPU only */
#include <time.h>
#include <sys/resource.h>

void rg_fstats_sys_refresh(void) {}

void rg_fstats_sys_sample(rg_fstats_sys *s)
{
    memset(s, 0, sizeof *s);
    struct timespec ts;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts) == 0)
        s->proc_cpu_ms = (double)ts.tv_sec * 1e3 + (double)ts.tv_nsec / 1e6;
    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) == 0)
        s->main_cpu_ms = (double)ts.tv_sec * 1e3 + (double)ts.tv_nsec / 1e6;
    struct rusage ru;
    if (getrusage(RUSAGE_SELF, &ru) == 0)
        s->page_faults = (uint64_t)ru.ru_minflt + (uint64_t)ru.ru_majflt;
}
#endif
