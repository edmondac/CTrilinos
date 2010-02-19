
/*! @HEADER */
/*
************************************************************************

                CTrilinos:  C interface to Trilinos
                Copyright (2009) Sandia Corporation

Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
license for use of this work by or on behalf of the U.S. Government.

This library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as
published by the Free Software Foundation; either version 2.1 of the
License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
USA
Questions? Contact M. Nicole Lemaster (mnlemas@sandia.gov)

************************************************************************
*/
/*! @HEADER */


#include "CTrilinos_config.h"


#ifdef HAVE_CTRILINOS_AZTECOO


#include "CEpetra_Operator_Cpp.hpp"
#include "CEpetra_MultiVector_Cpp.hpp"
#include "CEpetra_RowMatrix_Cpp.hpp"
#include "CEpetra_LinearProblem_Cpp.hpp"
#include "CTeuchos_ParameterList_Cpp.hpp"
#include "CAztecOO_Cpp.hpp"
#include "CAztecOO.h"
#include "AztecOO.h"
#include "Teuchos_RCP.hpp"
#include "CTrilinos_enums.h"
#include "CTrilinos_utils.hpp"
#include "CTrilinos_utils_templ.hpp"
#include "CTrilinos_TableRepos.hpp"
//
// Definitions from CAztecOO.h
//


extern "C" {


CT_AztecOO_ID_t AztecOO_Create_FromOperator ( 
  CT_Epetra_Operator_ID_t AID, CT_Epetra_MultiVector_ID_t XID, 
  CT_Epetra_MultiVector_ID_t BID )
{
    return CTrilinos::tableRepos().store<AztecOO, CT_AztecOO_ID_t>(
        new AztecOO(CEpetra::getOperator(AID).getRawPtr(), 
        CEpetra::getMultiVector(XID).getRawPtr(), 
        CEpetra::getMultiVector(BID).getRawPtr()));
}

CT_AztecOO_ID_t AztecOO_Create_FromRowMatrix ( 
  CT_Epetra_RowMatrix_ID_t AID, CT_Epetra_MultiVector_ID_t XID, 
  CT_Epetra_MultiVector_ID_t BID )
{
    return CTrilinos::tableRepos().store<AztecOO, CT_AztecOO_ID_t>(
        new AztecOO(CEpetra::getRowMatrix(AID).getRawPtr(), 
        CEpetra::getMultiVector(XID).getRawPtr(), 
        CEpetra::getMultiVector(BID).getRawPtr()));
}

CT_AztecOO_ID_t AztecOO_Create_FromLinearProblem ( 
  CT_Epetra_LinearProblem_ID_t LinearProblemID )
{
    return CTrilinos::tableRepos().store<AztecOO, CT_AztecOO_ID_t>(
        new AztecOO(*CEpetra::getConstLinearProblem(
        LinearProblemID)));
}

CT_AztecOO_ID_t AztecOO_Create (  )
{
    return CTrilinos::tableRepos().store<AztecOO, CT_AztecOO_ID_t>(
        new AztecOO());
}

CT_AztecOO_ID_t AztecOO_Duplicate ( CT_AztecOO_ID_t SolverID )
{
    return CTrilinos::tableRepos().store<AztecOO, CT_AztecOO_ID_t>(
        new AztecOO(*CAztecOO::getConstAztecOO(SolverID)));
}

void AztecOO_Destroy ( CT_AztecOO_ID_t * selfID )
{
    CTrilinos::tableRepos().remove(selfID);
}

int AztecOO_SetProblem ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_LinearProblem_ID_t probID, 
  boolean call_SetPrecMatrix )
{
    return CAztecOO::getAztecOO(selfID)->SetProblem(
        *CEpetra::getConstLinearProblem(probID), ((
        call_SetPrecMatrix) != FALSE ? true : false));
}

int AztecOO_SetUserOperator ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_Operator_ID_t UserOperatorID )
{
    return CAztecOO::getAztecOO(selfID)->SetUserOperator(
        CEpetra::getOperator(UserOperatorID).getRawPtr());
}

int AztecOO_SetUserMatrix ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_RowMatrix_ID_t UserMatrixID, 
  boolean call_SetPrecMatrix )
{
    return CAztecOO::getAztecOO(selfID)->SetUserMatrix(
        CEpetra::getRowMatrix(UserMatrixID).getRawPtr(), ((
        call_SetPrecMatrix) != FALSE ? true : false));
}

int AztecOO_SetLHS ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_MultiVector_ID_t XID )
{
    return CAztecOO::getAztecOO(selfID)->SetLHS(
        CEpetra::getMultiVector(XID).getRawPtr());
}

int AztecOO_SetRHS ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_MultiVector_ID_t BID )
{
    return CAztecOO::getAztecOO(selfID)->SetRHS(
        CEpetra::getMultiVector(BID).getRawPtr());
}

