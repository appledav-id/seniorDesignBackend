#!/bin/bash

if [[ -e ./build/Netlist.net ]]; then
    echo -e "Removing old Netlist.net"
    rm ./build/Netlist.net
fi

if [[ -e ./build/results.raw ]]; then
    echo -e "Removing old results.raw"
    rm ./build/results.raw
fi

cd build
make clean 
make 
./sspice 23000