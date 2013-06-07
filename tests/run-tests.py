#!/usr/bin/env python
"""
"""
import subprocess
import sys

import functional
import unit

def main():
    errors = 0

    print 'Running unit tests'
    errors += unit.test()

    print 'Running functional tests'
    errors += functional.test()

    if errors:
        print 'Total errors: %d' % errors
    else:
        print 'All tests completed successfully.'
    sys.exit(errors)

if __name__ == '__main__':
    main()
