/*
THIS SOFTWARE IS PROVIDED BY mcomariusATgmailDOTcom 'AS IS' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL mcomariusATgmailDOTcom BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*/


#ifndef MCP9600_H
#define MCP9600_H

#include <string.h>
#include "bmi160_global.h"
#include "../iper.h"


class EXPORT Bmi160 : public I_IDev
{

public:
    Bmi160(const char* dev, const char* name);
    virtual ~Bmi160();
    static void   squit(const char* name);
	Sqrat::Array  acceleration();
	Sqrat::Array  rotation();

	 const char* name()const;
	 const char* dev_key()const;
	 bool  is_monitorred(size_t t);
	 bool  set_value(const char* key, const char* value);
	 const char* get_value(const char* key);
	 const any_t& get_data()const;
	 void  sync(const char* filter);
	 Sqrat::Object object()const;



private:
    IoOps*          _ird;
    std::string     _name;
    double          _acc[3];
    double          _rot[3];
    any_t           _data;
    char            _retbuff[64];
    Sqrat::Object   _o;
};

#endif // MCP9600_H
