
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


#include "CTrilinos_utils.hpp"
#include "CTrilinos_utils_templ.hpp"


#include "CEpetra_Distributor_Cpp.hpp"
#include "CEpetra_SerialComm_Cpp.hpp"
#include "CEpetra_BLAS_Cpp.hpp"
#include "CEpetra_Comm_Cpp.hpp"
#include "CEpetra_Operator_Cpp.hpp"
#include "CEpetra_MultiVector_Cpp.hpp"
#include "CEpetra_OffsetIndex_Cpp.hpp"
#include "CEpetra_Object_Cpp.hpp"
#include "CEpetra_RowMatrix_Cpp.hpp"
#include "CEpetra_CompObject_Cpp.hpp"
#include "CEpetra_Directory_Cpp.hpp"
#include "CEpetra_Flops_Cpp.hpp"
#include "CEpetra_SrcDistObject_Cpp.hpp"
#include "CEpetra_MpiComm_Cpp.hpp"
#include "CEpetra_CrsMatrix_Cpp.hpp"
#include "CEpetra_CrsGraph_Cpp.hpp"
#include "CEpetra_DistObject_Cpp.hpp"
#include "CEpetra_Vector_Cpp.hpp"
#include "CEpetra_Export_Cpp.hpp"
#include "CEpetra_Map_Cpp.hpp"
#include "CEpetra_BlockMap_Cpp.hpp"
#include "CEpetra_Import_Cpp.hpp"
#include "CEpetra_Time_Cpp.hpp"
#include "CEpetra_JadMatrix_Cpp.hpp"
#include "CEpetra_LinearProblem_Cpp.hpp"
#include "CEpetra_LAPACK_Cpp.hpp"
#include "CTeuchos_CommandLineProcessor_Cpp.hpp"
#include "CTeuchos_ParameterList_Cpp.hpp"
#include "CTeuchos_ParameterEntry_Cpp.hpp"
#include "CTeuchos_any_Cpp.hpp"
#include "CAmesos_BaseSolver_Cpp.hpp"
#include "CAmesos_Cpp.hpp"
#include "CEpetra_FECrsMatrix_Cpp.hpp"
#include "CEpetra_IntSerialDenseVector_Cpp.hpp"
#include "CEpetra_SerialDenseMatrix_Cpp.hpp"
#include "CAztecOO_Cpp.hpp"
#include "CAztecOO_StatusTest_Cpp.hpp"
#include "CAztecOO_StatusTestCombo_Cpp.hpp"
#include "CAztecOO_StatusTestMaxIters_Cpp.hpp"
#include "CAztecOO_StatusTestResNorm_Cpp.hpp"
#include "CIfpack_Cpp.hpp"
#include "CIfpack_Preconditioner_Cpp.hpp"


