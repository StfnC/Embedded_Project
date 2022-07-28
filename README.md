
# RENEE BY 5471


_Version_ : 2.0


_Date_ : ***20 April 2022 (05:25:22 UTC-5)***


_Authors_ : 
- Belloui Lina
- Cotargasanu Stefan
- Rakotoarivony Faneva
- Sauquet Justine 


This project follows the requirements asked for the INF1900 class at Polytechnique Montreal University. 

---

## How to use

To use this project on your robot at home, or in the library, or in the Starbucks, you need to follow these five ***simple*** instructions :

1. Clean the library : 
    - Inside **project/lib** folder, use the command  : 
        - `make clean`

2. Compile the library : 
    - Inside the **project/lib** folder, use the command : 
        - `make`

3. Clean the app folder : 
    - Inside the **project/app** folder, use the command : 
        - `make clean`

4. Compile and install the app executable file on the robot : 
    - Inside the **project/app** folder, use the command : 
        - `make install`
    - Or if you want to debug, use the following commands : 
        - `make debug`
        - `make install` 

5. Enjoy your coffe and have ***fun***.


**Pro tip** : You can use the following alias in the folder **project/app** to make things easier : 
    
    
`alias AllMake='clear && make -C ../lib clean && make -C ../lib && make clean && make && make install'`


__Or for debug__ :


`alias AllDebug='clear && make -C ../lib clean && make -C ../lib && make clean && make debug && make install && serieViaUSB -l'`

---

### Lib Folder 

This folder implements the library needed to make the Robot work completely.

### App folder 

This folder implements the main logic of the Robot inside the parkour.

#### Robot.cpp

This file implements the object Robot who controls the Robot inside all of his state and all of the journey he is going to take, going from the wall follower, who follows wall like my rumba, or following light.

#### State.h 

This file describes all the states of the Finite State Machine of the Robot, following the following state table.


|   Curente State  |        Transition        |    Next State    |       Output      |
|:----------------:|:------------------------:|:----------------:|:-----------------:|
|       Init       |         Interupt         | Start_Autonomous |    Blinck Green   |
| Start_Autonomous |        3s. Elapsed       | Start_Memorizing |      Waiting      |
| Start_Memorizing |  Finish Memorazing Unit  |    Follow_Wall   |    Follow Wall    |
|    Follow_Wall   |     No Wall Detected     |   Follow_Light   |    Follow Light   |
|   Follow_Light   |         Interupt         |  End_Autonomous  | Turn On DEL Green |
|   Follow_Light   |     Bouton Breadboart    |  Stop_Memorizing |  Stop Memorazing  |
|  Stop_Memorizing |     Finish Memorazing    |   Start_U_Turn   |    Blinck Amber   |
|   Start_U_Turn   |        1s. Elapsed       |      U_Turn      |      Waiting      |
|      U_Turn      |        End U_Turn        |    Follow_Wall   |    Follow Wall    |
|   Follow_Light   |        Find a Wall       |    Follow_Wall   |    Follow Wall    |
|       Init       |     Bouton Breadboart    |    Start_Rerun   |     Blinck Red    |
|    Start_Rerun   |        3s. Elapsed       |       Rerun      |      Waiting      |
|       Rerun      | Read end of rerun marker |     End_Rerun    | Turn On DEL Green |

#### __BY THE WAY C'EST QUOI LE STEP ?__

