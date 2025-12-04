#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: $0 {assets_folder_path} {output_assets_folder_path}"
    exit 1
fi

ASSETS_PATH="$1"
OUTPUT_PATH="$2"
BASE_OUTPUT_PATH=$(dirname "$OUTPUT_PATH")

if [ ! -d "$ASSETS_PATH" ]; then
    echo "ERROR: Source assets folder doesn't exist"
    exit 2
fi

if [ -d "$OUTPUT_PATH" ]; then
    echo "Target folder already exists, skipping"
    exit 0
else
    echo "Creating output path folder $BASE_OUTPUT_PATH"
    mkdir -p "$BASE_OUTPUT_PATH"
    echo "Creating symbolic link $OUTPUT_PATH pointing to $ASSETS_PATH"
    ln -s "$ASSETS_PATH" "$OUTPUT_PATH"
    echo "Done!"
fi

exit 0
