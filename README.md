# page-replacement-simulator

## Compile

```shell
mkdir build
cd build
cmake ..
make
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
```

## Test
- in `build` directory
```shell
ctest
```

## Note
- For simplicity, disregard `displacement`