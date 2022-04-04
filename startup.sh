#!/bin/bash

if [[ -e "./build/Netlist.net" ]]; then
    echo -e "Removing old Netlist.net"
    rm ./build/Netlist.net
fi

cd build
make clean 
make 
./sspice 23000