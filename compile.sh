#!/bin/bash
clear
COMPILER="gcc"

SOURCES="libs/OrbMaths.c libs/FileParser.c libs/CONVERSIONS.c libs/Algos.c libs/Body.c libs/TermFuncs.c libs/Files.c main.c"

OUTPUT_DIR="output"

mkdir -p $OUTPUT_DIR

EXEC="SolSystem"

ARGS="-Wall -O3 -mlong-double-128 -std=gnu23 -masm=intel -m64 -march=x86-64 -flto"
ARGS="-Wall -O0 -mlong-double-128 -g -std=gnu23 -masm=intel -m64 -march=x86-64 -flto"

$COMPILER $ARGS $SOURCES -o $OUTPUT_DIR/$EXEC.out -lm