int AztecOO_SetPrecMatrix ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_RowMatrix_ID_t PrecMatrixID )
{
    return CAztecOO::getAztecOO(selfID)->SetPrecMatrix(
        CEpetra::getRowMatrix(PrecMatrixID).getRawPtr());
}

int AztecOO_SetPrecOperator ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_Operator_ID_t PrecOperatorID )
{
    return CAztecOO::getAztecOO(selfID)->SetPrecOperator(
        CEpetra::getOperator(PrecOperatorID).getRawPtr());
}

int AztecOO_ConstructPreconditioner ( 
  CT_AztecOO_ID_t selfID, double * condest )
{
    return CAztecOO::getAztecOO(selfID)->ConstructPreconditioner(
        *condest);
}

int AztecOO_DestroyPreconditioner ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getAztecOO(selfID)->DestroyPreconditioner();
}

double AztecOO_Condest ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->Condest();
}

int AztecOO_CheckInput ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->CheckInput();
}

CT_Epetra_LinearProblem_ID_t AztecOO_GetProblem ( 
  CT_AztecOO_ID_t selfID )
{
    return CEpetra::storeLinearProblem(CAztecOO::getConstAztecOO(
        selfID)->GetProblem());
}

CT_Epetra_Operator_ID_t AztecOO_GetUserOperator ( 
  CT_AztecOO_ID_t selfID )
{
    return CEpetra::storeOperator(CAztecOO::getConstAztecOO(
        selfID)->GetUserOperator());
}

CT_Epetra_RowMatrix_ID_t AztecOO_GetUserMatrix ( 
  CT_AztecOO_ID_t selfID )
{
    return CEpetra::storeRowMatrix(CAztecOO::getConstAztecOO(
        selfID)->GetUserMatrix());
}

CT_Epetra_Operator_ID_t AztecOO_GetPrecOperator ( 
  CT_AztecOO_ID_t selfID )
{
    return CEpetra::storeOperator(CAztecOO::getConstAztecOO(
        selfID)->GetPrecOperator());
}

CT_Epetra_RowMatrix_ID_t AztecOO_GetPrecMatrix ( 
  CT_AztecOO_ID_t selfID )
{
    return CEpetra::storeRowMatrix(CAztecOO::getConstAztecOO(
        selfID)->GetPrecMatrix());
}

CT_Epetra_MultiVector_ID_t AztecOO_GetLHS ( CT_AztecOO_ID_t selfID )
{
    return CEpetra::storeMultiVector(CAztecOO::getConstAztecOO(
        selfID)->GetLHS());
}

CT_Epetra_MultiVector_ID_t AztecOO_GetRHS ( CT_AztecOO_ID_t selfID )
{
    return CEpetra::storeMultiVector(CAztecOO::getConstAztecOO(
        selfID)->GetRHS());
}

void AztecOO_PrintLinearSystem ( 
  CT_AztecOO_ID_t selfID, const char * name )
{
    CAztecOO::getAztecOO(selfID)->PrintLinearSystem(name);
}

int AztecOO_SetParameters ( 
  CT_AztecOO_ID_t selfID, 
  CT_Teuchos_ParameterList_ID_t parameterlistID, 
  boolean cerr_warning_if_unused )
{
    return CAztecOO::getAztecOO(selfID)->SetParameters(
        *CTeuchos::getParameterList(parameterlistID), ((
        cerr_warning_if_unused) != FALSE ? true : false));
}

int AztecOO_SetAztecDefaults ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getAztecOO(selfID)->SetAztecDefaults();
}

int AztecOO_SetAztecOption ( 
  CT_AztecOO_ID_t selfID, int option, int value )
{
    return CAztecOO::getAztecOO(selfID)->SetAztecOption(option, 
        value);
}

int AztecOO_GetAztecOption ( CT_AztecOO_ID_t selfID, int option )
{
    return CAztecOO::getAztecOO(selfID)->GetAztecOption(option);
}

int AztecOO_SetAztecParam ( 
  CT_AztecOO_ID_t selfID, int param, double value )
{
    return CAztecOO::getAztecOO(selfID)->SetAztecParam(param, value);
}

const int * AztecOO_GetAllAztecOptions ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->GetAllAztecOptions();
}

const double * AztecOO_GetAllAztecParams ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->GetAllAztecParams();
}

int AztecOO_SetAllAztecOptions ( 
  CT_AztecOO_ID_t selfID, const int * options )
{
    return CAztecOO::getAztecOO(selfID)->SetAllAztecOptions(options);
}

int AztecOO_SetAllAztecParams ( 
  CT_AztecOO_ID_t selfID, const double * params )
{
    return CAztecOO::getAztecOO(selfID)->SetAllAztecParams(params);
}

