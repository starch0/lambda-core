
(Note: You need x86 Linux to run this code.)

Get Language 84 version 0.8 from https://norstrulde.org/language84/ and unpack.

    $ wget https://norstrulde.org/language84/language84-0.8.tar.xz
    $ tar xfJ language84-0.8.tar.xz

Copy `lambda-core.84` and `local.make` from this repo into the `language84-0.8` directory created above.

Build

    $ make CC=clang

Run

    $ ./lambda-core
