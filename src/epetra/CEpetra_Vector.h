#include "CTrilinos_config.h"


/* True C header file! */


#ifndef CEPETRA_VECTOR_H
#define CEPETRA_VECTOR_H


#include "CEpetra_BlockMap.h"
#include "CEpetra_MultiVector.h"
#include "CTrilinos_enums.h"


#ifdef __cplusplus
extern "C" {
#endif


/* Functions Epetra_Vector_Cast() and Epetra_Vector_Abstract()
   are used for casting CTrilinos objects from one type to another.
   The former function performs a dynamic cast on the underlying object
   and stores an RCP to it in the Epetra_Vector table, while
   the latter only converts the type of the struct that references the
   object so that an object of any type can be passed to the former
   function (use the _Abstract() function corresponding to the type
   of the object that will be casted, not the type to which it will
   be casted).
*/

CT_Epetra_Vector_ID_t Epetra_Vector_Cast ( CTrilinos_Object_ID_t id );

CTrilinos_Object_ID_t Epetra_Vector_Abstract ( 
  CT_Epetra_Vector_ID_t id );

/* Original C++ prototype:
   Epetra_Vector(const Epetra_BlockMap& Map, bool zeroOut = true);
*/
CT_Epetra_Vector_ID_t Epetra_Vector_Create ( 
  CT_Epetra_BlockMap_ID_t MapID, boolean zeroOut );

/* Original C++ prototype:
   Epetra_Vector(const Epetra_Vector& Source);
*/
CT_Epetra_Vector_ID_t Epetra_Vector_Duplicate ( 
  CT_Epetra_Vector_ID_t SourceID );

/* Original C++ prototype:
   Epetra_Vector(Epetra_DataAccess CV, const Epetra_BlockMap& Map, double *V);
*/
CT_Epetra_Vector_ID_t Epetra_Vector_Create_FromArray ( 
  CT_Epetra_DataAccess_E_t CV, CT_Epetra_BlockMap_ID_t MapID, 
  double * V );

/* Original C++ prototype:
   Epetra_Vector(Epetra_DataAccess CV, const Epetra_MultiVector& Source, int Index);
*/
CT_Epetra_Vector_ID_t Epetra_Vector_FromSource ( 
  CT_Epetra_DataAccess_E_t CV, CT_Epetra_MultiVector_ID_t SourceID, 
  int Index );

/* Original C++ prototype:
   virtual ~Epetra_Vector ();
*/
void Epetra_Vector_Destroy ( CT_Epetra_Vector_ID_t * selfID );

/* Original C++ prototype:
   int ReplaceGlobalValues(int NumEntries, double * Values, int * Indices);
*/
int Epetra_Vector_ReplaceGlobalValues ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, double * Values, 
  int * Indices );

/* Original C++ prototype:
   int ReplaceMyValues(int NumEntries, double * Values, int * Indices);
*/
int Epetra_Vector_ReplaceMyValues ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, double * Values, 
  int * Indices );

/* Original C++ prototype:
   int SumIntoGlobalValues(int NumEntries, double * Values, int * Indices);
*/
int Epetra_Vector_SumIntoGlobalValues ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, double * Values, 
  int * Indices );

/* Original C++ prototype:
   int SumIntoMyValues(int NumEntries, double * Values, int * Indices);
*/
int Epetra_Vector_SumIntoMyValues ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, double * Values, 
  int * Indices );

/* Original C++ prototype:
   int ReplaceGlobalValues(int NumEntries, int BlockOffset, double * Values, int * Indices);
*/
int Epetra_Vector_ReplaceGlobalValues_BlockPos ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, int BlockOffset, 
  double * Values, int * Indices );

/* Original C++ prototype:
   int ReplaceMyValues(int NumEntries, int BlockOffset, double * Values, int * Indices);
*/
int Epetra_Vector_ReplaceMyValues_BlockPos ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, int BlockOffset, 
  double * Values, int * Indices );

/* Original C++ prototype:
   int SumIntoGlobalValues(int NumEntries, int BlockOffset, double * Values, int * Indices);
*/
int Epetra_Vector_SumIntoGlobalValues_BlockPos ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, int BlockOffset, 
  double * Values, int * Indices );

/* Original C++ prototype:
   int SumIntoMyValues(int NumEntries, int BlockOffset, double * Values, int * Indices);
*/
int Epetra_Vector_SumIntoMyValues_BlockPos ( 
  CT_Epetra_Vector_ID_t selfID, int NumEntries, int BlockOffset, 
  double * Values, int * Indices );

/* Original C++ prototype:
   int ExtractCopy(double *V) const;
*/
int Epetra_Vector_ExtractCopy ( 
  CT_Epetra_Vector_ID_t selfID, double * V );

/* Original C++ prototype:
   int ExtractView(double **V) const;
*/
int Epetra_Vector_ExtractView ( 
  CT_Epetra_Vector_ID_t selfID, double ** V );

/* Original C++ prototype:
   const double& operator [] (int index) const;
*/
double Epetra_Vector_getElement ( 
  CT_Epetra_Vector_ID_t selfID, int index );


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* CEPETRA_VECTOR_H */

