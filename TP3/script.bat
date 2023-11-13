@echo off
cls
echo "<inicio bison y flex>"
flex -l lexico.l
bison -dv sintaxis.y
gcc -o main sintactico.tab.c lex.yy.c -lfl
echo "<fin>"
