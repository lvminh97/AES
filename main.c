//-----------------------------------------------------------------------------------------------
//----------------------------------------main.c-------------------------------------------------
//-------------------------------Author: Minh Luong Van------------------------------------------
//-------------------------------Created on: Oct 10, 2017----------------------------------------
//-----------------------------------------------------------------------------------------------

#include<stdio.h>
#include "AES.h"

void printRes(byte* a, int len){		// Print the result on the screen
	printf("0x");
	int i;
	for(i=0;i<len;i++){
		printf("%02X",a[i]);
	}
	printf("\n");
}

void mat2Arr(matrix a, byte* b, char dir){		// Convert a matrix into a 1D-array
	if(dir=='C') mat2Arr(transposedMat(a),b,'R');
	else{
		int i,j;
		for(i=0;i<a.m;i++){
			for(j=0;j<a.n;j++){
				b[i*a.m+j]=a.data[i][j];
			}
		}
	}
}

matrix encrypt(byte* inp, byte* key, int keyLen){
	// Encrypt a plaintext into a ciphertext
	// inp: plaintext
	// key: cipherkey
	// keyLen: the length of the key (128, 192 or 256 bit)
	matrix RKey[15];
	int Nr=(keyLen==128) ? 10 : ((keyLen==192) ? 12 : 14);
	matrix res=arr2Mat(inp,0,15,'C');
	keyExpansion(key,keyLen,RKey);
	int i;
	for(i=0;i<=Nr;i++){
		res=round(i,res,RKey[i],keyLen,'E');
	}
	return res;
}

matrix decrypt(byte* inp, byte* key, int keyLen){
	// Decrypt a ciphertext to get a plaintext
	// inp: ciphertext
	// key: cipherkey
	// keyLen: the length of the key (128, 192 or 256 bit)
	matrix RKey[15];
	int Nr=(keyLen==128) ? 10 : ((keyLen==192) ? 12 : 14);
	matrix res=arr2Mat(inp,0,15,'C');
	keyExpansion(key,keyLen,RKey);
	int i;
	for(i=0;i<=Nr;i++){
		res=round(i,res,RKey[Nr-i],keyLen,'D');
	}
	return res;
}

int main(){
	byte data_p[16]={0x45,0x58,0x41,0x4d,0x43,0x52,0x59,0x50,0x54,0x4f,0x47,0x52,0x41,0x50,0x48,0x59};
	//byte data_p[16]={0x9d,0x31,0xa0,0xee,0x3e,0x72,0xc8,0x09,0x9d,0x31,0xa0,0xee,0x3e,0x72,0xc8,0x09};
	//byte data_p[16]={0x00,0x04,0x12,0x14,0x12,0x04,0x12,0x00,0x0c,0x00,0x13,0x11,0x08,0x23,0x19,0x19};
	//byte data_p[16]={0x54,0x77,0x6f,0x20,0x4f,0x6e,0x65,0x20,0x4e,0x69,0x6e,0x65,0x20,0x54,0x77,0x6f};
	//
	//byte key[16]={0x24,0x75,0xa2,0xb3,0x34,0x75,0x56,0x88,0x31,0xe2,0x12,0x00,0x13,0xaa,0x54,0x87};
	//byte key[16]={0x54,0x68,0x61,0x74,0x73,0x20,0x6d,0x79,0x20,0x4b,0x75,0x6e,0x67,0x20,0x46,0x75};
	byte key[32]={0x24,0x75,0xa2,0xb3,0x34,0x75,0x56,0x88,0x31,0xe2,0x12,0x00,0x13,0xaa,0x54,0x87,0x47,0x2a,0x36,0xee,0xc9,0x01,0x33,0x21,0x02,0x03,0xbb,0xd2,0xca,0x21,0xb7,0x28};
	//byte key[24]={0x01,0x24,0x3a,0x91,0xee,0x26,0x13,0xa0,0xb2,0x64,0x5d,0x42,0x36,0x81,0x02,0x3c,0x72,0xf7,0x85,0x14,0xea,0x41,0x5b,0x26};
	// INPUT
	printf("INPUT:\n");
	printf("Plaintext: "); printRes(data_p,16);
	printf("Key      : "); printRes(key,sizeof(key));
	printf("\n\n");
	// ENCRYPTION
	printf("ENCRYPTION:\n");
	matrix c=encrypt(data_p,key,8*sizeof(key));
	byte data_c[16],data_r[16];
	mat2Arr(c,data_c,'C');
	printf("Ciphertext: "); printRes(data_c,16);
	printf("\n\n");
	// DECRYPTION
	printf("DECRYPTION:\n");
	matrix r=decrypt(data_c,key,8*sizeof(key));
	mat2Arr(r,data_r,'C');
	printf("Plaintext (recover) : "); printRes(data_r,16);
	return 0;
}

