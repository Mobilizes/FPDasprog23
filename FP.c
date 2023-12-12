#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

const int cSize = 1000;

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
int currver = 0;
int nextver = 0;
int maxlenGudang = 0;
int maxlenItem = 0;
int maxlenStok = 0;
int bigGudang = 0;
int tableLen = 0;

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
    nextver = currver;
    printf("File has been read successfully.\n\n");
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
    printf("File has been written successfully.\n\n");
    currver = nextver;
    readFile();
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
    printf("/");
    for(int i=0; i<tableLen; i++) printf("-");
    printf("\\\n");
}

void printFloor(){
    tableLen = 4+2+1+(maxlenGudang+2)+1+4+2+1+(maxlenItem+2)+1+(maxlenStok+2);
    printf("\\");
    for(int i=0; i<tableLen; i++) printf("-");
    printf("/\n");
}

void printOut(){
    updatelenGudang();
    updatelenItemStok();
    printRoof();
    // Print the data with table format
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        for(int j=0; j<1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0' && j!=1000-1) continue;
            // Print the divider of each data group to make the table more readable
            if(j==1000-1 && Gudang[i].itm[j].nama[0]=='\0'){
                // If at the end of the table, no need to print divider
                if(i==bigGudang) continue;

                printf("|");
                for(int k=0; k<tableLen; k++){
                    if(k==6 || k==6+maxlenGudang+2+1 || k==6+maxlenGudang+2+6+2 || k==6+maxlenGudang+2+6+maxlenItem+2+3) printf("+");
                    else printf("-");
                }
                printf("|\n");
                continue;
            }
            // Adapt the spaces accordingly
            printf("| %04d |", i);
            printf(" %s", Gudang[i].nama);
            for(int k=strlen(Gudang[i].nama); k<=maxlenGudang; k++) printf(" ");
            printf("| %04d |", j);
            printf(" %s", Gudang[i].itm[j].nama);
            for(int k=strlen(Gudang[i].itm[j].nama); k<=maxlenItem; k++) printf(" ");
            printf("| %d", Gudang[i].itm[j].stok);
            for(int k=checkDigit(Gudang[i].itm[j].stok); k<=maxlenStok; k++) printf(" ");
            printf("|\n");
        }
    }
    printFloor();
}

void printDataGroup(){
    printf("\n");
    printf("/");
    for(int i=0; i<4+2+1+(maxlenGudang+2); i++) printf("-");
    printf("\\\n");

    for(int i=0; i<4+2+1+(maxlenGudang+2); i++){
        if(Gudang[i].nama[0]=='\0') continue;
        printf("| %04d |", i);
        printf(" %s", Gudang[i].nama);
        for(int k=strlen(Gudang[i].nama); k<=maxlenGudang; k++) printf(" ");
        printf("|\n");
    }

    printf("\\");
    for(int i=0; i<4+2+1+(maxlenGudang+2); i++) printf("-");
    printf("/\n");
}

void printData(int query){
    // Print the roof with length adapted for item.
    printf("\n");
    printf("/");
    for(int i=0; i<4+2+1+(maxlenItem+2+1+(maxlenStok+2)); i++) printf("-");
    printf("\\\n");
    
    // Print the data available
    for(int i=0; i<1000; i++){
        if(Gudang[query].itm[i].nama[0]=='\0') continue;
        printf("| %04d |", i);
        printf(" %s", Gudang[query].itm[i].nama);
        for(int k=strlen(Gudang[query].itm[i].nama); k<=maxlenItem; k++) printf(" ");
        printf("| %d", Gudang[query].itm[i].stok);
        for(int k=checkDigit(Gudang[query].itm[i].stok); k<=maxlenStok; k++) printf(" ");
        printf("|\n");
    }

    // Print the floor with length adapted for item.
    printf("\\");
    for(int i=0; i<4+2+1+(maxlenItem+2)+1+(maxlenStok+2); i++) printf("-");
    printf("/\n\n");
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
    nextver++;
    printf("Data has been successfully added.\n");
    updatelenItemStok();
    return true;
}

