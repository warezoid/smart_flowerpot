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


### Drainage vent
- Electronics:
    - Update drainage_vent code:
        - Drive both vent separatly - first vent 1 then vent 2.
        - Than i can set different duty cycle and calibration will be easier.
        - I can block one roulette, do movement, then do same for second vent.
        - Solve problem of how to know when vent 1 finished its movement - do it efficient.
        - Use folowing state machine:
            - Waiting (0): listening for OPEN or CLOSE request. If request is observed then state is set to Starting 1 (1).
            - Start 1 (1): set PWM for given operation for vent 1, start cut off timer, set power mosfet 1 to ON. Set state to Moving 1 (2).
            - Moving 1 (2):
                - Check for given limit switch and if switch is active then switch off PWM, set power mosfet 1 to OFF and switch of power cut of timer, then acknowledge.
                - OR:
                - Wait for power cut off timer then switch off PWM, set power mosfet 1 to OFF. Then check if given limit switch is active, if yes acknowledge vent 1 movement. If no, then handle error logic (block vent and sent warning).
                - Set state to the NEXT STATE
        - Default state: both vents are unblocked, state machine is set to 0 (waiting), power cut off timer OFF, PWM channel 0, ...


    - Update schematics:
        - Show separated GNDs in schematic.
        - Check schemtics with real circuit.

    - Before instalation vents need to be calibrated properly. Their placement on OSB will need to be accurate a same for both vents. Then OPEN and CLOSE duty cycles in software will need to be changed.

### Roulette
- Final works:
    - Recalibrate TOP Hall sensor - TOP GREEN probably.
    - Check driver schematics with real circuit and update it if needed.
    - Put descriptions on circuit.
    - Do some last testing of circuit before epoxy cover.
    - Cover circuit in epoxy resin to prevent shorts and add some protection.

    - Update CAD files of roulette guides and winge rod gear.
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
