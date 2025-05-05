#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PARENT_DIR="$(dirname "$SCRIPT_DIR")"

# Define source and destination directories
SOURCE_DIR="$PARENT_DIR/Markdown"
DEST_DIR="$PARENT_DIR/PDF"

# Create destination directory if it doesn't exist
mkdir -p "$DEST_DIR"

# Check if source directory exists
if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory $SOURCE_DIR does not exist."
    exit 1
fi

# Find all PDF files in the source directory and copy them to the destination
echo "Copying PDF files from $SOURCE_DIR to $DEST_DIR..."

# Use a temporary file to store the list of copied files
temp_file=$(mktemp)

# Find all PDF files and process them
find "$SOURCE_DIR" -type f -name "*.pdf" -print0 | while IFS= read -r -d '' file; do
    # Get the filename without the path
    filename=$(basename "$file")
    
    # Copy the file to the destination directory, overwriting if it exists
    cp -f "$file" "$DEST_DIR/$filename"
    
    # Add the file path to our temp file
    echo "$DEST_DIR/$filename" >> "$temp_file"
done

# Check if any files were copied
if [ ! -s "$temp_file" ]; then
    echo "No PDF files found in $SOURCE_DIR."
    rm "$temp_file"
    exit 0
fi

# Display file information in Unix format
echo "Files copied:"
while IFS= read -r line; do
    ls -l "$line"
done < "$temp_file"

# Count the number of files copied
copied_count=$(wc -l < "$temp_file")
echo "Copy operation completed. $copied_count files copied."

# Clean up the temporary file
rm "$temp_file"