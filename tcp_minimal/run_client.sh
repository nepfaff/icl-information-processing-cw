#!/bin/bash
set -e

make tcp_client_minimal.o

./tcp_client_minimal.o
