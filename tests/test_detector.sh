#!/bin/bash
# Test Part 2: Zombie Detector

echo "=== Test: Zombie Detector ==="
# Crear zombies temporales
./zombie_creator 5 &
CREATOR_PID=$!
sleep 2

echo "Running detector..."
./zombie_detector

echo "Cleaning up creator..."
kill $CREATOR_PID
sleep 1
echo "Done."
