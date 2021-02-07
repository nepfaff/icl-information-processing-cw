#!/bin/bash
set -e

make udp_client_minimal.o

./udp_client_minimal.o
