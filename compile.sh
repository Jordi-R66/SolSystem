#!/bin/bash
clear
COMPILER="gcc"

SOURCES="libs/Files.c libs/OrbMaths.c libs/FileParser.c libs/CONVERSIONS.c libs/Algos.c libs/TermFuncs.c main.c"

OUTPUT_DIR="output"

mkdir $OUTPUT_DIR

EXEC="SolSytem"

ARGS="-Wall -O3 -std=c17 -m64 -march=x86-64 -flto"

$COMPILER $ARGS $SOURCES -o $OUTPUT_DIR/$EXEC -lm