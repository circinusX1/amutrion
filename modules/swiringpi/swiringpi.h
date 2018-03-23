/*
THIS SOFTWARE IS PROVIDED BY mcomariusATg.ailDOTcom 'AS IS' AND ANY
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

#if !defined(_SIMPLEMODULE_H_)
#define _SIMPLEMODULE_H_

#include "sqmodule.h"
#include "squirrel.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT SQRESULT sqmodule_load(HSKVM v, HSQAPI api);
EXPORT void sqmodule_unload(void);

int test(const char* ,int);

#ifdef __cplusplus
}
#endif

#endif
