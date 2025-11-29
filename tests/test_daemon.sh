#!/bin/bash
# Test Part 4: Long-Running Daemon

echo "=== Test: Daemon ==="
./process_daemon
echo "Daemon started. Monitoring zombies for 60 seconds..."
sleep 60

echo "Checking for zombies..."
ps aux | grep defunct | grep -v grep

echo "Stopping daemon..."
killall process_daemon
echo "Done."
