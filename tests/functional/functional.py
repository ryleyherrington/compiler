#!/usr/bin/env python
"""
"""
import os
import subprocess
import sys


class Scheme(object):
    def run(self, source):
        proc = subprocess.Popen(['guile', source],
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE)
        return proc.communicate()


class Gforth(object):
    def run(self, source):
        proc = subprocess.Popen(['gforth', source, '-e', 'bye'],
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE)
        return proc.communicate()


class Compiler(object):
    def __init__(self):
        self.path = local_file('../../compiler')

    def tokenize(self, source):
        return self.run(source, '-t')

    def parse(self, source):
        return self.run(source, '-p')

    def run(self, source, mode='', output=subprocess.PIPE):
        args = [self.path, source]
        if mode:
            args.insert(1, mode)
        proc = subprocess.Popen(args,
                                stdout=output,
                                stderr=subprocess.PIPE)
        return proc.communicate()


def file_text(path):
    with open(path, 'r') as open_file:
        return open_file.read()


def local_file(path):
    base = os.path.dirname(__file__)
    return os.path.join(base, path)


def run_lexer_tests():
    errors = 0
    golden = file_text(local_file('golden.out'))
    compiler = Compiler()
    (out, err) = compiler.tokenize(local_file('guest.lisp'))

    if err:
        print 'ERROR: stderr not empty'
        print err
        errors += 1
    if out != golden:
        print 'ERROR: output did not match expected'
        print out
        errors += 1

    return errors


def run_parser_tests():
    errors = 0
    golden = file_text(local_file('golden_parse.out'))
    compiler = Compiler()
    (out, err) = compiler.parse(local_file('float.ibtl'))

    if err:
        print 'ERROR: stderr not empty'
        print err
        errors += 1
    if out != golden:
        print 'ERROR: output did not match expected'
        print out
        errors += 1

    return errors


def run_translator_tests():
    errors = 0
    compiler = Compiler()
    scheme = Scheme()
    gforth = Gforth()

    with open(local_file('simple.fs'), 'w') as output:
        compiler.run(local_file('simple.scm'), output=output)

    (expected, err) = scheme.run(local_file('simple.scm'))
    (out, err) = gforth.run(local_file('simple.fs'))

    if (expected != out):
        print 'ERROR: Gforth output did not match Scheme output'
        print 'Scheme source:'
        print file_text(local_file('simple.scm'))
        print 'Scheme results:'
        print expected
        print 'Gforth source:'
        print file_text(local_file('simple.fs'))
        print 'Gforth results:'
        print out
        errors += 1

    return errors


def run_tests():
    errors = 0
    print "Running lexer tests"
    errors += run_lexer_tests()
    print "Running parser tests"
    errors += run_parser_tests()

    # These tests are diabled because I have yet to find a true equivalent for
    # println in Gforth. The closest apporximation to (println 10) is 10 . CR,
    # but while the former prints "10\n", the latter prints "10 \n". Unless we
    # find a way around this, we can't actually use this kind of testing and
    # will have to resort to more primitive methods. Of course, all of this is
    # irrelevant if we can't get our hands on an ibtl interpreter/compiler.
    #errors += run_translator_tests()
    return errors


if __name__ == '__main__':
   errors = run_tests()

   if errors:
       print 'Total errors: %d' % errors
   else:
       print 'Tests completed successfully.'

   sys.exit(errors)
