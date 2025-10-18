Calypsi board support for A2560 Foenix
======================================

This project contains a library and linker control files to make
it easy to get started on using the
[Calypsi C compiler](https://www.calypsi.cc/) for the A2560 Foenix.

Usage
-----

This board support is currently part of the Calypsi installation.
To use it you need to either compile and link with the command line
option `--target=a2560k` or `--target=a2560u`.  With this you
can include header files:

```
#include <foenix.h>
#include <mcp.h>
```

Pre-built libaries are also included in the installation and the one
matching your current compiler settings are automatically added to the
command line if not specified.

If you need to override or change anything, you can add files from
this board support to your project and modify them to suit. To get
changes part of the actual Calypsi product, create a pull request of
your changes.

Startup module
--------------

This project contains a startup module for A2560 Foenix that is
suitable for starting an application in its envionment. The default
startup module provided by the Calypsi tools is aimed at running from
a flash.

Stub interface
--------------

There is currently very limited stub functionality implemented in this
project. Basically only write to console and handle `exit()`. Feel
free to expand on it.

Notes on stack
--------------

The linker control files have been defined not to set up a stack and
relies on that the stack is already set up by the operating system (or
language environment) which load and run the application.

Alternative use
---------------

If you want more control, e.g. take over the machine completely then
you should probably take a look at the corresponding startup file and
example linker files provided in the Calypsi C compiler package.
