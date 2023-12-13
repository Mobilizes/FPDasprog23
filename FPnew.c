#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
#define black "\033[0;30m"
#define red "\033[0;31m"
#define green "\033[0;32m"
#define yellow "\033[0;33m"
#define blue "\033[0;34m"
#define purple "\033[0;35m"
#define cyan "\033[0;36m"
#define white "\033[0;37m"

typedef long long ll;
typedef struct{
    char nama[1000];
    int stok;
} item;
typedef struct{
    char nama[1000];
    item itm[1000];
} gudang;

gudang Gudang[1000];
bool updated = true;
int maxlenGudang = 0;
int maxlenItem = 0;
int maxlenStok = 0;
int bigGudang = 0;
int tableLen = 0;
int totalData = 0;

void readFile(){
    FILE *fptr;
    fptr = fopen("gudang.txt", "r");
    int idx = 0;
    while(1){
        fscanf(fptr, "%d ", &idx);
        if(idx==-1) break;
        fscanf(fptr, "%s", &Gudang[idx].nama);
    }
    while(1){
        fscanf(fptr, "%d:\n", &idx);
        // printf("%d\n", idx);
        if(idx==-1) break;
        while(1){
            int i; fscanf(fptr, "%d ", &i);
            if(i==-1) break;
            fscanf(fptr, "%s %d", Gudang[idx].itm[i].nama, &Gudang[idx].itm[i].stok);
        }
    }
    fclose(fptr);
    updated = true;
    printf(red"File has been read successfully.\n\n"white);
}

void writeFile(){
    FILE *fptr;
    fptr = fopen("gudang.txt", "w");
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        fprintf(fptr, "%d %s\n", i, Gudang[i].nama);
    }
    fprintf(fptr, "-1\n");
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        fprintf(fptr, "%d:\n", i);
        for(int j=0; j<1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            fprintf(fptr, "%d %s %d\n", j, Gudang[i].itm[j].nama, Gudang[i].itm[j].stok);
        }
        fprintf(fptr, "-1\n");
    }
    fprintf(fptr, "-1\n");
    // fprintf(fptr, "test\n");
    fclose(fptr);
    updated = true;
    printf(red"Data has been written successfully.\n\n"white);
}

int checkDigit(int n){
    int res = 0;
    while(n > 0){
        n /= 10;
        res++;
    }
    return res;
}

void updatelenGudang(){
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        maxlenGudang = max(maxlenGudang, strlen(Gudang[i].nama));
        bigGudang = i;
    }
}

void updatelenItemStok(){
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        for(int j=0; j<1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            maxlenItem = max(maxlenItem, strlen(Gudang[i].itm[j].nama));
            maxlenStok = max(maxlenStok, checkDigit(Gudang[i].itm[j].stok));
        }
    }
}

void printRoof(){
    tableLen = 4+2+1+(maxlenGudang+2)+1+4+2+1+(maxlenItem+2)+1+(maxlenStok+2);
    printf(cyan"/");
    for(int i=0; i<tableLen; i++) printf("-");
    printf("\\\n"white);
}

void printFloor(){
    tableLen = 4+2+1+(maxlenGudang+2)+1+4+2+1+(maxlenItem+2)+1+(maxlenStok+2);
    printf(cyan"\\");
    for(int i=0; i<tableLen; i++) printf("-");
    printf("/\n"white);
}

void printOut(int *pointer){
    updatelenGudang();
    updatelenItemStok();
    printRoof();
    // Print the data with table format
    const char colors[4][10] = {red, yellow, green, white};
    int coloridx = 0;
    int curridx = 0;
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        for(int j=0; j<1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0' && j!=1000-1) continue;
            // Print the divider of each data group to make the table more readable
            if(j==1000-1 && Gudang[i].itm[j].nama[0]=='\0'){
                // If at the end of the table, no need to print divider
                if(i==bigGudang) continue;
                printf(cyan"|");
                for(int k=0; k<tableLen; k++){
                    if(k==6 || k==6+maxlenGudang+2+1 || k==6+maxlenGudang+2+6+2 || k==6+maxlenGudang+2+6+maxlenItem+2+3) printf("+");
                    else printf("-");
                }
                printf("|\n"white);
                continue;
            }
            int temp = coloridx;
            if(curridx==*pointer) coloridx = 3;
            // Adapt the spaces accordingly
            printf(cyan"|%s %04d " cyan"|", colors[coloridx], i);
            printf("%s %s"white, colors[coloridx] , Gudang[i].nama);
            for(int k=strlen(Gudang[i].nama); k<=maxlenGudang; k++) printf(" ");
            printf(cyan"|%s %04d " cyan"|", colors[coloridx], j);
            printf("%s %s"white, colors[coloridx], Gudang[i].itm[j].nama);
            for(int k=strlen(Gudang[i].itm[j].nama); k<=maxlenItem; k++) printf(" ");
            printf(cyan"|%s %d"cyan, colors[coloridx], Gudang[i].itm[j].stok);
            for(int k=checkDigit(Gudang[i].itm[j].stok); k<=maxlenStok; k++) printf(" ");
            printf("|"white);
            if(curridx==*pointer) printf(" <--");
            printf("\n");
            curridx++;
            coloridx = temp;
        }
        coloridx++;
        if(coloridx==3) coloridx = 0;
    }
    printFloor();
}

void updateTotalData(){
    totalData = 0;
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        for(int j=0; j<1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            totalData++;
        }
    }
}

bool addData(int query){
    printf("Prompt data ID.\n");
    int idx = 0; scanf("%d", &idx);
    if(Gudang[query].itm[idx].nama[0]!='\0'){
        printf("That ID already exists!\n");
        return false;
    }
    printf("Prompt data name.\n");
    scanf("%s", Gudang[query].itm[idx].nama);
    printf("Prompt data stock.\n");
    scanf("%d", &Gudang[query].itm[idx].stok);
    printf("Data has been successfully added.\n");
    updatelenItemStok();
    return true;
}

int main()
{
    int pointer = 0;
    readFile();
    updateTotalData();
    while(1){
        system("cls");
        printOut(&pointer);
        printf(blue"Data is%sup to date with the file.\n\n"purple, (updated ? " " : red" NOT "blue));
        printf("M. Modify selected data.\n");
        printf("D. Delete selected data.\n");
        printf("A. Add new data.\n");
        printf("C. Commit changes to file.\n");
        printf("R. Reset changes.\n");
        printf("Esc. Exit the program.\n\n");
        int query = getch();
        if(query==0 || query==224){
            int dir = getch();
            if(dir==72) pointer--;
            if(dir==80) pointer++;
            pointer = max(0, pointer);
            pointer = min(pointer, totalData-1);
        } else{
            if(query=='m' || query=='M');
            else if(query=='d' || query=='D');
            else if(query=='a' || query=='A');
            else if(query=='c' || query=='C') writeFile();
            else if(query=='r' || query=='R') readFile();
            else if(query==27) break;
            else printf("Invalid Input!\n");
        }
    }
    printf(red"Program has successfully been exited.\n");
    return 0;
}
