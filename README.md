# Scorpion Antimalware

## Building the project

### Windows 64-bit

1. Download Visual Studio 17 2022
2. Download and install qt creator
3. Clone the repository
```bash
git clone https://github.com/ScorpionAntimalware/scorpion-antimalware.git
```
4. If you are using Qt Creator: select ``File -> Open File or Project`` or on keyboard ``Ctrl+o``
5. Select root ``CMakeLists.txt`` file
6. Press configure project button on the right
7. Run the project
8. If you are not using Qt Creator: have a look at the root ``CMakeLists.txt`` file and uncomment the lines needed.
9. Create a build directory for CMake output
```bash
mkdir .build
```
10. Go inside
```bash
cd .build
```
11. Run cmake
```bash
cmake .. -G "Visual Studio 17 2022"
```
12. Run the project
13. For any update you make in the source files just repeat steps 10 - 12

### Windows 64-bit (Using MSYS)

1. If you don't have a compiler, follow the steps in the link below to install ``mingw64`` from ``msys2``. I'm using ``GNU 13.1.0``. Note that some old versions such as ``GNU 6.0.0`` won't generate ``Makefile`` file correctly.
```
https://www.msys2.org/
```
2. Use the following commands from ``MSYS2 MINGW64`` or ``MSYS2 MINGW32`` terminal
 - for 64-bit Windows:
```bash
pacman -Sy mingw-w64-x86_64-gcc
```
```bash
pacman -Sy mingw64/mingw-w64-x86_64-gdb
```
 - for 32-bit Windows:
```bash
pacman -Sy mingw-w64-i686-gcc
```
```bash
pacman -Sy mingw32/mingw-w64-i686-gdb
```
3. Download and install qt creator
4. Clone the repository
```bash
git clone https://github.com/ScorpionAntimalware/scorpion-antimalware.git
```
3. If you are using Qt Creator: select ``File -> Open File or Project`` or on keyboard ``Ctrl+o``
4. Select root ``CMakeLists.txt`` file
5. Press configure project button on the right
6. Run the project
7. If you are not using Qt Creator: have a look at the root ``CMakeLists.txt`` file and uncomment the lines needed.
8. Create a build directory for CMake output
```bash
mkdir .build
```
9. Go inside
```bash
cd .build
```
10. Produce the ``Makefile`` file needed
```bash
cmake .. -G "MSYS Makefiles"
```
11. Build the project (if that doesn't work, just add ``C:\msys64\usr\bin`` to your path) (if that also doesn't work for you, just find out the correct naming of make executable, for me it's ``mingw32-make``)
```bash
make
```
12. Run the project
```bash
./scorpion-antimalware.exe
```
13. For any update you make in the source files just repeat steps 10 - 12
