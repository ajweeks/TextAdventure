@echo off

call java org.antlr.v4.Tool -Dlanguage=Cpp -visitor -o generated resources/textworld.g4

PAUSE