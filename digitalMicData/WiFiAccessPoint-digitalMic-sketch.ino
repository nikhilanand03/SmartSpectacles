/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <driver/i2s.h>
#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2

#define I2S_PORT I2S_NUM_0

#define LED_BUILTIN 13   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define array_size 5000
#define sampling_rate 2000


// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "yourPassword";

/*const int mic1 = 34;
const int mic2 = 33; // right-front
int mic3 = 32; // left-back
int mic4 = 35; // left-front

// Variable to hold analog values from mic
int mic1_values[array_size];
int mic2_values[array_size];
int mic3_values[array_size];*/
int mic1_values[array_size];

int checkTime;
long long int prev = 0;

WiFiServer server(80);

void i2s_install(){
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0, // default interrupt priority
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin(){
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Setup I2S ...");

  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
  delay(500);

  Serial.println("Server started");
}

void loop() {
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            prev = micros();
            int32_t sample = 0;
            for(int i=0; i<array_size; i++)
            {
              int bytes = i2s_pop_sample(I2S_PORT, (char*)&sample, portMAX_DELAY);
              if(bytes > 0){
                Serial.println(sample);
              }
              mic1_values[i] = sample;
              
              //delayMicroseconds(1000000/sampling_rate);
            }
            prev = micros() - prev;
            Serial.println(prev);
            client.print("<div id = 'output123'>");
            for(int i=0; i<array_size; i++)
            {
                client.print("<br>");
                client.print(mic1_values[i]);
            }
            client.print("</div>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
        
      }
      
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }

  
}
