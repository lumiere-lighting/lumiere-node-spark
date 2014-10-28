// Libs
#include "HttpClient.h"
#include "JsonParser.h"
using namespace ArduinoJson::Parser;


// Main configuration here
#define PIXEL_PIN D2
#define PIXEL_COUNT 8
#define PIXEL_TYPE WS2812B


// General vars
JsonParser<64> parser;
unsigned int wait_time = 7000;
String api_path = "/api/colors?format=hex0&noInput=true&limit=" + String(PIXEL_COUNT);

// HTTP requests
// NOTE: Always terminate headers with NULL
HttpClient http;
http_request_t request;
http_response_t response;
http_header_t headers[] = {
  { "Content-Type", "application/json" },
  { "Accept" , "application/json" },
  { "Accept" , "*/*"},
  { NULL, NULL }
};


void setup() {
  Serial.begin(9600);

}

void loop() {

  // Make request
  request.hostname = "lumiere.lighting";
  request.port = 80;
  request.path = api_path;
  http.get(request, response, headers);

  // Ensure it is good
  if (response.status == 200) {
    Serial.println(response.body);

    // Convert to char array
    int str_len = response.body.length() + 1;
    char response_char[str_len];
    response.body.toCharArray(response_char, str_len);

    // Check to see is indeed JSON since HTML can be passed
    // back when Meteor gives up
    if (1) {
      // Parse JSON
      JsonObject parsed = parser.parse(response_char);
      if (parsed.success()) {

        // Get ID
        char * char_id = parsed["_id"];
        String id = String(char_id);

        //Serial.println(id);
      }
    }
  }


  // Do again
  delay(wait_time);
}
