> [!CAUTION]
> # This repository is no longer maintained due to a problem with NumPy when embedding Python. Check [#25888](https://github.com/numpy/numpy/issues/25888) for more information.

# Scorpion Antimalware Console

This is a temporary GUI using Qt framework for Scorpion Anti-malware project until the next scratch version is done.

# Table of Contents

- [Scorpion Antimalware Console](#sam-console)
- [Table of Contents](#table-of-contents)
- [Building the project](#building-the-project)
  - [Windows 64-bit](#windows-64-bit)
  - [Windows 64-bit (Using MSYS MinGW GCC)](#windows-64-bit-using-msys-mingw-gcc)

# Building the project

## Windows 64-bit

1. Download and install Visual Studio 17 2022.

2. Download and install Qt6.

3. Download and install CMake.

4. Clone the repository.

```bash
git clone https://github.com/ScorpionAntimalware/sam-console.git
```

5. Change directory to project's root.

```bash
cd sam-console/
```

6. Create a build directory for CMake output.

```bash
mkdir .build
```

```
Note: Add your project build directory to the list of excluded directories of any anti-virus application that runs on your system.
```

7. Change directory to the build directory.

```bash
cd .build/
```

8. Run cmake

```bash
cmake .. -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:/Qt/{QT_VERSION}/{MSVC_VERSION}/lib/cmake/" -DLINK_CONSOLE=OFF
```

9. Build the project using solution file.

```bash
cmake --build .
```

10. Before running the executable, add ``C:/Qt/{QT_VERSION}/{MSVC_VERSION}/lib/`` and ``C:/Qt/{QT_VERSION}/{MSVC_VERSION}/bin/`` to your PATH enviroment variable.

11. Run the project.

```bash
./Debug/sam-console.exe
```

## Windows 64-bit (Using MSYS MinGW GCC)

1. Follow the instrutions in [msys2.org](https://www.msys2.org/) to Download and install MSYS2 and MinGW GCC.

2. Download and install MinGW GCC.

```bash
pacman -Sy mingw-w64-x86_64-gcc
```

```bash
pacman -Sy mingw64/mingw-w64-x86_64-gdb
```

3. Download and install Qt6.

4. Download CMake.

5. Clone the repository.

```bash
git clone https://github.com/ScorpionAntimalware/sam-console.git
```

6. Change directory to project's root.

```bash
cd sam-console/
```

7. Create a build directory for CMake output.

```bash
mkdir .build
```

8. Change directory to the build directory.

```bash
cd .build/
```

9. Run ``cmake`` to produce the ``Makefile`` file needed.

```bash
cmake .. -G "MSYS Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/{QT_VERSION}/{MINGW_VERSION}/lib/cmake/" -DLINK_CONSOLE=OFF
```

10. Build the project using ``make``. You can find ``make`` inside ``C:\msys64\usr\bin``.

```bash
make
```

11. Run the project.

```bash
./Debug/sam-console.exe
```
