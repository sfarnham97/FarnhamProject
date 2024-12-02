/*
  Edited By Shawn Farnham on 11-22-2024
  This code Does Analog outputs via PWM, and a slider on adafruit dashboards
  that controls the total duty cycle of the PWM.
  The slider is from 0 to 100 which is the % duty cycle
*/
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "PWM.h"

using namespace std;
using namespace exploringBB;

#define ADDRESS     "tcp://io.adafruit.com:1883"
#define CLIENTID    "Beagle2"
#define TOPIC       "sfarnham/feeds/projectcpe422.servocontrol"
#define AUTHMETHOD  "sfarnham"
#define AUTHTOKEN   "aio_vPOy06VPWo2acFBksWBObfqFbrrT"
#define QOS         1
#define TIMEOUT     10000L
#define THRESHOLD   30
#define PERIOD 20000000
// Use this function to control the LED
/*
void writeGPIO(string filename, string value){
   fstream fs;
   string path(LED_GPIO);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}
*/
volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt) {
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    PWM pwm("pwm-1:0");
    pwm.setPeriod(PERIOD);
    pwm.setPolarity(PWM::ACTIVE_LOW);
    char* payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = (char*) message->payload;
    printf("The data is :%s:\n", payloadptr);
    //new code
    int percent = atoi(payloadptr);
    printf("the percent is %i\n", percent);
    unsigned int duty = (PERIOD*percent)/100;
    printf("the duty cycle is %i of 20000000\n",duty);
    pwm.setDutyCycle(duty);
    pwm.run();
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

