#!/bin/bash

rm -f dpxcli

echo "Building ..."
gcc dpxcli.c -lcurl -ljson-c -o dpxcli
echo "Build Finish"

echo "Installing"

if [[ $(id -u) -ne 0 ]]; then
   
    echo "Installation failed, need root access for installtion"

else
   
    rm -f /usr/bin/dpxcli
    cp dpxcli /usr/bin/dpxcli
    echo "Installed successfully"

fi