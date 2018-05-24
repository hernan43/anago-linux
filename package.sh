#! /bin/bash

# Create distribution package (I really am too lazy to type these commands when
# I release :) )
cd src
make clean
cd ../dist
zip anago.zip *
mv -f anago.zip ..
cd ..
zip -r anago.zip package.sh src

