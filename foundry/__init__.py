"""
Babilonia project: Utility library and framework for C11/Python3
    Copyright (C) 2014  Alfredo Mungo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""

import sys
import os
import os.path
import concurrent.futures
import subprocess

## Module version
__version__ = '0.0.11'

## Verbosity level
_verbosity = 4

## Number of threads for parallel-enabled operations
_parallel_queues = 1

if __name__ == '__main__':
  print('This module cannot be run on its own', file=sys.stderr)
  os.abort()

# Ensure the CWD is always the script's directory
os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))
  
## Registered targets
_targets = {}

## Default target
_default_target = None

def Target(name, deps = [], repeatable = False, default = False, private = False):
  """!
    Target decorator
    
    \param name The target name
    \param deps A list of dependencies
    \param repeatable True if the target should be called more than once
    \param default True if this target should be the default target
    \param private True if the target should not appear in the target list
  """
  def wrap(func):
    global _targets, _default_target
    
    _targets[name] = _Target(name, func, deps, repeatable, default, private)
    
    if default:
      _default_target = _targets[name]
      
    def wrap_f(*args, **kwargs):
      func(*args, **kwargs)
      
    return wrap_f
    
  return wrap
  
class _Target:
  """!
    This private class represents a target inside the module.
  """
  def __init__(self, name, func, deps = [], repeatable = False, default = False, private = False):
    """!
      \param name The target name
      \param func The target function
      \param deps A list of dependency targets
      \param repeatable True if the target can be called multiple times
      \param default True if the target is the default target
      \param private True if the target should not appear in the target list
    """
    
    ## Target name
    self.name = name
    
    ## Target function
    self.target = func
    
    ## Target dependencies
    self.dependencies = deps[:]
    
    ## Target may be called multiple times
    self.repeatable = repeatable
    
    ## Target is the default target
    self.default = default
    
    ## Target is private
    self.private = private
    
    ## Target has already been called
    self.called = False
    
    ## Target is currently being called
    self.calling = False # True if the target is currently being called
    
  def call(self):
    """!
      Calls the target function, if it should be called.
    """
    self.calling = True
    
    if not self.called or self.repeatable:
      for dep in self.dependencies:
        try:
          if not _targets[dep].calling:
            _targets[dep].call()
          else:
            warn('Cyclic dependencies detected [' + self.name + ', ' + _targets[dep].name + ']')
        except KeyError:
          err('Unknown target \'' + dep + '\' dependency of \'' + self.name + '\'')
          sys.exit(1)
          
      msg('Current target: ' + self.name)
      self.target()
      self.called = True
    
    self.calling = False
    print()

@Target('targets', default=True, private=True)
def target_targets():
  """! Prints this message. """
  for tgt in _targets:
    if _targets[tgt].private is False:
      print(tgt + (' (DEFAULT)' if _targets[tgt].default else ''), end='')
      
      if _targets[tgt].target.__doc__ != None:
        print(' - ' + _targets[tgt].target.__doc__.strip())
      else:
        print()
      
def call_target(tgt):
  """!
    Calls a target function.
    
    \param tgt The target function
  """
  if tgt in _targets:
    _targets[tgt].call()
  else: target_targets()
  
def fatal(s):
  """!
    Prints an error message and exits.
  
    \param s The error message to log
  """
  err(s)
  sys.exit(1)
  
def err(s, fatal = False):
  """!
    Prints an error message.
    
    \param s The error message to log
    \param fatal True if this is a fatal error
  """
  if (_verbosity > 0 and fatal) or (_verbosity > 1):
    print(('ERROR: ' if not fatal else 'FATAL: ') + s, file=sys.stderr)
  
def msg(s, v = 4):
  """!
    Logs a message.
  
    \param s The message to log
    \param v The verbosity of the message

    \see set_verbosity()
  """
  if _verbosity >= v:
    print(s if v < 5 else 'DEBUG: ' + s)
  
def warn(s):
  """!
    Warning message logging.
  
    \param s The warning message to log
  """
  if _verbosity >= 3:
    print('Warning: ' + s, file=sys.stderr)

def _handle_switch(sw):
  """!
    Handles switches in command line.
    
    \param sw The switch to handle
  """
  try:
    if sw.startswith('-v:'):
      set_verbosity(int(sw[3:]))
    elif sw == '-h' or sw == '--help':
      _help()
      sys.exit(0)
    elif sw.startswith('-D:'):
      _export_switch_variable(sw[3:])
    elif sw.startswith('-n:'):
      global _parallel_queues
      _parallel_queues = int(sw[3:])
      msg('Set {} parallel queues.'.format(_parallel_queues), v = 5)
    else:
      err('Unknown switch value "{}"'.format(sw))
      _help()
      sys.exit(1)
  except ValueError:
    err('Error in command line arguments')
    _help()
    sys.exit(1)

def _export_switch_variable(svar):
  """! Exports a command line variable
    Exports a command line variable as an environment variable.

    \param svar The variable in the form 'name=value'
  """
  var = svar.split('=', 1)

  os.environ[var[0]] = var[1]

def _help():
  """! Shows the foundry help message """
  print('Babilonia\'s Foundry command line switches:')
  print()

  print('\t-v:N\t\tSets the verbosity of the build script (1 to 5)')
  print('\t-h\n\t--help\t\tShows this message')
  print('\t-D:name=value\tManually define an environment variable')

def _handle_switches():
  """! Checks the command line switches
  """
  for arg in sys.argv[1:]:
    if arg.startswith('-'):
      _handle_switch(arg)

def run_foundry():
  """!
    Runs the foundry standard behavior.
  """
  called_target = False
  
  for arg in sys.argv[1:]:
    if not arg.startswith('-'):
      call_target(arg)
      called_target = True
      
  if not called_target:
    if _default_target is not None:
      _default_target.call()
    else:
      warn('Default target not set')
      print()
      target_targets()

def dir_filter(src, filter, subdirs = True):
  """!
    Filters the files contained in \p src (or in its full tree) according to
    a filter function.
    
    The filter function must accept a file path as its argument and return
    True if the file should be added to the output, False if not.
    
    \param src The toplevel directory path
    \param filter A callable object which accepts a file path relative to \p src and returns a boolean value
    \param subdirs True if the output should also contain files in subdirectories
    
    \return An iterable object containing the filtered files of \p src
  """
  files = []
  
  for f in os.listdir(src):
    fpath = os.path.join(src, f)
    if os.path.isdir(fpath):
        if subdirs: files += dir_filter(fpath, filter, subdirs)
    elif filter(fpath):
      fpath = os.path.normpath(fpath)
      files.append(fpath)
      msg('Filter accepted file ' + fpath, v = 5)
  
  return files
  
def dir_filter_all(src, subdirs = True):
  """!
    Returns all files contained in a directory (tree).

    \param src The toplevel directory path
    \param subdirs True if the output should also contain files in subdirectories

    \return An iterable object containing the files of \p src
  """
  return dir_filter(src, lambda x: True, subdirs)

def dir_filter_ext(src, ext, subdirs = True):
  """! Filters files by extension
    Filters the files contained in \p src (or in its full tree) according to
    the supplied extensions.

    \param src The toplevel directory path
    \param ext An iterable object containing the file extensions to filter (without dot)
    \param subdirs True if the output should also contain files in subdirectories
    
    \return An iterable object containing the filtered files of \p src
    
    \sa dir_filter()
  """
  return dir_filter(src, lambda f: f.endswith(tuple(set(['.' + x for x in ext]))), subdirs)
  
def dir_filter_filename(src, fnames, remove_ext = False, subdirs = True):
  """! Filters files by name
    Filters the files contained in \p src (or in its full tree) according to
    the supplied filename.

    \param src The toplevel directory path
    \param fnames An iterable object containing the file names to filter
    \param remove_ext True to remove the extension before checking the filename, False to check the file along with its extension
    \param subdirs True if the output should also contain files in subdirectories
    
    \return An iterable object containing the filtered files of \p src
    
    \sa dir_filter()
  """
  def filter_f(f):
    f = os.path.basename(f) if not remove_ext else os.path.splitext(os.path.basename(f))[0]
    return f in fnames
  return dir_filter(src, filter_f, subdirs)

def source_object_assoc(sources, sext, oext):
  """! Associates sources with default objects
    Creates a dictionary object of which the keys are the provided source files
    and the values are their object file names. The default object file names
    are the source file names without their extension to which is appended the
    object file extension provided.
    
    \param sources An iterable object containing the source files
    \param sext The source file extension (without dot)
    \param oext The object file extension (without dot)
  """
  se_len = len(sext)
  srcs = tuple(sources)

  return dict(zip(srcs, [f[:-se_len] + oext for f in srcs]))

def set_verbosity(v):
  """! Sets the verbosity level
    Sets the verbosity level to \p v. \p v must be an integer number from 0 to
    5.

    The foundry uses verbosity this way:
    \li 0 - Silent running, no message is shown
    \li 1 - Silent running, only fatal errors are reported
    \li 2 - Silent running, every error is reported
    \li 3 - Normal running, warning messages are reported
    \li 4 - Normal running, warning messages and information messages are reported
    \li 5 - Verbose running, warning, information, and debug messages are reported

    Target change messages are shown with verbosity level greater than 1.
    
    \note
      Verbosity level is automatically set form command line. This method is
      used to allow overriding the default behavior.
  """
  global _verbosity

  if v >= 0 and v <= 5:
    _verbosity = v
    msg('Verbosity set to %d' % v, v = 5)
  else:
    warn('Verbosity level out of range. Setting default value of 4...')
    _verbosity = 4

def get_parallel_queues():
  """! Returns the number of parallel queues.
    Returns the number of parallel queues that will be used in parallel-enabled
    operations when no override is present.
  """
  return _parallel_queues

def get_verbosity():
  """! Returns the verbosity state
    \returns The current verbosity state
  """
  return verbosity

def parallel_call(func, args, threads = get_parallel_queues()):
  """! Parallel function call
    Enables a function to be executed in parallel.

    \param func The function to be executed
    \param args An iterable object of tuples, each one containing the arguments to be given to each function call
    \param threads The maximum number of function calls to be executed simultaniously
  """
  with concurrent.futures.ThreadPoolExecutor(threads) as xtor:
    res = xtor.map(func, *zip(*args))
    try:
      for r in res: pass
    except:
      xtor.shutdown()
      raise

def needs_compile(src, obj):
  """!
    Checks if a source file should be recompiled.
    
    \param src The source file path to check for compile
    \param obj The object file path the source needs to be compiled to
    
    \return True if the source file should be recompiled, false if not
    
    \throws FileNotFoundError If the source file does not exist
  """
  if os.path.isfile(obj):
    src_date = os.path.getmtime(src)
    obj_date = os.path.getmtime(obj)
        
    return (src_date - obj_date) > 0
  else:
    return True

def needs_link(obj, exe):
  """!
    Checks if an object file should be relinked.
    
    \param obj The object file path to check for linkage
    \param exe The executable path to check for linkage
    
    \return True if the object file should be relinked, false if not
    
    \throws FileNotFoundError If the object file does not exist
  """
  if os.path.isfile(exe):
    exe_date = os.path.getmtime(exe)
    obj_date = os.path.getmtime(obj)
        
    return (obj_date - exe_date) > 0
  else:
    return True

def call(args, stdin = None, stdout = None, stderr = None):
  """! Calls an external program

    \see subprocess.call()
  """
  msg(args)
  return subprocess.call(args, stdin = stdin, stdout = stdout, stderr = stderr, shell = True)

def check_call(args, stdin = None, stdout = None, stderr = None):
  """! Calls an external program
    Calls an external program and throws \p subprocess.CalledProcessError if
    return value is not 0.

    \see subprocess.check_call()
  """
  msg(args)
  return subprocess.check_call(args, stdin = stdin, stdout = stdout, stderr = stderr, shell = True)

def remove(f):
  """! Removes a file
    Removes an existing file.
    If the file does not exist or is not a file, does nothing.

    \param f The file to remove
  """
  if os.path.isfile(f):
    msg('Removing file \'{}\'...'.format(f))
    os.remove(f)

def mkdir(path, mode = 0o777, dir_fd = None):
  """! Creates a directory
    Creates an empty directory. If the directory already exists, does nothing.

    \see os.mkdir()
  """
  try:
    os.mkdir(path, mode, dir_fd)
    msg('Created directory \'%s\'' % path)
  except OSError:
    pass

# Check the command line switches
_handle_switches()
