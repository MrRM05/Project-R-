cls
@ECHO OFF 

echo building...
echo.

cd CORE
..\ARMIPS\bin\mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c "Main.c" -o "Main.o"

call LibraryLight.bat

..\ARMIPS\bin\armips "BUILD.asm"
..\ARMIPS\bin\n64crc "ROM\ProjectR.z64"

echo.
echo //////////////////////////////////////////////////////
echo.
echo DONE! NOW CHECK FOR BUILD ERRORS:
echo.
echo 1.CRC: 
echo "Bad, fixed" = crc successfully created
echo "Good" = crc error
echo.
echo 2.PROGRAMMING: 
echo Check output above "BootChip: CIC-NUS-6102"
echo.

pause
