#include <stdlib.h>
#include <stdio.h>
int main()
{
    FILE *streamIn;
    streamIn = fopen("lena512.bmp", "rb");
    unsigned char header[263222];
    int count = 0;
    printf(" address before seek = %u\n",streamIn);
 	for(int i=0;i<54;i++)
 	{
 		header[i] = getc(streamIn);  // strip out BMP header
 		//printf("%d",header[i]);

 	}
 	int File_size_in_Kbs= *(int*)&header[2];
 	printf(" address after header seek = %u\n",*streamIn);
 	int File_size =*(int*)&header[4];
 	int offset = *(int*)&header[10];
 	int Size = *(int*)&header[14];
    int width = *(int*)&header[18]; // read the width from the image header
 	int height = *(int*)&header[22]; // read the height from the image header
	int bitDepth = *(int*)&header[28]; // read the bitDepth from the image header
	int compression = *(int*)&header[30];
	printf("the first 2 character  %c %c\n",header[0], header[1]);
	printf("File_size_in_Kbs %d\n",File_size_in_Kbs);
	printf("File_size %d\n",File_size);
	printf("offset: %d\n",offset);
	printf("Size: %d\n",Size);
	printf("width: %d\n",width);
	printf("height: %d\n",height );
	printf("bitDepth bits per pixel: %d\n",bitDepth );
	printf("compression: %d\n",compression );
	printf("%u",offset);


unsigned char buf[height * width]; // to store the image data

unsigned char colorTable[1024];

if(offset != 54)
{

    // colore table is present
    printf("color is present\n");
    fseek( streamIn, 54, SEEK_SET);
        printf("address after 54 bytes= %u \n",*streamIn);
		fread(colorTable, sizeof(unsigned char), 1024, streamIn);
		//printf(" bitDepth=%d ",bitDepth);
}




printf("address= %u \n",streamIn);


fread(buf, sizeof(unsigned char), (height * width), streamIn);




FILE *fo = fopen("file.bmp","wb"); // Output File name
fwrite(header, sizeof(unsigned char), 54, fo); // write the image header to output file
if(offset != 54){
    printf("address= %u \n",fo);
    int j=fseek( fo, 54, SEEK_SET );
    printf("j=%d\n",j);
    printf("address= %u \n",fo);
    fwrite(colorTable, sizeof(unsigned char), 1024, fo);
}

printf("address= %u \n",fo);
fwrite(buf, sizeof(unsigned char), (height * width), fo);// data write



fclose(fo);
fclose(streamIn);



}
