# Smart flowerpot
This document is overview of progress and TODOs on smart flowerpot project.



## TODOs
- Add some RPI web server notes - MAN/AUTO mode, ...



## To buy



## Project roadmap
- Version 1: create functional sample of smart flowerpot.
    - Mechanical phase:
        - Create and make smartflowerpot structure.
        - Steel frame, OSB, polycarbonate, 3d printing.
        - CAD, FEM, 3d printing.
        - Output should be physical structure of smartflowerpot without drivers, sensors and electronics.

    - Driver phase:
        - Create hardware and software drivers for smart flowerpot.
        - Drainage vent, roulette, flower vent, roof vent.
        - Water circuit driver, solar power recharge.
        - Software, hardware, electronics.
        - Output should be functional drivers.

    - Sensor phase:
        - Place sensors for watering, overview, ventilation, ...
        - Create some algorithms for data procesing.
        - Output should be updated table with sensor data.
        - Coding, electronics, logic, simple table database.

    - Master-slave phase:
        - Create communication between MASTER (RPi) and multiple slaves (ESP32).
        - Send commands from MASTER to SLAVE, which will reply.
        - Start self-hosting webserver on RPi.
        - Create simple web GUI which will serve as commands IO.

    - Advanced master-slave phase:
        - RPi will get data from sensor ESP32 and store them in some local copy for overviews and commands.
        - Data will be checked and if needed drivers will be called to do some action.
        - Drivers will reply with action status and process is done.
        - Update GUI to more profesional form - overviews, logs, ...

- Version 1.1: fix bugs. Write potentional future improvements. See if second roulette is needed. Think about driving vents independently (first drive Vent 1, then vent 2) -> better for instalation, new code should be written. Harder calibration.

- Version 2: add IR camera and add some machine vision. Pests monitoring.



## Construction
- OSB:
    - Cut needed holes into OSBs, grind them.
    - Grind some edge on roullete OSB hole - bottom edge of roulette window, roulette hit it and can be stucked (only on it's way down).
    - Paint OSBs by some protective paint.
    - Drill holes for OSBs mounting.
    - Add thread to the holes.
    - Repaint steel construction - drilled holes only.
    - Mount walls to the steel construction.

    - OSB FEM sources:
        - https://www.drevoostrava.cz/cz/osb-desky/ostra-hrana/3-swiss-krono-osb-3-18-x-1250-x-2500.html?varianta=3
        - https://regata.b-cdn.net/media/folio3/productattachments/SKHU_Technical_Data_EN_2025_03_03.pdf
        - https://europanels.org/the-wood-based-panel-industry/types-of-wood-based-panels-economic-impact/oriented-strand-board/
        - https://hrcak.srce.hr/file/263350

- Post-finish works:
    - Update metal profile photo and finished steel frame section.
    - Add FEM section of metal frame.

- Polycarbonate:
    - Plan OSB and polycarbonate from walls and roof - create CAD files.
        - https://www.hornbach.cz/p/polykarbonatova-deska-bravo-dutinkova-3000-x-1050-x-10-mm-cira/8234584/



## ESP32 / DRIVERs / MOTION
- Final testing:
    - Write nice testing code for both: vent and roulette.
    - Do needed recalibration.
    - Test everything nicely and properly.

- Upgrade Excel table.
    - Separate MOTION to diferent lists, ....
- Create bill of material table for all drivers.

### Drainage vent
- Electronics:
    - Update drainage_vent code:
        - DONT USE TIMERS or DELAY or some different sort of WAITING. Use tick systems instead.
        - Use folowing state machine:
            - IDLE (0):
                - Scan for process code. If process code (in control byte) is 00 then break. If not, then copy&paste control byte process code to temporary byte process code. Set state machine to 1 and breake.
                - Commands will be set by process code bits: 00 non active, 01 opening, 10 closing, 11 spare, in future maybe calibration.
                - Program will read only from temporary process code, which can be set only in IDLE, so overriding should be solved.
            
            - Start 1 (1):
                - If vent 1 is enabled then set action_start_ticks, set power mosfet 1 to ON, and set PWM for given operation for vent 1. Then set state machine to 2 and break.
                - Otherwise set state machine to 3 and break.

            - Moving 1 (2):
                - Check for given limit switch and if switch is active then switch off PWM, set power mosfet 1 to OFF and null action_start_ticks. Then acknowledge - set vent 1 enable bit to 1. Set state machine bit to 3 and break.
                - If limit switch is not active, then check if current_ticks - action_start_ticks are bellow given time interval. If yes, just break. If no, then  switch off PWM, set power mosfet 1 to OFF and null action_start_ticks and block vent 1 - set vent 1 enable bit to 0. Then set state machine bit to 3 and break.

            - Start 2 (3):
                - If vent 2 is enabled then set action_start_ticks, set power mosfet 2 to ON, and set PWM for given operation for vent 2. Then set state machine to 4 and break.
                - Otherwise set state machine to 5 and break.

            - Moving 2 (4):
                - Check for given limit switch and if switch is active then switch off PWM, set power mosfet 2 to OFF and null action_start_ticks. Then acknowledge - set vent 2 enable bit to 1. Set state machine bit to 5 and break.
                - If limit switch is not active, then check if current_ticks - action_start_ticks are bellow given time interval. If yes, just break. If no, then  switch off PWM, set power mosfet 2 to OFF and null action_start_ticks and block vent 2 - set vent 2 enable bit to 0. Then set state machine bit to 5 and break.
            
            - Finish (5):
                - Null control byte process code, temporary process code.
                - Set state machine bit to 0 and breake.

        - Default state: both vents are unblocked, state machine is set to 0 (waiting), power cut off timer OFF, PWM channel 0, ...

    - Update schematics:
        - Check schemtics with real circuit.

### Roulette
- Final works:
    - Recalibrate TOP Hall sensor - TOP GREEN probably.
    - Check driver schematics with real circuit and update it if needed.
    - Put descriptions on circuit.
    
    - Update CAD files of roulette guides and winge rod gear.

    - Do some last testing of circuit before epoxy cover.
    - Cover circuit in epoxy resin to prevent shorts and add some protection.

    - Maybe solve some better system for holding hall sensors than hot glue - easier calibration.



## Documentation

### warezoid.com
- Project description.
- Pictures.
- Guide.
- TODOs.
- Roadmap.
- DOCs.
- Download links.


### Documentation
- Construction: steele frame, OSB, polycarbonate, FEM.
- Drivers: drainage vent system, roulette system, flower vent system.
- Sensors, RPI server, communication, ...



## SO
- Research:
    - Grandma
    - github.com/honzagalajda

- Consultation:
    - Marťas
    - github.com/MichalKonvic
    - github.com/zombon1

- Making stage help:
    - Honzajs
