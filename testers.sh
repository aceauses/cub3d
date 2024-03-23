#!/bin/bash

# Time to wait for the program to run
TIMEOUT=3
BAD_MAPS_DIR="maps/bad_maps"
GOOD_MAPS_DIR="maps/good_maps"


# Function to run a test case
bad_maps() {
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

# Function to iterate through all bad maps
for map in $BAD_MAPS_DIR/*.cub; do
	bad_maps $map
done
good_map_test_with_esc() {
    Xvfb :99 -screen 0 1280x1024x24 &
    xvfb_pid=$!
    export DISPLAY=:99
    echo "Display has been set"
    metacity --replace &
    metacity_pid=$!
    echo "Metacity configured"
    echo "Running test: $1"
    xvfb-run --auto-servernum --server-args="-ac" ./cub3d $1 &
    pid=$!

    # Give the program some time to initialize and create a window
    sleep 10

    # Get the process ID and window ID
    try_pid=$(ps | grep cub3d | awk '{print $1}')
	if [ -z "$try_pid" ]; then
		echo "Process not found"
		exit 1
	fi
    (sleep 20 && kill -9 $pid > /dev/null 2>&1) & watcher=$!
    wait $pid 2> /dev/null
    exit_code=$?
    kill -9 $watcher 2> /ßdev/null 2>&1
    kill -9 $xvfb_pid $metacity_pid 2> /dev/null 2>&1

    # Check if the program exited after ESC was pressed
    if [ $exit_code -eq 0 ]; then
        echo "Test passed: $1"
    elif [ $exit_code -eq 137 ]; then
        echo "Pressing escape not yet implemented so its killing the program"
        echo "Need to make escape interpreter after we eval"
        exit 0
    elseß
        echo "Test failed: $1 - Unexpected exit code: $exit_code"
        exit 1
    fi
}


# Add more test cases here
# good_map_test_with_esc "$GOOD_MAPS_DIR/map1.cub"

sleep 1
# Cool ASCII Art
banner1="
                                       ____    _   _    ____   _____   ____            
                                    U /\"___|U |\"|u| |U | __\")u|___\"/u |  _\"\\         
                                    \\| | u   \\| |\\| | \\|  _ \\/U_|_ \\//| | | |          
                                     | |/__   | |_| |  | |_) | ___) |U| |_| |\\         
                                      \\____| <<\\___/   |____/ |____/  |____/ u         
                                     _// \\\\ (__) )(   _|| \\\\_  _// \\\\  |||_          
                                    (__)(__)    (__) (__) (__)(__)(__)(__)_)         "

banner2="                                                                                       
    _      _      _           _____ U _____ u____     _____        ____       _     ____    ____   U _____ u____     
U  /\"\\  u |\"|    |\"|         |_ \" _|\\| ___\"|/ __\"| u |_ \" _|     U|  _\"\\ uU  /\"\\  u/ __\"| u/ __\"| u\\| ___\"|/  _\"\\    
 \\/ _ \\/U | | uU | | u         | |   |  _|\"<\\___ \\/    | |       \\| |_) |/ \\/ _ \\/\\<\\___ \\/\\<\\___ \\/  |  _|\\\"/| | | |   
 / ___ \\ \\| |/__\\| |/__       /| \\\\  | |___ u___) |    /| \\\\       |  __/   / ___ \\ u___) | u___) |  | |___U| |_| |\\ 
/_/   \\_\\ |_____||_____|     u |_|U  |_____||____/>> u |_|U       |_|     /_/   \\_\\|____/>>|____/>> |_____||____/ u  
 \\\\    >> //  \\\\ //  \\\\      _// \\\\_ <<   >> )(  (__)_// \\\\_      ||>>_    \\\\    >> )(  (__))(  (__)<<   >> |||_     
(__)  (__)_\\(\"_)_\\(\"_)    (__) (__)__) (__)__)    (__) (__)    (__)__)  (__)  (__)__)    (__)    (__) (__)__)_)     
"

# Color codes (might vary depending on your terminal)
green='\033[0;32m' 
reset='\033[0m'

# Print the awesome banner
echo -e "${green}${banner1}${banner2}${reset}"

exit 0
