# Microshell
Microshell napisany na systemy operacyjne

```shell
MicroShell SOP
Autor: Bartosz Jackowiak
My implementation:
'cd ~' || 'cd' - Home directory
'cd -' - Previous directory
'cd ..' - Parent directory
'cd /etc' - Absolute path
'cd Downloads' - Relative path
Fork & exec example:
'ls -l -a' - 1 and more arguments
'exit'
```

Kompilacja
```shell
gcc -o microshell microshell.c
./microshell
```
