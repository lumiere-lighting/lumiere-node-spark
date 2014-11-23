all: compile

# make flash spark=zSpark
flash:
	spark cloud flash $(spark) .

# Requires dfu-util (brew install dfu-util)
# and http://docs.spark.io/connect/#appendix-dfu-mode-device-firmware-upgrade
flash_usb:
	spark compile . lumiere.bin
	spark flash $(spark) --usb lumiere.bin

# Compiling actually uses the Spark infrastructure
# and requires an Internet connection
compile: clean
	spark compile . lumiere.bin

monitor:
	spark serial monitor

# These should really have commit, tags, or branches with them.  Package
# dependency at its finest.
dependencies:
	rm -rf lib/*

	git clone https://github.com/bblanchon/ArduinoJson.git .tmp/ArduinoJson
	mkdir -p lib/ArduinoJson
	cp -v .tmp/ArduinoJson/JsonParser/{*.cpp,*.h} lib/ArduinoJson/
	rm -rf .tmp/ArduinoJson

	git clone https://github.com/nmattisson/HttpClient.git .tmp/HttpClient
	mkdir -p lib/HttpClient
	cp -v .tmp/HttpClient/firmware/{*.cpp,*.h} lib/HttpClient/
	rm -rf .tmp/HttpClient

	git clone  https://github.com/technobly/SparkCore-NeoPixel.git .tmp/SparkCore-NeoPixel
	mkdir -p lib/SparkCore-NeoPixel
	cp -v .tmp/SparkCore-NeoPixel/firmware/{*.cpp,*.h} lib/SparkCore-NeoPixel/
	rm -rf .tmp/SparkCore-NeoPixel

clean:
	rm -f *.bin
	test -d .tmp && rm -rf .tmp || true
