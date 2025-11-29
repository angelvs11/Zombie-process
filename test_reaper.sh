#!/bin/bash
# Test Part 3: Zombie Reaper Strategies

for strategy in 1 2 3; do
    echo "=== Testing Reaper Strategy $strategy ==="
    ./zombie_reaper $strategy
    echo "Checking no zombies remain..."
    ps aux | grep defunct | grep -v grep
    echo ""
done

echo "Done."
