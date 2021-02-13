#!/bin/bash

# Installing packages
sudo apt update
sudo apt install \
tmux \
g++ \
git \
make \
python3 \
curl \

# Making sure python3.6 is installed
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt-get update
sudo apt-get install python3.6

# Changing default editor to vim
sudo update-alternatives --set editor $(which vim.basic)
