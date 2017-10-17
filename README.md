# Rowbits
Generic Arduino Robot Firmware (Config file sets robot motion and sensors AKA make a robot with bits)
Most code was taken from the BQ Zowi firmware see (https://github.com/bq/zowiLibs)

Still working it out.  Goal is to make most routines Static to save on space and have a configuration file set up what parts are avaible to the robot API and error handle the rest that dont exist.  That way a programer can just use the Rowbits API (BQ Zowi) to do fun stuff. 

If the API keeps to zowi integration into BQ Bitbloqs should be pretty easy... maybe...

Wants:
Add min, max, average motor trims into Eeprom for cheap servos that dont have good calibration.
Add a biped motion with arms (moonwalks need wavy arms)
Add Kame quadraped motion controler
Add checksums to communications protocol
Simplify com protocol to use one interface  (BT --> Serial --> command protocol)
Add command prtoocols with interupts for better com system
