
TRIBITS_ADD_EXECUTABLE_AND_TEST(
  RowMatrix_test 
  SOURCES CEpetra_RowMatrix_AppTest.cpp
  ARGS -v
  COMM mpi serial
  NUM_MPI_PROCS 1
#  FAIL_REGULAR_EXPRESSION "tests FAILED"
  FAIL_REGULAR_EXPRESSION "check failed"
  )
