#include "Types.h"
#define MAX_ARGS_LEN 512

class FuncContext
{
public:
	FuncContext(void *pFuncAddr, const String& strPFName);

	~FuncContext(void);

	void           runPFunc();

public:
	unsigned int                m_uiESP1;
    unsigned int				m_uiESP2;
    unsigned int				m_uiEBP1;
    unsigned int				m_uiEBP2;
    unsigned int                m_uiEAX;
    unsigned int                m_uiEDX;
    void *						m_pRets;
    int							m_iRetsLen;
    char 						m_acArgs[MAX_ARGS_LEN];
    int							m_iArgsLen;
protected:
	std::string          m_strFuncName;
	void *               m_pFuncAddr;
}
