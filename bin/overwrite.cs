// SCRIPT  TESTED

::using(eCURL|eSRV|eBASE);

setdbg(0xFF);

class XX extends BASE
{
    _value = "";
    curl   = CURL(2000,"led");
    constructor()
    {
        _value = "xx";
        base.constructor(this, eSTRING, "wrapp");
    }

    // get sample    get JSON ->>>>>>>
    function get_value(key)
    {
       curl.set_url("192.168.1.223",0,"");
       var html = curl.perform(4000);
       if(html.find("Off"))
            this._value="ON";
       else
            this._value="OFF";

        return { /*dump test */
            LED = this._value,
            CMDS = ["ON","OFF"],
            VALS = [0,1,2,3,4,5],
            REALS = [3.4,5.6,0.7777]
        };
    }

    function set_value(k,v)
    {
        curl.set_url("192.168.1.223/LED="+v,0,"");
        println("--------sending ---->" + "192.168.1.223/LED="+v )
        var html = curl.perform(4000);
        return true;
    }
};


var xx = XX();
var srv = SRV(8000,"ddd");

function main(o)
{
    return run(loo,-1);
}

function loo(x,d)
{
    return true;
}

