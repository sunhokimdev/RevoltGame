#pragma once

#define SAFE_RELEASE(p) { if(p) p->Release() ; p = NULL ;}
#define SAFE_DELETE(p) { if(p) delete p ; p = NULL ; }
#define SAFE_DELETE_ARRAY(p) {if(p) delete[] p; p = NULL;}
#define SAFE_DESTROY(p) {if(p) p->Destroy();}
#define SAFE_UPDATE(p) {if(p) p->Update();}
#define SAFE_RENDER(p) {if(p) p->Render();}

#define SINGLETONE(class_name) \
	private : \
		class_name(void); \
		~class_name(void); \
	public: \
		static class_name* GetInstance() \
		{ \
			static class_name instance; \
			return &instance; \
		}

#define SYNTHESIZE( varType , varName , funName) \
protected: varType varName ; \
public : inline varType Get##funName(void) const { return varName ; } \
public : inline void Set##funName(varType var) { varName = var ; }

#define SYNTHESIZE_VIRTUAL( varType , varName , funName) \
protected: varType varName; \
public: inline virtual varType Get##funName(void) const { return varName; } \
public : inline virtual void Set##funName(varType var) { varName = var ; }

#define SYNTHESIZE_PASS_BY_REF( varType , varName , funName) \
protected: varType varName ; \
public : inline varType& Get##funName(void)  { return varName ; } \
public : inline void Set##funName(varType& var) { varName = var ; }

#define SAFE_ADD_REF(p) { if(p) p->AddRef() ; }

#define SYNTHESIZE_ADD_REF( varType , varName, funName) \
	protected : varType  varName ; \
	public : virtual varType Get##funName(void) const { \
									return varName ; } \
	public : virtual void Set##funName(varType var) { \
				if( varName != var ) { \
					SAFE_ADD_REF(var) ; \
					SAFE_RELEASE(varName) ; \
					varName = var ; \
				} \
		}\

