#!/bin/bash
if rm -rf build/; then
    echo "Removed build..."
else
    echo "No such directory 'build' exits!. Exiting..."
fi
