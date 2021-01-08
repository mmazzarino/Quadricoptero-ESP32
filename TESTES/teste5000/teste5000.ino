#include <SPIFFS.h>
#include <FS.h>
//#include "Html.h"
//#include "backbone.h"
//#include "buton.h"
//#include "canvas.h"
//#include "joystick_view.h"
//#include "jquery.h"
//#include "underscore.h"
#include "joy.h"
//#include "joyJS.h"
//#include "joyMinJS.h"



void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);
 
    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }
 
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
 
void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);
 
    File file = fs.open(path);
    delay(1000);
    if(!file || file.isDirectory()){
        Serial.println("Failed to open file for reading");
        return;
    }
 
    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
}
 
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);
 
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
}
 
void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);
 
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
}
 
void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}
 
void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}
 
void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }
 
 
    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
 
    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}
 
void setup(){
    Serial.begin(115200);
    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }


    /*writeFile(SPIFFS, "/joystick-master_index.html", MainHtml);
    writeFile(SPIFFS, "/js/backbone-min.js", backBoneJS);
    writeFile(SPIFFS, "/js/joystick_view.js", joystickJS);
    writeFile(SPIFFS, "/js/jquery-1.11.2.min.js", jqueryJS);
    writeFile(SPIFFS, "/js/jquery.js", jqueryJS);
    writeFile(SPIFFS, "/js/underscore-min.js", underscoreJS);
    writeFile(SPIFFS, "/img/button.png", butonPNG);
    writeFile(SPIFFS, "/img/canvas.png", canvas.png);
    */
   
    /*
    writeFile(SPIFFS, "/joy.js", joyJs);
    writeFile(SPIFFS, "/joy.min.js", joyMinJs);
   
    readFile(SPIFFS, "/joy.html");
    Serial.println("/n/n-------------------------------------------------/n/n");

    readFile(SPIFFS, "/joy.js");
    Serial.println("/n/n-------------------------------------------------/n/n");

    readFile(SPIFFS, "/joy.min.js");
    Serial.println("/n/n-------------------------------------------------/n/n");
    
    renameFile(SPIFFS, "/hello.txt", "/foo.txt");
    
    testFileIO(SPIFFS, "/test.txt");
    deleteFile(SPIFFS, "joy.html");
    

   
    //listDir(SPIFFS, "/", 0);*/
    readFile(SPIFFS, "/joy.html");
    // writeFile(SPIFFS, "/joy.html", joyHtml);
}
 
void loop(){
 
}
