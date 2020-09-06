//
//  WifiReader.cpp
//  hertzianSpace
//
//  Created by Daniël Korssen on 03/09/2020.
//

#include "WifiReader.hpp"

#include <array>
#include <vector>
#include <string>

    
void  WifiReader::addNetwork(std::array<std::string, 4> _network)
{
    networks.push_back({ _network });
}

//--------------------------------------------------------------

std::string WifiReader::executeCommand(const std::string& command) {
    system((command + " > temp.txt").c_str());
 
    std::ifstream ifs("temp.txt");
    std::string ret{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
    ifs.close();
    
    if (std::remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
    }
    
    return ret;
}
 
void WifiReader::getNetworks(){
    std::string result;
//    cout << executeCommand("/System/Library/PrivateFrameworks/Apple80211.framework/Versions/A/Resources/airport -s") << endl;
//    std::stringstream iss(result);
//    std::string line;
//
//    while(std::getline(iss,line,'\n')){
//        cout << line << endl;
//    }
//
    addNetwork({ "Ziggo", "72:54:d2:98:ef:f5", "-78", "WPA2(802.1x/AES/AES)" });
    addNetwork({ "Ziggo96319", "b0:c2:87:e1:e6:cf", "-80", "WPA2(PSK/AES/AES)" });
    addNetwork({ "BeepBoop Technology_5G", "50:d2:f5:0b:82:9e", "-44", "WPA(PSK/TKIP,AES/TKIP) WPA2(PSK/TKIP,AES/TKIP" });
    addNetwork({ "BeepBoop Technology", "50:d2:f5:0b:82:9f", "-43", "WPA(PSK/TKIP,AES/TKIP) WPA2(PSK/TKIP,AES/TKIP)" });
    addNetwork({ "ziggo-ap-6708473", "d8:b6:b7:d9:b8:e4", "-93", "WPA2(PSK/AES/AES)" });
    addNetwork({ "H369ABED2DC", "20:e8:82:be:d2:dc", "-69", "WPA2(PSK/AES/AES)" });
    addNetwork({ "Ziggo34627", "64:cc:22:f1:e7:07", "-81", "WPA2(PSK/AES/AES)" });
    addNetwork({ "VGV75196A29AA", "37:f3:12:c9:32:ef:", "-72", "WPA2(PSK/AES/AES)" });

}
