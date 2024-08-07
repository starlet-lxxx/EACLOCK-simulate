# EACLOCK Simulation Framework

Our evaluation framework is derived from WATT [here](https://github.com/leanstore/leanstore/blob/WATT/README.md).

## Compiling

``` bash
mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && make -j
```

## Running

``` bash
./evalAccessTable tracefile outdir
```

## Adding Strategies

New strategies can be added in `/algos/` and have to be linked in `/algos/Generators.cpp` and `/algos/Generators.hpp`.

## Adding Runconfigurations

Configurations can be added in `/evalAccessTable/evalAccessTable.cpp`.
