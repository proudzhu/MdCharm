#!/usr/bin/python3

import os
import sys
from datetime import datetime

if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.exit(1)
    if sys.argv[1] == "debug":
        if os.path.isfile("version.h"):
            print('Already Exist')
            sys.exit(0)
    with open('../../src/MdCharm/version.h.in') as version_h_file:
        version_h = version_h_file.read()
    with open('../../src/MdCharm/mdcharm.rc.in') as mdcharm_rc_file:
        mdcharm_rc = mdcharm_rc_file.read()
    revision_output = os.popen('git log -1 --format="%H"')
    if revision_output:
        revision = str(revision_output.read()).strip()
    else:
        sys.exit(2)
    tag_output = str(os.popen('git tag').read()).strip()
    if tag_output:
        tag = tag_output.replace('\r\n', '\n').split('\n')[-1]
    else:
        sys.exit(3)
    if len(tag.split('.')) != 3:
        sys.exit(4)
    version_list = tag.split('.')
    ntime_str = datetime.now().strftime('%B %d %Y %H:%M:%S +0800')
    real_version_h = version_h.strip().format(tag,
                                              version_list[0],
                                              version_list[1],
                                              version_list[2],
                                              revision,
                                              ntime_str)
    with open("../../src/MdCharm/version.h", 'w+') as version_header_file:
        version_header_file.write(real_version_h)
    real_rc_file = mdcharm_rc.format(version_list[0], version_list[1], version_list[2], 0, tag)
    with open("../../src/res/mdcharm.rc", 'w+') as rc_file:
        rc_file.write(real_rc_file)
