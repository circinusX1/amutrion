/*
Copyright (c) 2014-2016 Marius C. All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
by the https://github.com/circinusX1. The name of the
https://github.com/circinusX1/amutrion may not be used to endorse or promote
products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifdef WITH_SSH
#include "sshcomm.h"

bool SshComm::_squed;

SshComm::SshComm(const char* cred,
                 const char* name):ComSsh(cred),
                                    Divais(eSTRING,eSSH,name),
                                    Reg<SshComm>(this),
                                    RtxBus<SshComm>(this,false,true)
{
    SshComm::_squed ? _o.BindCppObject(this) : (void)(0);
}

SshComm::SshComm(SqObj& o,
                 const char* cred,
                 const char* name):ComSsh(cred),
                                    Divais(eSTRING,eSSH,name),
                                    Reg<SshComm>(this),
                                    RtxBus<SshComm>(this,false,true)
{
    plug_it(o, name);
}


SshComm::~SshComm()
{
}

bool  SshComm::_write_now(const devdata_t& vl)
{
    return this->bwrite(vl.c_bytes(), vl.length());
}

size_t  SshComm::_fecth(devdata_t& vl, const char* filter)
{
    return 0;
}

bool SshComm::_mon_callback(time_t tnow)
{
/*
    if(_etype==eSTRING){
        const char* rv = gets(_bufsz);
        return this->Divais::_call_cb(rv);
    }
    const SqArr& rv = read(_bufsz);
    return this->Divais::_call_cb(rv);
    */
    return false;
}

const char* SshComm::_gets()
{
    return RtxBus<SshComm>::_gets();
}

bool SshComm::set_cb(SqMemb& mem)
{
    return this->Divais::set_cb(mem);
}

void SshComm::on_event(E_VENT e, const uint8_t* buff, int len, int options)
{
    _mon_dirt = true;
}

bool	SshComm::_set_value(const char* key, const char* value)
{
    return false;
}

const char*	SshComm::_get_values(const char* key)
{
    return Divais::_get_values(key);
}

#endif //ifdef WITH_SSH
