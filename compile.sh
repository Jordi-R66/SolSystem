#!/bin/bash
clear
COMPILER="gcc"

SOURCES="libs/OrbMaths.c libs/FileParser.c libs/CONVERSIONS.c libs/Algos.c libs/Body.c libs/TermFuncs.c libs/TimeFuncs.c libs/Files.c main.c"

OUTPUT_DIR="output"

mkdir -p $OUTPUT_DIR
mkdir -p asm

EXEC="SolSystem"

ARGS="-Wall -std=gnu23 -masm=intel -m64 -Oz -flto -ffunction-sections -fdata-sections -Wl,--gc-sections -s -fomit-frame-pointer -march=x86-64-v3 -mtune=generic -fmerge-all-constants -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-exceptions -fno-stack-protector -fno-plt -Wl,--strip-all"
#ARGS="-Wall -O0 -g -std=gnu23 -masm=intel -m64 -march=x86-64"

$COMPILER $ARGS $SOURCES -o $OUTPUT_DIR/$EXEC.out -lm

$COMPILER $ARGS $SOURCES -lm -S

mv *.s asm/