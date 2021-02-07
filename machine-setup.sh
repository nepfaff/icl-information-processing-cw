#!/bin/bash

# Installing packages
sudo apt update
sudo apt install \
tmux \
g++ \
git

# Changing default editor to vim
sudo update-alternatives --set editor $(which vim.basic)
