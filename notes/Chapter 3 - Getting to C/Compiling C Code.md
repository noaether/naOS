- since we are [[Calling C Code From Assembly]], there is no standard libraries
	- means a lot of gcc flags need to be used
	- C code shouldn't assume the presence of a stdlib
```
-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector     -nostartfiles -nodefaultlibs
```
- when writing C code, recommended to turn on all warnings
```
    -Wall -Wextra -Werror
```
- now can save [[Calling C Code From Assembly|C code]] to kmain.c, [[Calling C Code From Assembly|called]] with loader.s