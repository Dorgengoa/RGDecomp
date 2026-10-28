/* SPDX-License-Identifier: CC0-1.0 */
/* rgprof: a minimal external sampling profiler for rg-game (i686).
 *   rgprof OUT.tsv PERIOD_MS EXE [ARGS...]
 * Starts EXE (inheriting the environment), and every PERIOD_MS suspends
 * each of its threads, records EIP and up to 12 stack words that point into
 * the exe image (candidate return addresses; the post-processor keeps the
 * ones preceded by a call), and resumes it.  Rows: t_ms tid eip w0 w1 ...
 * Module list (base size path) appended as "#mod" rows every few seconds. */
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <string.h>

static DWORD exe_lo = 0x400000, exe_hi = 0x400000 + 0x1000000;
static void write_mods(FILE *f, HANDLE p, double t)
{
    HMODULE m[512]; DWORD need = 0;
    if (!EnumProcessModules(p, m, sizeof m, &need)) return;
    int n = (int)(need / sizeof(HMODULE));
    for (int i = 0; i < n && i < 512; i++) {
        MODULEINFO mi; char path[MAX_PATH];
        if (!GetModuleInformation(p, m[i], &mi, sizeof mi)) continue;
        if (!GetModuleFileNameExA(p, m[i], path, MAX_PATH)) strcpy(path, "?");
        fprintf(f, "#mod\t%.1f\t%08lx\t%08lx\t%s\n", t, (unsigned long)(uintptr_t)mi.lpBaseOfDll,
                (unsigned long)mi.SizeOfImage, path);
        if (i == 0) { exe_lo = (DWORD)(uintptr_t)mi.lpBaseOfDll; exe_hi = exe_lo + mi.SizeOfImage; }
    }
}

int main(int argc, char **argv)
{
    if (argc < 4) { fprintf(stderr, "usage: rgprof OUT PERIOD_MS EXE [ARGS]\n"); return 2; }
    FILE *f = fopen(argv[1], "w");
    if (!f) return 2;
    int period = atoi(argv[2]);
    char cmd[8192] = "";
    for (int i = 3; i < argc; i++) {
        strcat(cmd, "\""); strcat(cmd, argv[i]); strcat(cmd, "\" ");
    }
    STARTUPINFOA si; PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof si); si.cb = sizeof si;
    if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess failed %lu\n", GetLastError()); return 2;
    }
    timeBeginPeriod(1);
    LARGE_INTEGER fq, t0, tn; QueryPerformanceFrequency(&fq); QueryPerformanceCounter(&t0);
    fprintf(f, "#pid\t%lu\n", pi.dwProcessId);
    ResumeThread(pi.hThread);
    HANDLE th[256]; DWORD tid[256]; int nth = 0;
    double last_enum = -1e9, last_mods = -1;
    static DWORD stk[1024];
    for (;;) {
        if (WaitForSingleObject(pi.hProcess, period) == WAIT_OBJECT_0) break;
        QueryPerformanceCounter(&tn);
        double t = (double)(tn.QuadPart - t0.QuadPart) * 1000.0 / (double)fq.QuadPart;
        if (t - last_enum > 500) {
            last_enum = t;
            HANDLE s = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
            THREADENTRY32 te; te.dwSize = sizeof te;
            if (Thread32First(s, &te)) do {
                if (te.th32OwnerProcessID != pi.dwProcessId) continue;
                int k; for (k = 0; k < nth; k++) if (tid[k] == te.th32ThreadID) break;
                if (k == nth && nth < 256) {
                    HANDLE h = OpenThread(THREAD_SUSPEND_RESUME | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION,
                                          FALSE, te.th32ThreadID);
                    if (h) { th[nth] = h; tid[nth] = te.th32ThreadID; nth++; }
                }
            } while (Thread32Next(s, &te));
            CloseHandle(s);
        }
        if ((t > 300 && last_mods < 0) || t - last_mods > 5000) { last_mods = t; write_mods(f, pi.hProcess, t); }
        for (int k = 0; k < nth; k++) {
            if (SuspendThread(th[k]) == (DWORD)-1) continue;
            CONTEXT c; memset(&c, 0, sizeof c);
            c.ContextFlags = CONTEXT_CONTROL;
            if (GetThreadContext(th[k], &c)) {
                SIZE_T got = 0;
                ReadProcessMemory(pi.hProcess, (LPCVOID)(uintptr_t)c.Esp, stk, sizeof stk, &got);
                fprintf(f, "%.2f\t%lu\t%08lx", t, tid[k], c.Eip);
                int n = 0;
                for (SIZE_T i = 0; i < got / 4 && n < 12; i++)
                    if (stk[i] >= exe_lo && stk[i] < exe_hi) { fprintf(f, "\t%08lx", stk[i]); n++; }
                fputc('\n', f);
            }
            ResumeThread(th[k]);
        }
    }
    DWORD rc = 0; GetExitCodeProcess(pi.hProcess, &rc);
    fprintf(f, "#exit\t%lu\n", rc);
    fclose(f);
    return (int)rc;
}
