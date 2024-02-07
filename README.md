# Graphical_Editor

A program that simulates a simple interactive graphical editor, I made based on a challenge in Steven S. Skiena and Miguel A. Revilla's book "Programming Challenges", it currently supports the following commands, as described in the book:

| Command         | What it does                                                 |
|--------------------------------------------------------------------------------|
| I M N           | Create a new M × N image with all pixels initially colored   |
|                 | white (O).                                                   |
|--------------------------------------------------------------------------------|
| C               | Clear the table by setting all pixels white (O). The size    |
|                 | remains unchanged.                                           |
|--------------------------------------------------------------------------------|                  
| L X Y C         | Colors the pixel (X, Y ) in color (C).                       |
|--------------------------------------------------------------------------------|
| V X Y1 Y2 C     | Draw a vertical segment of color (C) in column X, between    |
|                 | the rows Y 1 and Y 2 inclusive.                              |
|--------------------------------------------------------------------------------|                  
| H X1 X2 Y C     | Draw a horizontal segment of color (C) in the row Y ,        |
|                 | between the columns X1 and X2 inclusive.                     |
|--------------------------------------------------------------------------------|                  
| K X1 Y1 X2 Y2 C |  Draw a filled rectangle of color C, where (X1, Y 1) is the  |
|                 |  upper-left and (X2, Y 2) the lower right corner.            |
|--------------------------------------------------------------------------------|                  
| F X Y C         | Fill the region R with the color C, where R is defined as    |
|                 | follows. Pixel (X, Y ) belongs to R. Any other pixel which   |
|                 | is the same color as pixel (X, Y ) and shares a common side  |
|                 | with any pixel in R also belongs to this region.             |
|--------------------------------------------------------------------------------|                  
| S               | Name Write the file name in MSDOS 8.3 format followed by the |
|                 | contents of the current image.                               |
|--------------------------------------------------------------------------------|                  
| X               | Terminate the session.                                       |
|--------------------------------------------------------------------------------|


| First Header  | Second Header |
| ------------- | ------------- |
| Content Cell  | Content Cell  |
| Content Cell  | Content Cell  |
