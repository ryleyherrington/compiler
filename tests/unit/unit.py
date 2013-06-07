#!/usr/bin/env python
"""
"""
import os
import subprocess
import sys

def local_file(path):
    base = os.path.dirname(__file__)
    return os.path.join(base, path)

def run_tests():
    return subprocess.call([local_file('./unit_tests')])

if __name__ == '__main__':
   errors = run_tests()
   if errors:
       print 'Total errors: %d' % errors
   else:
       print 'All tests completed successfully.'
   sys.exit(errors)
