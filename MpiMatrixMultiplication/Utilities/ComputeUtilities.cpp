#include "ComputeUtilities.h"



MatrixClass* MatricesProduct(MatrixClass A, MatrixClass B, int commSize, int commRank)
{
	if (A.GetDemensionJ() != B.GetDemensionI()) return new MatrixClass;
	
	//auto indexes = GetVectorById(commRank, )
	auto result = MultiplyMatrix(A, B, 1, 0);
	//for (int i = 0; i < A.GetDemensionI(); i++)
	//	for (int k = 0; k < A.GetDemensionJ(); k++)
	//		for (int j = 0; j < B.GetDemensionJ(); j++)
	//			C->Set(i, j, A.Get(i, k) + B.Get(k, j));
	///*for (i = 0; i < SIZE; i++) {
	//	for (j = 0; j < SIZE; j++) {
	//		for (k = 0; k < SIZE; k++)
	//			c[i][j] = c[i][j] + a[i][k] * b[j][k];
	//	}
	//}*/
	return result;
}

MatrixClass* MultiplyMatrix(MatrixClass A, MatrixClass B, const int commSize = 1, const int commRank = 0)
{
	auto transposedB = MatrixClass::Transpose(B);
	auto C = new MatrixClass(A.GetDemensionJ(), B.GetDemensionI(), {});
	for (int i = commRank; i < A.GetDemensionI(); i+=commSize)
		for (int j = 0; j < transposedB.GetDemensionJ(); j++)
			for (int k = 0; k < A.GetDemensionJ(); k++)
				C->Set(i, j, C->Get(i,j) + A.Get(i, k) + B.Get(j, k));
	return C;
}
