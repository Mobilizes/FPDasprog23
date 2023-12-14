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
#define printError printf(red"%s\n"white, errorMsg);

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
    for(int i=0; i<=1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        totalDataGroup++;
        for(int j=0; j<=1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            totalData++;
        }
    }
}

void updatelenGudang(){
    maxlenGudang = 0;
    for(int i=0; i<=1000; i++){
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
    maxlenItem = 0;
    maxlenStok = 0;
    for(int i=0; i<=1000; i++){
        if(Gudang[i].nama[0]=='\0') continue;
        for(int j=0; j<=1000; j++){
            if(Gudang[i].itm[j].nama[0]=='\0') continue;
            maxlenItem = max(maxlenItem, strlen(Gudang[i].itm[j].nama));
            maxlenStok = max(maxlenStok, checkDigit(Gudang[i].itm[j].stok));
        }
    }
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

void printSpecificGroup(int *selectedGroup, int *selectedData){
    clear;
    int curridx = 0;
    const char colors[4][10] = {red, purple, green, white};
    int coloridx = 0;
    int temp = 0;
    printRoof(4+2+1+(maxlenItem+2)+1+(maxlenStok+2));
    for(int i=0; i<=1000; i++){
        if(Gudang[*selectedGroup].itm[i].nama[0]=='\0') continue;
        temp = coloridx;
        if(curridx==*selectedData) coloridx = 3;

        printf(cyan"|%s %04d " cyan"|", colors[coloridx], i);
        printf("%s %s"white, colors[coloridx], Gudang[*selectedGroup].itm[i].nama);
        for(int k=strlen(Gudang[*selectedGroup].itm[i].nama); k<=maxlenItem; k++) printf(" ");

        printf(cyan"|%s %d"cyan, colors[coloridx], Gudang[*selectedGroup].itm[i].stok);
        for(int k=checkDigit(Gudang[*selectedGroup].itm[i].stok); k<=maxlenStok; k++) printf(" ");
        printf("|"white);

        if(curridx==*selectedData) printf(" <--");
        printf("\n");
        curridx++;
        coloridx = temp;
        coloridx++;
        if(coloridx==3) coloridx = 0;
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

void addData(int *group){
    int trash = -1;
    bool flag = false;
    if(*group==-1){
        flag = true;
        printDataGroup(&trash, group);
        printf("Prompt data group ID.\n");
        while(!inputNum(group) || Gudang[*group].nama[0]=='\0'){
            if(Gudang[*group].nama[0]=='\0') strcpy(errorMsg, "That ID doesn\'t exist!");
            printError;
            printf("Prompt data group ID.\n");
        }
    }

    int idx;
    if(flag) printSpecificGroup(group, &trash);
    printf("Prompt data ID.\n");
    while(!inputNum(&idx) || Gudang[*group].itm[idx].nama[0]!='\0'){
        if(Gudang[*group].itm[idx].nama[0]!='\0') strcpy(errorMsg, "That ID already exists!");
        printError;
        printf("Prompt data ID.\n");
    }
    
    printf("Prompt data name.\n");
    scanf("%s", Gudang[*group].itm[idx].nama);
    fflush(stdin);

    printf("Prompt data stock.\n");
    while(scanf("%d", &Gudang[*group].itm[idx].stok)!=1){
        strcpy(errorMsg, "Invalid input!");
        fflush(stdin);
        printError;
        printf("Prompt data stock.\n");
    }
    fflush(stdin);

    Gudang[*group].itm[idx].stok = max(Gudang[*group].itm[idx].stok, 0);
    printOut(&trash, &trash, &trash);

    updatelenItemStok();
    updateTotalData();
    updated = false;
    strcpy(errorMsg, "The new data has successfully been added.");
}

void addDataGroup(){
    int trash = -1;
    printDataGroup(&trash, &trash);
    printf("Prompt data group ID.\n");
    int group; 
    while(!inputNum(&group) || Gudang[group].nama[0]!='\0'){
        if(Gudang[group].nama[0]!='\0') strcpy(errorMsg, "That ID already exists!");
        printError;
        printf("Prompt data group ID.\n");
    }
    updateTotalData();

    printf("Prompt data group name.\n");
    scanf("%s", Gudang[group].nama);
    fflush(stdin);

    updatelenGudang();

    printf("Please add data to newly added data group.\n");
    addData(&group);
    
    updated = false;
    strcpy(errorMsg, "The new data group has successfully been added.");
}

void deleteData(int *group, int *data){
    strcpy(Gudang[*group].itm[*data].nama, "\0");
    Gudang[*group].itm[*data].stok = 0;
    updatelenItemStok();
    updateTotalData();
    updated = false;
    strcpy(errorMsg, "The selected data has successfully been deleted.");
}

void deleteDataGroup(int *group){
    strcpy(Gudang[*group].nama, "\0");
    for(int data=0; data<=1000; data++) deleteData(group, &data);
    updatelenGudang();
    updateTotalData();
    strcpy(errorMsg, "The selected data group has successfully been deleted.");
}

void modifyData(int *group, int *data){
    printSpecificGroup(group, data);
    printf("Prompt new ID. (-1 to leave unchanged.)\n");
    int ID; 
    bool flag = false;
    while(flag = !inputNum(&ID)){
        if(ID!=-1 && Gudang[*group].itm[ID].nama!='\0'){
            strcpy(errorMsg, "That ID already exists!");
            printError;
            flag = false;
            continue;
        }
        printError;
        printf("Prompt new ID.\n");
    }

    strcpy(Gudang[*group].itm[ID].nama, Gudang[*group].itm[*data].nama);
    Gudang[*group].itm[ID].stok = Gudang[*group].itm[*data].stok;
    deleteData(group, data);

    ID = *data;

    printf("Prompt new name. (-1 to leave unchanged.)\n");
    char name[1001]; scanf("%s", name);
    fflush(stdin);
    if(strcmp(name, "-1")!=0) strcpy(Gudang[*group].itm[ID].nama, name);

    printf("Prompt updated stock. (-1 to leave unchanged.)\n");
    int stock; 
    while(!inputNum(&stock)){
        printError;
        printf("Prompt updated stock.\n");
    }
    if(stock!=-1) Gudang[*group].itm[ID].stok = stock;

    strcpy(errorMsg, "The selected data has successfully been modified.");
    updated = false;
}

void modifyDataGroup(int *pointer, int *group){
    printDataGroup(pointer, group);
    printf("Prompt new ID. (-1 to leave unchanged.)\n");
    int ID; 
    while(!inputNum(&ID)){
        printError;
        printf("Prompt data group ID.\n");
    }
    if(ID!=-1 && ID != *group){
        if(Gudang[*group].itm[ID].nama[0]=='\0'){
            strcpy(errorMsg, "That ID doesn\'t exist!");
            return;
        }
        if(Gudang[ID].nama[0]!='\0'){
            strcpy(errorMsg, "That ID already exists!");
            return;
        }
        strcpy(Gudang[ID].nama, Gudang[*group].nama);
        for(int i=0; i<=1000; i++){
            if(Gudang[*group].itm[i].nama[0]=='\0') continue;
            strcpy(Gudang[ID].itm[i].nama, Gudang[*group].itm[i].nama);
            Gudang[ID].itm[i].stok = Gudang[*group].itm[i].stok;
        }
        deleteDataGroup(group);
    } else ID = *group;

    printf("Prompt new name. (-1 to leave unchanged.)\n");
    char name[1001]; scanf("%s", name);
    fflush(stdin);
    if(strcmp(name, "-1")!=0) strcpy(Gudang[*group].itm[ID].nama, name);

    strcpy(errorMsg, "The selected data group has successfully been modified.");
    updated = false;
}

void wrongFormat(){
    strcpy(errorMsg, "gudang.txt is not on correct format!");
}

void writeBackup(){
    FILE *fptr1, *fptr2;
    fptr1 = fopen("gudang.txt", "r");
    fptr2 = fopen("backup.txt", "w");
    char c;
    while (fscanf(fptr1, "%c", &c) != EOF){ 
        fprintf(fptr2, "%c", c);
    }
    fclose(fptr1);
    fclose(fptr2);
}

void getBackup(){
    FILE *fptr1, *fptr2;
    fptr1 = fopen("gudang.txt", "w");
    fptr2 = fopen("backup.txt", "r");
    char c;
    while (fscanf(fptr2, "%c", &c) != EOF){ 
        fprintf(fptr1, "%c", c);
    }
    fclose(fptr1);
    fclose(fptr2);
}

void readFile(){
    int i=0, j=0;
    for(i=0; i<=1000; i++){
        strcpy(Gudang[i].nama, "");
        for(j=0; j<=1000; j++){
            strcpy(Gudang[i].itm[j].nama, "");
            Gudang[i].itm[j].stok = 0;
        }
    }
    FILE *fptr;
    fptr = fopen("gudang.txt", "r");
    int idx = 0;
    while(1){
        int output = fscanf(fptr, "%d", &idx);
        printf("%d\n", idx);
        if(output!=1 || output==EOF){
            wrongFormat();
            return;
        }
        if(idx>1000){
            wrongFormat();
            return;
        }
        if(idx==-1) break;
        if(Gudang[idx].nama[0]!='\0'){
            wrongFormat();
            return;
        }
        fscanf(fptr, "%s", &Gudang[idx].nama);
        
    }
    while(1){
        int output = fscanf(fptr, "%d:", &idx);
        if(output!=1 || output==EOF){
            wrongFormat();
            return;
        }
        if(idx>1000){
            wrongFormat();
            return;
        }
        if(idx==-1) break;
        if(Gudang[idx].nama[0]=='\0'){
            wrongFormat();
            return;
        }
        while(1){
            int i;
            int output = fscanf(fptr, "%d", &i);
            if(output!=1 || output==EOF){
                wrongFormat();
                return;
            }
            if(i>1000){
                wrongFormat();
                return;
            }
            if(i==-1) break;
            if(Gudang[idx].itm[i].nama[0]!='\0'){
                wrongFormat();
                return;
            }
            fscanf(fptr, "%s %d", Gudang[idx].itm[i].nama, &Gudang[idx].itm[i].stok);
        }
    }
    fclose(fptr);

    updated = true;
    updatelenGudang();
    updatelenItemStok();
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
    writeBackup();
}

int main()
{
    int pointer = 0;
    int selectedGroup = 0;
    int selectedID = 0;
    bool groupToggle = false;
    readFile();
    if(strcmp(errorMsg, "gudang.txt is not on correct format!")==0){
        // clear;
        printError;
        printf("Do you wish to use a backup? ("green"Y"white"/"red"N"white")\n");
        int query = getch();
        if(query=='Y' || query=='y') getBackup();
        else return 0;
        readFile();
        strcpy(errorMsg, "gudang.txt\'s data is lost.");
    }
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
        printf("B. Get backup. "red"(ONLY USE WHEN NECESSARY!)\n"white);
        printf("Esc. Exit the program.\n\n");
        printError;
        strcpy(errorMsg, "");

        int query = getch();
        if(query==0 || query==224){
            int dir = getch();
            if(dir==72) pointer--;
            else if(dir==80) pointer++;
            else strcpy(errorMsg, "Invalid input!");
        } else{
            if(query=='1'){
                if(groupToggle) modifyDataGroup(&pointer, &selectedGroup);
                else modifyData(&selectedGroup, &selectedID);
            }
            else if(query=='2'){
                if(groupToggle) deleteDataGroup(&selectedGroup);
                else deleteData(&selectedGroup, &selectedID);
            }
            else if(query=='3'){
                int trash = -1;
                if(groupToggle) addDataGroup();
                else addData(&trash);
            }
            else if(query=='T' || query=='t'){
                groupToggle = !groupToggle;
                pointer = 0;
            }
            else if(query=='C' || query=='c') writeFile();
            else if(query=='R' || query=='r'){
                readFile();
                if(strcmp(errorMsg, "gudang.txt is not on correct format!")==0){\
                    getBackup();
                    readFile();
                    strcpy(errorMsg, "gudang.txt is tampered manually and not on correct format! backup.txt has been used to fix the issue.\n");
                }
            }
            else if(query=='B' || query=='b'){
                printf(red"Are you sure? "white"("green"Y"white"/"red"N"white")\n");
                int confirm = getch();
                if(confirm=='Y' || confirm=='y'){
                    getBackup();
                    readFile();
                    strcpy(errorMsg, "Restoration executed.");
                } else strcpy(errorMsg, "Restoration aborted.");
            }
            else if(query==27) break;
            else strcpy(errorMsg, "Invalid input!");
        }
        pointer = max(0, pointer);
        pointer = min(pointer, (groupToggle ? totalDataGroup-1 : totalData-1));
        updatelenGudang();
        updatelenItemStok();
        updateTotalData();
    }
    printf(red"Program has successfully been exited.\n");
    return 0;
}
