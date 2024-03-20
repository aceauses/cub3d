#!/bin/bash

# Time to wait for the program to run
TIMEOUT=3
BAD_MAPS_DIR="maps/bad_maps"
GOOD_MAPS_DIR="maps/good_maps"

# Function to run a test case
bad_maps() {
    echo "Running test: $1"
    (./cub3d $1 2> /dev/null) & pid=$!
    (sleep $TIMEOUT && kill -9 $pid > /dev/null 2>&1) & watcher=$!
    wait $pid 2> /dev/null
    exit_code=$?
    kill -9 $watcher 2> /dev/null 2>&1
    if [ $exit_code -eq 1 ]; then
        echo "Test passed: $1"
    elif [ $exit_code -eq 0 ]; then
        echo "Test timed out: $1"
        exit 1
    else
        echo "Test failed: $1"
        exit 1
    fi
}

good_map_test_with_esc() {
    echo "Running test: $1"
    (./cub3d $1 2> /dev/null) & pid=$!
    sleep 2
    xdotool key Escape
    (sleep $TIMEOUT && kill -9 $pid > /dev/null 2>&1) & watcher=$!
    wait $pid 2> /dev/null
    exit_code=$?
    kill -9 $watcher 2> /dev/null 2>&1 

    # Assuming graceful exit on ESC has exit code 0
    if [ $exit_code -eq 0 ]; then
        echo "Test passed: $1"
    else
        echo "Test failed: $1 - ESC handling may be incorrect"
        exit 1
    fi
}

# Test cases with bad maps or bad names of map
bad_maps "$BAD_MAPS_DIR/map1.cubb"
bad_maps "$BAD_MAPS_DIR/map2..cub"
bad_maps "$BAD_MAPS_DIR/map2.cub.cub"
bad_maps "$BAD_MAPS_DIR/map3.txt.cub"
bad_maps "$BAD_MAPS_DIR/map4.cub.txt"
bad_maps "$BAD_MAPS_DIR/map_errors_1.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_2.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_3.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_4.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_5.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_6.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_7.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_8.cub"
bad_maps "$BAD_MAPS_DIR/map_errors_9.cub"
bad_maps "$BAD_MAPS_DIR/map_errors.cub"
bad_maps "$BAD_MAPS_DIR/doesnt_exit.cub"

# Add more test cases here
good_map_test_with_esc "$GOOD_MAPS_DIR/map1.cub"

echo "All tests passed"
exit 0
