#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wemo.h"

void sendCommand(String data1, String data2, String &doc) {
    HTTPClient http;
    http.begin(Wemo_IP, Wemo_Port, "/upnp/control/basicevent1");
    http.addHeader("Content-Type", "text/xml; charset=utf-8");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("SOAPACTION", data2);
    int httpCode = http.POST(data1);
    if(httpCode > 0) {
        if(httpCode == HTTP_CODE_OK) {
            doc = http.getString();
        }
    } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}

int switchON() {
    String data1;
    String data2;
    String doc;
    data1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"><BinaryState>1</BinaryState></u:SetBinaryState></s:Body></s:Envelope>"; // Use HTML encoding for comma's
    data2 = "\"urn:Belkin:service:basicevent:1#SetBinaryState\"";
    sendCommand(data1, data2, doc);
    int DataStart = doc.indexOf("<BinaryState>") + 13;
    int DataEnd = doc.indexOf("</BinaryState>");
    return doc.substring(DataStart, DataEnd).toInt();
 }

int switchOFF() {
    String data1;
    String data2;
    String doc;
    data1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"><BinaryState>0</BinaryState></u:SetBinaryState></s:Body></s:Envelope>"; // Use HTML encoding for comma's
    data2 = "\"urn:Belkin:service:basicevent:1#SetBinaryState\"";
    sendCommand(data1, data2, doc);
    int DataStart = doc.indexOf("<BinaryState>") + 13;
    int DataEnd = doc.indexOf("</BinaryState>");
    return doc.substring(DataStart, DataEnd).toInt();
}

int getSignal() {
    String data1;
    String data2;
    String doc;
    data1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:GetSignalStrength xmlns:u=\"urn:Belkin:service:basicevent:1\"><GetSignalStrength>0</GetSignalStrength></u:GetSignalStrength></s:Body></s:Envelope>"; // Use HTML encoding for comma's
    data2 = "\"urn:Belkin:service:basicevent:1#GetSignalStrength\"";
    sendCommand(data1, data2, doc);
    int DataStart = doc.indexOf("<SignalStrength>") + 16;
    int DataEnd = doc.indexOf("</SignalStrength>");
    return doc.substring(DataStart, DataEnd).toInt();
}

String getName() {
    String data1;
    String data2;
    String doc;
    data1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:GetFriendlyName xmlns:u=\"urn:Belkin:service:basicevent:1\"></u:GetFriendlyName></s:Body></s:Envelope>"; // Use HTML encoding for comma's
    data2 = "\"urn:Belkin:service:basicevent:1#GetFriendlyName\"";
    sendCommand(data1, data2, doc);
    int DataStart = doc.indexOf("<FriendlyName>") + 14;
    int DataEnd = doc.indexOf("</FriendlyName>");
    return doc.substring(DataStart, DataEnd);
}

int getState() {
    String data1;
    String data2;
    String doc;
    data1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:GetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\" /></s:Body></s:Envelope>"; // Use HTML encoding for comma's
    data2 = "\"urn:Belkin:service:basicevent:1#GetBinaryState\"";
    sendCommand(data1, data2, doc);
    int DataStart = doc.indexOf("<BinaryState>") + 13;
    int DataEnd = doc.indexOf("</BinaryState>");
    return doc.substring(DataStart, DataEnd).toInt();
}
