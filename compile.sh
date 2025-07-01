#!/bin/bash
clear
COMPILER="gcc"

SOURCES="libs/OrbMaths.c libs/FileParser.c libs/CONVERSIONS.c libs/Algos.c libs/Body.c libs/TermFuncs.c main.c"

OUTPUT_DIR="output"

mkdir -p $OUTPUT_DIR

EXEC="SolSytem"

ARGS="-Wall -O3 -std=gnu17 -masm=intel -m64 -march=x86-64 -flto"
ARGS="-Wall -O3 -g -std=gnu17 -masm=intel -m64 -march=x86-64 -flto"

$COMPILER $ARGS $SOURCES -o $OUTPUT_DIR/$EXEC.out -lm