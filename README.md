# Scorpion Antimalware

This is a temporary GUI using Qt framework for Scorpion Anti-malware project until the next scratch version is done.

# Table of Contents

- [Scorpion Antimalware](#scorpion-antimalware)
- [Table of Contents](#table-of-contents)
- [Introduction](#introduction)
- [Building the project](#building-the-project)
  - [Windows 64-bit](#windows-64-bit)
  - [Windows 64-bit (Using MSYS MinGW)](#windows-64-bit-using-msys)

# Building the project

## Windows 64-bit

1. Download Visual Studio 17 2022.

2. Download and install qt creator.

3. Clone the repository.

```bash
git clone https://github.com/ScorpionAntimalware/scorpion-antimalware.git
```

4. If you are using Qt Creator: select ``File -> Open File or Project`` or on keyboard ``Ctrl+o``.

5. Select root ``CMakeLists.txt`` file.

6. Press configure project button on the right.

7. Run the project.

8. If you are not using Qt Creator: have a look at the root ``CMakeLists.txt`` file.

9. Create a build directory for CMake output.

```bash
mkdir .build
```

```
Note: Add your project build directory to the list of excluded directories of any anti-virus application that runs on your system.
```

10. Change directory to the build directory.

```bash
cd .build
```

11. Run cmake

```bash
cmake .. -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:/Qt/{QT_VERSION}/msvc{MSVC_VERSION}_64/lib/cmake/"
```

12. You can then build the project by opening the ``.sln`` file in ``.build/`` directory or by adding ``C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin`` to your path and running:

```bash
msbuild scorpion-antimalware.sln
```

13. For any update you make in the source files just repeat steps 10 - 12

## Windows 64-bit (Using MSYS MinGW)

1. If you don't have a compiler, follow the steps in the link below to install ``mingw64`` from ``msys2``. I'm using ``GNU 13.1.0``. Note that some old versions such as ``GNU 6.0.0`` won't generate ``Makefile`` file correctly.

```
https://www.msys2.org/
```

2. Use the following commands from ``MSYS2 MINGW64`` or ``MSYS2 MINGW32`` terminal.
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

3. Download and install qt creator.

4. Clone the repository.

```bash
git clone https://github.com/ScorpionAntimalware/scorpion-antimalware.git
```

3. If you are using Qt Creator: select ``File -> Open File or Project`` or on keyboard ``Ctrl+o``.

4. Select root ``CMakeLists.txt`` file.

5. Press configure project button on the right.

6. Run the project.

7. If you are not using Qt Creator: have a look at the root ``CMakeLists.txt`` file.

8. Create a build directory for CMake output.

```bash
mkdir .build
```

9. Change directory to the build directory.

```bash
cd .build
```

10. Produce the ``Makefile`` file needed.

```bash
cmake .. -G "MSYS Makefiles"
```

11. Build the project (if that doesn't work, just add ``C:\msys64\usr\bin`` to your path) (if that also doesn't work for you, just find out the correct naming of make executable, for me it's ``mingw32-make``).

```bash
make
```

12. Run the project.

```bash
./scorpion-antimalware.exe
```

13. For any update you make in the source files just repeat steps 10 - 12