namespace CTrilinos {


void pass_bool_out( const bool * pval, boolean * pvalout )
{
    pvalout = new boolean[1];
    *pvalout = (*pval ? TRUE : FALSE);
}


void pass_bool_in( const boolean * pval, bool * pvalout )
{
    pvalout = new bool[1];
    *pvalout = (*pval != FALSE ? true : false);
}


void pass_string_out( const std::string * const s, char *c[] )
{
    *c = new char[s->size()+1];
    strcpy(*c, s->c_str());
}


void pass_string_in( const char * const c[], std::string *s )
{
    s = new std::string(*c);
}


#ifdef HAVE_CTRILINOS_IFPACK
Ifpack::EPrecType convert_to_difficult_enum( CT_EPrecType_E_t en )
{
    switch (en) {
    case CT_EPrecType_E_POINT_RELAXATION:
        return Ifpack::POINT_RELAXATION;
    case CT_EPrecType_E_POINT_RELAXATION_STAND_ALONE:
        return Ifpack::POINT_RELAXATION_STAND_ALONE;
    case CT_EPrecType_E_BLOCK_RELAXATION:
        return Ifpack::BLOCK_RELAXATION;
    case CT_EPrecType_E_BLOCK_RELAXATION_STAND_ALONE:
        return Ifpack::BLOCK_RELAXATION_STAND_ALONE;
    case CT_EPrecType_E_BLOCK_RELAXATION_STAND_ALONE_ILU:
        return Ifpack::BLOCK_RELAXATION_STAND_ALONE_ILU;
#ifdef HAVE_CTRILINOS_AMESOS
    case CT_EPrecType_E_BLOCK_RELAXATION_STAND_ALONE_AMESOS:
        return Ifpack::BLOCK_RELAXATION_STAND_ALONE_AMESOS;
    case CT_EPrecType_E_BLOCK_RELAXATION_AMESOS:
        return Ifpack::BLOCK_RELAXATION_AMESOS;
    case CT_EPrecType_E_AMESOS:
        return Ifpack::AMESOS;
    case CT_EPrecType_E_AMESOS_STAND_ALONE:
        return Ifpack::AMESOS_STAND_ALONE;
#endif /* HAVE_CTRILINOS_AMESOS */
    case CT_EPrecType_E_IC:
        return Ifpack::IC;
    case CT_EPrecType_E_IC_STAND_ALONE:
        return Ifpack::IC_STAND_ALONE;
    case CT_EPrecType_E_ICT:
        return Ifpack::ICT;
    case CT_EPrecType_E_ICT_STAND_ALONE:
        return Ifpack::ICT_STAND_ALONE;
    case CT_EPrecType_E_ILU:
        return Ifpack::ILU;
    case CT_EPrecType_E_ILU_STAND_ALONE:
        return Ifpack::ILU_STAND_ALONE;
    case CT_EPrecType_E_ILUT:
        return Ifpack::ILUT;
    case CT_EPrecType_E_ILUT_STAND_ALONE:
        return Ifpack::ILUT_STAND_ALONE;
#ifdef HAVE_IFPACK_SPARSKIT
    case CT_EPrecType_E_SPARSKIT:
        return Ifpack::SPARSKIT;
#endif /* HAVE_IFPACK_SPARSKIT */
#ifdef HAVE_IFPACK_HIPS
    case CT_EPrecType_E_HIPS:
        return Ifpack::HIPS;
#endif /* HAVE_IFPACK_HIPS */
#ifdef HAVE_HYPRE
    case CT_EPrecType_E_HYPRE:
        return Ifpack::HYPRE;
#endif /* HAVE_HYPRE */
    case CT_EPrecType_E_CHEBYSHEV:
        return Ifpack::CHEBYSHEV;
    default:
        throw CTrilinosMiscException("Likely error in preprocessor macros for Ifpack::EPrecType conversion.\n");
        break;
    }
}
#endif /* HAVE_CTRILINOS_IFPACK */


#ifdef HAVE_CTRILINOS_IFPACK
CT_EPrecType_E_t convert_from_difficult_enum( Ifpack::EPrecType en )
{
    switch (en) {
    case Ifpack::POINT_RELAXATION:
        return CT_EPrecType_E_POINT_RELAXATION;
    case Ifpack::POINT_RELAXATION_STAND_ALONE:
        return CT_EPrecType_E_POINT_RELAXATION_STAND_ALONE;
    case Ifpack::BLOCK_RELAXATION:
        return CT_EPrecType_E_BLOCK_RELAXATION;
    case Ifpack::BLOCK_RELAXATION_STAND_ALONE:
        return CT_EPrecType_E_BLOCK_RELAXATION_STAND_ALONE;
    case Ifpack::BLOCK_RELAXATION_STAND_ALONE_ILU:
        return CT_EPrecType_E_BLOCK_RELAXATION_STAND_ALONE_ILU;
#ifdef HAVE_CTRILINOS_AMESOS
    case Ifpack::BLOCK_RELAXATION_STAND_ALONE_AMESOS:
        return CT_EPrecType_E_BLOCK_RELAXATION_STAND_ALONE_AMESOS;
    case Ifpack::BLOCK_RELAXATION_AMESOS:
        return CT_EPrecType_E_BLOCK_RELAXATION_AMESOS;
    case Ifpack::AMESOS:
        return CT_EPrecType_E_AMESOS;
    case Ifpack::AMESOS_STAND_ALONE:
        return CT_EPrecType_E_AMESOS_STAND_ALONE;
#endif /* HAVE_CTRILINOS_AMESOS */
    case Ifpack::IC:
        return CT_EPrecType_E_IC;
    case Ifpack::IC_STAND_ALONE:
        return CT_EPrecType_E_IC_STAND_ALONE;
    case Ifpack::ICT:
        return CT_EPrecType_E_ICT;
    case Ifpack::ICT_STAND_ALONE:
        return CT_EPrecType_E_ICT_STAND_ALONE;
    case Ifpack::ILU:
        return CT_EPrecType_E_ILU;
    case Ifpack::ILU_STAND_ALONE:
        return CT_EPrecType_E_ILU_STAND_ALONE;
    case Ifpack::ILUT:
        return CT_EPrecType_E_ILUT;
    case Ifpack::ILUT_STAND_ALONE:
        return CT_EPrecType_E_ILUT_STAND_ALONE;
#ifdef HAVE_IFPACK_SPARSKIT
    case Ifpack::SPARSKIT:
        return CT_EPrecType_E_SPARSKIT;
#endif /* HAVE_IFPACK_SPARSKIT */
#ifdef HAVE_IFPACK_HIPS
    case Ifpack::HIPS:
        return CT_EPrecType_E_HIPS;
#endif /* HAVE_IFPACK_HIPS */
#ifdef HAVE_HYPRE
    case Ifpack::HYPRE:
        return CT_EPrecType_E_HYPRE;
#endif /* HAVE_HYPRE */
    case Ifpack::CHEBYSHEV:
        return CT_EPrecType_E_CHEBYSHEV;
    default:
        throw CTrilinosMiscException("Likely error in preprocessor macros for Ifpack::EPrecType conversion.\n");
        break;
    }
}
#endif /* HAVE_CTRILINOS_IFPACK */


/* stringify the enum name */
std::string
enum2str( CTrilinos_Table_ID_t ty )
{
    std::string s;
    switch (ty) {
    case CT_Epetra_Distributor_ID:
        s.assign("CT_Epetra_Distributor_ID");
        break;
    case CT_Epetra_SerialComm_ID:
        s.assign("CT_Epetra_SerialComm_ID");
        break;
    case CT_Epetra_BLAS_ID:
        s.assign("CT_Epetra_BLAS_ID");
        break;
    case CT_Epetra_Comm_ID:
        s.assign("CT_Epetra_Comm_ID");
        break;
    case CT_Epetra_Operator_ID:
        s.assign("CT_Epetra_Operator_ID");
        break;
    case CT_Epetra_MultiVector_ID:
        s.assign("CT_Epetra_MultiVector_ID");
        break;
    case CT_Epetra_OffsetIndex_ID:
        s.assign("CT_Epetra_OffsetIndex_ID");
        break;
    case CT_Epetra_Object_ID:
        s.assign("CT_Epetra_Object_ID");
        break;
    case CT_Epetra_RowMatrix_ID:
        s.assign("CT_Epetra_RowMatrix_ID");
        break;
    case CT_Epetra_CompObject_ID:
        s.assign("CT_Epetra_CompObject_ID");
        break;
    case CT_Epetra_Directory_ID:
        s.assign("CT_Epetra_Directory_ID");
        break;
    case CT_Epetra_Flops_ID:
        s.assign("CT_Epetra_Flops_ID");
        break;
    case CT_Epetra_SrcDistObject_ID:
        s.assign("CT_Epetra_SrcDistObject_ID");
        break;
    case CT_Epetra_MpiComm_ID:
        s.assign("CT_Epetra_MpiComm_ID");
        break;
    case CT_Epetra_CrsMatrix_ID:
        s.assign("CT_Epetra_CrsMatrix_ID");
        break;
    case CT_Epetra_CrsGraph_ID:
        s.assign("CT_Epetra_CrsGraph_ID");
        break;
    case CT_Epetra_DistObject_ID:
        s.assign("CT_Epetra_DistObject_ID");
        break;
    case CT_Epetra_Vector_ID:
        s.assign("CT_Epetra_Vector_ID");
        break;
    case CT_Epetra_Export_ID:
        s.assign("CT_Epetra_Export_ID");
        break;
    case CT_Epetra_Map_ID:
        s.assign("CT_Epetra_Map_ID");
        break;
    case CT_Epetra_BlockMap_ID:
        s.assign("CT_Epetra_BlockMap_ID");
        break;
    case CT_Epetra_Import_ID:
        s.assign("CT_Epetra_Import_ID");
        break;
    case CT_Epetra_Time_ID:
        s.assign("CT_Epetra_Time_ID");
        break;
    case CT_Epetra_JadMatrix_ID:
        s.assign("CT_Epetra_JadMatrix_ID");
        break;
    case CT_Epetra_LinearProblem_ID:
        s.assign("CT_Epetra_LinearProblem_ID");
        break;
    case CT_Epetra_LAPACK_ID:
        s.assign("CT_Epetra_LAPACK_ID");
        break;
    case CT_Teuchos_CommandLineProcessor_ID:
        s.assign("CT_Teuchos_CommandLineProcessor_ID");
        break;
    case CT_Teuchos_ParameterList_ID:
        s.assign("CT_Teuchos_ParameterList_ID");
        break;
    case CT_Teuchos_ParameterEntry_ID:
        s.assign("CT_Teuchos_ParameterEntry_ID");
        break;
    case CT_Teuchos_any_ID:
        s.assign("CT_Teuchos_any_ID");
        break;
    case CT_Amesos_BaseSolver_ID:
        s.assign("CT_Amesos_BaseSolver_ID");
        break;
    case CT_Amesos_ID:
        s.assign("CT_Amesos_ID");
        break;
    case CT_Epetra_FECrsMatrix_ID:
        s.assign("CT_Epetra_FECrsMatrix_ID");
        break;
    case CT_Epetra_IntSerialDenseVector_ID:
        s.assign("CT_Epetra_IntSerialDenseVector_ID");
        break;
    case CT_Epetra_SerialDenseMatrix_ID:
        s.assign("CT_Epetra_SerialDenseMatrix_ID");
        break;
    case CT_AztecOO_ID:
        s.assign("CT_AztecOO_ID");
        break;
    case CT_AztecOO_StatusTest_ID:
        s.assign("CT_AztecOO_StatusTest_ID");
        break;
    case CT_AztecOO_StatusTestCombo_ID:
        s.assign("CT_AztecOO_StatusTestCombo_ID");
        break;
    case CT_AztecOO_StatusTestMaxIters_ID:
        s.assign("CT_AztecOO_StatusTestMaxIters_ID");
        break;
    case CT_AztecOO_StatusTestResNorm_ID:
        s.assign("CT_AztecOO_StatusTestResNorm_ID");
        break;
    case CT_Ifpack_ID:
        s.assign("CT_Ifpack_ID");
        break;
    case CT_Ifpack_Preconditioner_ID:
        s.assign("CT_Ifpack_Preconditioner_ID");
        break;
    default:
        s.assign("(unrecognized)");
        break;
    }

    return s;
}


/* isSameObject(generic_id, generic_id) */
bool
isSameObject( CTrilinos_Universal_ID_t id1, CTrilinos_Universal_ID_t id2 )
{
    bool shares = false;

    if (id1.is_const) {
        switch (id1.table) {
        case CT_Epetra_Distributor_ID:
            shares = isSameObject(CEpetra::getConstDistributor(id1), id2);
            break;
        case CT_Epetra_SerialComm_ID:
            shares = isSameObject(CEpetra::getConstSerialComm(id1), id2);
            break;
        case CT_Epetra_BLAS_ID:
            shares = isSameObject(CEpetra::getConstBLAS(id1), id2);
            break;
        case CT_Epetra_Comm_ID:
            shares = isSameObject(CEpetra::getConstComm(id1), id2);
            break;
        case CT_Epetra_Operator_ID:
            shares = isSameObject(CEpetra::getConstOperator(id1), id2);
            break;
        case CT_Epetra_MultiVector_ID:
            shares = isSameObject(CEpetra::getConstMultiVector(id1), id2);
            break;
        case CT_Epetra_OffsetIndex_ID:
            shares = isSameObject(CEpetra::getConstOffsetIndex(id1), id2);
            break;
        case CT_Epetra_Object_ID:
            shares = isSameObject(CEpetra::getConstObject(id1), id2);
            break;
        case CT_Epetra_RowMatrix_ID:
            shares = isSameObject(CEpetra::getConstRowMatrix(id1), id2);
            break;
        case CT_Epetra_CompObject_ID:
            shares = isSameObject(CEpetra::getConstCompObject(id1), id2);
            break;
        case CT_Epetra_Directory_ID:
            shares = isSameObject(CEpetra::getConstDirectory(id1), id2);
            break;
        case CT_Epetra_Flops_ID:
            shares = isSameObject(CEpetra::getConstFlops(id1), id2);
            break;
        case CT_Epetra_SrcDistObject_ID:
            shares = isSameObject(CEpetra::getConstSrcDistObject(id1), id2);
            break;
#ifdef HAVE_MPI
        case CT_Epetra_MpiComm_ID:
            shares = isSameObject(CEpetra::getConstMpiComm(id1), id2);
            break;
#endif /* HAVE_MPI */
        case CT_Epetra_CrsMatrix_ID:
            shares = isSameObject(CEpetra::getConstCrsMatrix(id1), id2);
            break;
        case CT_Epetra_CrsGraph_ID:
            shares = isSameObject(CEpetra::getConstCrsGraph(id1), id2);
            break;
        case CT_Epetra_DistObject_ID:
            shares = isSameObject(CEpetra::getConstDistObject(id1), id2);
            break;
        case CT_Epetra_Vector_ID:
            shares = isSameObject(CEpetra::getConstVector(id1), id2);
            break;
        case CT_Epetra_Export_ID:
            shares = isSameObject(CEpetra::getConstExport(id1), id2);
            break;
        case CT_Epetra_Map_ID:
            shares = isSameObject(CEpetra::getConstMap(id1), id2);
            break;
        case CT_Epetra_BlockMap_ID:
            shares = isSameObject(CEpetra::getConstBlockMap(id1), id2);
            break;
        case CT_Epetra_Import_ID:
            shares = isSameObject(CEpetra::getConstImport(id1), id2);
            break;
        case CT_Epetra_Time_ID:
            shares = isSameObject(CEpetra::getConstTime(id1), id2);
            break;
        case CT_Epetra_JadMatrix_ID:
            shares = isSameObject(CEpetra::getConstJadMatrix(id1), id2);
            break;
        case CT_Epetra_LinearProblem_ID:
            shares = isSameObject(CEpetra::getConstLinearProblem(id1), id2);
            break;
        case CT_Epetra_LAPACK_ID:
            shares = isSameObject(CEpetra::getConstLAPACK(id1), id2);
            break;
        case CT_Teuchos_CommandLineProcessor_ID:
            shares = isSameObject(CTeuchos::getConstCommandLineProcessor(id1), id2);
            break;
        case CT_Teuchos_ParameterList_ID:
            shares = isSameObject(CTeuchos::getConstParameterList(id1), id2);
            break;
        case CT_Teuchos_ParameterEntry_ID:
            shares = isSameObject(CTeuchos::getConstParameterEntry(id1), id2);
            break;
        case CT_Teuchos_any_ID:
            shares = isSameObject(CTeuchos::getConstany(id1), id2);
            break;
#ifdef HAVE_CTRILINOS_AMESOS
        case CT_Amesos_BaseSolver_ID:
            shares = isSameObject(CAmesos::getConstBaseSolver(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AMESOS */
#ifdef HAVE_CTRILINOS_AMESOS
        case CT_Amesos_ID:
            shares = isSameObject(CAmesos::getConstAmesos(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AMESOS */
        case CT_Epetra_FECrsMatrix_ID:
            shares = isSameObject(CEpetra::getConstFECrsMatrix(id1), id2);
            break;
        case CT_Epetra_IntSerialDenseVector_ID:
            shares = isSameObject(CEpetra::getConstIntSerialDenseVector(id1), id2);
            break;
        case CT_Epetra_SerialDenseMatrix_ID:
            shares = isSameObject(CEpetra::getConstSerialDenseMatrix(id1), id2);
            break;
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_ID:
            shares = isSameObject(CAztecOO::getConstAztecOO(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTest_ID:
            shares = isSameObject(CAztecOO::getConstStatusTest(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTestCombo_ID:
            shares = isSameObject(CAztecOO::getConstStatusTestCombo(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTestMaxIters_ID:
            shares = isSameObject(CAztecOO::getConstStatusTestMaxIters(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTestResNorm_ID:
            shares = isSameObject(CAztecOO::getConstStatusTestResNorm(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_IFPACK
        case CT_Ifpack_ID:
            shares = isSameObject(CIfpack::getConstIfpack(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_IFPACK */
#ifdef HAVE_CTRILINOS_IFPACK
        case CT_Ifpack_Preconditioner_ID:
            shares = isSameObject(CIfpack::getConstPreconditioner(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_IFPACK */
        default:
            break;
        }
    } else {
        switch (id1.table) {
        case CT_Epetra_Distributor_ID:
            shares = isSameObject(CEpetra::getDistributor(id1), id2);
            break;
        case CT_Epetra_SerialComm_ID:
            shares = isSameObject(CEpetra::getSerialComm(id1), id2);
            break;
        case CT_Epetra_BLAS_ID:
            shares = isSameObject(CEpetra::getBLAS(id1), id2);
            break;
        case CT_Epetra_Comm_ID:
            shares = isSameObject(CEpetra::getComm(id1), id2);
            break;
        case CT_Epetra_Operator_ID:
            shares = isSameObject(CEpetra::getOperator(id1), id2);
            break;
        case CT_Epetra_MultiVector_ID:
            shares = isSameObject(CEpetra::getMultiVector(id1), id2);
            break;
        case CT_Epetra_OffsetIndex_ID:
            shares = isSameObject(CEpetra::getOffsetIndex(id1), id2);
            break;
        case CT_Epetra_Object_ID:
            shares = isSameObject(CEpetra::getObject(id1), id2);
            break;
        case CT_Epetra_RowMatrix_ID:
            shares = isSameObject(CEpetra::getRowMatrix(id1), id2);
            break;
        case CT_Epetra_CompObject_ID:
            shares = isSameObject(CEpetra::getCompObject(id1), id2);
            break;
        case CT_Epetra_Directory_ID:
            shares = isSameObject(CEpetra::getDirectory(id1), id2);
            break;
        case CT_Epetra_Flops_ID:
            shares = isSameObject(CEpetra::getFlops(id1), id2);
            break;
        case CT_Epetra_SrcDistObject_ID:
            shares = isSameObject(CEpetra::getSrcDistObject(id1), id2);
            break;
#ifdef HAVE_MPI
        case CT_Epetra_MpiComm_ID:
            shares = isSameObject(CEpetra::getMpiComm(id1), id2);
            break;
#endif /* HAVE_MPI */
        case CT_Epetra_CrsMatrix_ID:
            shares = isSameObject(CEpetra::getCrsMatrix(id1), id2);
            break;
        case CT_Epetra_CrsGraph_ID:
            shares = isSameObject(CEpetra::getCrsGraph(id1), id2);
            break;
        case CT_Epetra_DistObject_ID:
            shares = isSameObject(CEpetra::getDistObject(id1), id2);
            break;
        case CT_Epetra_Vector_ID:
            shares = isSameObject(CEpetra::getVector(id1), id2);
            break;
        case CT_Epetra_Export_ID:
            shares = isSameObject(CEpetra::getExport(id1), id2);
            break;
        case CT_Epetra_Map_ID:
            shares = isSameObject(CEpetra::getMap(id1), id2);
            break;
        case CT_Epetra_BlockMap_ID:
            shares = isSameObject(CEpetra::getBlockMap(id1), id2);
            break;
        case CT_Epetra_Import_ID:
            shares = isSameObject(CEpetra::getImport(id1), id2);
            break;
        case CT_Epetra_Time_ID:
            shares = isSameObject(CEpetra::getTime(id1), id2);
            break;
        case CT_Epetra_JadMatrix_ID:
            shares = isSameObject(CEpetra::getJadMatrix(id1), id2);
            break;
        case CT_Epetra_LinearProblem_ID:
            shares = isSameObject(CEpetra::getLinearProblem(id1), id2);
            break;
        case CT_Epetra_LAPACK_ID:
            shares = isSameObject(CEpetra::getLAPACK(id1), id2);
            break;
        case CT_Teuchos_CommandLineProcessor_ID:
            shares = isSameObject(CTeuchos::getCommandLineProcessor(id1), id2);
            break;
        case CT_Teuchos_ParameterList_ID:
            shares = isSameObject(CTeuchos::getParameterList(id1), id2);
            break;
        case CT_Teuchos_ParameterEntry_ID:
            shares = isSameObject(CTeuchos::getParameterEntry(id1), id2);
            break;
        case CT_Teuchos_any_ID:
            shares = isSameObject(CTeuchos::getany(id1), id2);
            break;
#ifdef HAVE_CTRILINOS_AMESOS
        case CT_Amesos_BaseSolver_ID:
            shares = isSameObject(CAmesos::getBaseSolver(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AMESOS */
#ifdef HAVE_CTRILINOS_AMESOS
        case CT_Amesos_ID:
            shares = isSameObject(CAmesos::getAmesos(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AMESOS */
        case CT_Epetra_FECrsMatrix_ID:
            shares = isSameObject(CEpetra::getFECrsMatrix(id1), id2);
            break;
        case CT_Epetra_IntSerialDenseVector_ID:
            shares = isSameObject(CEpetra::getIntSerialDenseVector(id1), id2);
            break;
        case CT_Epetra_SerialDenseMatrix_ID:
            shares = isSameObject(CEpetra::getSerialDenseMatrix(id1), id2);
            break;
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_ID:
            shares = isSameObject(CAztecOO::getAztecOO(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTest_ID:
            shares = isSameObject(CAztecOO::getStatusTest(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTestCombo_ID:
            shares = isSameObject(CAztecOO::getStatusTestCombo(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTestMaxIters_ID:
            shares = isSameObject(CAztecOO::getStatusTestMaxIters(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_AZTECOO
        case CT_AztecOO_StatusTestResNorm_ID:
            shares = isSameObject(CAztecOO::getStatusTestResNorm(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_AZTECOO */
#ifdef HAVE_CTRILINOS_IFPACK
        case CT_Ifpack_ID:
            shares = isSameObject(CIfpack::getIfpack(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_IFPACK */
#ifdef HAVE_CTRILINOS_IFPACK
        case CT_Ifpack_Preconditioner_ID:
            shares = isSameObject(CIfpack::getPreconditioner(id1), id2);
            break;
#endif /* HAVE_CTRILINOS_IFPACK */
        default:
            break;
        }
    }

    return shares;
}


} // namespace CTrilinos

