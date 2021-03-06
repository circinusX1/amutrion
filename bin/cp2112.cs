// SCRIPT  TESTED ON BBB

::using(eI2C|eGPIO|eUART|eSRV);

l1 := GPIO(506,  DIR_OUT, LOW, "led");
l2 := GPIO(507,  DIR_OUT, HIGH, "led2");
i2c := I2C(11, 0x68, "i2c");
json := SRV(8000,"rest");


function main(ctx)
{
    i2c.autoopen(false);
    if(i2c.open(2)){
        var arr = i2c.ioread(0, 4);
        i2c.close();
        println("reg: " + 0 + " = " + intarr2a(arr,","));
    }
    println("L1=" + l1.set_toggle());
    println("L2=" + l2.set_toggle());
    return run(loop,2000);
}

function loop(ctx, dev)
{
    println("L1=" + l1.set_toggle());
    println("L2=" + l2.set_toggle());
    if(i2c.open(2)){
        var arr = i2c.ioread(0, 4);
        i2c.close();
        println("reg: " + 0 + " = " + intarr2a(arr,","));
    }
    return true;
}

