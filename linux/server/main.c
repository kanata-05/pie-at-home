#include <stdio.h>
#include <gmp.h>
#include "networking.h"
#include "loadCalc.h"
#include "verification.h"
#include "io.h"

#define PORT 5000
#define PI_PATH "/data/pi/"

int main() {
    // connection handshake
    int clientPort;
    float clientScore;
    int clientSock = listenConnect(PORT, &clientScore, &clientPort);
    char* clientSpecs;

    if (connectionStat != -1) {
        printf("client connection from port %d with sock %d", clientPort, connectionStat);
        sendD(clientSock, msg, sizeof(msg));
        recieve(clientSock, clientSpecs);
        append("/data/specs.txt", clientSpecs);
    } else printf("connection from client failed");
    
    // tasking
    char** fileList = getFiles(PI_PATH);
    int currentPlace = getDigitCount(fileList);
    for (int i = 0; fileList[i] != NULL; i++) free(fileList[i]);
    free(fileList);
    
    typedef struct {
        int start;
        int end;
    } range;

    range task = loadCalc(currentPlace, clientScore);
    int taskArr[] = {task.start, task.end};   
    size_t sizeArr = sizeof(taskArr);

    if (sendD(clientSock, taskArr, sizeArr) != 0) printf("task send failed");
    
    return 0;
}
