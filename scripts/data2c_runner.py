#!/usr/bin/env python3
"""Session-isolated build transport. Never uses the shared host workspaces."""
import os
import json
import re
import runpy
import shlex
import subprocess
import sys
import uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'scripts'))
SESSION_FILE = ROOT / 'build/data2c-session.json'
SESSION_FILE.parent.mkdir(parents=True, exist_ok=True)
if SESSION_FILE.exists():
    UUID = json.loads(SESSION_FILE.read_text())['uuid']
else:
    UUID = uuid.uuid4().hex
    SESSION_FILE.write_text(json.dumps({'uuid': UUID}) + '\n', newline='\n')
if not re.fullmatch('[0-9a-f]{32}', UUID):
    raise ValueError('invalid session UUID')
import rgd as _rgd
REMOTE = _rgd.REMOTE_ROOT + '/data2c-' + UUID
KEY = _rgd.SSH_KEY
HOST = _rgd.BUILD_HOST
BASH = os.environ.get('RGD_BASH', '')
original_popen = subprocess.Popen


def posix_path(value):
    value = str(value)
    if re.match(r'^[A-Za-z]:[/\\]', value):
        return '/' + value[0].lower() + '/' + value[3:].replace('\\', '/')
    return value


def git_transport(args, *a, **kw):
    if BASH and isinstance(args, (list, tuple)) and args and args[0] in ('ssh', 'scp'):
        args = list(args)
        if '-i' in args:
            args[args.index('-i') + 1] = str(KEY)
        args = [BASH, '-lc', 'exec ' + shlex.join([posix_path(v) for v in args])]
    return original_popen(args, *a, **kw)


def main():
    os.chdir(ROOT)
    subprocess.Popen = git_transport
    import rgd
    mode = sys.argv[1]
    if '--tag' in sys.argv:
        raise SystemExit('Use this session UUID namespace; --tag would override isolation.')
    if mode == 'build':
        import hostbuild
        hostbuild.REMOTE = REMOTE + '-compile'
        hostbuild.JOBS = 2
        native_args = sys.argv[2:]
        marker = rgd.OBJ_DIR / '.data2c-native-build.ok'
        if not native_args:
            marker.unlink(missing_ok=True)
        sys.argv = ['hostbuild.py'] + sys.argv[2:]
        result = hostbuild.main()
        if result == 0 and not native_args:
            marker.write_text('host')
            import data2c_integration
            if data2c_integration.enabled():
                import data2c_build
                sys.argv = ['data2c_build.py']
                data2c_build.main()
        return result
    if mode == 'link':
        import link
        link.REMOTE = REMOTE + '-link'
        sys.argv = ['link.py'] + sys.argv[2:]
        return link.main()
    raise SystemExit('usage: data2c_runner.py build|link [arguments]')


if __name__ == '__main__':
    raise SystemExit(main())
