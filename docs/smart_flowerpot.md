# Smart flowerpot
This document is overview of progress and TODOs on smart flowerpot project.



## TODOs
- Add some RPI web server notes - MAN/AUTO mode, ...



## To buy
- https://www.hornbach.cz/p/sit-proti-hmyzu-seda-sirka-1-m-metraz/4262685/ [ 85 CZK/m -> needed 2m = 170 CZK ]
- https://www.hornbach.cz/p/univerzalni-barva-balakryl-uni-mat-0199-cerna-ekologicka-0-7-kg/4289282/ [ 300 CZK ]
- https://www.obi.cz/lazury-na-drevo/balakryl-tenkovrstva-lazura-na-drev-dixol-orech-0-7-kg/p/6361679 [ 280 CZK ]



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

- Version 1.1: fix bugs. Write potentional future improvements. See if second roulette is needed.

- Version 2: add IR camera and add some machine vision. Pests monitoring.



## Construction - **COMPLETE BY THE END OF JULY**
- OSB:
    - Buy OSBs - front and back walls (only lowerparts), bottom and side walls.
    - Cut needed holes into OSBs, grind them.
    - Grind some edge on roullete OSB hole - bottom edge of roulette window, roulette hit it and can be stucked (only on it's way down).
    - Paint OSBs by some protective paint.
    - Drill holes for OSBs mounting.
    - Do the things to finish steel construction.
    - Mount walls to the steel construction.

    - OSB FEM sources:
        - https://www.drevoostrava.cz/cz/osb-desky/ostra-hrana/3-swiss-krono-osb-3-18-x-1250-x-2500.html?varianta=3
        - https://regata.b-cdn.net/media/folio3/productattachments/SKHU_Technical_Data_EN_2025_03_03.pdf
        - https://europanels.org/the-wood-based-panel-industry/types-of-wood-based-panels-economic-impact/oriented-strand-board/
        - https://hrcak.srce.hr/file/263350

- Finish steel construcion:
    - Sand structure with coarse-grit sandpaper - P80 or P100.
    - Clean and degrease structure.
    - Paint construction by some color - multiple layers.

- Post-finish works:
    - Update metal profile photo and finished steel frame section.
    - Add FEM section of metal frame.

- Polycarbonate:
    - Plan OSB and polycarbonate from walls and roof - create CAD files.
        - https://www.hornbach.cz/p/polykarbonatova-deska-bravo-dutinkova-3000-x-1050-x-10-mm-cira/8234584/



## ESP32 / DRIVERs / MOTION

### Drainage vent
- Electronics:
    - Test new circuit on breadboard - (**21. Jun 2026**).
    - Solder together new circuit.
    - Test and repair new circut.

### Roulette **COMPLETE BY THE END OF JUNE**
- Redesign roulette driver:
    - Calibrate hall sensors and debug roulette code  - (**21. Jun 2026**).
        - Solve ESP32 overheating problem.
        - Solve CD4001BE overheating problem.
        - Replace broken motor driver and power motor with independent power supply.
        - Solder 100nF capacitor to motor and add power cables - twisted.
        - Debug DIR signals of motor driver, curently it is not working - stucked add final position - probably it need calibration.
    - Fix bugs - (**21. Jun 2026**).

- Final works:
    - Solder together roulette driver circuit and debug it.
    - Put description on board.
    - Update schematic of roulette driver.
    - Update CAD files of roulette guides and winge rod gear.



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
