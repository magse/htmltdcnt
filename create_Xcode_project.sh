#!/bin/sh

PROJ=${1:-proj}

echo "Trying to create a Xcode project in directory \"$PROJ\""

if [ ! -d "$PROJ" ]
then
    echo "Creating Xcode project in directory \"$PROJ\""
    mkdir "$PROJ"
    cd "$PROJ" || exit
    cmake -G Xcode ..
else
    echo "\"$PROJ\" already exist"
fi
