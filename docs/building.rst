Building IndentByFold
=====================

To compile IndentByFold you can use `Visual Studio`_.
Project files for VS2019 are provided and actively used.
Visual Studio Community Edition is enough to get the job done.

There is also a `MinGW-w64`_ makefile, using both their 32-bit and 64-bit compilers.
It can be used from `Cygwin`_, MSYS2 and on Linux (including WSL).

.. _Visual Studio: https://visualstudio.microsoft.com/vs/
.. _MinGW-w64: https://mingw-w64.org/
.. _Cygwin: https://www.cygwin.com/

Know that the MinGW version of the DLL can't be loaded in Notepad++.
For some reason Notepad++ says the DLL is not compatible.


Building the documentation
--------------------------

The documentation of IndentByFold is written in `reStructuredText`_ and hosted
on `Read The Docs`_.

To build you need `Python Sphinx`_ and the `Sphinx RTD Theme`_.

You can build it with native Python Sphinx on Windows, WSL or Cygwin.

Use ``make html`` in the ``docs`` directory to generate the documentation.
Other forms of output are not used, but might work.

You can also build it is use the included ``Dockerfile``.

Run ``docker build -t python-sphinx .`` to build the image and
use ``docker run --rm -ti -v "%CD%":/docs python-sphinx make html``
to build the docs.

.. _reStructuredText: https://docutils.sourceforge.io/rst.html
.. _Read The Docs: https://readthedocs.org/
.. _Python Sphinx: https://www.sphinx-doc.org/
.. _Sphinx RTD Theme: https://sphinx-rtd-theme.readthedocs.io/
