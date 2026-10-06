/* Minimal AUTOSAR Compiler.h (host build). */
#ifndef COMPILER_H
#define COMPILER_H

#define AUTOMATIC
#define TYPEDEF
#define STATIC static
#define NULL_PTR ((void *)0)
#define INLINE inline
#define LOCAL_INLINE static inline

#define FUNC(rettype, memclass) rettype
#define FUNC_P2CONST(rettype, ptrclass, memclass) const rettype *
#define FUNC_P2VAR(rettype, ptrclass, memclass) rettype *
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)
#define CONST(consttype, memclass) const consttype
#define VAR(vartype, memclass) vartype

#endif /* COMPILER_H */
