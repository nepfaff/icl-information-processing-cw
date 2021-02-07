#!/bin/bash
set -e

make udp_server_minimal.o

./udp_server_minimal.o
