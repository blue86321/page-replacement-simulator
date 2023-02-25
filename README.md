# page-replacement-simulator

## Compile

```shell
mkdir build
cd build
cmake ..
make
```

## Test
- in `build` directory
```shell
ctest
```

## Run
- in `build` directory
```shell
cd example
./different_frames
./different_modify_percent
./different_pages
./different_periods
./sequence_access
./small_page_frequent_access
./time_algorithms
```

## Algorithms
- Aging
- Clock
- FIFO (first-in-first-out)
- LRU (Least Recently Used)
- NRU (Not Recently Used)


## Note
- For simplicity, disregard `displacement`