# Pancake
basic, start of Geant4-simulation of Pancake

pleas ask to understand this mess.

I did not made it nice at all, I am sorry.

## Obtain this code

Clone this repository and compile the code:
  * Create a `build` directory within the repository and access it
    ```
    mkdir build
    cd ./build
    ```
  * Run cmake (version >= 3.16, <=3.21)
     ```
     cmake ..
     ```
  * As the dependencies are generated, you can start the compilation
    ```
    make -j<number_of_cpus>
    ```
    where the option `-j` is not mandatory, but it speeds up the compilation time using more CPUs (if available).

    Here you will get a lot of warnings, that is find, coming from unused variables.

When it compiled correctly you can run it by
...
./exampleB1 <macro>
...

    * visualisation_vrml.mac used for visualisation
    * run1.mac: used for simple hitpattern: induces a scorer at pos of PMT array which measures photon flux, gives back .txt file with x,y pos and flux
    * run2.mac: tried for Edep in lXe, produces scorer in the middle of lXe, gives back .txt file with Edep in scorer
    
