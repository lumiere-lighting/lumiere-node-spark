all: compile

flash:
	spark cloud flash zSpark .

# Requires dfu-util (brew install dfu-util)
# and http://docs.spark.io/connect/#appendix-dfu-mode-device-firmware-upgrade
flash_usb:
	spark compile . lumiere.bin
	spark flash zSpark --usb lumiere.bin

compile: clean
	spark compile . lumiere.bin

monitor:
	spark serial monitor

dependencies:
	git clone https://github.com/bblanchon/ArduinoJson.git .tmp/ArduinoJson
	cp -v .tmp/ArduinoJson/JsonParser/*.cpp lib/
	cp -v .tmp/ArduinoJson/JsonParser/*.h lib/
	rm -rf .tmp/ArduinoJson

	git clone https://github.com/nmattisson/HttpClient.git .tmp/HttpClient
	cp -v .tmp/HttpClient/firmware/{*.cpp,*.h} lib/
	rm -rf .tmp/HttpClient

clean:
	rm -f *.bin
	test -d .tmp && rm -rf .tmp || true
