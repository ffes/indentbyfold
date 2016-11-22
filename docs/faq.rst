Frequently Asked Questions
==========================

.. _faq_python:

**Q:** The plug-in works beautifully for HTML, but I couldn't get it to
work for Python. I open a new file, set the language to Python, start
typing - no indenting. I use the "Reindent File" command - no indenting.
What can I do to make it work?

**A:** Python has a bit of a conflict here, Python's fold points are
generated dependent on indentation, and this plug-in is dependent on
fold points to know how to do the indentation. Not really much I can do
about this I'm afraid. That's why "Reindent File" is disabled for
Python.

**Q:** In CSS, "}" brackets don't indent left like they do in the
C-based languages. Between ``<style>`` tags in HTML, indentation doesn't
happen at all.

**A:** This is an issue with the CSS lexer in Scintilla, rather than in
IndentByFold. It's inconsistent in that it sets the next line's fold
level to be the same as the current.
