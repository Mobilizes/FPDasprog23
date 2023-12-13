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
#define clear system("cls")

typedef long long ll;
typedef struct{
    char nama[1001];
    int stok;
} item;
typedef struct{
    char nama[1001];
    item itm[1001];
} gudang;

gudang Gudang[1001];
bool updated = true;
int maxlenGudang = 0;
int maxlenItem = 0;
int maxlenStok = 0;
int tableLen = 0;
int totalData = 0;
int totalDataGroup = 0;
char errorMsg[1001] = "";

void updateTotalData(){
    totalData = 0;
    totalDataGroup = 0;
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        totalDataGroup++;
        for(int j=0; j<1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            totalData++;
        }
    }
}

void updatelenGudang(){
    for(int i=0; i<1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        maxlenGudang = max(maxlenGudang, strlen(Gudang[i].nama));
    }
}

int checkDigit(int n){
    int res = 0;
    while(n > 0){
        n /= 10;
        res++;
    }
    return res;
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
    updateTotalData();
    strcpy(errorMsg, "File has successfully been read.");
}

void writeFile(){
    FILE *fptr;
    fptr = fopen("gudang.txt", "w");
    for(int i=0; i<=1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        fprintf(fptr, "%d %s\n", i, Gudang[i].nama);
    }
    fprintf(fptr, "-1\n");
    for(int i=0; i<=1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        fprintf(fptr, "%d:\n", i);
        for(int j=0; j<=1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            fprintf(fptr, "%d %s %d\n", j, Gudang[i].itm[j].nama, Gudang[i].itm[j].stok);
        }
        fprintf(fptr, "-1\n");
    }
    fprintf(fptr, "-1\n");
    // fprintf(fptr, "test\n");
    fclose(fptr);
    updated = true;
    strcpy(errorMsg, "Data has successfully been written.");
}

void printRoof(int tableLen){
    printf(cyan"/");
    for(int i=0; i<tableLen; i++) printf("-");
    printf("\\\n"white);
}

void printFloor(int tableLen){
    printf(cyan"\\");
    for(int i=0; i<tableLen; i++) printf("-");
    printf("/\n"white);
}

void printOut(int *pointer, int *selectedGroup, int *selectedData){
    clear;
    updatelenGudang();
    updatelenItemStok();
    printRoof(4+2+1+(maxlenGudang+2)+1+4+2+1+(maxlenItem+2)+1+(maxlenStok+2));
    // Print the data with table format
    const char colors[4][10] = {red, purple, green, white};
    int coloridx = 0;
    int curridx = 0;
    for(int i=0; i<=1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        int temp = coloridx;
        for(int j=0; j<=1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            if(curridx==*pointer) coloridx = 3;
            printf(cyan"|%s %04d " cyan"|", colors[coloridx], i);
            printf("%s %s"white, colors[coloridx] , Gudang[i].nama);
            for(int k=strlen(Gudang[i].nama); k<=maxlenGudang; k++) printf(" ");
            
            printf(cyan"|%s %04d " cyan"|", colors[coloridx], j);
            printf("%s %s"white, colors[coloridx], Gudang[i].itm[j].nama);
            for(int k=strlen(Gudang[i].itm[j].nama); k<=maxlenItem; k++) printf(" ");

            printf(cyan"|%s %d"cyan, colors[coloridx], Gudang[i].itm[j].stok);
            for(int k=checkDigit(Gudang[i].itm[j].stok); k<=maxlenStok; k++) printf(" ");
            printf("|"white);

            if(curridx==*pointer){
                printf(" <--");
                *selectedGroup = i;
                *selectedData = j;
            }
            printf("\n");
            curridx++;
            coloridx = temp;
        }
        coloridx++;
        if(coloridx==3) coloridx = 0;
    }
    printFloor(4+2+1+(maxlenGudang+2)+1+4+2+1+(maxlenItem+2)+1+(maxlenStok+2));
}

void printDataGroup(int *pointer, int *selectedGroup){
    clear;
    int curridx = 0;
    const char colors[4][10] = {red, purple, green, white};
    int coloridx = 0;
    int temp = 0;
    printRoof(4+2+1+(maxlenGudang+2));
    for(int i=0; i<=1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        temp = coloridx;
        if(curridx==*pointer) coloridx = 3;

        printf(blue"|%s %04d "blue"|", colors[coloridx], i);
        printf("%s %s", colors[coloridx], Gudang[i].nama);
        for(int k=strlen(Gudang[i].nama); k<=maxlenGudang; k++) printf(" ");
        printf(blue"|"white);

        if(curridx==*pointer){
            printf(" <--");
            *selectedGroup = i;
        }
        printf("\n");
        curridx++;
        coloridx = temp;
        coloridx++;
        if(coloridx==3) coloridx = 0;
    }
    printFloor(4+2+1+(maxlenGudang+2));
}

void printSpecificGroup(int *pointer, int *selectedGroup){
    clear;
    int curridx = 0;
    const char colors[4][10] = {red, purple, green, white};
    int coloridx = 0;
    int temp = 0;
    printRoof(4+2+1+(maxlenItem+2)+1+(maxlenStok+2));
    for(int i=0; i<=1000; i++){
        if(Gudang[*selectedGroup].itm[i].nama[0]=='\0') continue;
        temp = coloridx;
        if(curridx==*pointer) coloridx = 3;

        printf(cyan"|%s %04d " cyan"|", colors[coloridx], i);
        printf("%s %s"white, colors[coloridx], Gudang[*selectedGroup].itm[i].nama);
        for(int k=strlen(Gudang[*selectedGroup].itm[i].nama); k<=maxlenItem; k++) printf(" ");

        printf(cyan"|%s %d"cyan, colors[coloridx], Gudang[*selectedGroup].itm[i].stok);
        for(int k=checkDigit(Gudang[*selectedGroup].itm[i].stok); k<=maxlenStok; k++) printf(" ");
        printf("|"white);

        if(curridx==*pointer) printf(" <--");
        printf("\n");
        curridx++;
        coloridx = temp;
    }
    printFloor(4+2+1+(maxlenItem+2)+1+(maxlenStok+2));
}

