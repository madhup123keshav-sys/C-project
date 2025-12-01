#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long toDecimal(char numStr[], int base) {
    return strtol(numStr, NULL, base);
}

void fromDecimal(long num, int base, char *output) {
    char temp[65];     
    int idx = 0;

    if (num == 0) {
        strcpy(output, "0");
        return;
    }

    while (num > 0) {
        int rem = num % base;
        temp[idx++] = (rem < 10) ? (rem + '0') : (rem - 10 + 'A');
        num /= base;
    }
    temp[idx] = '\0';

    for (int i = 0; i < idx; ++i)
        output[i] = temp[idx - i - 1];
    output[idx] = '\0';
}

void printMenu() {
    printf("\n-------------------------------\n");
    printf(" Number Conversion System\n");
    printf("-------------------------------\n");
    printf("Input number type:\n");
    printf(" 1. Decimal\n");
    printf(" 2. Octal\n");
    printf(" 3. Binary\n");
    printf(" 4. Hexadecimal\n");
    printf("-------------------------------\n");
}

void printOutputMenu() {
    printf("\nConvert to:\n");
    printf(" 1. Decimal\n");
    printf(" 2. Octal\n");
    printf(" 3. Binary\n");
    printf(" 4. Hexadecimal\n");
    printf("-------------------------------\n");
}

int getValidSelection(int min, int max) {
    int sel;
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &sel) == 1 && sel >= min && sel <= max)
            break;
        while (getchar() != '\n'); 
        printf("Invalid selection! Try again.\n");
    }
    return sel;
}

void getInputNumber(int base, char *numStr) {
    int valid;
    do {
        valid = 1;
        printf("Enter your number: ");
        scanf("%s", numStr);
        for (size_t i = 0; i < strlen(numStr); ++i) {
            char c = toupper(numStr[i]);
            if (base == 2 && (c!='0' && c!='1')) valid = 0;
            if (base == 8 && (c<'0' || c>'7')) valid = 0;
            if (base == 10 && !isdigit(c)) valid = 0;
            if (base == 16 && !(isdigit(c) || (c>='A' && c<='F'))) valid = 0;
            if (!valid) break;
        }
        if (!valid)
            printf("Invalid number for the selected base! Try again.\n");
    } while (!valid);
}

int main() {
    int inputType, outputType;
    char numStr[65];
    char result[65];
    int bases[] = {10, 8, 2, 16};

    printf("======== Number Converter ========\n");

    printMenu();
    inputType = getValidSelection(1, 4);

    getInputNumber(bases[inputType-1], numStr);

    printOutputMenu();
    outputType = getValidSelection(1, 4);

    long decimalVal = toDecimal(numStr, bases[inputType-1]);

    if (outputType == inputType) {
        printf("Output (%s): %s\n",
            (outputType == 1)?"Decimal":(outputType == 2)?"Octal":(outputType==3)?"Binary":"Hexadecimal",
            numStr);
    } else if (outputType == 1) {
        printf("Output (Decimal): %ld\n", decimalVal);
    } else {
        fromDecimal(decimalVal, bases[outputType-1], result);
        printf("Output (%s): %s\n",
            (outputType == 2)?"Octal":(outputType==3)?"Binary":"Hexadecimal",
            result);
    }

    printf("==================================\n");

    return 0;
}