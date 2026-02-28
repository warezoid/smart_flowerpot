# Roulette driver - CODE PLAN

## Code diagram
1. Get OPEN/CLOSE request.
2. If operation open/close isn't already running then do:
    1. If roulette is not blocked then do:
        1. Set motor direction.
        2. Set Hall effect check index - lower or higher hall effect will be checked.
        3. Switch on power to motor & Start callback timer & start ticks.
        4. Check for Hall effect senzor status change.
            1. If valid status changed then switch off power to motor.
        5. After timer collapse callback will switch off power to motor - EVERYTIME!
        6. After ticks collapse check if roulette is in valid position if not:
            1. Set roulette to blocked status.
        7. Clear ticks, hall effect check index, ...
        8. Return.
3. Ignore request.

##### Created by warezoid with the love of freedom and numbers <3