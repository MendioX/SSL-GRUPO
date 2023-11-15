@echo off
cls
echo "<inicio bison y flex>"
flex -l lexico.l
bison -yd sintaxis.y
gcc y.tab.c lex.yy.c -lfl -o output
echo "<fin>"
