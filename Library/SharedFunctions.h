#include <sys/types.h>
#include <math.h>
#include <stdbool.h>

extern int LoadData(int SourceInput, int SizeData);
extern bool CheckPlatform();
extern bool CheckEmulator();
extern void runDMA();
extern void runRAM();
extern void runTKM();
extern void runMIO();
extern void loadEEPROM(uint Destination);
extern void saveEEPROM(uint Source);

extern ushort GetRGBA16(int R, int G, int B, int A);
extern uint GetRGB32(int R, int G, int B);

extern void SetFontColor(int FontR, int FontG, int FontB, int ShadowR, int ShadowG, int ShadowB);
extern void printFloat(int X, int Y, float Value);
extern int GetRealAddress(int RSPAddress);

//extern void ResetObject();
extern void DrawBox(int X, int Y, int SizeX, int SizeY, int R, int G, int B, int A);
extern char* printHex(char *buf, int num, int nDigits);
extern void printNumberSprite(int X, int Y, int Value);

extern char ReturnStringLength(char *stringAddress);
extern char CharacterConvert[];
extern char CharacterUnconvert[];