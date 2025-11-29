#!/bin/bash
# Test Part 1: Zombie Creator

echo "=== Test: Zombie Creator ==="
./zombie_creator 10 &
CREATOR_PID=$!
sleep 2

echo "Checking zombies..."
./zombie_detector

echo "Cleaning up creator..."
kill $CREATOR_PID
sleep 1
echo "Done."