void modifyData(){
    while(1){
        // Print the data group available
        printDataGroup();
        printf("\nWhich data group do you want to modify? (-1 to exit current module.)\n");
        int query; scanf("%d", &query);
        if(query==-1) break;
        if(query<0 && query>1000){
            printf("Invalid input!\n");
            continue;
        }
        if(Gudang[query].nama[0]=='\0'){
            printf("Invalid input!\n");
            continue;
        }
        while(1){
            printData(query);
            printf("Please select the command.\n");
            printf("1. Add a data.\n");
            printf("2. Modify a data.\n");
            printf("3. Delete a data.\n");
            printf("0. Change data group.\n");
            char query2[100]; scanf("%s", query2);
            if(strcmp(query2, "1")==0){
                addData(query);
            }
            else if(strcmp(query2, "2")==0){
                printf("Prompt data ID.\n");
                int idx = 0; scanf("%d", &idx);
                if(Gudang[query].itm[idx].nama=='\0'){
                    printf("That ID doesn\'t exist!\n");
                    continue;
                }
                printf("Prompt data name. (Prompt -1 if you do not wish to modify this attribute.)\n");
                char newname[1000]; scanf("%s", newname);
                if(strcmp(newname, "-1")!=0) strcpy(Gudang[query].itm[idx].nama, newname);
                printf("Prompt data stock. (Prompt -1 if you do not wish to modify this attribute.)\n");
                int stock = 0; scanf("%d", &stock);
                if(stock!=-1) Gudang[query].itm[idx].stok = stock;
                nextver++;
                printf("Data has been successfully modified.\n");
                updatelenItemStok();
            }
            else if(strcmp(query2, "3")==0){
                printf("Prompt data ID.\n");
                int idx = 0; scanf("%d", &idx);
                if(Gudang[query].itm[idx].nama=='\0'){
                    printf("That ID doesn\'t exist!\n");
                    continue;
                }
                strcpy(Gudang[query].itm[idx].nama, "");
                Gudang[query].itm[idx].stok = 0;
                nextver++;
                printf("Data has been successfully deleted.\n");
                updatelenItemStok();
                bool empty = true;
                for(int i=0; i<1000; i++){
                    if(Gudang[query].itm[i].nama[0]!='\0') empty = true;
                }
                if(empty){
                    strcpy(Gudang[query].nama, "");
                    printf("The data group is empty; Data group has been deleted.\n");
                }
            }
            else if(strcmp(query2, "0")==0) break;
        }
    }
}

void modifyDataGroup(){
    while(1){
        printDataGroup();
        printf("Please select the command.\n");
        printf("1. Add new data group.\n");
        printf("2. Delete a data group.\n");
        printf("3. Modify a data group.\n");
        printf("0. Cancel.\n");
        char query[100]; scanf("%s", query);
        if(strcmp(query, "1")==0){
            printf("Prompt group ID.\n");
            int idx = 0; scanf("%d", &idx);
            if(Gudang[idx].nama[0]!='\0'){
                printf("That ID already exists!\n");
                continue;
            }
            printf("Prompt group name.\n");
            scanf("%s", Gudang[idx].nama);
            printf("New data group added.\n\n");
            printf("Please add a data to the newly added data group.\n\n");
            bool added = addData(idx);
            while(!added) added = addData(idx);
        }
        else if(strcmp(query, "2")==0){
            printf("Prompt group Id.\n");
            int idx = 0; scanf("%d", &idx);
            for(int i=0; i<1000; i++) strcpy(Gudang[idx].itm[i].nama, "");
            for(int i=0; i<1000; i++) Gudang[idx].itm[i].stok = 0;
            strcpy(Gudang[idx].nama, "");
            printf("Data group has been deleted.\n");
            nextver++;
        }
        else if(strcmp(query, "3")==0) modifyData();
        else if(strcmp(query, "0")==0) break;
    }
}

int main()
{
    readFile();
    while(1){
        printf("\n");
        printOut();
        printf("Data version : 1.%d\n", nextver);
        printf("Current version : 1.%d\n\n", currver);
        printf("Welcome to Gudang FP.\n");
        printf("Please select the command.\n");
        printf("1. Modify the data.\n");
        printf("2. Commit the file.\n");
        printf("3. Reset the changes.\n");
        printf("0. Exit.\n");
        char query[100]; scanf("%s", query);
        if(strcmp(query, "2")==0) writeFile();
        else if(strcmp(query, "1")==0) modifyDataGroup();
        else if(strcmp(query, "3")==0) readFile();
        else if(strcmp(query, "0")==0) break;
        else printf("Invalid input! Try again.\n");
        printf("\n");
    }
    printf("The program has been closed successfully.\n");
    return 0;
}