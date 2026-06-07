# Smart flowerpot
This document is overview of progress and TODOs on smart flowerpot project.



## TODOs
- Add some RPI web server notes - MAN/AUTO mode, ...



## Project roadmap
- Version 1: create functional sample of smart flowerpot.
    - Mechanical phase:
        - Create and make smartflowerpot structure.
        - Steel frame, OSB, polycarbonate, 3d printing.
        - CAD, FEM, 3d printing.
        - Output should be physical structure of smartflowerpot without drivers, sensors and electronics.

    - Driver phase:
        - Create hardware and software drivers for smart fowerpot.
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

- Version 2: add IR camera and add some machine vision. Pests monitoring.



## Construction - **COMPLETE BY THE END OF JULY**
- Finish welding (**14. JUN 2026**):
    - Weld roof and bottom together.
    - Grind all welds.
    - Check length, perpendicularity and levelness.

- Finish steel construcion:
    - Paint construction by some color.
    - Update warezoid.com page: update metal profile photo and finished steel frame.
    - Add FEM section of metal frame.

- OSB + polycarbonate:
    - Plan OSB and polycarbonate from walls and roof - create CAD files.
        - https://www.hornbach.cz/p/polykarbonatova-deska-bravo-dutinkova-3000-x-1050-x-10-mm-cira/8234584/
    - OSB FEM sources:
        - https://www.drevoostrava.cz/cz/osb-desky/ostra-hrana/3-swiss-krono-osb-3-18-x-1250-x-2500.html?varianta=3
        - https://regata.b-cdn.net/media/folio3/productattachments/SKHU_Technical_Data_EN_2025_03_03.pdf
        - https://europanels.org/the-wood-based-panel-industry/types-of-wood-based-panels-economic-impact/oriented-strand-board/
        - https://hrcak.srce.hr/file/263350



## ESP32 / DRIVERs / MOTION

### Drainage vent
- Electronics:
    - Update vent schematic - add signal filtering and circuit proctection.
    - Buy new parts - capacitors, rezistors, diodes, ...
    - Test new circuit on breadboard.
    - Solder together new circuit.
    - Test and repair new circut.

### Roulette
- Redesign roulette driver:
    - Create Hall effect senors parts - solder them together and mount them to the stand.
    - Calibrate Hall sensoros - both should be active on TOP and BOTTOM.
    - Put logic circuit on breadboard, try it and debugit.

- Version 1 will have only one roulette.
    - Next versions can have 2 roulettes - independet driving, only one circuit, ???
    - Update code, Excel, ...

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
