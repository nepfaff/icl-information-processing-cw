#!/bin/bash
set -e

IPv4Address="$1";

make tcp_client_minimal.o

./tcp_client_minimal.o $IPv4Address
