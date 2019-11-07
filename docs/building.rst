Building IndentByFold
=====================

To compile IndentByFold you can use `Visual Studio`_. Project files for VS2017
are provided and actively used. The free version of Visual Studio Express
gets the job done. Obviously the paid versions work as well.
To compile with newer versions of Visual Studio you can convert an existing
project file.

There is also a `MinGW-w64`_ makefile, using both their 32-bit and 64-bit compilers.
It can be used from `Cygwin`_, MSYS2 and on Linux (including WSL).

.. _Visual Studio: https://visualstudio.microsoft.com/vs/
.. _MinGW-w64: https://mingw-w64.org/
.. _Cygwin: https://www.cygwin.com/

Know that the MinGW version of the DLL can't be loaded in Notepad++. For some reason
Notepad++ says the DLL is not compatible. Still building with MinGW is done by
Travis CI to make sure the code compiles without errors.


Building the documentation
--------------------------

The documentation of IndentByFold is written in `reStructuredText`_ and hosted
on `Read The Docs`_.

To build on Windows you need `Python Sphinx`_. When using Cygwin you can install
the ``python-sphinx`` and ``make`` packages.

Use ``make html`` in the ``docs`` directory to generate the documentation.
Other forms of output are not used, but might work.

If you want the local docs the look like Read The Docs:
- Clone the `Sphinx RTD Theme`_.
- Create a directory named ``_themes`` in the ``docs`` directory.
- There you need to create a symlink to the ``sphinx_rtd_theme`` subdirectory
  in the cloned repo.

.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _Read The Docs: https://readthedocs.org/
.. _Python Sphinx: http://www.sphinx-doc.org/
.. _Sphinx RTD Theme: https://github.com/snide/sphinx_rtd_theme/
