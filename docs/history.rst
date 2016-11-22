Revision History
================

Version XXX (Yet To Be Released)
--------------------------------

-  Provide a 64-bit version of the plug-in.

-  Converted the documentation from DocBook to reStructuredText.


Version 0.7.1 (2013-04-17)
--------------------------

-  Frank Fesevur has taken over the maintenance of this plug-in.

-  Fixed: Reindent file is now one undo action.

-  Fixed: Disabled "Reindent File" for Python, see :ref:`the FAQ <faq_python>`
   for more details.

-  Restructured the source files to personal preference.

-  Solution files for VS2005 are provided as well.

-  Started to write documentation using DocBook. This is the first
   result. The current FAQ is based upon issues posted on `Ben's
   BitBucket`_ page. The revision history until version 0.7 are taken
   from the `forum post`_ about this plug-in.

.. _FAQ: #faq_python_1
.. _Ben's BitBucket: https://bitbucket.org/bbluemel/indentbyfold/issues
.. _forum post: http://sourceforge.net/p/notepad-plus/discussion/482781/thread/246f82f6


Version 0.7 (2011-09-18)
------------------------

-  This release fixes issues with certain lexers that notify on the
   following line (Ruby, HTML, Lisp, Lua, Pascal, XML). For these lexers
   you need to have a line following the one you are typing on.

-  The following screencast shows it in use and how it works:
   http://screencast.com/t/tUD2nfeLX


Version 0.6 (2011-06-19)
------------------------

-  This changes IndentByFold to more heavily rely on the
   SC\_MOD\_CHANGEFOLD notification from Scintilla.

   This means that when you end a fold (e.g. with a } ) it will unindent to
   the same level as the start of the fold.

-  One Bonus feature of this handles } else {, in that it will unindent at
   the }, and when you have else {, it will know that the fold has
   increased again, so will on the next line increase the indent.

   NOTE: This can only do it in one go (i.e. you can't go onto a line with
   }, and type in else {, and expect it to be indented on the next line, as
   it won't have known that it unindented for the }. I may be able to work
   around this at some point, so we shall see, but hopefully not too much
   of an issue.

-  Same goes for the Reindent file, because it doesn't actually have a
   logged decrement of the fold at } else {, it looks to the reindent code
   that it's remained at the same level ( so won't decrement the
   indentation for } else { )


Version 0.5 (2011-05-21)
------------------------

-  Idea behind this plug-in is rather simple, if the fold level increases
   or decreases, so should the indentation.

-  Using C-like languages as an example:

   Typing in { and pressing enter, will mean the line you are now on, has
   1 more level of indent than the {.

   Typing in } and pressing enter, will match the indentation of { line, so
   the } is now lined up properly.

-  There is also an option in the plug-in menu to reindent the file based
   on the fold levels.
