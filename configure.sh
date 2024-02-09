#!/bin/bash

# Update package lists
sudo apt update

# Install build-essential for C projects
sudo apt install -y build-essential

# Install cmake for C++ projects
sudo apt install -y cmake

# Install additional packages for C and C++ development
sudo apt install -y gcc g++ gdb make

# Install libraries and headers for common C and C++ development
sudo apt install -y libc6-dev libncurses5-dev libssl-dev libxml2-dev

# Install libraries and headers for graphics programming
sudo apt install -y libgl1-mesa-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libxxf86vm-dev libxss-dev libglfw3-dev libglew-dev


# Install libraries and headers for game development
sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

# Install libraries and headers for testing
sudo apt install -y libgtest-dev

echo "Packages installation completed."
