#!/bin/bash

# Directories to exclude
EXCLUDE_DIRS="build cmake-build-debug"

# Convert excluded dirs to find's -path format
EXCLUDE_ARGS=""
for DIR in $EXCLUDE_DIRS; do
  EXCLUDE_ARGS="$EXCLUDE_ARGS -path ./$(basename $DIR) -prune -o"
done

# Print file titles and contents
eval find . $EXCLUDE_ARGS -type f -print | while read -r file; do
  echo "==== $file ===="
  cat "$file"
  echo -e "\n"
done

