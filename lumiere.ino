// Libs
#include "HttpClient.h"
#include "lib/ArduinoJson/src/ArduinoJson.h"
#include "neopixel.h"


/**********************
 *
 * Main configuration here
 *
 **********************/

// Data pin for lights
#define PIXEL_PIN D2
// Limit seems to be over 800
#define PIXEL_COUNT 8
// Type of LEDs
#define PIXEL_TYPE WS2812B
// Global brightness of the lights (0 - 255).  More brightness
// will mean more power usage
#define BRIGHTNESS 50
// How long should the animation run
#define ANIMATION_TIME 1000
// Poll time (time between HTTP requests)
#define POLL_TIME 3000
// Color input limt for API
//#define INPUT_LIMIT PIXEL_COUNT
#define INPUT_LIMIT 5



// Global vars
JsonParser<40> parser;
String current_id;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

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
  //Serial.begin(9600);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
}

void loop() {

  // Make request
  request.hostname = "lumiere.lighting";
  request.port = 80;
  request.path = "/api/colors?format=rgb&noInput=true&limit=" + String(INPUT_LIMIT);
  http.get(request, response, headers);

  // Ensure it is good.
  // This is kind of hacky.  Meteor will response
  // with an HTML page when error, but not necessarily a bad response status
  // if (response.status == 200 && response.body.indexOf("{") < 10 && response.body.indexOf("{") >= 0)  {
  if (response.status == 200)  {
    //Serial.println(response.body);

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

        // If different ID, change lights
        if (id != current_id) {
          current_id = id;

          // The sizeof does not work for json array so we work around it
          // a bit
          int color_set_count = 0;
          for (int i = 0; i < PIXEL_COUNT; i++) {
            if (parsed["colors"][i].success()) {
              color_set_count++;
            }
          }

          // Reset lights
          for (int j = PIXEL_COUNT - 1; j >= 0; j--) {
            strip.setPixelColor(j, strip.Color(0, 0, 0));
            delay(1000 / PIXEL_COUNT);
            strip.show();
          }

          // Change lights
          for (int j = 0; j < PIXEL_COUNT; j++) {
            JsonValue c = parsed["colors"][j % color_set_count];
            strip.setPixelColor(j, strip.Color(int(double(c[0])), int(double(c[1])), int(double(c[2]))));
            delay(1000 / PIXEL_COUNT);
            strip.show();
          }
        }
      }
    }
  }


  // Do again
  delay(POLL_TIME);
}
