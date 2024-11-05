#include <cpr.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


int sendToServer(int moistureValue){
    auto response = cpr::Get(cpr::Url{"http://192.168.1.166:5000/set_moisture/" + std::to_string(moistureValue)});
    return response.status_code;

}

std::vector<std::string> scanDevices(){
    std::vector<std::string> foundDevices{}; 

    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("hci_inquiry");

    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
            name, 0) < 0)
        strcpy(name, "[unknown]");
        foundDevices.push_back(std::string(addr) + std::string(name));
    }

    free( ii );
    close( sock );
    return foundDevices;
}



int main(int argc, char **argv){
    //Send values from HUB to server via HTTP
    int statusCode = sendToServer(50);
    std::cout << statusCode << std::endl;

    //Get values from monitor via Bluetooth
    std::vector<std::string> foundDevices = scanDevices();

    for(auto device: foundDevices) {
        std::cout << device << std::endl;
    }




}