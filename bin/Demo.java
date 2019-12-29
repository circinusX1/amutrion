


REMBIX REMBIX REMBIX REMBIX REMBIX REMBIX REMBIX REMBIX REMBIX REMBIX REMBIX



                                               NO PYTHON or NODE JS

                SIMPLE, FAST, SMART                     Written in C++






                                                 By. Marius C.












//              SIMPLE LED BLINK //////////////

::using(eGPIO|ePWM);
led  := PIO(20, DIR_OUT, LOW, "led");
function main(ctx)
{
    return run(program,10);
}
function program(ctx,devs)
{
    led.set_toggle();
    sleep(200);
    return true;
}












/////////////  BMO 160 accelerometer and gyro //////////////////
::using(eI2C|eSRV);
::loadmod("./modules/libbmi160.so","ACCEL");
i2c    := I2C(11, 0x68, "i2c");
accel  := ACCEL("i2c", "accel");
server := SRV(8000,"xxx");

function main(x)
{
    return run_program(l, -1);
}

function l(c, d)
{
    var data1 = accel.acceleration();
    var data2 = accel.rotation();

    do {
        println("ACC " + data1.pop());
    } while (data1.len() > 0);

    do {
        println("ACC " + data2.pop());
    } while (data2.len() > 0);
    return true;
}

/////////////  2 GPIO;s I2C REST server //////////////////
::using(eI2C|eGPIO|eUART|eSRV);
l1   := PIO(506,  DIR_OUT, LOW, "led");
l2   := PIO(507,  DIR_OUT, HIGH, "led2");
i2c  := I2C(11, 0x68, "i2c");
json := SRV(8000,"rest");

function main(ctx)
{
    i2c.autoopen(false);
    if(i2c.open(2)){
        var arr = i2c.ioread(0, 4);
        i2c.close();
    }
    return run_program(program,2000);
}

function program(ctx, dev)
{
    if(i2c.open(2)){
        var arr = i2c.ioread(0, 4);
        i2c.close();
    }
    return true;
}


/////////////  OPENGL WINDOW //////////////////
::using(eSOLIB);
lib := LIB("libglfw.so");                       lib2 := LIB("libGL.so.1.0.0");
GL_COLOR_BUFFER_BIT := 0x00004000
lib.load("glfwInit",true,0);                    lib.load("glfwCreateWindow",true,5);
lib.load("glfwMakeContextCurrent",false,1);     lib.load("glfwWindowShouldClose",true,1);
lib.load("glfwSwapBuffers",false,1);            lib.load("glfwPollEvents",false,0);
lib.load("glfwTerminate",false,0);              lib2.load("glClear",0,1);

function main(x)
{
   glfwInit();
   var window = glfwCreateWindow(640, 480, "Hello World", null, null);
   glfwMakeContextCurrent(window);
   while (!glfwWindowShouldClose(window))
   {
       glClear(GL_COLOR_BUFFER_BIT);
       glfwSwapBuffers(window);
       glfwPollEvents();
   }
   glfwTerminate();
   return false;
}




/////////////  WIRING PI LIBRARY //////////////////

::using(eSOLIB|eGPIO|ePWM);

lib := LIB("libwiringPi.so");
lib.load("wiringPiSetupGpio",true,0);   // has return value takes 0 params
lib.load("digitalWrite",false,2);       // no return 2 parameters
lib.load("delay",0,1);                  // har return takes one param
lib.load("pinMode",0,2);                // har return takes one param

var LED = 26;
function main(x)
{
    wiringPiSetupGpio() ;
    pinMode (LED, OUTPUT) ;
    for (;;)
    {
        digitalWrite (LED, 1) ;     // On
        delay (500) ;               // mS
        digitalWrite (LED, 0) ;     // Off
        delay (500) ;
    }
    return false;
}



/////////////  OLED 96 CLOCK  //////////////////

::using(eI2C|eGPIO|ePWMM|eSRV|eDB);
::include("modules/_oled96.inc");

var s = Oled96(11, 0x3c, "OLED96");
s.autoopen(false);
function main(a)
{
    var k;
    s.autoopen(false);
    if(s.xopen("128x64",0,0)){
        s.clear_display(0);
        k = run_program(kk, 1000);
    }
    s.xclose();
    return k;
}

function kk(ctx,dev)
{
    s.write_string(0,1, get_strtime() ,2);
}




/////////////  CURL CONTROL ESP ARDIONO WEB PAGE1 //////////////////

::using(eCURL|eSRV|eBASE|eBASE);
class XX extends BASE
{
    curl   = CURL(2000,"led");
    constructor()
    {
        _value = "xx";
        base.constructor(this, eSTRING, "wrapp");
    }
    function get_value(key)
    {
        curl.set_url("192.168.1.223",0,"");
        var html = curl.perform(4000);
        if(html.find("pin is now: Off")!=0)
            return "LED,OFF";
        return "LED,ON";
    }

    function set_value(k,v)
    {
        curl.set_url("192.168.1.223/LED="+v,0,"");
        var html = curl.perform(4000);
        return true;
    }
};
/////////////  CURL CONTROL ESP ARDIONO WEB PAGE2 //////////////////
var xx = XX();  var srv = SRV(8000,"ddd");

function main(o)
{
    return run_program(loo,-1);
}

function loo(x,d)
{
    return true;
}
















/////////////  GPIO PWM COUNTER AND BUZZER //////////////////

::using(eGPIO|ePWMM|eSRV);

var l3 = PIO(13,  DIR_OUT, LOW, "led3");
var pb = PIO(21,  DIR_IN,  LOW, "buton");
var tone = PIO(17,  50, "tone");
var counter = PIO(4, -1000, "count");
var pwm = PWM("0.0", 1000, 100, false, "pwm");

function main(ctx)
{
    pb.set_monitor(true);
    l1.set_value(0);
    return run_program(program,10000);
}

var k = 0;
function program(ctx, dev)
{
    pwm.set_value(k++);
    if(dev)
        println("pb freq is: " + dev.get_value());
    println("counter = " + counter.get_freq());
    return true;
}


/////////////  R-PI WIRING EXTENSION //////////////////

::import("./modules/libardulike.so");

var LED=26;

function main(x)
{
    wiringPiSetupGpio () ;
    pinMode (LED, OUTPUT) ;
    for (;;)
    {
        digitalWrite (LED, 1) ;     // On
        delay (500) ;               // mS
        digitalWrite (LED, 0) ;     // Off
        delay (500) ;
    }
}















    THAK YOU.                       marrius9876@gmail.com








































