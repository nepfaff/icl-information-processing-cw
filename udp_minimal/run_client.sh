#!/bin/bash
set -e

IPv4Address="$1";

make udp_client_minimal.o

./udp_client_minimal.o $IPv4Address
