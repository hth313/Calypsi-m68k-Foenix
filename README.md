Calypsi board support for A2560 Foenix
======================================

This project contains a library and linker control files to make
it easy to get started on using the
[Calypsi C compiler](https://www.calypsi.cc/) for the A2560 Foenix.

Usage
-----

This module is currently intended to be included as a Git submodule
in your own project. You can see examples of this in existing projects
such as
[Hello World for m68k](https://github.com/hth313/Calypsi-m68k-hello-world)
where this project is included under the `module` folder.

To attach this project to you project while standing in the root folder
of your project:

```
git submodule add https://github.com/hth313/Calypsi-m68k-Foenix.git module/Calypsi-m68k-Foenix
```

This will put the project under the `module` folder which can be a
good idea if you end up having more than one sub-module in your
project. You may need to create the `module` folder first.

Also note the use of HTTPS (`https://` prefix) rather than SSH
(`git@github.com:user` prefix) which is important if you want
to allow people to clone your project with the submodule.
If you use SSH it will require them to have SSH keys set up to
access your account and that will usually result in errors
for them, while it will work when you try it.

You can read more about working with Git submodules
[here](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

You need to commit some files in your project about the submodule.
There are two parts, one describes that you have a submodule and
its related paths. The other is the commit hash of the version you
are using.
The commit hash is used when the project is cloned later. That
actual version isthe one that will be checked out.

If you want to make changes to a submodule there are a couple of
things to pay attention to:

1. You probably want to fork the submodule project so you have a
   place where you can push your changes to.

2. You should add this forked version of the project as
   another `git remote`, e.g.
   `git remote add <name> <url>` where `<name> is the name you
   what to call this remote and the `<url>` is the SSH URL
   the fork you created.

3. Ensure that you are on a branch and not in a
   detached head state before you commit. You can do this
   using `git status`. If you are in detached head state, check
   out a branch, e.g. `git checkout main`.

4. Make changes and commit as you would normally do.

5. Push your changes to your code hosting platform, e.g. Github or Gitlab.

6. Inspect your actual (parent) project. It will have the new
   commit hash for the changed submodule, which you want to commit
   to your project and also push to your code hosting platform.

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
