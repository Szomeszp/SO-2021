#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

//TODO:
//Utworzenie tablicy wskaźników (tablicy głównej) — w tej tablicy będą przechowywane wskaźniki na wiersze zmergowanych plików — pierwszy element tablicy głównej zawiera wykaz wierszy pierwszej pary zmergowanych plików, drugi element dla drugiej pary, itd. Pojedynczy blok wierszy (element wskazywany z tablicy głównej), to tablica wskaźników na poszczególne wiersze w zmergowanym pliku
//DONE - mainArray + createMAinTable + memoryBlock
//Definiowanie sekwencji par plików
//??
//Przeprowadzenie zmergowania (dla każdego elementu sekwencji) oraz zapisanie wyniku zmergowania do pliku tymczasowego
//
//Utworzenie, na podstawie zawartość pliku tymczasowego, bloku wierszy — tablicy wskaźników na wiersze, ustawienie w tablicy głównej (wskaźników) wskazania na ten blok; na końcu, funkcja powinna zwrócić indeks elementu tablicy (głównej), który zawiera wskazanie na utworzony blok
//Zwrócenie informacji o ilości wierszy w danym bloku wierszy
//Usunięcie, z pamięci, bloku (wierszy) o zadanym indeksie
//Usunięcie, z pamięci, określonego wiersza dla podanego bloku wierszy
//Wypisanie zmergowanych plików, z uwzględnieniem wcześniejszych usuniętych bloków wierszy / wierszy


typedef struct rowsBlock {
    char **rows;
    int size;
} rowsBlock_t;

typedef struct mainArray {
    rowsBlock_t **rowsBlocks;
    int size;
} mainArray_t;


mainArray_t *createMainArray(int size); //Done?

rowsBlock_t *createRowsBlock(FILE *mergedFile); //Done?
FILE *mergeFiles(char *firstFile, char *secondFile); //Done?

int numberOfRows(mainArray_t* mainArray, int blockIndex); //Done?

void removeBlock(mainArray_t* mainArray, int blockindex);
void removeRow(mainArray_t* mainArray, int blockIndex, int row);

void printMergedBlocks(mainArray_t* mainArray);