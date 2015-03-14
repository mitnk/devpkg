# devpkg
A Unix Tools Installer


## Cannot make bstrlib.o on Mac?

Change `#if defined(__GNUC__)` to `#if defined(__GNUC__) && !defined(__APPLE__)` in bstrlib.c


## original
http://c.learncodethehardway.org/book/ex26.html
