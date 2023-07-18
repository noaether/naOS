- cpu has six segment register 
	- **cs** code segment, fetching instructions
	- **ss** stack segment, through *esp* stack pointer
	- **ds** data segment, data access
	- **es gs fs** used by os
**implicit use of segment registers**
```
    func:
        mov eax, [esp+4]
        mov ebx, [eax]
        add ebx, 8
        mov [eax], ebx
        ret
``` 
**explicit use of segment registers**
```
    func:
        mov eax, [ss:esp+4]
        mov ebx, [ds:eax]
        add ebx, 8
        mov [ds:eax], ebx
        ret
```

you dont ***need*** to use ds for ds and ss for ss - but don't be a snowflake and make your life easier by storing things in the right place even if you don't need to 