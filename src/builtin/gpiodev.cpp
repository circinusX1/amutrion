/*
Copyright (c) 2014-2016 comarius.DPT All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the https://github.com/comarius. The name of the
https://github.com/comarius may not be used to endorse or promote
products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "gpiodev.h"
#include "inst.h"

GpioDev::GpioDev(EGPIO_PIN pn,
                 EPIN_DIR pd, int on,
                 const char* name):DvGpio(pn,pd,on),
                 Divais(eINT, eGPIO, name),Reg<GpioDev>(this),
                                        _sec(0),
                                        _dir(pd),
                                        _counter(0),
                                        _curval(eLOW),
                                        _counting(false)
{
   _o.BindCppObject(this);
    LOGD3(__FUNCTION__ <<" "<< name);
}

GpioDev::GpioDev(SqObj& o,
                 EGPIO_PIN pn,
                 EPIN_DIR pd, int on,
                 const char* name):DvGpio(pn,pd,on),
                 Divais(eINT, eGPIO, name),Reg<GpioDev>(this),
                                    _sec(0),
                                    _dir(pd),
                                    _counter(0),
                                    _curval(eHIGH),
                                    _counting(false)
{
    ctx_it(o, name);
    LOGD3(__FUNCTION__ <<" "<< name);
}


//tone up to 500 Hz
GpioDev::GpioDev(EGPIO_PIN pn, int freq,
                 const char* name):DvGpio(pn,freq >0 ? eOut : eIn,0),
                 Divais(eINT,eGPIO,name),Reg<GpioDev>(this),
                                  _sec(0),
                                  _dir(freq >0 ? eOut : eIn),
                                  _freq(freq > 0 ? freq : 0 ),
                                  _counter(0),
                                  _curval(eHIGH),
                                  _counting(freq < 0)
{
    _o.BindCppObject(this);
    _monitor = true;
    if(freq>=0)
    {
        if(_freq==0)
            _freq=2;
        _freq*=2;
    }
    else {
        _interval=-freq;
    }
    LOGD3(__FUNCTION__ <<" "<< name);
}

GpioDev::~GpioDev()
{
    LOGD3(__FUNCTION__ <<" "<< _name);
}

int    GpioDev::set_toggle()
{
    int v = get_value();
    if(v>=0)
    {
        v = !v;
        return set_value(v);
    }
    return -1;
}

int  GpioDev::set_value(int val)
{
    _curval = _reversed ? !val : val;
    std::string s = std::to_string(val);
    return this->bwrite((const uint8_t*)s.c_str(), s.length());
}

int  GpioDev::get_value()
{
    if(_mon_dirt)
    {
        _mon_dirt = false;
        int cv = _curdata.to_t<int>();
        return _reversed ? !cv : cv;
    }
    _curdata.clear();
    char val[8]={0};
    if(this->bread((uint8_t*)val,sizeof(val)))
    {
        if(_monitor)
            _mon_dirt=_check_dirt();
        return _curdata.to_t<int>();
    }
    return eLERR;
}

bool  GpioDev::_write_now(const any_t& vl)
{
    return this->bwrite(vl.c_bytes(), vl.length());
}

size_t  GpioDev::_read_now(any_t& vl, const char* filter)
{
    return get_value();
}

int GpioDev::get_freq()
{
    return _freq/2;
}

int GpioDev::set_freq(int freq)
{
    if(_dir & eOut)
    {
        if(freq==0)freq = 2;
        freq *= 2;
        return _freq = freq;
    }
    return 0;
}

bool GpioDev::_touch_it(size_t t)
{
    if(_dir & eIn)
    {
        int cv = get_value();
        if(_counting)
        {
            if(t - _sec>_interval)
            {
                _freq = _counter;
                _counter  = 0;
                _sec = t;
            }
            if(cv != _curval)
            {
                ++_counter;
                _curval = cv;
            }
            return false;
        }
        return _mon_dirt;
    }
    else
    {
        //as tone buzzer
        size_t msecs = 1000 / _freq;
        if(t - _sec >= msecs)
        {
            const uint8_t* ts = tos(_curval =! _curval);
            this->bwrite(ts,::strlen((const char*)ts));
            _sec = t;
        }
    }
    return false;
}

bool GpioDev::set_monitor(bool mon)
{
    if(_dir & eOut || _counting )
    {
        LOGW("cannot moitor an out pin or a counter");
        return false;
    }
    _monitor = mon;
    return true;
}

void GpioDev::on_event(E_VENT e, const uint8_t* val, int len, int options)
{
    if(e==eREAD)
    {
        int ival = ::atoi((const char*)val);
        if(_reversed)
            ival = !ival;
        _curdata.let(ival);
    }
}

bool	GpioDev::_set_values(const char* key, const char* value)
{
    if(key[0]=='v') return set_value(::atoi(value));
    if(key[0]=='f') return  set_freq(::atoi(value));
    if(key[0]=='r') { _reversed = value[0]==1 ? true : false; return true;}
    if(key[0]=='t') { return set_toggle();}
    return false;
}

const char*	GpioDev::_get_values(const char* key)
{
    if(key[0]==ALLDATA)
    {
        _forjson += "value,";
        _forjson += _curdata.to_string<int>();
        _forjson += ",freq,";
        _forjson += std::to_string(_freq);
        _forjson += ",reverse,";
        _forjson += std::to_string(_reversed);
        return _forjson.c_str();
    }
    if(key[0]=='v') { return _curdata.c_chars();}
    if(key[0]=='f') { ::sprintf(_sret,"%d",_freq); return _sret;}
    if(key[0]=='r') { ::sprintf(_sret,"%d",_reversed); return _sret;}
    GETER_SYSCAT();
}

