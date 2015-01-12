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
    
-------------------------------------------------------------------------------
  EXPANSION MODULE as an executable
  
  The expansion module can also be called as a standalone executable by running
  
  python -m bbl.expansion [options] -o:out_file in_file
  
  
  When running as an executable, you can provide the following options:
  
    * -f to overwrite existing files
    * -D:name=value to define a substitution variable
    * -o:out to define the output file
  
  
  If no input and/or output file is provided, an exception is thrown.
"""

import sys
import os.path
from . import err, fatal, msg

## Module version
__version__ = '0.0.2'

def expand_file(src, dest, vars, overwrite = False, newline = '\n'):
  """! Expands a template file.
    Transforms a template file to a destination file, expanding its
    @@-variables.
    
    Template files are text files which contain regular text and variables in
    the form @@VARSPEC@@, meant to be expanded to their values by this module.
    
    \code{.unparsed}
    VARSPEC = [+-]VARNAME
    VARNAME = <Name of the variable>
    +,- = <Respectively uppercase and lowercase substitution>
    
    Examples:
      @@AUTHOR@@  => "John Doe"
      @@+AUTHOR@@ => "JOHN DOE"
      @@-AUTHOR@@ => "john doe"
    \endcode
    
    \param src The path to the template file
    \param dest The path to the destination file. \p None to return the expanded file as a string
    \param vars A dictionary of variables/values to expand in the template file
    \param overwrite True if an existing destination file should be overwritten
    \param newline The newline character to use when transforming files
    
    \returns Nothing unless \p dest is set to \p {None}. In that case returns the expanded file as a string

    \throws FileExistsError if the destination file exists and \p overwrite is False
  """
  with open(src, 'r', encoding = 'utf_8') as input_file:
    if dest is not None:
      if os.path.exists(dest) and not overwrite:
        err('expansion.expand_file(): The destination file "{}" exists.'.format(dest))
        raise FileExistsError

      with open(dest, 'wt', newline = newline) as output_file:
        msg('Expanding file "{}" to file "{}"...'.format(src, dest), v = 5)
  
        for line in input_file:
          print(_expand_line(line, vars), end='', file=output_file)
    else: # Return expanded file as string
      msg('Expanding file "{}" to string...'.format(src), v = 5)
      lines = ''

      for line in input_file:
        lines += _expand_line(line, vars)

      return lines

def _expand_line(line, vars):
  """! Expands a line.
    Expands a line by expanding @@[+-]VARNAME@@ to its value in \p vars.

    \see expand_file()
  """
  for var in vars:
    line = line.replace('@@' + var + '@@', vars[var]) \
    .replace('@@+' + var + '@@', vars[var].upper()) \
    .replace('@@-' + var + '@@', vars[var].lower())

  return line

def _help():
  """! Module as a program help method """
  print('Usage: expansion.py [OPTIONS] -o:out_file in_file')
  print()
  
  print('OPTIONS:')
  print('\t-o:out_file\tOutput filename')
  print('\t-f\tOverwrite existing files')
  print('\t-D:name=value\tDefine variable')
  
def _main(args = sys.argv[1:]):
  """! Runs this module as a standalone program
  
    \param args The command line arguments to pass to the main method
  """
  vars = {}
  owrite = False
  
  for a in args:
    if a.startswith('-D:'):
      var = a[3:].split('=', 1)

      try:
        vars[var[0]] = var[1]
      except IndexError:
        vars[var[0]] = ''
    elif a.startswith('-o:'):
      out_file = a[3:]
    elif a == '-f':
      owrite = True
    elif a.startswith('-'):
      fatal('{} option not allowed'.format(a))
      sys.exit(1)
  try:
    if not args[-1].startswith('-'):
      in_file = args[-1]
    
    expand_file(in_file, out_file, vars, owrite)
  except NameError:
    _help()
    sys.exit(1)
  except IndexError:
    _help()
    sys.exit(1)
    
if __name__ == '__main__':
  _main()
