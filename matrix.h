//-----------------------------------------------------------------------------------------------
//-------------------------------Implement matrix algorithm--------------------------------------
//-------------------------------Author: Minh Luong Van------------------------------------------
//-------------------------------Created on: Oct 10, 2017----------------------------------------
//-----------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------
//-----------------------------------Data types--------------------------------------------------
//-----------------------------------------------------------------------------------------------
typedef unsigned char byte;			// 1 Byte

typedef struct matrix {				// Matrix
	int m,n;
	byte data[4][4];
} matrix;
matrix init(int m, int n) {			// Initialize matrix with m rows, n columns
	matrix a;
	a.m=m;
	a.n=n;
	return a;
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------Prototypes--------------------------------------------------
//-----------------------------------------------------------------------------------------------

byte multi(byte a, byte b);							// Implement multiplication in GF(2^8)

matrix rowMat(matrix mat, int r);					// Export a row from a matrix
matrix colMat(matrix mat, int c);					// Export a column from a matrix

matrix addCol(matrix mat, matrix col);				// Insert a column into matrix

matrix arr2Mat(byte *inp, int id1, int id2, char dir);		// Create a matrix from an 1D array

matrix transposedMat(matrix mat);					// Create transposed matrix
matrix addMat(matrix mat1, matrix mat2);			// Implement XOR 2 matrix
matrix multiMat(matrix mat1, matrix mat2);			// Implement multiplication 2 matrix in GF(2^8)

//-----------------------------------------------------------------------------------------------
//----------------------------Function definitions-----------------------------------------------
//-----------------------------------------------------------------------------------------------

byte multi(byte a, byte b) {						// Implement multiplication in GF(2^8)
	byte res=0;
	while(a&&b) {
		if(b&1)
			res^=a;
		if(a&0x80)
			a=(a<<1)^0x011b;
		else a<<=1;
		b>>=1;
	}
	return res;
}

matrix rowMat(matrix mat, int r) {					// Export a row from a matrix
	matrix res=init(1,mat.n);
	int i;
	for(i=0; i<mat.n; i++)
		res.data[0][i]=mat.data[r][i];
	return res;
}
matrix colMat(matrix mat, int c) {					// Export a column from a matrix
	matrix res=init(mat.m,1);
	int i;
	for(i=0; i<mat.m; i++)
		res.data[i][0]=mat.data[i][c];
	return res;
}

matrix addCol(matrix mat, matrix col){				// Insert a column into matrix
	mat.n++;
	int i;
	for(i=0;i<mat.m;i++)
		mat.data[i][mat.n-1]=col.data[i][0];
	return mat;
}

matrix arr2Mat(byte* inp,int id1, int id2, char dir) {	// Create a matrix from a 1D-array
	matrix res=init(4,(id2-id1+1)/4);
	int i,j;
	if(dir=='C'){
		for(j=0; j<res.n; j++) {
			for(i=0; i<res.m; i++) {
				res.data[i][j]=inp[id1+j*res.n+i];
			}
		}
	}
	else{
		for(i=0; i<res.m; i++){
			for(j=0; j<res.n; j++){
				res.data[i][j]=inp[id1+i*res.m+j];
			}
		}
	}
	return res;
}

matrix transposedMat(matrix mat) {					// Create transposed matrix
	matrix res = init(mat.n,mat.m);
	int i,j;
	for(j=0; j<mat.n; j++)
		for(i=0; i<mat.m; i++)
			res.data[j][i]=mat.data[i][j];
	return res;
}
matrix addMat(matrix mat1, matrix mat2) {			// Implement XOR 2 matrix
	matrix res=init(mat1.m,mat1.n);
	int i,j;
	for(i=0; i<res.m; i++) {
		for(j=0; j<res.n; j++) {
			res.data[i][j]=mat1.data[i][j]^mat2.data[i][j];
		}
	}
	return res;
}
matrix multiMat(matrix mat1, matrix mat2) {		// Implement multiplication 2 matrix in GF(2^8)
	matrix res = init(mat1.m,mat2.n);
	int i,j,k;
	for(i=0; i<mat1.m; i++) {
		for(j=0; j<mat2.n; j++) {
			res.data[i][j]=0;
			for(k=0; k<mat1.n; k++)
				res.data[i][j]^=multi(mat1.data[i][k],mat2.data[k][j]);
		}
	}
	return res;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void printMat(matrix mat){
	int i,j;
	for(i=0;i<mat.m;i++){
		for(j=0;j<mat.n;j++)
			printf("%02X  ",mat.data[i][j]);
		printf("\n");
	}
}
