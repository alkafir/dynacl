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

from sys import platform
from . import fatal, msg

def name_executable(name):
  """!
    Names an executable file following the platform's convention.
    
    \param name The platform independent name of the executable file
    
    \return A platform-dependent executable name
  """
  out_name = name

  if platform in ['cygwin', 'linux', 'darwin']:
    pass
  elif platform == 'win32':
    out_name += '.exe'
  else:
    fatal('Unknown platform')
    
  msg('Executable name set to "{}"'.format(out_name), v = 5)
  return out_name

def name_library_static(name):
  """!
    Names a static library following the platform's convention.
    
    \param name The platform independent name of the static library file
    
    \return A platform-dependent static library name
  """
  out_name = name

  if platform in ['cygwin', 'linux', 'darwin']:
    out_name = 'lib' + name + '.a'
  elif platform == 'win32':
    out_name += '.lib'
  else:
    fatal('Unknown platform')
    
  msg('Library name set to "{}"'.format(out_name), v = 5)
  return out_name

def name_library_dynamic(name):
  """!
    Names a dynamic library following the platform's convention.
    
    \param name The platform independent name of the dynamic library file
    
    \return A platform-dependent dynamic library name
  """
  out_name = name

  if platform in ['cygwin', 'linux', 'darwin']:
    out_name = 'lib' + name + '.so'
  elif platform == 'win32':
    out_name += '.dll'
  else:
    fatal('Unknown platform')
    
  msg('Dynamic library name set to "{}"'.format(out_name), v = 5)
  return out_name

if __name__ == '__main__':
  fatal('This script cannot be run on its own.')
