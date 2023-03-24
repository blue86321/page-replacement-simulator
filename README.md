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


### Demo
- in `build` directory
- illustrate each page replacement process

```shell
cd example
./demo
```

### Different Settings 
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

## Output Data
- Frame: number of frames in physical memory.
- Page: number of pageEntry in page table.
- Strategy: page replacement algorithm being used.
- Modify Pct: percentage of modify command in input file.
- Period: `PeriodOperation` will be triggered every how many lines.
  - Because some algorithms do something periodically.
  - e.g. NRU reset all frames' reference bit to 0 periodically.
- Line: number of accumulated lines in the input file.
- Page fault: number of page fault so far in the input file.
- Time: time elapses so far from `Run` the simulator, the unit is second.


- e.g.
  - Frame: 1024
  - Page: 1024
  - Strategy: NRU
  - Modify Pct: 0%
  - Period: 100
  - Line: 20000
  - Page fault: 1024
  - Time: 0.007801

## Note
- For simplicity, disregard `displacement` when referencing a page.