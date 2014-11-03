# Lumiere with SparkCore

Lumiere node using the Spark Core.

## Build and flash

Note that these command use the Spark command line interface and assumes the first Spark found, so if you have more than one Spark connected, then you'll have to manually compile and flash.

1. You can compile with: `make compile`
1. To flash the Spark via the internet: `make flash`
1. To flash the Spark via the USB, though this involves installing other software: `make flash_usb`

## Package management

Not quite sure about the way the Spark manages libraries.  A `spark.include` file is needed to make references to files to include, but then they are are referenced in the application by just their file name?

1. We manage and get thrid-party libraries with `make dependencies`

## Helpful links

* If you need to [factory reset](http://docs.spark.io/connect/#appendix-factory-reset).
* To [manually set the Wifi credentials vis USB](http://docs.spark.io/connect/#connecting-your-core-connect-over-usb), in case the Spark App is not connecting.
