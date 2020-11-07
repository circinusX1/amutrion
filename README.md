
### Amutrion (old rembix), Industrial Strength Scripting Engine

#### No dependencies,
#### Written in C++
#### Scripted: Java/C++ like syntax
#### S O L I D / K I S S. architecture
#### No obfuscated syntax. Straight up readable API's.

   * HAL LAYER FOR LINUX (see https://github.com/circinusX1/amutrion/tree/master/src/drivers  FOLDER)
       * I2C
       * SPI
       * GPIO
       * PWM
       * ADC
       * UART
       

##### Published: 1 Oct 2017

```
   git pull https://github.com/circinusX1/amutrion
   cd amution
   ./make.sh
   cd bin
   Some samples runs only on R-PI or BBB
```



```C++
var l1 = PIO(26,  DIR_OUT, LOW, "led");         // GPIO
l1.set_value(0);
var pwm = PWM("0.0", 1000, 100, false, "pwm");  // PWM
pwm.set_value(80);
li.call_back(my_function, ON_RISE|ON_FALL);
```


#### SDK
[!SDK](https://github.com/circinusX1/amutrion/wiki)


#### VIDEO
[![video](https://raw.githubusercontent.com/circinusX1/amutrion/master/docs/rrembdemo.gif)](https://youtu.be/ZMlJj0PciWA)


## RASPBERRY-PI GPIO, PWM, SPI, I2C, UART FRAMEWORK.  
### script them(GPIO PWM I2C SPI ADC UART USB FILE-IO & /dev/input/ TCP SSH CURL)
### access them REST-FULLY {JSON IN & OUT}
### All written in C++
#### REACTION TIME ~ 1ms
##### Get automated systems up and running in a mater of few hours.
###### Optional system dependecies (sqlite / CURL)
   
This is a self contained program written in C++. I start it almost 13 years ago using it 
for a game engine automation (see Getic). Then from controlling a game engine I 
extended to do automation scripting adding UART telnet and ssh (see othe projects here). 
Slowly I added SSH, TCP, I2C, ... GPIO's and so on.

    * Usage:
```
    amutrion script_file.src
    
```

Where the script_file is a script like java/c++, but is not java neither c++. 

The Language features can be seen at: 
   * http://squirrel-lang.org/   
   * https://developer.electricimp.com/squirrel/squirrelcrib

    * It targets:
        * Raspberry PI
        * Beaglebone(s)
        * iMX6
        * Nano PI
        * Cherry PI
        * C.H.I.P

### What you can do with it

You can automate a system in matter of few hours depending of the complexity of the automation. 
You get out of the box a JSON output over a socket, you can build a web UI in few moves. 
For example you can make a STOVE or a HVAC or any automation funcy device. It allows fine tunning
from scripted API's to target almost any ARM device that the kernel exposes the peripherials to either 
/sys or /dev filestem. 


### Sample code R-PI
```c++
::using(eGPIO|ePWM|eSRV);

var l1 = PIO(26,  DIR_OUT, LOW, "led"); 
var l2 = PIO(19,  DIR_OUT, HIGH, "led2");
var l3 = PIO(13,  DIR_OUT, LOW, "led3");
var l4 = PIO(6,   DIR_OUT, HIGH, "led4");
var pb = PIO(21,  DIR_IN,  LOW, "button");
var tone = PIO(17,  440, "buzer");       // tone
var counter = PIO(4, -1000, "count");    // frequence-meter
                                        
var pwm = PWM("0.0", 1000, 100, false, "pwm");  // this is a PWM, on chip 0 pwm 0, running a 1000Hz with default 100% pwm

var json_interface = SRV(8078);            // start a TCP Json server on port 8070
var database_sqlite  = Database("/usr/share/embix/db1");

var value = 1;
var k = 0;

function main(ctx)
{
    pb.monitor(callback);               // this PIO fires events into the loop when state changes. 
    l1.set_value(0);                // set this led to 0
    db.save_interval(15000);        // will save sensors/PIO's every 15 seconds
    return run_loop(loop,1000);     // run loop() calling it at 1000 ms interval, though when pb state changes
}

function loop(ctx, dev)                // dev is not null when the monitored device has a change in state.
{
    l1.set_value(value); 
    l2.set_value(!value);
    l3.set_value(value);
    l4.set_value(!value);
    pwm.set_duty(k++);
    value=!value;
    println("counter = " + counter.get_freq());  // this will print roughy 440
    return true;
}

/* this has changed in all flavours*/
function  callback(dev)
{
    println("dev = " + dev.get_value()); // dev is not null only when the monitorred pin is triggered
    return false; // end the program  
}


```

#### Sample to control OLED96 display

```c++

include("plugins/oled96.scr");
/*
sudo nano /lib/udev/rules.d/60-i2c-tools.rules
KERNEL=="i2c-0"     , GROUP="i2c", MODE="0660"
KERNEL=="i2c-[1-9]*", GROUP="i2c", MODE="0666"
sudo adduser $USER i2c
sudo service udev restart
*/

function main(a)
{

    local s = Oled96(2, 0x3c, "96");
    if(s.open("128x64",0,0))
    {
        s.write_string(0,0,"ABCDEF",1);
        kbhit();
        s.clear_display(0);
        s.write_string(0,0,"DEFGHIJKLMN",2);
        kbhit();
        s.clear_display(0);
        s.write_string(0,0,"GHIHGHISHAN",3);
        kbhit();
        s.clear_display(0);
        s.write_string(0,0,"JKLISHAN",1);
        s.write_string(0,1,"2341234134134134",1);
        kbhit();
        s.close();
    }
    return true;
}
```

### Extend amutrion with custom modules. 
### Let's use wiringpi.so module wrapped around wiringPI.so. 
### so wiringPi/arduino style coding can be used
 
```cpp
::using(eSOLIB); // load what we use only 
::import("./modules/libardulike.so");

/*  the code here was pasted as it was taken form Wiring pi example */
var LED=26;

function main(x)
{
    wiringPiSetupGPIO () ;

    PinMode (LED, OUTPUT) ;

    for (;;)
    {
        digitalWrite (LED, 1) ;     // On
        delay (500) ;               // mS
        digitalWrite (LED, 0) ;     // Off
        delay (500) ;
    }
}

```

# Wow!
### Or call directin to wiringpi.so library using arduino style.
#### Import library, get functions and call them.

```cpp
::using(eSOLIB); // load what we use only 

lib := LIB("libwiringPi.so");
lib.load("wiringPiSetupGpio",true,0);   // function name from the so ,function type has return value takes 0 params
lib.load("digitalWrite",false,2);       // function name from the so ,function type no return 2 parameters
lib.load("delay",0,1);                  // function name from the so ,function type no return takes one param
lib.load("PinMode",0,2);                // function name from the so ,function type no return takes one param

var LED = 26;
function main(x)
{
    wiringPiSetupGpio() ;
    PinMode (LED, OUTPUT) ;
    for (;;)
    {
        digitalWrite (LED, 1) ;     // On
        delay (500) ;               // mS
        digitalWrite (LED, 0) ;     // Off
        delay (500) ;
    }
    return false;
}

```

### New declarative tokens as 0o 0c 0s 0w 0i 0u for signed/usigned bit & strong typed binary operations

```cpp

   var v = 0x4444D4D4; print("hex size_t            " + v + "\n");    //  will print the unsigned int value
   var v = 0o4444D4D4; print("octet 8             " + v + "\n");       //  will print 212
   var v = 0c4444D4D4; print("char 8              " + v + "\n");         // will print -44
   var v = 0s4444D4D4; print("short 16            " + v + "\n");       // will print -11052
   var v = 0w4444D4D4; print("unsigned short 16   " + v + "\n");//     will print 54484
   var v = 0iDD44D4D4; print("integer 32          " + v + "\n");         //   will print the negative int value
   var v = 0uDD44D4D4; print("unsigned integer 32 " + v + "\n");  // will print the unsigned int value

// prints

hex size_t          1145361620
octet 8             212
char 8              -44
short 16            -11052
unsigned short 16   54484
integer 32          -582691628
unsigned integer 32 -582691628  // print allways prints int,

```

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=L9RVWU5NUZ4YG)   [goes to meeiot]

Donations are owsom' appreciated 

### Embeded RESFULL / JSON server to control every device (Can be turned on and off)

    *Custom application & scripts....contact me here: https://www.meeiot.org/?p=contact.php    
    

![logo](https://raw.githubusercontent.com/circinusX1/rembix/master/docs/emb3.png)


Credits:

    *https://github.com/albertodemichelis/squirrel
    *https://github.com/hakase-labs/sqrat
    *https://github.com/circinusX1/Easy-ssh_automation
    *https://github.com/circinusX1/xomata
    *https://github.com/circinusX1/scrite
    *https://github.com/circinusX1/The-Ultra-C-Monex-
    
    

![logo](https://raw.githubusercontent.com/circinusX1/rembix/master/docs/embixico.png)



[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=L9RVWU5NUZ4YG)   [donations are taken care by meeiot]



#### Build from sources
###### Prerequisites: root file systems for ARM boards, arm gcc cross compiler and a Linux machine

    * make sure in TOOLS folder you have links to filesystems fo ARM boards and to the arm-gnu-eaby toolcahin
    * cd  to src and make the make_file ENV=env_bbb.sh  or env_rpi.sh or on the host for the host env_thishost.sh
       
       
       
```
.
├── TOOLS                                      <<<<<<<<<<<<<<<  DO THIS
│   ├── beaglebone   -> sym link to debian_root_file_system_beaglebone
│   ├── imx6         -> sym link to debian_imx_file_system
│   ├── raspberrypi  -> sym link to debian_root_file_system_raspberrypi
│   ├── qteverywhere -> sym link to qt-everywhere-opensource-src-5.8.0
│   └── toolchain    -> sym link to tolchain_arm_gcc_compiler
    - chroot to every system root fs and install sqlite/curl/libusb, otherwise disable them form the Makefile   
├── bin
├── env_thishost.sh
├── lib
│   ├── libsqstdlib.a
│   └── libsquirrel.a
├── modules
│   ├── bme280
│   ├── bmi160
│   └── swiringpi
├── src
│   ├── amutrion.pro
│   ├── apis.cpp
│   ├── apis.h
│   ├── apis.o
│   ├── builtin
│   ├── comm
│   ├── drivers
│   │   ├── common
│   │   └── platform
│   │       ├── freebsd
│   │       │   ├── beaglebone
│   │       │   ├── nanopineozero
│   │       │   └── raspberrypi
│   │       └── linux
│   │           ├── beaglebone
│   │           ├── imx6
│   │           ├── nanopineozero
│   │           ├── raspberrypi
│   │           └── thishost
│   ├── env_bbb.sh
│   ├── env_rpi.sh
│   ├── env_thishost.sh
│   ├── env_x86.sh
│   ├── make_file
│   ├── rapidjson
│   ├── sq
│   │   ├── include
│   │   ├── sqrat
│   │   │   ├── include
│   │   │   └── sqratthread
│   │   ├── sqstdlib
│   │   └── squirrel

55 directories, 556 files
```



# LICENSE ADDON

    * Not for commercial witout written consent


[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=L9RVWU5NUZ4YG)   [donations are taken care by meeiot domain]

    

###  You can check my reverse ssh online service and online key value database at 

[reverse ssh as a service](http://www.mylinuz.com)

[key value database as a service](https://www.meeiot.org)


