#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main()
{

    FILE *streamIn;// making a file pointer
    streamIn = fopen("lena512.bmp", "rb");// pointing the image file using file pointer

    unsigned char imageHeader[54]; // to get the image header
    fread(imageHeader, sizeof(unsigned char), 54, streamIn);// reading the image header using fread function
    /*
    Following is the declaration for fread() function.
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
    ptr − This is the pointer to a block of memory with a minimum size of size*nmemb bytes.
    size − This is the size in bytes of each element to be read.
    nmemb − This is the number of elements, each one with a size of size bytes.
    stream − This is the pointer to a FILE object that specifies an input stream.
    */






    // extract image height and width from imageHeader
    int width = *(int*)&imageHeader[18];
    int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];
	int offset = *(int*)&imageHeader[10];

    // colorTable related operations
    unsigned char colorTable[1024];

    if(offset != 54)
    {
    // colore table is present
    printf("color is present\n");
    fseek( streamIn, 54, SEEK_SET);
		fread(colorTable, sizeof(unsigned char), 1024, streamIn);// reading color table and storing it in colortable array
    }






   	// image data reading operations
	int imgDataSize = width * height; // calculate image size

    unsigned char imageData[imgDataSize], newimageData[imgDataSize];// array to store the data of image
    fread( imageData, sizeof(unsigned char), imgDataSize, streamIn);// putting the data into imageData array





    for(int i=0;i<=imgDataSize;i++)
    newimageData[i] = 255 - imageData[i];// reversing the data of image




    FILE *fo = fopen("lena_negative.bmp", "wb");// making a new image file and opening it in write mode

    fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back.
    /*
    The C library function size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
    writes data from the array pointed to, by ptr to the given stream.
    ptr − This is the pointer to the array of elements to be written.
    size − This is the size in bytes of each element to be written.
    nmemb − This is the number of elements, each one with a size of size bytes.
    stream − This is the pointer to a FILE object that specifies an output stream.
    */
    fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back
    fwrite( newimageData, sizeof(unsigned char), imgDataSize, fo); // write the values of the negative image.

fclose(fo);
fclose(streamIn);
int time= clock();
printf("time in second %f",(float)time/CLOCKS_PER_SEC);


}
