#!/bin/bash

echo "I AM A SCRIPT."  
rosrun nodes interface -lah  
SOMEVAR='I have run the rosrun'  
echo "$SOMEVAR"  
echo "I have started the interface"
