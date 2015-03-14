# devpkg
A Unix Tools Installer

## Dependencies

- Apache Portable Runtime https://apr.apache.org/
- bstrlib.{c,h} http://bstring.sourceforge.net/


## Cannot make bstrlib.o on Mac?

Change `#if defined(__GNUC__)` to `#if defined(__GNUC__) && !defined(__APPLE__)` in bstrlib.c


## Original
http://c.learncodethehardway.org/book/ex26.html
