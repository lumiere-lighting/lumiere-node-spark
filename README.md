**DEPRECATED.  See `lumiere-client-*` projects.**

# Lumiere with SparkCore

Lumiere node using the Spark Core.

Currently, only [NeoPixel lights](https://www.adafruit.com/categories/168) are supported with the existing code base; make sure to read through the [NeoPixel guide](https://learn.adafruit.com/adafruit-neopixel-uberguide/overview) when using these lights.

## Install

### Setup Spark

1. [Setup your Spark](http://docs.spark.io/start/).
1. Install the [`spark` command line](http://docs.spark.io/cli/) utility with: `npm install -g spark-cli`

### Configure code

Update `lumiere.ino` with the relevant configuration values, overall this should just be the number of lights you have.

*This should be in a non-committed config header file eventually*.

### Compile and flash

* You can compile with the following, though note that this uses the default Spark infrastructure and requires the Internet: `make compile`
* To flash the Spark via the internet: `make flash spark=YOUR_SPARK_ID`

## Package management

Not quite sure about the way the Spark manages libraries.  A `spark.include` file is needed to make references to files to include, but then they are are referenced in the application by just their file name?

1. We manage and get thrid-party libraries with `make dependencies`

## Helpful Spark links

* If you need to [factory reset](http://docs.spark.io/connect/#appendix-factory-reset).
* To [manually set the Wifi credentials via USB](http://docs.spark.io/connect/#connecting-your-core-connect-over-usb), in case the Spark App is not connecting.

## Connecting lights

### Spark and NeoPixels powered by Spark USB

The Spark outputs 3.3V, and the NeoPixel can handle this if both power and data are the same.  But, this will only work with a small number of pixels, like [8](https://www.adafruit.com/product/1426).

[![Spark and NeoPixels powered by Spark diagram](https://raw.githubusercontent.com/lumiere-lighting/lumiere-node-spark/master/diagrams/spark-neopixel-usb.png)](https://raw.githubusercontent.com/lumiere-lighting/lumiere-node-spark/master/diagrams/spark-neopixel-usb.png)

### Spark and NeoPixels powered by external 5V

To power a signifcant amount of lights, you'll need more power (do make sure to read the [NeoPixel guide](https://learn.adafruit.com/adafruit-neopixel-uberguide/overview)).  But, the Spark outputs 3.3V on the data pin and NeoPixels want 5V so we have to convert.  The [74AHCT125 quad level-shifter](https://www.adafruit.com/product/1787) is a great option.

[![Spark and NeoPixels powered by 5V external diagram](https://raw.githubusercontent.com/lumiere-lighting/lumiere-node-spark/master/diagrams/spark-neopixel-external-5v.png)](https://raw.githubusercontent.com/lumiere-lighting/lumiere-node-spark/master/diagrams/spark-neopixel-external-5v.png)
