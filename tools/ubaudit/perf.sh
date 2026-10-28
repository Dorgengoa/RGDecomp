#!/bin/sh
# EE game-code cost per field from fixture states (docs/UB-AUDIT.md "Performance"):
#   tools/ubaudit/perf.sh EXE OUTDIR [REPS]
# For each window (field 8000+1000, battle 23000+1000, town 29060+600) loads the
# milestone state of EXE's fixture set, runs headless with RG_FIELD_TIMES and
# prints the mean step ms (the field's EE + emulated-pipeline step) per window.
exe=$1; out=$2; reps=${3:-1}
mkdir -p "$out"
for r in $(seq 1 $reps); do
  for w in field:1000 battle:1000 town:600; do
    m=${w%%:*}; n=${w##*:}
    RG_FIELD_TIMES="$out/$m.$r.tsv" python tools/fixtures/run_from.py "$m" --run "$n" --exe "$exe" --no-regen > "$out/$m.$r.log" 2>&1
    python - "$out/$m.$r.tsv" "$m" "$r" <<'PY'
import sys
v=[l.split() for l in open(sys.argv[1]) if l.split() and l.split()[0].isdigit()]
v=v[30:]  # skip the load transient
st=[float(x[2]) for x in v]; wa=[float(x[1]) for x in v]
pr=sorted(st[i]+st[i+1] for i in range(0,len(st)-1,2)); ss=sorted(st)
print(f"{sys.argv[2]:7s} rep{sys.argv[3]} n={len(v)} step_ms={sum(st)/len(st):.3f} frame_median={pr[len(pr)//2]:.3f} wall_ms={sum(wa)/len(wa):.3f}")
PY
  done
done