bool inputNum(int *num){
    if(scanf("%d", num)!=1){
        strcpy(errorMsg, "Invalid input!");
        fflush(stdin);
        return false;
    }
    fflush(stdin);
    if(*num>1000){
        strcpy(errorMsg, "Too big of an input! Please keep it within 0 to 1000 inclusive.");
        return false;
    }
    return true;
}

void addData(){
    int trash = -1;
    printOut(&trash, &trash, &trash);
    printf("Prompt data group ID.\n");
    int group; if(!inputNum(&group)) return;
    if(Gudang[group].nama[0]=='\0'){
        strcpy(errorMsg, "That ID doesn\'t exist!");
        return;
    }
    printf("Prompt data ID.\n");
    int idx; if(!inputNum(&idx)) return;
    if(Gudang[group].itm[idx].nama[0]!='\0'){
        strcpy(errorMsg, "That ID already exists!");
        return;
    }
    printf("Prompt data name.\n");
    scanf("%s", Gudang[group].itm[idx].nama);
    fflush(stdin);
    printf("Prompt data stock.\n");
    if(!inputNum(&Gudang[group].itm[idx].stok)) return;
    updatelenItemStok();
    updateTotalData();
    updated = false;
    strcpy(errorMsg, "The new data has successfully been added.");
}

void deleteData(int *group, int *data){
    strcpy(Gudang[*group].itm[*data].nama, "");
    Gudang[*group].itm[*data].stok = 0;
    updated = false;
    updatelenItemStok();
    updateTotalData();
    strcpy(errorMsg, "The selected data has successfully been deleted.");
}

void deleteDataGroup(int *group){
    strcpy(Gudang[*group].nama, "");
    for(int data=0; data<=1000; data++) deleteData(group, &data);
    updatelenGudang();
    strcpy(errorMsg, "The selected data group has successfully been deleted.");
}

void modifyData(int *pointer, int *group, int *data){
    int trash = -1;
    printSpecificGroup(pointer, group);
    printf("Prompt new ID. (-1 to leave unchanged.)\n");
    int ID; if(!inputNum(&ID)) return;
    if(ID!=-1){
        if(Gudang[*group].itm[ID].nama[0]!='\0'){
            strcpy(errorMsg, "That ID already exists!");
            return;
        }
        strcpy(Gudang[*group].itm[ID].nama, Gudang[*group].itm[*data].nama);
        Gudang[*group].itm[ID].stok = Gudang[*group].itm[*data].stok;
        deleteData(group, data);
    } else ID = *data;
    printf("Prompt new name. (-1 to leave unchanged.)\n");
    char name[1001];
    scanf("%s", name);
    fflush(stdin);
    if(strcmp(name, "-1")!=0) strcpy(Gudang[*group].itm[ID].nama, name);
    printf("Prompt updated stock. (-1 to leave unchanged.)\n");
    int stock; if(!inputNum(&stock)) return;
    if(stock!=-1) Gudang[*group].itm[ID].stok = stock;
    strcpy(errorMsg, "The selected data has successfully been modified.");
    updated = false;
}

void modifyDataGroup(int *pointer, int *group){
    
}

int main()
{
    int pointer = 0;
    int selectedGroup = 0;
    int selectedID = 0;
    bool groupToggle = false;
    readFile();
    updateTotalData();
    while(1){
        if(!groupToggle) printOut(&pointer, &selectedGroup, &selectedID);
        else printDataGroup(&pointer, &selectedGroup);
        printf(blue"The data are%sup to date with the file.\n\n"white, (updated ? " " : red" NOT "blue));
        printf("1. Modify selected data%s\n", groupToggle ? " group." : ".");
        printf("2. Delete selected data%s\n", groupToggle ? " group." : ".");
        printf("3. Add new data%s\n", groupToggle ? " group." : ".");
        printf("T. Toggle to %s\n", groupToggle ? "singular." : "group.");
        printf("R. Reset changes.\n");
        printf("C. Commit changes to file.\n");
        printf("Esc. Exit the program.\n\n");
        printf(red"%s\n"white, errorMsg);
        strcpy(errorMsg, "");
        int query = getch();
        if(query==0 || query==224){
            int dir = getch();
            if(dir==72) pointer--;
            else if(dir==80) pointer++;
            else strcpy(errorMsg, "Invalid input!");
            pointer = max(0, pointer);
            pointer = min(pointer, (groupToggle ? totalDataGroup-1 : totalData-1));
        } else{
            if(query=='1'){
                if(groupToggle) deleteDataGroup(&selectedGroup);
                else modifyData(&pointer, &selectedGroup, &selectedID);
            }
            else if(query=='2'){
                if(groupToggle) deleteDataGroup(&selectedGroup);
                else deleteData(&selectedGroup, &selectedID);
            }
            else if(query=='3') addData();
            else if(query=='T' || query=='t'){
                groupToggle = !groupToggle;
                pointer = 0;
            }
            else if(query=='C' || query=='c') writeFile();
            else if(query=='R' || query=='r') readFile();
            else if(query==27) break;
            else strcpy(errorMsg, "Invalid input!");
        }
    }
    printf(red"Program has successfully been exited.\n");
    return 0;
}