int AztecOO_Iterate_Current ( 
  CT_AztecOO_ID_t selfID, int MaxIters, double Tolerance )
{
    return CAztecOO::getAztecOO(selfID)->Iterate(MaxIters, 
        Tolerance);
}

int AztecOO_Iterate ( 
  CT_AztecOO_ID_t selfID, CT_Epetra_RowMatrix_ID_t AID, 
  CT_Epetra_MultiVector_ID_t XID, CT_Epetra_MultiVector_ID_t BID, 
  int MaxIters, double Tolerance )
{
    return CAztecOO::getAztecOO(selfID)->Iterate(
        CEpetra::getRowMatrix(AID).getRawPtr(), 
        CEpetra::getMultiVector(XID).getRawPtr(), 
        CEpetra::getMultiVector(BID).getRawPtr(), MaxIters, 
        Tolerance);
}

int AztecOO_recursiveIterate ( 
  CT_AztecOO_ID_t selfID, int MaxIters, double Tolerance )
{
    return CAztecOO::getAztecOO(selfID)->recursiveIterate(MaxIters, 
        Tolerance);
}

const double * AztecOO_GetAztecStatus ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->GetAztecStatus();
}

int AztecOO_SetUseAdaptiveDefaultsTrue ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getAztecOO(
        selfID)->SetUseAdaptiveDefaultsTrue();
}

int AztecOO_SetAdaptiveParams ( 
  CT_AztecOO_ID_t selfID, int NumTrials, double * athresholds, 
  double * rthresholds, double condestThreshold, double maxFill, 
  int maxKspace )
{
    return CAztecOO::getAztecOO(selfID)->SetAdaptiveParams(NumTrials, 
        athresholds, rthresholds, condestThreshold, maxFill, 
        maxKspace);
}

int AztecOO_AdaptiveIterate ( 
  CT_AztecOO_ID_t selfID, int MaxIters, int MaxSolveAttempts, 
  double Tolerance )
{
    return CAztecOO::getAztecOO(selfID)->AdaptiveIterate(MaxIters, 
        MaxSolveAttempts, Tolerance);
}

int AztecOO_NumIters ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->NumIters();
}

double AztecOO_TrueResidual ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->TrueResidual();
}

double AztecOO_ScaledResidual ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->ScaledResidual();
}

double AztecOO_RecursiveResidual ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->RecursiveResidual();
}

double AztecOO_SolveTime ( CT_AztecOO_ID_t selfID )
{
    return CAztecOO::getConstAztecOO(selfID)->SolveTime();
}

int AztecOO_GetAllAztecStatus ( 
  CT_AztecOO_ID_t selfID, double * status )
{
    return CAztecOO::getAztecOO(selfID)->GetAllAztecStatus(status);
}


} // extern "C"


//
// Definitions from CAztecOO_Cpp.hpp
//


/* get AztecOO from non-const table using CT_AztecOO_ID */
const Teuchos::RCP<AztecOO>
CAztecOO::getAztecOO( CT_AztecOO_ID_t id )
{
    return CTrilinos::tableRepos().get<AztecOO, CT_AztecOO_ID_t>(id);
}

/* get AztecOO from non-const table using CTrilinos_Universal_ID_t */
const Teuchos::RCP<AztecOO>
CAztecOO::getAztecOO( CTrilinos_Universal_ID_t id )
{
    return CTrilinos::tableRepos().get<AztecOO, CTrilinos_Universal_ID_t>(id);
}

/* get const AztecOO from either the const or non-const table
 * using CT_AztecOO_ID */
const Teuchos::RCP<const AztecOO>
CAztecOO::getConstAztecOO( CT_AztecOO_ID_t id )
{
    return CTrilinos::tableRepos().getConst<AztecOO, CT_AztecOO_ID_t>(id);
}

/* get const AztecOO from either the const or non-const table
 * using CTrilinos_Universal_ID_t */
const Teuchos::RCP<const AztecOO>
CAztecOO::getConstAztecOO( CTrilinos_Universal_ID_t id )
{
    return CTrilinos::tableRepos().getConst<AztecOO, CTrilinos_Universal_ID_t>(id);
}

/* store AztecOO in non-const table */
CT_AztecOO_ID_t
CAztecOO::storeAztecOO( AztecOO *pobj )
{
    return CTrilinos::tableRepos().store<AztecOO, CT_AztecOO_ID_t>(pobj, false);
}

/* store const AztecOO in const table */
CT_AztecOO_ID_t
CAztecOO::storeConstAztecOO( const AztecOO *pobj )
{
    return CTrilinos::tableRepos().store<AztecOO, CT_AztecOO_ID_t>(pobj, false);
}



#endif /* HAVE_CTRILINOS_AZTECOO */


