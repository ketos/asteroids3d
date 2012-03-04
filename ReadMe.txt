Um das Programm zu Kompilieren build.sh ausführen.
Um das Programm zu starten run.sh ausführen.

Um das Doxygen zum bauen braucht man graphviz,
danach nur doxygen doxconf eingeben.
(meine Lieblingsseite im Doxygen: ./doc/html/Game_8hpp.html)

Steuerung:
    Menü:
        Enter           : Startet das Spiel
        H               : Zeigt den Highscore
    Spiel:
        W               : Beschleunigt das Schiff
        S               : Bremst das Schiff
        Pfeil Hoch      : Nase hoch
        Pfeil Runter    : Nase runter
        Pfeil Links     : Nase links
        Pfeil Rechts    : Nase rechts
        1               : Ansicht außen 1
        2               : Ansicht außen 2
        3               : Ansicht Cokpit

        9
        0
        Bild rauf
        Bild runter
        Escape

    Joystick (XBox360 Wireless)
        Linker Analogstick
        Linker Trigger
        Rechter Trigger
        A
        B
        X
        Y

        LB
        RB
        Rechter Analogstick
        Start

benötigte Packages:
joystick, libxmu, libxi, libglu, libqt4, libsdl, libsdl-mixer, libopengl
