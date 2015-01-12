from foundry import *
from foundry.naming import *

PROJECT_NAME = 'DynaCL'
LIB_NAME = name_library_static(PROJECT_NAME.lower())

srcdir = 'src/'
includedir = 'include/'
testdir = 'test/'

@Target('compile')
def target_compile():
  """ Compiles the sources """
  sources = dir_filter_ext(srcdir, 'c')
  objects = source_object_assoc(sources, 'c', 'o')

  for src, obj in objects.items():
    if needs_compile(src, obj):
      check_call('gcc -c -o {obj} -I{includedir} {src}'.format(obj=obj, src=src, includedir=includedir))

@Target('build', deps=('compile',), default=True)
def target_build():
  pass

@Target('clean', deps=('clean-tests',))
def target_clean():
  objects = dir_filter_ext(srcdir, 'o')

  for obj in objects:
    remove(obj)

@Target('build-tests', deps=('build',))
def target_tests_build():
  """ Builds the tests """
  sources = dir_filter_ext(testdir, 'c')
  objects = source_object_assoc(sources, 'c', 'exe')

  for src, exe in objects.items():
    if needs_compile(src, exe):
      check_call('gcc -o {exe} -I{includedir} src/dynacl.o {src}'.format(exe=exe, src=src, includedir=includedir))

@Target('test', deps=('build-tests',))
def target_tests_run():
  """ Runs the tests """
  tests = dir_filter_ext(testdir, ('exe',))

  for test in tests:
    print('Running test "{0}"...'.format(test))
    call(test)

@Target('clean-tests')
def target_tests_clean():
  """ Cleans the tests """
  tests = dir_filter_ext(testdir, ('exe',))

  for test in tests:
    remove(test)

run_foundry()
