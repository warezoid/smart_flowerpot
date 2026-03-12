# Roulette driver

## Problems
- Main problem is that I need somehow always stop the motor -> without relaying on ESP or some driver.
    - Potentional solution:
        - Physicly add some guards which will block weight from some places - bellow and above guides.
        - Normal run -> hall effect sensors connected to ESP.
            - Weight magnet reference with sensor -> ESP get notification -> switch off motor power.
            - Operation will set check index and ESP will check it in main program loop. (index 0 -> check nothing, index > 0 -> check up, index < 0 -> check down)
            - To stop motor 2 sensors will be in OR mode, to check if position is valid use AND mode.
        - Emergency -> limit switch (msw13 microswitch) physicaly behind hall efffect sensor (upper or lower) -> normaly close -> in series with motor power -> if active (error) motor shuts down.
            - This is emergency stop in electrical layer.
            - If ESP goes down -> no problem -> NC switch connected with motor power in series.
            - If motor or motor driver goes down -> motor will not spin -> no problem -> ESP set motor to block and sent alerts.
        - Emergency 2 -> try to get motor driver with overcurrent protection -> if motor is drawing too much current it will switch off power to motor.
            - Use MP6550 motor driver.

## CAD

## Code diagram
1. Get OPEN/CLOSE request.
2. If operation open/close isn't already running then do:
    1. If roulette is not blocked then do:
        1. Set motor direction.
        2. Set Hall effect check index - lower or higher hall effect will be checked.
        3. Switch on power to motor & Start callback timer and ticks.
        4. Check for Hall effect senzor status change.
            1. If valid status changed then switch off power to motor - main switch off!
            - There are two hall effect sensors for top and two for bottom.
            - In this checkout hall effect sensors in one section will work in OR mode -> one or both must be active else dont stop.
        5. After timer collapse callback will switch off power to motor - EVERYTIME - emergency switch off!
        6. After ticks collapse check if roulette is in valid position if not:
            1. Set roulette to blocked status.
            - In this checkout hall effect sensors in one section will work in AND mode -> both must be active else block.
        7. Clear ticks, hall effect check index, ...
        8. Return.
3. Ignore request.

- Drive 2 roulettes separatly -> STEP 1: write code only for 1 roulette. 

##### Created by warezoid with the love of freedom and numbers <3