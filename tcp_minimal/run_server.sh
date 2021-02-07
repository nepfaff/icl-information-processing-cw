#!/bin/bash
set -e

make tcp_server_minimal.o

./tcp_server_minimal.o
