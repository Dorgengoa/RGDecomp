#!/usr/bin/env python3
"""Compile unlinked MAIN data candidates in the session UUID namespace."""
import json
import hashlib
import sys
import subprocess
import tarfile
from pathlib import Path
import data2c_runner as session

ROOT = session.ROOT
REMOTE = session.REMOTE + '-data'


def main():
    import data2c
    # The generated sources (src/main_data) and their manifest ship with the
    # release; data2c.generate() needs the project's git history, so it only
    # runs when the manifest is missing.
    if not (ROOT / 'handoff/data2c-manifest.json').exists():
        data2c.generate()
    log = ROOT / 'handoff/verify/baseline-build-retry.log'
    from data2c_integration import enabled
    native_ok = ROOT / 'build/obj/.data2c-native-build.ok'
    baseline_ok = log.exists() and 'built 17705/17705 on' in log.read_text(errors='replace')
    if not baseline_ok and not (enabled() and native_ok.exists()):
        raise SystemExit('Baseline compiler job must finish before candidate compilation.')
    subprocess.Popen = session.git_transport
    manifest = json.loads((ROOT / 'handoff/data2c-manifest.json').read_text())
    all_objects = manifest['objects']
    selected = set(sys.argv[1:])
    if selected == {'--changed'}:
        out = ROOT / 'build/data2c-obj'
        previous = json.loads((out / 'source-hashes.json').read_text())
        selected = {o['object'][:-2] for o in all_objects
                    if not (out / o['object']).exists() or
                    previous.get(o['source']) != hashlib.sha256((ROOT / o['source']).read_bytes()).hexdigest()}
        if not selected:
            print('No changed or missing generated data objects; no compiler job started.')
            return
        print('Changed data object selection:', ', '.join(sorted(selected)), flush=True)
    objects = [o for o in all_objects if not selected or o['object'][:-2] in selected]
    if selected - {o['object'][:-2] for o in objects}:
        raise SystemExit('unknown candidate object selection')
    out = ROOT / 'build/data2c-obj'
    out.mkdir(parents=True, exist_ok=True)
    if selected:
        previous = json.loads((out / 'source-hashes.json').read_text())
        for obj in all_objects:
            if obj not in objects and (not (out / obj['object']).exists() or
                    previous.get(obj['source']) != hashlib.sha256((ROOT / obj['source']).read_bytes()).hexdigest()):
                raise SystemExit('partial rebuild cannot preserve stale object: ' + obj['object'])
    cc = '../wibo ../mwcps2-3.0.1b210-060308/mwccps2.exe -O4 -c -Cpp_exceptions off -RTTI off -strings readonly -nostdinc -stderr -i include -sdatathreshold 0'
    commands = ''.join(cc + ' ' + o['source'] + ' -o ' + o['object'] + ' > ' + o['object'][:-2] + '.log 2>&1\n' for o in objects)
    (out / 'commands.txt').write_text(commands, newline='\n')
    with tarfile.open(out / 'input.tar.gz', 'w:gz') as tar:
        tar.add(ROOT / 'include/types.h', arcname='include/types.h')
        tar.add(out / 'commands.txt', arcname='commands.txt')
        for obj in objects:
            tar.add(ROOT / obj['source'], arcname=obj['source'])
    ssh = ['ssh', '-i', str(session.KEY), '-o', 'BatchMode=yes', '-o', 'StrictHostKeyChecking=no',
           '-o', 'UserKnownHostsFile=/dev/null', session.HOST]
    # Removing stale local objects is confined to this session's object dir.
    for obj in objects:
        (out / obj['object']).unlink(missing_ok=True)
    with (out / 'input.tar.gz').open('rb') as stream:
        subprocess.run(ssh + ['rm -rf ' + REMOTE + ' && mkdir -p ' + REMOTE + ' && tar xzf - -C ' + REMOTE], stdin=stream, check=True)
    # Exactly two compiler jobs; no background daemon or name-pattern kills.
    subprocess.run(ssh + ["cd " + REMOTE + " && tr -d '\\r' < commands.txt | xargs -P 2 -d '\\n' -I CMD sh -c CMD"], check=True)
    with (out / 'output.tar.gz').open('wb') as stream:
        subprocess.run(ssh + ['cd ' + REMOTE + ' && tar czf - *.o *.log'], stdout=stream, check=True)
    with tarfile.open(out / 'output.tar.gz') as tar:
        for member in tar.getmembers():
            if '/' in member.name or '\\' in member.name or member.name.startswith('.'):
                raise ValueError('unexpected archive path')
        tar.extractall(out)
    failures = [o['object'] for o in objects if not (out / o['object']).exists()]
    for obj in objects:
        message = (out / (obj['object'][:-2] + '.log')).read_text(errors='replace')
        if message.strip():
            print(obj['object'] + ': ' + message)
    print('Data candidates built %d/%d' % (len(objects)-len(failures), len(objects)))
    if failures:
        raise SystemExit('Missing: ' + ' '.join(failures))
    (out / '.built-by').write_text('host')
    (out / 'source-hashes.json').write_text(json.dumps({o['source']: hashlib.sha256((ROOT / o['source']).read_bytes()).hexdigest() for o in all_objects}, indent=2) + '\n', newline='\n')


if __name__ == '__main__':
    main()
