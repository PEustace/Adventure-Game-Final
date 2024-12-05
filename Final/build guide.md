```
-   Make sure you have saved everything
-   Open a terminal window and make sure the cursor is located in the root of the project folder, where the CMakeLists.txt file is located
-   Type to following to create a cmake project and compile into an executable
    ```
    cmake -S . -B build
    cmake --build build
    ```
-   Note that anytime you want to rebuild the prject all you need is `cmake --build build`
-   Note that also, anytime you want to start over with the project, delete everything in the build folder and re-enter the two lines of code above.
-   Open the build folder and you should see the file blackjack that is an executable
-   From the terminal window, enter
    `./build/blackjack`
-   This should run the executable.