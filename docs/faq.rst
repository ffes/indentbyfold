Frequently Asked Questions
==========================

.. _faq_python:

**Q:** The plug-in works beautifully for HTML, but I couldn't get it to
work for Python. I open a new file, set the language to Python, start
typing - no indenting. I use the ``Reindent File`` command - no indenting.
What can I do to make it work?

**A:** Python has a bit of a conflict here, Python's fold points are
generated dependent on indentation, and this plug-in is dependent on
fold points to know how to do the indentation. Not really much I can do
about this I'm afraid. That's why ``Reindent File`` is disabled for
Python.

----------------------------------------------------------------------

.. _faq_css:

**Q:** In CSS, ``}`` brackets don't indent left like they do in the
C-styled languages. Between ``<style>`` tags in HTML, indentation doesn't
happen at all.

**A:** This is an issue with the CSS lexer in Scintilla [1]_, rather than in
IndentByFold. It's inconsistent in that it sets the next line's fold
level to be the same as the current.

----------------------------------------------------------------------

.. _faq_reindent_fails:

**Q:** The ``Reindent File`` command doesn't always work.

**A:** I investigated this quite thoroughly and think it has to do with caching
in Scintilla [1]_ or Notepad++ itself, although I obviously don't want to rule
out that it is something in the plugin. See `issue #2`_ for more details.

The easy work-around is to go to the last line of your file, run the command
``Reindent File`` from there and see that your file is reindented as expected.

----------------------------------------------------------------------

.. _faq_if_else:

**Q:** The plugin indents wrong in certain ``if else`` situations in various languages

My (JavaScript) code looks like this:

.. code-block:: javascript
    :emphasize-lines: 4

    function myFunction(args) {
        if (checkSomething(arg)) {
            doSomething(arg);
        } else {
            doSomethingElse(arg);
        }
    }

But after a ``Reindent File`` is looks like this:

.. code-block:: javascript
    :emphasize-lines: 4

    function myFunction(args) {
        if (checkSomething(arg)) {
            doSomething(arg);
            } else {
            doSomethingElse(arg);
        }
    }

**TL;DR:** Scintilla doesn't understand your code style and it's unlikely that I will fix it.

**A:** The whole idea of IdentByFold is to use the folding points that Scintilla [1]_
recognizes and tell Notepad++ to indent the code at those points. This makes the
plugin almost completely language independent! When you look at the ``[+]`` or ``[-]``
in the left margin you can see want those parsers thinks are folding points.

All the points mentioned in the various question I got those folding point don't
exist in the situations mentioned. There simply is no ``[+]`` or ``[-]`` at those lines.

There are two solutions to this issue. The best would be that the folding points
recognition by Scintilla is improved. This is an upstream fix for Scintilla that
I don't intend to develop.

The other is that the plugin will need to get languages specific solutions for
those languages that can recognizes this special cases and work around the
limitations of Scintilla. And I don't see myself doing that any time soon.

To give a little background. The plugin was originally developed by Ben Bluemel
in 2011. He abandoned it a little later and all I did was make sure it is still
around today because I like it the way it is. It suits my coding style and
it works good enough for me. The code has changed very little, in its core
it is still Ben's code. It doesn't have much comment and there are many points
in the code where I haven't got a clue what exactly is happening.

I really need to dig in to try and solve a problem that I never run in to
myself because I don't use that code style or those languages. Knowing that
I have many other projects (online and offline) that need my attention
I don't see that happen any time soon.

That all being said, I understand your problem. I will obviously gladly review
and merge pull requests that solve these problems. See `issue #1`_ for more details.

Know that when your style look like this, everything works as expected.
Note that the ``}`` is not on the same line as a ``{``.

.. code-block:: javascript
    :emphasize-lines: 4,5

    function myFunction(args) {
        if (checkSomething(arg)) {
            doSomething(arg);
        }
        else {
            doSomethingElse(arg);
        }
    }

.. _issue #1: https://github.com/ffes/indentbyfold/issues/1
.. _issue #2: https://github.com/ffes/indentbyfold/issues/2

.. [1] `Scintilla`_ is the source code editing component that Notepad++ is built around.

.. _Scintilla: https://www.scintilla.org/
