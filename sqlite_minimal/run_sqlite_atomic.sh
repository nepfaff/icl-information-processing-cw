#!/bin/bash
set -e

make sqlite_atomic_minimal.o

./sqlite_atomic_minimal.o
