# Smart flowerpot
This document is overview of progress and TODOs on smart flowerpot project.



## TODOs
- Add project roadmap.
- Add project structure - electronis, construction, code, ...
- Add some RPI web server notes - MAN/AUTO mode, ...
- Add roulettes program text.



## Construction - **COMPLETE BY THE END OF MAY**
- Finish welding:
    - Weld roof and bottom together.
    - Grind all welds.
    - Check length, perpendicularity and levelness.
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
- Repair vent driver electronics (**FINISH TILL 11. APR 2026**):
    - Resolder new servo.
    - Assembly new ESP32 on a board.
    - Test for shorts, poor soldering and wire brakes.
    - Put circuit description on board.

- Update schematic of vent driver circuit. (**FINISH UNTIL 16. APR 2026**)

- Program update (**FINISH TILL 12. APR 2026**):
    - Update file structure of project.
    - Update GPIOs names and check their numbers to be compatible with *smartflowerpot_tech_db*.
    - Test software with hardware.

- Create servo case (**COMPLETE BY THE END OF APRIL**):
    - Plan case for vent servo and RJ45 mini-board.
    - Make CAD model - include cabel input with some default protection.
    - Print cases and add them to test stand.


### Roulette
- Hardware & Software (**FINISH UNTIL 19. APR 2026**):
    - Put roulette driver circuit on breadboard.
    - Create development diagram.
    - Write roulette driver code and debug it.

- CAD and making (**FINISH UNTIL 26. APR 2026**):
    - Redesign roulette guide - make deeper groves, think about wall OSB, ...
    - Create roulette guides test stand and test it with hardware & software.

- Second pair:
    - Make 2 pairs of roulette guides test stands.
    - Duplicate breadboard circuit and test stand with hardware & software.

- Final works:
    - Solder together roulette driver circuit and debug it.
    - Put description on board.
    - Update schematic of roulette driver.



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
