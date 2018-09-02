#!/bin/sh

chmod 755 rncomponent
cp rncomponent /usr/local/bin

# command successful?
if [ $? -eq 0 ]; then
  echo "Completed!"
else
  echo "Failed...\nSee https://github.com/HenryQuan/rncomponent/"
fi