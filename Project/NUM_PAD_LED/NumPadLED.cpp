/*
  Edited By Shawn Farnham on 11-22-2024
  This program subscribes to the adafruit dashboard to toggle an LED attachted to
  the beagle bone black on and off when a button on the dashboard is pressed.
  The Button is a momentary button
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MQTTClient.h"
#include "LED.h"

using namespace std;

#define ADDRESS     "tcp://io.adafruit.com:1883"
#define CLIENTID    "Beagle2"
#define TOPIC       "sfarnham/feeds/projectcpe422.numpadled"
#define AUTHMETHOD  "sfarnham"
#define AUTHTOKEN   "aio_vPOy06VPWo2acFBksWBObfqFbrrT"
#define QOS         1
#define TIMEOUT     10000L
#define THRESHOLD   30

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt) {
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    //int i=0;
    LED led[4]={LED(0),LED(1),LED(2),LED(3)};
    
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = (char*) message->payload;
    printf("The data is :%s:\n", payloadptr);
    //here
      int temp = atoi(payloadptr);
      printf("%i\n",temp);
      (temp&1)==1?led[0].turnOn():led[0].turnOff();
      printf("%i\n",temp);
      (temp>>1&1)==1?led[1].turnOn():led[1].turnOff();
      printf("%i\n",temp);
      (temp>>2&1)==1?led[2].turnOn():led[2].turnOff();
      printf("%i\n",temp);
      (temp>>3&1)==1?led[3].turnOn():led[3].turnOff();
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause) {
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

int main(int argc, char* argv[]) {

  MQTTClient client;
    MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
    int rc;
    int ch;
    //writeGPIO("direction", "out");

    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    opts.keepAliveInterval = 20;
    opts.cleansession = 1;
    opts.username = AUTHMETHOD;
    opts.password = AUTHTOKEN;
    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((rc = MQTTClient_connect(client, &opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);

    do {
        ch = getchar();
    } while(ch!='Q' && ch != 'q');
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}

